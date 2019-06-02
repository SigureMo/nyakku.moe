"""
ref: https://gitee.com/localhost_liangbing/itchat_op_pc/blob/master/itchat_op_pc
"""

import os
import subprocess
import threading
import time

import cv2
import itchat
from PIL import ImageGrab

from utils.compress import zip
from utils.config import Config
from utils.filer import touch_dir

CONFIG = Config('wechat_viewer').conf
TMP_DIR = touch_dir(CONFIG['tmp_dir'])

Help_Msg = """Wechat Viewer is running ...
- help
- prtsc
- prtph
- cmd <cmd_string>
- fget <file_path>
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
            cv2.imwrite(os.path.join(TMP_DIR, "prtph.png"), img)
            itchat.send('@img@%s' % os.path.join(TMP_DIR, "prtph.png"), 'filehelper')
            cap.release()
        elif message == "prtsc":
            ImageGrab.grab().save(os.path.join(TMP_DIR, "prtsc.png"))
            itchat.send('@img@%s' % os.path.join(TMP_DIR, "prtsc.png"), 'filehelper')
        elif message.startswith("$ "):
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
                    filepath = os.path.join(TMP_DIR, "tmp.zip")
                    zip(path, filepath)
                itchat.send_file(u"%s" % filepath, toUserName='filehelper')
            else:
                itchat.send("路径错误", 'filehelper')
        else:
            itchat.send("暂不支持呦！", 'filehelper')


if __name__ == '__main__':
    itchat.auto_login(hotReload=True, statusStorageDir=os.path.join(TMP_DIR, "itchat.pkl"), enableCmdQR=True)
    itchat.send(Help_Msg, "filehelper")
    itchat.run()
