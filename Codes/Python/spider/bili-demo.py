import requests
import re
import json

avid = 6538245
sess = requests.session()
mirrors = ['', 'cos', 'kodo', 'ks3', 'bos', 'ks3u', 'kodou']

url = 'https://www.bilibili.com/video/av{avid}'.format(avid=avid)
headers = {
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/64.0.3282.167 Safari/537.36',
    'Referer': 'https://www.bilibili.com'
    }

res = sess.get(url, headers=headers)
title = re.search(r'<title .*>(.*)_哔哩哔哩 \(゜-゜\)つロ 干杯~-bilibili</title>', res.text).group(1)
print(title)
info = json.loads(re.search(r'\"pages\":(\[.*}}\]),', res.text).group(1))
rexxx = [80, 64, 32, 16] # 高清 1080P  高清 720P  清晰 480P  流畅 360P
video_api = 'https://api.bilibili.com/x/player/playurl?avid={avid}&cid={cid}&qn={sp}&type=&otype=json'
video_txt = open('video.txt', 'w')
for item in info:
    name = item['part']
    api = video_api.format(avid=avid, cid=item['cid'], sp=80)
    video_res = sess.get(api, headers=headers)
    video_url = video_res.json()['data']['durl'][0]['url']
    url_mirror = re.search(r'mirror(.*?)\.', video_url).group(1)
    if url_mirror not in mirrors:
        print(f'新源！{url_mirror}')
    for mirror in mirrors:
        if mirror:
            video_url = re.sub(r'mirror.*?\.', 'mirror%s.' % mirror, video_url)
        print(video_url)
        try:
            reh = requests.head(video_url, headers=headers, timeout=20)
            if reh.status_code != 200:
                raise Exception
        except:
            print('尝试换源中')
            continue
        print(f'{name} 源{mirror}可用')
        break
    else:
        raise Exception('无可用源')
    video_txt.write(video_url+'\n')
    video_txt.flush()
    continue
    res = sess.get(video_url, headers=headers)
    with open(name + '.flv', 'wb') as f:
        f.write(res.content)
video_txt.close()