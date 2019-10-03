import time
import os

from common.config import Config
from utils.smtp import SMTP
from utils.loop import Loop
from utils.ssh import Server
from common.file import touch_dir
from async_lib.utils import Task
from drivers.ffmpeg import FFmpeg
from utils.db import SQLite, IntegerField, StringField, FloatField, Model
from common import console


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

class User(Model):

    id = IntegerField('id', primary_key=True, not_null=True)
    age = IntegerField('age')
    name = StringField('name', not_null=True)
    height = IntegerField('height')

    def __init__(self, db, **kw):
        self.db = db
        super().__init__(**kw)

def db_test():
    db_path = os.path.join(touch_dir('tmp/db_test'), 'user.db')
    db = SQLite(db_path)
    User(db).create()
    User(db, id=1, name='Xiaoming', height=176, age=19).insert()
    User(db, name='Xiaomiao', age=20).insert()
    print(User(db, name=True, age=True).select(
            conditional="age > 18 AND name LIKE 'Xiao%'",
            order = ['age DESC']
            ))
    User(db, age_=1).update(conditional="age in (19, 20)")
    User(db).delete(conditional="name = 'Xiaomiao'")
    print(User(db).select())

def console_test():
    frames = ["⠈ ", " ⠁", " ⠐", " ⠠", " ⡀", "⢀ ", "⠄ ", "⠂ "]
    done_sign = console.color_str(" ", background_color=console.BLUE)
    undone_sign = console.color_str(" ", background_color=console.WHITE)
    total = 10000
    for cnt in range(1, total+1):
        # console.clear_line()
        print(
            "{:5}/{:5}".format(cnt, total),
            console.slide(cnt, frames),
            console.process_bar(cnt/total, width=50, done_sign=done_sign, undone_sign=undone_sign),
            end="\r"
        )

if __name__ == '__main__':
    console_test()
