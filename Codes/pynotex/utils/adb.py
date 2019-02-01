import time
import re
import subprocess

from PIL import Image
from io import BytesIO
from utils.config import Config
from utils.filer import touch_dir


CONFIG = Config('adb').conf
touch_dir(CONFIG['tmp_dir'])

class ADB():
    def __init__(self):
        self.path = CONFIG['adb_path']

    def run(self, cmd):
        print('{} {}'.format(self.path, cmd))
        return subprocess.Popen('{} {}'.format(self.path, cmd), stdout=subprocess.PIPE, stderr=subprocess.PIPE)

    def screenshot(self):
        process = self.run('shell screencap -p')
        binary_screenshot = process.stdout.read()
        try:
            return Image.open(BytesIO(binary_screenshot))
        except OSError:
            pass
        try:
            return Image.open(BytesIO(binary_screenshot.replace(b'\r\n', b'\n')))
        except OSError:
            pass
        try:
            return Image.open(BytesIO(binary_screenshot.replace(b'\r\r\n', b'\n')))
        except OSError:
            tmp_dir = CONFIG['tmp_dir'].rstrip('/').rstrip('\\')
            self.run('shell screencap -p /sdcard/screencap.png')
            self.run('pull /sdcard/screencap.png {}'.format(tmp_dir))
            return Image.open('{}/screencap.png'.format(tmp_dir))

    def get_devices(self):
        process = self.run('devices')
        result = process.stdout.read().decode('utf-8')
        devices = re.findall(r'\r\n(\w+?)\tdevice', result)
        unauthorized = re.findall(r'\r\n(\w+?)\tunauthorized', result)
        return devices, unauthorized

    def is_connected(self):
        devices, unauthorized = self.get_devices()
        if len(devices) == 1:
            return True
        elif len(devices) > 1:
            print('当前有多个设备连接，请断开不必要的设备连接')
            return False
        else:
            if len(unauthorized) > 0:
                print('请在手机上授权 USB 调试')
                return False
            else:
                print('请您确定已经开启开发者模式与 USB 调试')
                return False

    def click(self, point):
        self.run('shell input tap {} {}'.format(point[0], point[1]))

    def swipe(self, point_1, point_2, duration=''):
        self.run('shell input swipe {} {} {} {} {}'.format(point_1[0], point_1[1], point_2[0], point_2[1], duration))
