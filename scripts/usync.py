import subprocess
import os
import re
import sys
import argparse

SYS = sys.platform

def usbpath(name=None):
    """ 获取 U 盘根目录
    ref: https://blog.csdn.net/tp7309/article/details/82226110
    """
    if SYS == 'win32':
        cmd = "wmic logicaldisk get deviceid, description"
        p = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE)
        result = p.stdout.read().decode("gbk")
        disks = result.split('\n')
        for disk in disks:
            if 'Removable' in disk or "可移动磁盘" in disk:
                return re.search(r'\w:', disk).group()
    elif SYS in ["darwin", "linux"]:
        roots = ["/Volumes"] if SYS == "darwin" else ["/media", "/mnt"]
        for root in roots:
            for base_dir, dir_names, _ in os.walk(root):
                if name in dir_names:
                    return os.path.join(base_dir, name)
        else:
            return None

def sync(src, tar):
    """ 两路径内容同步 """
    print(src, end="\r")
    if os.path.isfile(src):
        with open(src, "rb") as fr:
            with open(tar, "wb") as fw:
                fw.write(fr.read())
    else:
        if not os.path.exists(tar):
            os.makedirs(tar)
        for file_name in os.listdir(src):
            sync(
                os.path.join(src, file_name),
                os.path.join(tar, file_name)
            )

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="U Sync")
    parser.add_argument('direct', help='同步方向')
    parser.add_argument("-n", "--name", help='U 盘名称')
    parser.add_argument("-p", "--path", default=".", help='备份路径')
    parser.add_argument("-y", "--yes", action="store_true", help='禁用提示')
    args = parser.parse_args()

    uroot = usbpath(name=args.name)
    if uroot is None:
        print("未检测到可用的可移动磁盘")
        sys.exit(1)
    if not args.yes and input("请确认 U 盘根路径为 %s" % uroot):
        sys.exit(1)
    if not args.yes and input("请确认操作为 %s" % args.direct):
        sys.exit(1)

    if args.direct == "u++":
        src_root = ""
        tar_root = uroot
    elif args.direct == "u--":
        src_root = uroot
        tar_root = ""

    sync(
        os.path.join(src_root, args.path),
        os.path.join(tar_root, args.path)
    )
