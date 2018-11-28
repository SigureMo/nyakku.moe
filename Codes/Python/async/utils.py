# -*- coding: utf-8 -*-
"""核心程序组件"""

import re
import os
import asyncio
import aiohttp
import aiofiles
import json

SYS = os.name

class Coroutine(object):
    """协程控制器

    用来启动和控制协程
    """
    def __init__(self):
        self.todo = []
        try:
            import uvloop
        except ImportError as e:
            print("no install uvloop package")
        else:
            asyncio.set_event_loop_policy(uvloop.EventLoopPolicy())
        finally:
            self._loop = asyncio.get_event_loop()

    def __del__(self):
        """析构，销毁_loop"""
        self._loop.close()

    def get_loop(self):
        print(self._loop)

    def add_task(self, tasks):
        """添加协程多任务到todo"""
        if isinstance(tasks, dict):
            for task, num in tasks.items():
                self.todo.extend([task for i in range(num)])
        elif isinstance(tasks, list):
            self.todo.extend(tasks)
        else:
            self.todo.append(tasks)

    def set_task(self, task = None):
        """设置协程任务"""
        if task is None:
            self.task = asyncio.wait(self.todo)
            self.todo.clear()
        else:
            self.task = asyncio.ensure_future(task)

    def run(self):
        """启动协程"""
        self._loop.run_until_complete(self.task)

    def run_task(self, task):
        """放弃异步，以同步方式即时执行单件异步事件"""
        result = self._loop.run_until_complete(asyncio.ensure_future(task))
        return result
    

class Resource(object):
    """所有资源类的基类

    用来定义一个资源，但不同类型的资源可能要对部分功能进行重写。

    属性
        类
            regex_sort：匹配序号的正则表达式；
            regex_file：匹配 Windows 下文件名的非法字符；
            regex_spaces：匹配连续多个空白字符。
            type：资源的类型，默认是 'Resource'；

        id：资源的唯一标识，用于在程序中标识一个资源，如 '2.3.2'；
        name：资源的名称（可含有特殊字符），和最终的文件名有关；
        meta：资源的元信息，比如资源在每个网站的 ID 和文件名等等；
        feature：其他特征（基本用不到）。
    """

    regex_sort = re.compile(r'^[第一二三四五六七八九十\d]+[\s\d._\-章课节讲]*[.\s、\-]\s*\d*')
    regex_file = re.compile(r'[\\/:*?"<>|]')
    regex_spaces = re.compile(r'\s+')
    type = 'Resource'

    def __init__(self, identify, name, meta, feature=None):
        """将 name 的序号消除，并依次为属性赋值"""
        self.id = str(identify)
        self.name = Resource.regex_spaces.sub(' ', Resource.regex_sort.sub('', name)).strip()
        self.meta = meta
        self.feature = feature

    def __str__(self):
        """返回资源的名称"""

        return self.name

    @property
    def file_name(self):
        """动态生成文件名（包含前缀的 ID，不含扩展名），比如 '2.3.2 file_name'"""

        return self.id + ' ' + Resource.regex_file.sub('', self.name)

    async def operation(self, *funcs):
        """传入函数，使用函数对资源对象进行调用"""

        for func in funcs:
            if not callable(fun):
                raise
            try:
                await func(self)
            except TypeError:
                await asyncio.sleep(0.001)

    @staticmethod
    def file_to_save(name):
        """通过一个名字生成文件名"""

        return Resource.regex_file.sub('', Resource.regex_spaces.sub(' ', Resource.regex_sort.sub('', name)).strip())


### 异步的话 没必要 学学https://github.com/lateautunm/AshProduction/blob/master/jianshu/add_pageview.py
class Crawler():
    """ClientSession 类安全的二次封装

    扩展了 aiohttp 的 ClientSession 类。

    属性
        header：默认使用的浏览器头部。
    """

    header = {'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) '
                            'Chrome/68.0.3440.106 Safari/537.36'}

    def __init__(self, cookies = None):
        """初始化 Session，并更新头部"""

        self.cookies = cookies
        asyncio.ensure_future(self._get_session())

    async def _get_session(self):
        self.session = ClientSession(
            connector=aiohttp.TCPConnector(ssl=False),
            headers = Crawler().header,
            cookies = cookies,
            )

    def set_cookies(self, cookies):
        """传入一个字典，用于设置 cookies"""
        
        self.cookies = cookies

    async def get(self, url, **kw):
        async with aiohttp.ClientSession(
            connector=aiohttp.TCPConnector(ssl=False),
            headers = Crawler().header,
            cookies = self.cookies,
            ) as session:
            return session.get(url, **kw)

    async def post(self, url, **kw):
        async with aiohttp.ClientSession(
            connector=aiohttp.TCPConnector(ssl=False),
            headers = Crawler().header,
            cookies = self.cookies,
            ) as session:
            return session.post(url, **kw)

    async def download_bin(self, url, file_name, **kw):
        """下载二进制文件"""

        async with self.get(url, **kw) as res:
            content = await res.read()
            async with aiofiles.open(file_name, 'wb') as f:
                await f.write(content)

    async def download(self, url, file_name, **kw):
        """下载文件为 UTF-8 编码"""

        async with self.get(url, **kw) as res:
            text = await res.text()
            async with aiofiles.open(file_name, 'w', encoding='utf_8') as f:
                await f.write(text)



