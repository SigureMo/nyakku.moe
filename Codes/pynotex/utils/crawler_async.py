import asyncio
import aiohttp
import aiofiles


class ExecuteError(Exception):
    def __init__(self, message):
        self.message = message

class Coroutine(object):
    """协程控制器

    用来启动和控制协程
    """
    def __init__(self):
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

    def set_task(self, todo):
        """设置协程任务"""
        if isinstance(todo, list):
            self.task = asyncio.wait(todo)
        else:
            self.task = asyncio.ensure_future(todo)

    def run(self):
        """启动协程"""
        self._loop.run_until_complete(self.task)

    def sync(self, todo):
        """放弃异步，以同步方式即时执行单件异步事件"""
        result = self._loop.run_until_complete(asyncio.ensure_future(todo))
        return result

async def Crawler_async(*funcs, **kw):
    """用于执行爬虫任务"""

    header = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/71.0.3578.98 Safari/537.36',
    }
    session = aiohttp.ClientSession(
        connector = aiohttp.TCPConnector(ssl=False),
        headers = kw.get('headers', header),
        cookies = kw.get('cookies', {}),
        )
    for func, args in funcs:
        try:
            await execute(func, (session, *args))
        except ExecuteError as e:
            print(e.message)
    await session.close()

async def download_bin(session, url, file_name, **kw):
    """下载二进制文件"""

    if kw.pop('stream', True):
        chunk_size = kw.pop('chunk_size', 1024)
        async with session.get(url, **kw) as res:
            async with aiofiles.open(file_name, 'wb') as f:
                while True:
                    chunk = await res.content.read(chunk_size)
                    if not chunk:
                        break
                    await f.write(chunk)

    else:
        async with session.get(url, **kw) as res:
            content = await res.read()
            async with aiofiles.open(file_name, 'wb') as f:
                await f.write(content)

async def download_text(session, url, file_name, **kw):
    """下载文本，以 UTF-8 编码保存文件"""

    async with session.get(url, **kw) as res:
        text = await res.text()
        async with aiofiles.open(file_name, 'w', encoding='utf_8') as f:
            await f.write(text)

async def execute(func, args=()):
    """在异步方法下，无论同步还是异步函数都可以执行"""

    if not callable(func):
        raise ExecuteError('{} is not a function'.format(func))
    try:
        await func(*args)
    except TypeError:
        await asyncio.sleep(0.001)

if __name__ == '__main__':
    coroutine = Coroutine()
    coroutine.set_task([
        Crawler_async(
            (download_text, ('https://www.baidu.com', 'tmp/tmp0.html')),
            (download_bin, ('https://www.baidu.com', 'tmp/tmp1.html'))
        ),
    ])
    coroutine.run()
