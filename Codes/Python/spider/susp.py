import requests,bs4,re,os
from bs4 import BeautifulSoup
def getHTMLText(url):
    try:
        r=requests.get(url,headers={'user-agent':'Mozilla/5.0'},timeout=30)
        r.raise_for_status()
        r.encoding=r.apparent_encoding
        return r.text
    except:
        return ''

def save(root,url,extension):
    try:
        if not os.path.exists(root):
            os.mkdir(root)
        if not os.path.exists(root+url.split('/')[-1]+extension):
            with open(root+url.split('/')[-1]+extension,'wb') as f:
                r=requests.get(url,headers={'user-agent':'Mozilla/5.0'},timeout=30)
                f.write(r.content)
                f.close()
                print('文件{}保存成功'.format(url.split('/')[-1]+extension))
        else:
            print('文件{}已存在'.format(url.split('/')[-1]+extension))
    except:
        print('爬取失败')

def susp():
    url=input('请输入url：')
    root=input('请输入存放位置，默认桌面\\spshortcut：')
    if not root:
        root='C:/Users/asus/Desktop/spshortcut/'
    extension=input('请输入保存格式，若URL中存在可跳过：')
    save(root,url,extension)
    input('Press <Enter>')
    
susp()
