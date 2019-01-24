import time


class Task():
    """任务对象"""

    def __init__(self, action, args=()):
        """接受函数与参数以初始化对象"""

        self.action = (action, args)

    def run(self):
        """函数 action 不得返回 None"""

        result = self.action[0](*self.action[1])
        status = result is not None
        return result, status

    def then(self, task):
        """
        self.run, return task
        Sample：
            task1.then(task2).then(task3).run()
        """

        result, status = self.run()
        if status:
            return task

class Loop():
    """循环对象"""

    def __init__(self, interval):
        """初始化并设间隔时间"""
        self.interval = interval
        self.task_lists = []

    def add_task_list(self, *task_list):
        """添加一个依次运行的任务列表
        同一列表的前驱任务不返回 None 才可以执行后继函数
        不同列表互不影响
        """

        self.task_lists.append(task_list)

    def run(self):
        """执行所有任务"""

        while True:
            for task_list in self.task_lists:
                for task in task_list:
                    result, status = task.run()
                    if not status:
                        break
            time.sleep(self.interval)
