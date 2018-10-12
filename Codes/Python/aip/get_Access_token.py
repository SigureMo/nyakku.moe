import requests

# client_id 为官网获取的AK， client_secret 为官网获取的SK
host = 'https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id=zS***fdGC&client_secret=kT3A****KWfb4sV'


h={'Content-Type': 'application/json; charset=UTF-8'}

content = requests.post(host,headers=h).content
if (content):
    print(content)
