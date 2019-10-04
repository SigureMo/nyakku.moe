import requests
import threading
import time
import queue

from urllib import parse

class ChatEngine():
    def __init__(self, pub_key, sub_key, sep = ''):
        self.pub_key = pub_key
        self.sub_key = sub_key
        self.queue = queue.Queue()
        self.sep = sep
        self.format = '{time}\n{mode}:{nickName}{sep}{message}'
        self.session = requests.Session()

    def set_channel(self, channel):
        self.channel = channel

    def set_sep(self, sep):
        self.sep = sep

    def message_loop(self, print_res=False, log = False, ignore = None):
        timetoken = 0
        while True:
            msgs, timetoken = self.subscribe(timetoken)
            if msgs:
                for msg in msgs:
                    self.queue.put(msg)
                    if self.sep in msg:
                        nickName, msg = msg.split(self.sep)
                    else:
                        nickName = 'Manager'
                    if nickName == ignore:
                        continue
                    if print_res:
                        print(self.format.format(
                            time = time.strftime("%y-%m-%d %H:%M:%S", time.localtime()),
                            mode = 'Result',
                            nickName = nickName,
                            sep = self.sep,
                            message = msg,
                            )
                              )
                    if log:
                        with open('log.csv', 'a', encoding = 'utf8', newline = '\r\n') as f:
                            f.write(','.join([time.strftime("%y-%m-%d %H:%M:%S", time.localtime()), nickName, msg]) + '\n')

    def publish(self, msg):
        signature = 0
        callback = 0
        message = parse.quote(msg.encode())
        url = 'http://pubsub.pubnub.com/publish/{}/{}/{}/{}/{}/"{}"'.format(self.pub_key, self.sub_key, signature, self.channel, callback, message)
        try:
            res = self.session.get(url).json()
            assert res[0] == 1
        except:
            res = {}
        return res

    def subscribe(self, timetoken = 0):
        callback = 0
        url = 'http://pubsub.pubnub.com/subscribe/{}/{}/{}/{}'.format(self.sub_key, self.channel, callback, timetoken)
        try:
            res = self.session.get(url, timeout=10).json()
        except:
            res = [[], timetoken]
        return res

    def history(self):
        callback = 0
        limit = 10
        url = 'http://pubsub.pubnub.com/history/{}/{}/{}/{}'.format(self.sub_key, self.channel, callback, limit)
        try:
            res = self.session.get(url).json()
        except:
            res = []
        return res

if __name__ == '__main__':
    pub_key = 'pub-c-d899e684-d620-4ba5-843c-8e7589819236'
    sub_key = 'sub-c-c2e24f18-db8c-11e8-957e-be7a2fcdb3b6'
    channel = "Miao"
    sep = '+said:+'
    nickName = input('nickName:')
    chatEngine = ChatEngine(pub_key, sub_key)
    chatEngine.set_channel(channel)
    chatEngine.set_sep(sep)
    messager = threading.Thread(target=chatEngine.message_loop, args=(True, False, nickName))
    messager.setDaemon(True)
    messager.start()
    while True:
        t = time.strftime("%y-%m-%d %H:%M:%S", time.localtime())
        code, status, timetoken = chatEngine.publish(nickName + chatEngine.sep + input('{}\nSend:'.format(t)))
        time.sleep(0.2)
