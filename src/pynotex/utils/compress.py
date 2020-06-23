import zipfile
import tarfile
import rarfile
import os

def unzip(path, target_dir=None):
    if target_dir is None:
        target_dir = os.path.dirname(path)
    z = zipfile.ZipFile(path)
    z.extractall(target_dir)
    z.close()

def zip(path, target_path=None):
    path = os.path.normpath(path).rstrip(os.sep)
    if target_path is None:
        dir_name = os.path.dirname(path)
        file_name = os.path.splitext(os.path.split(path)[1])[0] + '.zip'
        target_path = os.path.join(dir_name, file_name)
    z = zipfile.ZipFile(target_path, 'w', zipfile.ZIP_DEFLATED)

    root = os.path.normpath(path) + os.sep
    zroot = os.path.split(path)[1] + os.sep
    z.write(root, zroot)

    for dirpath, dirnames, filenames in os.walk(root):
        for filename in filenames:
            fpath = os.path.join(dirpath, filename)
            zpath = os.path.join(zroot, fpath.replace(root, ''))
            z.write(fpath, zpath)
        for dirname in dirnames:
            fpath = os.path.join(dirpath, dirname)
            zpath = os.path.join(zroot, fpath.replace(root, ''))
            z.write(fpath, zpath)
    z.close()

def untgz(path, target_dir=None):
    if target_dir is None:
        target_dir = os.path.dirname(path)
    t = tarfile.open(path)
    t.extractall(target_dir)
    t.close()

def tgz(path, target_path=None):
    path = os.path.normpath(path).rstrip(os.sep)
    if target_path is None:
        dir_name = os.path.dirname(path)
        file_name = os.path.splitext(os.path.split(path)[1])[0] + '.tar.gz'
        target_path = os.path.join(dir_name, file_name)
    t = tarfile.open(target_path, "w:gz")

    root = os.path.normpath(path) + os.sep
    troot = os.path.split(path)[1] + os.sep
    t.add(root, troot)
    t.close()

def unrar(path, target_dir=None):
    if target_dir is None:
        target_dir = os.path.dirname(path)
    print(path, target_dir)
    r = rarfile.RarFile(path)
    r.extractall(target_dir)

if __name__ == '__main__':
    tgz('tmp/test/')
    zip('tmp/test/')
    untgz('tmp/test.tar.gz')
    unzip('tmp/test.zip')
    unrar('tmp/test.rar')
