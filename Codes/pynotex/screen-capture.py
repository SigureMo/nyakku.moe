import threading
import tkinter as tk

import numpy as np
from cv2 import cv2
from PIL import ImageGrab


"""
ref: https://blog.csdn.net/zzzzjh/article/details/80903597
"""

class ScreenCapture(threading.Thread):

    def __init__(self, out_file, fps=24, size=None):
        threading.Thread.__init__(self)
        self.out_file = out_file
        self.fps = fps
        self.size = size
        self.time = None
        self.setDaemon(True)
        self.__flag = threading.Event()
        self.__flag.set()
        self.__running = threading.Event()
        self.__running.set()

    def run(self):
        """ 录屏线程启动 """
        print("录屏开始")
        p = ImageGrab.grab()
        size = p.size if self.size is None else self.size
        fourcc = cv2.VideoWriter_fourcc(*'XVID')
        video = cv2.VideoWriter(out_file, fourcc, self.fps, size)
        while self.__running.isSet():
            self.__flag.wait()
            im = ImageGrab.grab()
            im = cv2.cvtColor(np.array(im), cv2.COLOR_RGB2BGR)
            video.write(im)
        print("录屏结束")
        video.release()
        cv2.destroyAllWindows()

    def pause(self):
        """ 暂停 """
        self.__flag.clear()

    def resume(self):
        """ 继续 """
        self.__flag.set()

    def stop(self):
        """ 停止 """
        self.__flag.set()
        self.__running.clear()

    @property
    def paused(self):
        """ 返回是否暂停 """
        return not self.__flag.isSet()

class GUI():

    def __init__(self, screen_capture):
        self.__screen_capture = screen_capture
        self.__init_window()

    def __init_window(self):
        """ 初始化界面 """
        win = tk.Tk()
        win.title("Python 录屏")
        frame = tk.LabelFrame(win, height=200, width=300, text='录屏选项')
        frame.pack(side='top', fill='both', expand=True)
        self.button_start = tk.Button(frame, text="开始", command=self.start)
        self.button_start.grid(row=0, column=0)
        self.button_pause = tk.Button(frame, text="暂停", command=self.pause)
        self.button_pause.grid(row=0, column=1)
        self.button_stop = tk.Button(frame, text="停止", command=self.stop)
        self.button_stop.grid(row=0, column=2)
        win.mainloop()

    def start(self):
        self.__screen_capture.start()

    def pause(self):
        if self.__screen_capture.paused:
            self.button_pause["text"] = "暂停"
            self.__screen_capture.resume()
        else:
            self.button_pause["text"] = "继续"
            self.__screen_capture.pause()

    def stop(self):
        self.__screen_capture.stop()

    def __del__(self):
        self.__screen_capture.stop()


if __name__ == '__main__':
    fps = 24
    out_file = "tmp/test.mp4"
    screen_capture = ScreenCapture(out_file, fps)
    gui = GUI(screen_capture)
