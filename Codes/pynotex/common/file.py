import os
import re
import hashlib


class Writer():

    def __init__(self, path, mode='wb', **kw):
        self.path = path
        self._f = open(path, mode, **kw)

    def __del__(self):
        self._f.close()

    def flush(self):
        self._f.flush()

    def write(self, content):
        self._f.write(content)

class Text(Writer):

    def __init__(self, path, **kw):
        kw['encoding'] = kw.get('encoding', 'utf-8')
        super().__init__(path, 'w', **kw)

    def write_string(self, string):
        self.write(string + '\n')

class Playlist(Text):

    def __init__(self, path, path_type):
        super().__init__(path)
        self.path_type = path_type

    def switch_path(self, path):
        path = os.path.normpath(path)
        if self.path_type == 'AP':
            path = os.path.abspath(path)
        elif self.path_type == 'RP':
            path = os.path.relpath(path, start=os.path.dirname(self.path))
        return path

    def write_path(self, path):
        path = self.switch_path(path)
        self.write_string(path)

class M3u(Playlist):

    def __init__(self, path, path_type='RP'):
        super().__init__(path, path_type)

class Dpl(Playlist):

    def __init__(self, path, path_type='RP'):
        super().__init__(path, path_type)
        self.write_string('DAUMPLAYLIST\n')
        self._count = 0

    def write_path(self, path, name=None):
        self._count += 1
        path = self.switch_path(path)
        self.write_string('{}*file*{}'.format(self._count, path))
        if name is not None:
            self.write_string('{}*title*{}\n'.format(self._count, name))


class Dir():
    def __init__(self, base):
        """ 初始化并创建 base """
        self.base = touch_dir(base)

    def join(self, *path):
        """ 返回 base 路径添加多段路径后的位置 """
        return os.path.join(self.base, *path)

    def __str__(self):
        return self.base


def touch_dir(path):
    if not os.path.exists(path):
        os.makedirs(path)
    return os.path.normpath(path)

def touch_file(path):
    if not os.path.exists(path):
        open(path, 'w').close()
    return os.path.normpath(path)

def repair_filename(filename):
    regex_path = re.compile(r'[\\/:*?"<>|]')
    return regex_path.sub('', filename)

def get_size(path):
    if os.path.isfile(path):
        return os.path.getsize(path)
    elif os.path.isdir(path):
        size = 0
        for subpath in os.listdir(path):
            size += get_size(os.path.join(path, subpath))
        return size
    else:
        print(path)
        return 0

def size_format(size, ndigits=2):
    """ 输入数据字节数，与保留小数位数，返回数据量字符串 """
    flag = '-' if size < 0 else ''
    size = abs(size)
    units = ["Bytes", "kB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB", "BB"]
    idx = len(units) - 1
    while idx >= 0:
        unit_size = 2 ** (idx * 10)
        if size >= unit_size:
            unit = units[idx]
            return "{}{:.{}f} {}".format(flag, size/unit_size, ndigits, unit)
        idx -= 1

def md5(path, chunk_size = 8192):
    myhash = hashlib.md5()
    try:
        f = open(path, 'rb')
        while True:
            b = f.read(chunk_size)
            if not b :
                break
            myhash.update(b)
    except:
        return
    finally:
        f.close()
    return myhash.hexdigest()
