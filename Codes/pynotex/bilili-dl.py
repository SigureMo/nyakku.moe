import os
import re
import argparse
import json
import threading
import queue
import time

from utils.config import Config
from utils.crawler import Crawler
from utils.filer import touch_dir
from utils.thread import ThreadPool
from utils.async_lib.utils import Task
from utils.video_editor import FFmpeg

"""
快速根据 url 下载 b 站系列视频，比如 'https://www.bilibili.com/video/av6538245'
另外也支持下番 比如 'https://www.bilibili.com/bangumi/media/md2543/'
ref : https://github.com/1033020837/Bilibili
"""

CONFIG = Config('bilili-dl').conf
GLOBAL = Config('bilili-dl').glob
spider = Crawler()
ffmpeg = FFmpeg()
video_queue = queue.Queue()
sps = [80, 64, 32, 16] # 高清 1080P  高清 720P  清晰 480P  流畅 360P
headers = {
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/64.0.3282.167 Safari/537.36',
    'Referer': 'https://www.bilibili.com',
}
spider.headers.update(headers)
touch_dir(CONFIG['tmp_dir'])
touch_dir(CONFIG['data_dir'])

# avid-dl
def bilili_dl_by_avid(avid):
    GLOBAL['info'] = []
    for cid, name in get_info(avid):
        GLOBAL['info'].append(get_part_info(cid, name))
    pool = ThreadPool(10)
    merge_thread = threading.Thread(target=merge_flv)
    merge_thread.setDaemon(True)
    for part_info in GLOBAL['info']:
        for segment_info in part_info:
            num, total, name, segment_url, status, sp = segment_info
            file_path = os.path.join(CONFIG['data_dir'], GLOBAL['title'], '{}_{:02d}.flv'.format(name, num))
            pool.add_task(Task(download_segment, (segment_url, file_path, segment_info)))
    merge_thread.start()
    pool.run()
    pool.join()

def get_info(avid):
    res = spider.get(GLOBAL['args'].url)
    title = re.search(r'<title .*>(.*)_哔哩哔哩 \(゜-゜\)つロ 干杯~-bilibili</title>', res.text).group(1)
    print(title)
    touch_dir(os.path.join(CONFIG['data_dir'], title))
    GLOBAL['title'] = title
    info = json.loads(re.search(r'\"pages\":(\[\{.+?\}\}\]),', res.text).group(1))
    # print(info)
    for item in info:
        yield item['cid'], item['part']

def get_part_info(cid, name):
    video_api = 'https://api.bilibili.com/x/player/playurl?avid={avid}&cid={cid}&qn={sp}&type=&otype=json'
    accept_quality = spider.get(video_api.format(avid=GLOBAL['avid'], cid=cid, sp=80)).json()['data']['accept_quality']
    for sp in GLOBAL['sp_seq']:
        if sp in accept_quality:
            break
    video_api_url = video_api.format(avid=GLOBAL['avid'], cid=cid, sp=sp)
    res = spider.get(video_api_url)
    part_info = []
    for num, segment in enumerate(res.json()['data']['durl']):
        segment_url = segment['url']
        part_info.append([
            num,
            len(res.json()['data']['durl']),
            name,
            segment_url,
            'NOT_DL',
            sp,
        ])
    return part_info

def download_segment(segment_url, file_path, segment_info):
    num, total, name, segment_url, status, sp = segment_info
    print('{} sp:{} {} of {}'.format(name, sp, num, total))
    spider.download_bin(segment_url, file_path)
    segment_info[4] = file_path

    for part_info in GLOBAL['info']:
        if all([segment_info[4] not in ['NOT_DL', 'MERGE'] for segment_info in part_info]):
            video_queue.put((
                [status for num, total, name, segment_url, status, sp in part_info],
                os.path.join(CONFIG['data_dir'], GLOBAL['title'], '{}.mp4'.format(segment_info[2]))
            ))
            for segment_info in part_info:
                segment_info[4] = 'MERGE'

def merge_flv():
    while True:
        if not video_queue.empty():
            video_path_list, output_path = video_queue.get()
            ffmpeg.join_videos(video_path_list, output_path)
            time.sleep(5)
            for video_path in video_path_list:
                os.remove(video_path)
        time.sleep(1)


# bangumi-dl
def bilili_dl_bangumi(season_id):
    res = spider.get(GLOBAL['args'].url)
    with open('tmp/ttt.html', 'w', encoding='utf8') as f:
        f.write(res.text)
    title = re.search(r'<span class="media-info-title-t">(\w+)</span>', res.text).group(1)
    GLOBAL['title'] = title
    print(title)
    touch_dir(os.path.join(CONFIG['data_dir'], title))
    GLOBAL['info'] = []
    ep_list_api = 'https://bangumi.bilibili.com/web_api/get_ep_list?season_id={}'
    ep_list = spider.get(ep_list_api.format(season_id)).json()['result']
    for ep_info in ep_list:
        GLOBAL['info'].append(get_video_info(ep_info))
    pool = ThreadPool(10)
    merge_thread = threading.Thread(target=merge_flv)
    merge_thread.setDaemon(True)
    for part_info in GLOBAL['info']:
        for segment_info in part_info:
            num, total, name, segment_url, status, sp = segment_info
            file_path = os.path.join(CONFIG['data_dir'], GLOBAL['title'], '{}_{:02d}.flv'.format(name, num))
            pool.add_task(Task(download_segment, (segment_url, file_path, segment_info)))
    merge_thread.start()
    pool.run()
    pool.join()

def get_video_info(ep_info):
    video_api = 'https://api.bilibili.com/pgc/player/web/playurl?avid={avid}&cid={cid}&qn={sp}&ep_id={ep_id}'
    accept_quality = spider.get(video_api.format(avid=ep_info['avid'], cid=ep_info['cid'], ep_id=ep_info['episode_id'], sp=80)).json()['result']['accept_quality']
    for sp in GLOBAL['sp_seq']:
        if sp in accept_quality:
            break
    video_api_url = video_api.format(avid=ep_info['avid'], cid=ep_info['cid'], ep_id=ep_info['episode_id'], sp=sp)
    res = spider.get(video_api_url)
    video_info = []
    for num, segment_info in enumerate(res.json()['result']['durl']):
        segment_url = segment_info['url']
        video_info.append([
            num,
            len(res.json()['result']['durl']),
            ep_info['index'],
            segment_url,
            'NOT_DL',
            sp,
        ])
    return video_info


# launcher
def bilili_dl(url):
    if re.match(r'https?://www.bilibili.com/video/av(\d+)', url):
        avid = re.match(r'https?://www.bilibili.com/video/av(\d+)', url).group(1)
        GLOBAL['avid'] = avid
        bilili_dl_by_avid(avid)
    elif re.match(r'https?://www.bilibili.com/bangumi/media/md(\d+)/', url):
        season_id = re.match(r'https?://www.bilibili.com/bangumi/media/md(\d+)/', url).group(1)
        GLOBAL['season_id'] = season_id
        bilili_dl_bangumi(season_id)

def main():
    parser = argparse.ArgumentParser(description='bilili-dl')
    parser.add_argument('url', help='主页 url')
    parser.add_argument('-r', default='80', help='视频清晰度')
    args = parser.parse_args()
    GLOBAL['args'] = args
    GLOBAL['sp_seq'] = sps[sps.index(int(args.r)):] + list(reversed(sps[:sps.index(int(args.r))]))
    bilili_dl(args.url)

if __name__ == '__main__':
    main()
    # url = 'https://www.bilibili.com/video/av6538245'
    # url = 'https://www.bilibili.com/bangumi/media/md2543/'
    # bilili_dl(url)
