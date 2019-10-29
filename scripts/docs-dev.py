"""
为了方便部署与 dev 使用不同的配置，这里在 dev 的时候临时修改部分配置
比如
    - 移除 markdown-it-katex 以防止 dev 无法进行
    - 移除 node 主题配置 reco
"""

import re
import os
import sys
import subprocess
import time

config_file = "docs/.vuepress/config.js"
bak_file = "data/config.js"
re_katex = re.compile(r"md\.use\(require\(\"@iktakahiro/markdown-it-katex\"\), \{[\s\S]+?\}\);")
re_theme = re.compile(r"theme: \"reco\",")
replace_list = [re_katex, re_theme]

def backup():
    print("已备份 config.js")
    with open(config_file, "r", encoding="utf8") as f:
        config_text = f.read()
    with open(bak_file, "w", encoding="utf8") as f:
        f.write(config_text)

def gen_dev_config():
    with open(config_file, "r", encoding="utf8") as f:
        config_text = f.read()
    for re_replace in replace_list:
        config_text = re_replace.sub("", config_text)
    with open(config_file, "w", encoding="utf8") as f:
        f.write(config_text)

def restore():
    print("已还原 config.js")
    with open(bak_file, "r", encoding="utf8") as f:
        config_text = f.read()
    with open(config_file, "w", encoding="utf8", newline="\n") as f:
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
        gen_dev_config()
        docs_dev()
    finally:
        restore()
