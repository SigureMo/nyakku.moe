import os
import re

DOCS = ['.txt', '.py', '.c', '.cpp', '.java', '.md', '.js', '.csv', '.html',
        '.css', '.json']

def search(keyword, root = '.', ext = DOCS):
    paths = []
    matching = []
    for path, dirnames, filenames in os.walk(root):
        for filename in filenames:
            if os.path.splitext(filename)[1] in ext:
                paths.append(path + os.sep + filename)
    if isinstance(keyword, str):
        matcher = re.compile(keyword)
    else:
        matcher = keyword
    for path in paths:
        with open(path, 'r') as f:
            cnt = 1
            matching_lines = []
            for line in f:
                if matcher.search(line):
                    matching_lines.append(cnt)
                cnt += 1
            if matching_lines:
                matching.append((path, matching_lines))
    return matching
                
for localtion in search('decode'):
    print(localtion)
