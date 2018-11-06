import re
import os

def clearOldDir(root):
    path = os.path.join(root, 'Playlist.dpl')
    if not os.path.isfile(path):
        return
    with open(path, 'r', encoding = 'utf8') as f:
        s = ''
        oldDirRe = re.compile(r'\d+\*file\*(?P<dir>.+\\)Videos\\')
        for line in f:
            if oldDirRe.search(line):
                oldDir = oldDirRe.search(line).group('dir')
                s += line.replace(oldDir, '')
            else:
                s += line
    with open(path, 'w', encoding = 'utf8') as f:
        f.write(s)

if __name__ == '__main__':
    for path in os.listdir('.'):
        if os.path.isdir(path):
            for course in os.listdir(path):
                clearOldDir(os.path.join(path, course))

    print('Done!')

