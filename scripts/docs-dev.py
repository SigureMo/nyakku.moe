"""
为了方便部署与 dev 使用不同的配置，这里在 dev 的时候临时修改部分配置
比如
    - 移除 markdown-it-katex 以防止 dev 无法进行
    - 移除 node 主题配置 reco
并且支持传入参数，以定制化 dev 时候的操作
"""

import re
import os
import sys
import subprocess
import time

config_file = "docs/.vuepress/config.js"
bak_file = "data/config.js"
replaces = {
    "katex": re.compile(r"md\.use\(require\(\"@iktakahiro/markdown-it-katex\"\)(,\s?\{[\s\S]+?\})?\);"),
}

def backup():
    print("已备份 config.js")
    with open(config_file, "r", encoding="utf8") as f:
        config_text = f.read()
    with open(bak_file, "w", encoding="utf8") as f:
        f.write(config_text)
    return config_text

def gen_dev_config(keys):
    with open(config_file, "r", encoding="utf8") as f:
        config_text = f.read()
    for key in keys:
        config_text = replaces[key].sub("", config_text)
    with open(config_file, "w", encoding="utf8") as f:
        f.write(config_text)

def restore(config_text):
    print("已还原 config.js")
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

    allow_keys = replaces.keys()
    keys = list(map(lambda arg: arg.lstrip('--no-'), sys.argv[1: ]) if sys.argv[1: ] else allow_keys)
    assert all([key in allow_keys for key in keys])

    try:
        config_text = backup()
        gen_dev_config(keys)
        docs_dev()
    finally:
        restore(config_text)
