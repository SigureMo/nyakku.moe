import argparse
import os
import re

import markdown
from markdown.extensions.fenced_code import FencedCodeExtension
from markdown.extensions.tables import TableExtension

from common.app import App
from utils.smtp import SMTP

app_name = "markdown-mail"
CONFIG = App(app_name).config


def get_title(title, markdown_txt):
    """ 获取标题
    如果没有指定标题，则默认使用 Markdown 第一行文本作为标题
    如果第一行并非 H1 ，则返回 '无标题'
    """
    if title is not None:
        return title
    title_line = markdown_txt.split("\n")[0]
    if title_line.startswith("# "):
        return title_line[2:].rstrip()
    else:
        return "无标题"


def to_html(markdown_txt):
    """ 将 Markdown 文本转换为 HTML
    可通过扩展以丰富 Markdown 的内容
    """
    html = markdown.markdown(markdown_txt, extensions=[
                             'tables', 'fenced_code'])
    return html


def parse_address(address):
    """ 解析邮件地址各个参数 """
    re_mail = re.compile(
        r"(?P<username>\w+)@(?P<hostname>\w+)\.(?P<domain>\w+)")
    res = re_mail.match(address)
    if res is None:
        return None
    else:
        return {
            "username": res.group("username"),
            "hostname": res.group("hostname"),
            "domain": res.group("domain")
        }


def read(markdown_file):
    """ 读取 Markdown 文本 """
    with open(markdown_file, "r", encoding="utf-8") as f:
        markdown_txt = f.read()
    return markdown_txt


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Markdown Mail')
    parser.add_argument('markdown', help='Markdown 文件路径')
    parser.add_argument('--to', default="example@xxx.com", help='目标邮箱')
    parser.add_argument('--footer', action="store_true", help='使用脚注文件')
    parser.add_argument('--subject', default=None, help="主题")
    args = parser.parse_args()

    # 获得 Markdown 文本，并转化 HTML
    markdown_txt = read(args.markdown)
    if args.footer and CONFIG["footer"] and os.path.exists(CONFIG["footer"]):
        markdown_txt += read(CONFIG["footer"])
    html = to_html(markdown_txt)

    # 获取邮件相关信息
    subject = args.subject
    title = get_title(subject, markdown_txt)
    from_username = CONFIG["username"] if CONFIG.get("username") \
        else parse_address(CONFIG["address"])["username"]
    to_username = parse_address(args.to)["username"]

    # 发送邮件
    smtp = SMTP(parse_address(CONFIG["address"])["hostname"])
    smtp.login_(CONFIG["address"], CONFIG["password"])
    print("发送中...")
    smtp.send_html(args.to, html,
                   title=title, appName=from_username, userName=to_username)
    print("发送成功！")
