import requests
import subprocess
import json
import time
import os

from urllib.request import urlopen

rpc_url = "http://localhost:{port}/jsonrpc"


class Aria2():
    """ Aria2 RPC 接口调用器
    完整接口见（简单封装即可）：
    http://aria2.github.io/manual/en/html/aria2c.html#rpc-interface
    """

    def __init__(self, aria2_path="aria2c", port=6800):
        self.port = port
        self.rpc_url = rpc_url.format(port=port)
        self.aria2_path = aria2_path
        self.process_file = open("process.out", "w")
        assert self.is_installed(), "请配置正确的 aria2 路径"
        if not self.is_connected():
            self.process = self.init_rpc()
            # 防止操作过快导致 aria2 没来得及开启
            time.sleep(1)

    def __del__(self):
        """ 析构时确保 aria2 关闭 """
        if self.is_connected():
            self.shutdown()
        self.process_file.close()
        try:
            os.remove(self.process_file.name)
        except:
            print("process.out 自动删除失败……")

    def rpc_api(method):
        """ RPC 装饰器 """
        def rpc_method(func):
            def new_func(self, *args):
                data = {
                    'jsonrpc': '2.0',
                    'id': 'qwer',
                    'method': method,
                    'params': list(filter(lambda arg: arg is not None, args)),
                }
                res = requests.post(
                    self.rpc_url, data=json.dumps(data), timeout=2)
                return res.json()["result"]
            return new_func
        return rpc_method

    @rpc_api(method="aria2.addUri")
    def add_uri(self, uris, options=None, position=None):
        """ 添加 URI 任务 """
        pass

    @rpc_api(method="aria2.getGlobalStat")
    def get_global_stat(self):
        """ 获取全局统计信息 """
        pass

    @rpc_api(method="aria2.shutdown")
    def shutdown(self):
        """ 关闭 aria2 """
        pass

    @rpc_api(method="aria2.tellStatus")
    def tell_status(self, gid, keys=None):
        """ 获取某一下载资源的状态信息 """
        pass

    def init_rpc(self):
        """ 启动 aria2 RPC """
        cmd = self.aria2_path + \
            ' --enable-rpc' \
            ' --rpc-listen-port %d' \
            ' --continue' \
            ' --max-concurrent-downloads=20' \
            ' --max-connection-per-server=10' \
            ' --rpc-max-request-size=1024M' % self.port

        return subprocess.Popen(cmd, shell=True, stdout=self.process_file)

    def is_connected(self):
        """ 是否可以连接 aria2 """
        try:
            requests.post(self.rpc_url)
            return True
        except requests.exceptions.ConnectionError:
            return False

    def is_installed(self):
        """ 是否已经下载 aria2 """
        try:
            return subprocess.run([self.aria2_path], stdout=subprocess.PIPE,
                                  stderr=subprocess.PIPE).returncode == 1
        except FileNotFoundError:
            return False


class Aria2File():

    def __init__(self, aria2, url, file_name, dir, overwrite=False):
        self.aria2 = aria2
        self.path = os.path.join(dir, file_name)
        self.tmp_path = self.path + ".t"
        self.aria2_file = self.tmp_path + ".aria2"
        if overwrite and os.path.exists(self.tmp_path):
            os.remove(self.tmp_path)
        if overwrite and os.path.exists(self.aria2_file):
            os.remove(self.aria2_file)
        self.gid = aria2.add_uri([url], {"dir": dir, "out": file_name+".t"})

    def get_length(self):
        """ 获取总大小 """
        length = int(self.aria2.tell_status(self.gid)["totalLength"])
        cnt = 0
        while length == 0:
            time.sleep(0.1)
            length = int(self.aria2.tell_status(self.gid)["totalLength"])
            if cnt == 5:
                break
        return length

    def get_complete_length(self):
        """ 获取已完成部分大小 """
        return int(self.aria2.tell_status(self.gid)["completedLength"])

    def get_status(self):
        """ 获取状态 """
        return self.aria2.tell_status(self.gid)["status"]

    def get_speed(self):
        """ 获取下载速度 """
        return int(self.aria2.tell_status(self.gid)["downloadSpeed"])

    def exists(self):
        """ 文件是否已存在 """
        return os.path.exists(self.path)

    def rename(self):
        """ 将文件从临时位置移动到目标位置 """
        if os.path.exists(self.path):
            with open(self.tmp_path, "rb") as fr:
                with open(self.path, "wb") as fw:
                    fw.write(fr.read())
            os.remove(self.tmp_path)
        else:
            os.rename(self.tmp_path, self.path)

