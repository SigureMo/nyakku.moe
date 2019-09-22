""" 构建中 """

import os
import subprocess

BASE_DIR = "bin/"
BIN_DIRs = [
    "docs/Images/",
    "docs/.vuepress/public/",
    "tools/"
]

def add_dir(bin_dir):
    tar_dir = os.path.join(BASE_DIR, bin_dir)
    print(bin_dir, tar_dir)
    subprocess.run(["rm", "-rf", tar_dir])
    if not os.path.exists(tar_dir):
        os.makedirs(tar_dir)
    subprocess.run(["cp", "-rf", bin_dir+"*", tar_dir])
    if not os.path.exists(os.path.join(BASE_DIR, ".git")):
        subprocess.run(["git", "init"], cwd=BASE_DIR)
    subprocess.run(["git", "add", bin_dir+"*"], cwd=BASE_DIR)


def push():
    for bin_dir in BIN_DIRs:
        add_dir(bin_dir)


push()
