import requests
import os
import threading
import time

from chatEngine import ChatEngine
from turing import Turing

def bot_response(chatEngine, bot, queue):
    while True:
        if not queue.empty():
            msg = queue.get()
            if '@' + bot.name not in msg:
                continue
            if chatEngine.sep in msg:
                nickName, msg = msg.split(chatEngine.sep)
                userId = ''
                for i in nickName:
                    userId += str(ord(i))
                bot.set_userId(str(int(userId) % 100))
            res = bot.send_text(msg.replace('@' + bot.name, ''))
            if res['intent']['code']:
                for result in res['results']:
                    if result['resultType'] == 'text':
                        chatEngine.publish(bot.name + chatEngine.sep + result['values']['text'])
                    elif result['resultType'] == 'url':
                        chatEngine.publish(bot.name + chatEngine.sep + result['values']['url'])

apikey = '55592cf090974e4f906e3311605e8873'
pub_key = 'pub-c-d899e684-d620-4ba5-843c-8e7589819236'
sub_key = 'sub-c-c2e24f18-db8c-11e8-957e-be7a2fcdb3b6'
channel = "Miao"
sep = '+said:+'
chatEngine = ChatEngine(pub_key, sub_key)
chatEngine.set_channel(channel)
chatEngine.set_sep(sep)
messager = threading.Thread(target=chatEngine.message_loop, args = (True, True))
messager.setDaemon(True)
messager.start()
mybot = Turing(apikey)
bot_response(chatEngine, mybot, chatEngine.queue)
