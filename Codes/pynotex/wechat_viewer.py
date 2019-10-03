"""
ref: https://gitee.com/localhost_liangbing/itchat_op_pc/blob/master/itchat_op_pc
"""

import os
import subprocess
import threading
import time

import cv2
import itchat
try:
    from PIL import ImageGrab
except ImportError:
    import pyscreenshot as ImageGrab

from utils.compress import zip
from common.app import App

app_name = 'wechat_viewer'
APP = App(app_name)

Help_Msg = """Wechat Viewer is running ...
- help
- prtsc
- prtph
- fget <file_path>
- > <cmd_string>
"""

@itchat.msg_register('Text')
def text_reply(msg):
    message = msg['Text']
    user_name = msg['FromUserName']
    to_user_name = msg['ToUserName']

    if to_user_name == "filehelper":
        if message == "help":
            itchat.send(Help_Msg, "filehelper")
        elif message == "prtph":
            cap = cv2.VideoCapture(0)
            ret, img = cap.read()
            cv2.imwrite(APP.tmp_dir.join("prtph.png"), img)
            itchat.send('@img@%s' % APP.tmp_dir.join("prtph.png"), 'filehelper')
            cap.release()
        elif message == "prtsc":
            ImageGrab.grab().save(APP.tmp_dir.join("prtsc.png"))
            itchat.send('@img@%s' % APP.tmp_dir.join("prtsc.png"), 'filehelper')
        elif message.startswith("> "):
            cmd = message[2: ]
            print(message)
            res = subprocess.run(cmd, stdout=subprocess.PIPE, shell=True)
            itchat.send(res.stdout.decode(), 'filehelper')
            if res.stderr:
                itchat.send(res.stderr.decode(), 'filehelper')
        elif message.startswith("fget "):
            path = message[5: ]
            if os.path.exists(path):
                if os.path.isfile(path):
                    filepath = path
                elif os.path.isdir(path):
                    filepath = APP.tmp_dir.join("tmp.zip")
                    zip(path, filepath)
                itchat.send_file(u"%s" % filepath, toUserName='filehelper')
            else:
                itchat.send("路径错误", 'filehelper')
        else:
            itchat.send("暂不支持呦！", 'filehelper')


if __name__ == '__main__':
    itchat.auto_login(hotReload=True, statusStorageDir=APP.tmp_dir.join("itchat.pkl"))
    itchat.send(Help_Msg, "filehelper")
    itchat.run()
