import os
import re
import chardet
import argparse


DOCS = ['.txt', '.py', '.c', '.cpp', '.java', '.md', '.js', '.csv', '.html',
        '.css', '.json', '.ts', '.as', '.xml']

def search(keyword, root = '.', ext = DOCS, ignore_paths = []):
    """
    搜索关键词，并将匹配到的位置返回
    :param keyword: str or re.complied, 需要查找的关键词，支持字符串和编译后的正则表达式
    :param root: str = '.', 需要查找的路径
    :param ext: list or set = DOCS, 需要处理的扩展名，可自行传入，默认使用全局变量DOCS，
    若使用bool值为空的对象(set()和[])，那么将匹配所有文件
    :param ignore_paths: list or set = [], 忽略的路径集合，可以是正则
    :return: list(str, list(int)), 返回每个匹配结果的路径以及行号组成的列表
    """
    paths = []
    # matching = []
    ignore_paths = list(map(lambda path: re.compile(path), ignore_paths))
    """使用yarn式的进度条"""
    sign = '⠁⠂⠄⡀⢀⠠⠐⠈' # ['-', '\\', '|', '/']

    """收集所有有效路径"""
    for path, dirnames, filenames in os.walk(root):
        for filename in filenames:
            """若传入的扩展名集合为空，直接短路"""
            full_path = path + os.sep + filename
            if any(ignore_path.search(full_path) for ignore_path in ignore_paths):
                continue
            if not ext or os.path.splitext(filename)[1] in ext:
                paths.append(full_path)

    """根据类型判断传入是已经编译好的还是还没有编译过的正则表达式"""
    if isinstance(keyword, str):
        matcher = re.compile(keyword)
    else:
        """传入时已经编译过"""
        matcher = keyword

    """读取各路径下的文件"""
    for num, path in enumerate(paths):
        print(f'{sign[num % len(sign)]} {path}' + ' '*20, end='\r')
        """首先根据使用rb判断下文本编码格式"""
        with open(path, 'rb') as file:
            buf = file.read()
            result = chardet.detect(buf)
        try:
            """使用预判编码进行读取"""
            with open(path, 'r', encoding=result["encoding"]) as f:
                matching_lines = []
                for cnt, line in enumerate(f, 1):
                    if matcher.search(line):
                        matching_lines.append(cnt)
                if matching_lines:
                    # matching.append((path, matching_lines))
                    yield (path, matching_lines)
        except:
            """预判错误，无法读取"""
            print(f'{path} decode with {result["encoding"]} Error!')
    # return matching

def test():
    for localtion in search('S_Note', ignore_paths={'vuepress', 'node_modules'}):
        print(localtion)
    print('Done!')

def main():
    parser = argparse.ArgumentParser(description='docs_search')
    parser.add_argument('--doc', help='待搜索文档')
    parser.add_argument('--keyword', help='待搜索关键词（支持正则表达式）')
    args = parser.parse_args()
    for localtion in search(args.keyword, root=args.doc):
        print(localtion)
    print('Done!')

if __name__ == '__main__':
    test()
