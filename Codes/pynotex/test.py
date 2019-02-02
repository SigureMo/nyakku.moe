import time

from utils.config import Config
from utils.smtp import SMTP
from utils.loop import Loop
from utils.ssh import Server
from utils.async_lib.utils import Task
from utils.video_editor import FFmpeg

CONFIGs = {}
CONFIGs['smtp'] = Config('smtp').conf
CONFIGs['ssh'] = Config('ssh').conf

def test():
    print(1)
    if int(time.time()) % 5 == 0:
        return True

def smtp_test():
    CONFIG = CONFIGs['smtp']
    smtp = SMTP('163')
    smtp.login_(CONFIG['from_addr'], CONFIG['password'])
    loop = Loop(1)
    loop.on(
        Task(test),
        Task(smtp.send_text, (CONFIG['to_addr'], '<message>'))
    )
    loop.run()

def ssh_test():
    CONFIG = CONFIGs['ssh']
    server = Server(
        CONFIG['host'],
        CONFIG['port'],
        CONFIG['username'],
        CONFIG['password']
        )
    print(server.exec('hostname')[0].strip('\n'))

def video_test():
    ffmpeg = FFmpeg()
    ffmpeg.join_videos([
        'tmp/video_editor/01.mp4',
        'tmp/video_editor/02.mp4',
    ], 'tmp/t.mp4')
    ffmpeg.convert('tmp/video_editor/01.mp4', 'tmp/video_editor/05.flv')

if __name__ == '__main__':
    video_test()
