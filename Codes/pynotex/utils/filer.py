import os
import hashlib

def touch_dir(path):
    if os.path.exists(path):
        return
    os.makedirs(path)

def touch_file(path):
    if os.path.exists(path):
        return
    os.open(path, 'w').close()

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
