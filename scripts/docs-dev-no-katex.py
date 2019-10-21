"""
由于现阶段 KaTeX 作为插件会使得文档 dev 无法进行，
所以做一个临时移除 KaTeX 进行 dev 的脚本
"""

import re
import os
import sys
import subprocess
import time

config_file = "docs/.vuepress/config.js"
bak_file = "data/config.js"
re_remove = re.compile(r"md\.use\(require\(\"@iktakahiro/markdown-it-katex\"\), \{[\s\S]+?\}\);")

def backup():
    print("已备份 config.js")
    with open(config_file, "r", encoding="utf8") as f:
        config_text = f.read()
    with open(bak_file, "w", encoding="utf8") as f:
        f.write(config_text)

def remove_katex():
    with open(config_file, "r", encoding="utf8") as f:
        config_text = f.read()
    config_text_no_katex = re_remove.sub("", config_text)
    with open(config_file, "w", encoding="utf8") as f:
        f.write(config_text_no_katex)

def restore():
    print("已还原 config.js")
    with open(bak_file, "r", encoding="utf8") as f:
        config_text = f.read()
    with open(config_file, "w", encoding="utf8") as f:
        f.write(config_text)
    # os.remove(bak_file)

def docs_dev():
    shell = os.name == "nt"
    p = subprocess.Popen(["vuepress", "dev", "docs"], shell=shell)
    while True:
        try:
            time.sleep(1)
        except KeyboardInterrupt:
            p.terminate()
            break

if __name__ == '__main__':

    try:
        backup()
        remove_katex()
        docs_dev()
    finally:
        restore()
