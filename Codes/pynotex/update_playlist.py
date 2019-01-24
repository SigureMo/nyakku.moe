import re
import os
import sys

from utils.config import Config

"""
用于 [course-crawler](https://github.com/SigureMo/course-crawler)

由于使用 potplayer 打开视频后会更改播放列表的路径（相对变绝对），这使得移动课程后播放列表不可用
本脚本针对该问题，将更改后的播放列表中的绝对路径部分剔除，以适应课程的移动

本脚本支持传入多个参数以启动
``` bash
python path/to/pynotex/update_playlist.py path/to/dir1 path/to/dir2
```

同时也可以不加参数，使用默认参数启动，事先请自行创建并填写 config.json
``` json
{
  "name": "pynotex",
  "APPs": {
    "update_playlist": {
      "clean_dirs": [
        "path/to/dir1",
        "path/to/dir2",
        "path/to/dir3"
      ]
    }
  }
}
```
"""


CONFIG = Config('update_playlist').conf

def delete_old_dir(root):
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
    print('{} done!'.format(path))

if __name__ == '__main__':
    args = sys.argv[1:]
    if args:
        clean_dirs = args
    else:
        clean_dirs = CONFIG['clean_dirs']
    for clean_dir in clean_dirs:
        for course in os.listdir(clean_dir):
            delete_old_dir(os.path.join(clean_dir, course))

    print('Done!')

