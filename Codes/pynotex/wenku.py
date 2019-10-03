import argparse
import json
import os
import re

from utils.crawler import Crawler
from common.file import touch_dir
from common.image import imgs2pdf
from common.app import App

app_name = "wenku"
APP = App(app_name)
spider = Crawler()


class ParseError(Exception):
    def __init__(self, message):
        self.message = message


def parse(url):
    types = {
        '0': {'str': '', 'parse_func': parse_xxx},
        '1': {'str': 'doc', 'parse_func': parse_doc},
        '2': {'str': 'xls', 'parse_func': parse_xxx},
        '3': {'str': 'ppt', 'parse_func': parse_ppt},
        '4': {'str': 'docx', 'parse_func': parse_xxx},
        '5': {'str': 'xlsx', 'parse_func': parse_xxx},
        '6': {'str': 'pptx', 'parse_func': parse_ppt},
        '7': {'str': 'pdf', 'parse_func': parse_pdf},
        '8': {'str': 'txt', 'parse_func': parse_txt},
        '9': {'str': 'wps', 'parse_func': parse_xxx},
        '10': {'str': 'et', 'parse_func': parse_xxx},
        '11': {'str': 'dps', 'parse_func': parse_xxx},
        '12': {'str': 'vsd', 'parse_func': parse_xxx},
        '13': {'str': 'rtf', 'parse_func': parse_xxx},
        '14': {'str': 'pot', 'parse_func': parse_xxx},
        '15': {'str': 'pps', 'parse_func': parse_xxx},
        '16': {'str': 'epub', 'parse_func': parse_xxx},
    }
    doc_id = re.match(r'https://wenku.baidu.com/view/(\w+).html', url).group(1)
    doc_info = parse_info(doc_id)
    tp = types[doc_info['docInfo']['docType']]['str']
    parse_func = types[doc_info['docInfo']['docType']]['parse_func']
    name = doc_info['docInfo']['docTitle']
    print(name + '.' + tp)
    # print(doc_info)
    params = (name, doc_info)
    try:
        parse_func(doc_id, *params)
        print('Successful! Please visit {}'.format(APP.data_dir.join(name)))
    except ParseError as e:
        print('Failed! {}'.format(e.message))


def parse_info(doc_id):
    info_api = 'https://wenku.baidu.com/api/doc/getdocinfo?callback=cb&doc_id={}'
    result = spider.get(info_api.format(doc_id))
    json_text = re.search(r'\(([\s\S]+)\)', result.text).group(1)
    json_data = json.loads(json_text)
    return json_data


def parse_ppt(doc_id, *params):
    name = params[0]
    img_path_list = []
    pics_url_api = 'https://wenku.baidu.com/browse/getbcsurl?doc_id={}&pn=1&rn=99999&type=ppt'
    for page_info in spider.get(pics_url_api.format(doc_id)).json():
        zoom, page = page_info.values()
        img_data = spider.get(zoom).content
        img_path = APP.tmp_dir.join('{}{:02}.jpg'.format(name, page))
        img_path_list.append(img_path)
        with open(img_path, 'wb') as f:
            f.write(img_data)
    imgs2pdf(img_path_list, APP.data_dir.join(name+'.pdf'))


def parse_doc(doc_id, *params):
    name = params[0]
    home_url = 'https://wenku.baidu.com/view/{}.html'.format(doc_id)
    html = spider.get(home_url).text
    html_urls = re.findall('(https.*?0.json.*?)\\\\x22}', html)
    texts = ''
    for html_url in html_urls[:len(html_urls)//2]:
        result = spider.get(html_url.replace('\\', ''))
        json_text = re.search(
            r'\(([\s\S]+)\)', result.text.encode('utf-8').decode('unicode_escape', 'ignore')).group(1)
        json_data = json.loads(json_text)
        for i, segment in enumerate(json_data['body'], 1):
            texts += segment['c']
            if segment['ps'] and segment['ps']['_enter'] == 1 and i < len(json_data['body']):
                # TODO 由于换页会加换行符，所以暂且当做最后一行没有换行符，也许会修正
                texts += '\n'
    with open(APP.data_dir.join(name + '.txt'), 'w', encoding='utf8') as f:
        f.write(texts)


def parse_txt(doc_id, *params):
    name, doc_info = params[: 2]
    page_num = doc_info['docInfo']['totalPageNum']
    md5 = doc_info['md5sum']
    rsign = doc_info['rsign']
    txt_api = 'https://wkretype.bdimg.com/retype/text/{doc_id}?rn={page_num}&type=txt{md5}&rsign={rsign}'
    result = spider.get(txt_api.format(
        doc_id=doc_id, page_num=page_num, md5=md5, rsign=rsign))
    json_text = result.text
    json_data = json.loads(json_text)
    texts = ''
    for page_info in json_data:
        for parag in page_info['parags']:
            texts += parag['c']
    with open(APP.data_dir.join(name + '.txt'), 'w', encoding='utf8') as f:
        f.write(texts)


def parse_pdf(doc_id, *params):
    home_url = 'https://wenku.baidu.com/view/{}.html'.format(doc_id)
    name = params[0]
    img_path_list = []
    html = spider.get(home_url).text
    cnt = 0
    info = re.search(
        r"WkInfo\.htmlUrls\s=\s([\s\S]+?)WkInfo\.verify_user_info", html)
    for item in info.group(1).split(r"\x22"):
        if re.match('https.*?0.png.*?', item):
            png_url = item.replace("\\", "")
            img_data = spider.get(png_url).content
            img_path = APP.tmp_dir.join('{}{:02}.png'.format(name, cnt))
            img_path_list.append(img_path)
            with open(img_path, 'wb') as f:
                f.write(img_data)
            cnt += 1
    imgs2pdf(img_path_list, APP.data_dir.join(name+'.pdf'))


def parse_xxx(doc_id, *params):
    print('TODO ...')
    raise ParseError('无法解析该类型')


def test():
    doc_url = 'https://wenku.baidu.com/view/501a1ea20408763231126edb6f1aff00bfd57048.html'
    pptx_url = 'https://wenku.baidu.com/view/3202acfbba4cf7ec4afe04a1b0717fd5360cb220.html'
    txt_url = 'https://wenku.baidu.com/view/ec7db56fb84ae45c3b358c6f.html'
    xls_url = 'https://wenku.baidu.com/view/724833840b1c59eef9c7b448.html'
    parse(xls_url)


def main():
    parser = argparse.ArgumentParser(description='wenku')
    parser.add_argument('url', help='资源 url')
    args = parser.parse_args()
    parse(args.url)


if __name__ == '__main__':
    main()
