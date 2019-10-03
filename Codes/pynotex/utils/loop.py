import time

from async_lib.utils import Task


class Loop():
    """循环对象"""

    def __init__(self, interval):
        """初始化并设间隔时间"""

        self.interval = interval
        self.events = []

    def on(self, task, action):
        self.events.append((task, action))

    def run(self):
        """执行所有任务"""

        while True:
            for task, action in self.events:
                if task.run():
                    action.run()
            time.sleep(self.interval)
