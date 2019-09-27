import os
import subprocess

from utils.config import Config
from utils.filer import touch_dir


CONFIG = Config('video_editor').conf
touch_dir(CONFIG['tmp_dir'])

"""
ref : https://github.com/soimort/you-get
"""

class FFmpeg():
    def __init__(self):
        self.path = CONFIG['ffmpeg_path']

    def exec(self, params):
        cmd = [self.path]
        cmd.extend(params)
        print(' '.join(cmd))
        return subprocess.run(cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

    def convert(self, input_path, output_path):
        params = [
            '-i', input_path,
            '-c', 'copy',
            '-map', '0',
            '-y',
            output_path
        ]
        self.exec(params)

    def join_videos(self, video_path_list, output_path):
        concat_list_path = os.path.join(CONFIG['tmp_dir'], 'concat_list.tmp').replace('\\', '/')
        with open(concat_list_path, 'w', encoding='utf-8') as f:
            for video_path in video_path_list:
                if os.path.isfile(video_path):
                    video_relpath = os.path.relpath(video_path, start=CONFIG['tmp_dir'])
                    f.write("file '{}'\n".format(video_relpath))
        params = [
            '-f', 'concat',
            '-safe', '-1',
            '-i', concat_list_path,
            '-c', 'copy',
            '-y',
            output_path
            ]
        self.exec(params)

