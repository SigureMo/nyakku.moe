import sys
import os
import re

from common.file import Dpl

formats = {'.mp4', '.flv', '.ts', '.wmv'}
numbers = ['零', '一', '二', '三', '四', '五', '六', '七', '八', '九', '十']

def listdir(dirname, order = lambda x: x):
    filepaths = []
    paths = list(filter(
        lambda path: os.path.splitext(path)[1] in formats or os.path.isdir(os.path.join(dirname, path)),
        os.listdir(dirname)
        ))
    sorted_paths = order(paths)
    for path in sorted_paths:
        path = os.path.join(dirname, path)
        if os.path.isfile(path):
            filepaths.append(path)
        elif os.path.isdir(path):
            filepaths.extend(listdir(path, order=order))
    return filepaths

def create_playlist(base_dir, playlist_path, path_type='RP', order=lambda x: x):
    playlist = Dpl(os.path.join(base_dir, 'Playlist.dpl'), path_type=path_type)
    for path in listdir(base_dir, order=order):
        playlist.write_path(path)

def order(paths):
    re_number = re.compile(r'\d+')
    re_cn_number = re.compile(r'[零一二三四五六七八九十]')
    if all([re_cn_number.search(path) for path in paths]):
        print('已使用中文数字对目录重排')
        paths = sorted(paths, key=lambda path: numbers.index(re_cn_number.search(path).group(0)))
    elif all([re_number.search(path) for path in paths]):
        print('已使用数字对目录重排')
        paths = sorted(paths, key=lambda path: int(re_number.search(path).group(0)))
    else:
        print('未对目录重排')
    return paths

if __name__ == '__main__':
    base_dirs = sys.argv[1:]
    for base_dir in base_dirs:
        create_playlist(base_dir, os.path.join(base_dir, 'Playlist.dpl'), order=order)
