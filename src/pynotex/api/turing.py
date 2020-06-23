import requests
import threading
import time
import copy
import json

from urllib import parse

class Turing():
    def __init__(self, apikey, name = 'QBot', userId = 'QBot'):
        self.url = 'http://openapi.tuling123.com/openapi/api/v2'
        self.data = {}
        self.name = name
        self.session = requests.Session()
        self.data['perception'] = {}
        self.data['userInfo'] = {
            'userId': userId,
            'apiKey': apikey,
            }

    def send_text(self, msg):
        data = copy.deepcopy(self.data)
        data['reqType'] = 0
        data['perception']['inputText'] = {'text': msg}
        headers = {'Content-Type': 'application/json'}
        res = self.session.post(self.url, data = json.dumps(data).encode('utf8'), headers = headers).json()
        return res

    def set_city(self, city, province='', street=''):
        self.data['perception']['selfInfo'] = {
            'location': {
                'city': city,
                'province': province,
                'street': street,
                }
            }

    def set_userId(self, userId):
        self.data['userInfo']['userId'] = userId

if __name__ == '__main__':
    apikey = '55592cf090974e4f906e3311605e8873'
    mybot = Turing(apikey)
    print(mybot.send_text('你好'))
