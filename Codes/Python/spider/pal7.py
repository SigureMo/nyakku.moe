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

def href(url):
    href=[]
    patch_extension=['.png','.jpg','.rar','.jpeg','.bmp','.zip']
    soup=BeautifulSoup(getHTMLText(url),'html.parser')
    for ex in patch_extension:
        href+=soup.find_all(href=re.compile(ex))
    return href

def src(url):
    src=[]
    patch_extension=['.png','.jpg','.rar']
    soup=BeautifulSoup(getHTMLText(url),'html.parser')
    for ex in patch_extension:
        src+=soup.find_all(src=re.compile(ex))
    return src

def save(root,url):
    #try:
    if not os.path.exists(root):
        os.mkdir(root)
    if not os.path.exists(root+url.split('/')[-1]):
        with open(root+url.split('/')[-1],'wb') as f:
            r=requests.get(url,headers={'user-agent':'Mozilla/5.0'},timeout=30)
            f.write(r.content)
            f.close()
            print('文件{}保存成功'.format(url.split('/')[-1]))
    else:
        print('文件{}已存在'.format(url.split('/')[-1]))
    #except:
        #print('爬取失败')

def pal7():
    url='https://pal7.cubejoy.com/index.html'
    root='E:/trashy/Pal7/'
    for h in href(url):
        save(root,'https://pal7.cubejoy.com/'+h.attrs['href'])
    for h in src(url):
        save(root,'https://pal7.cubejoy.com/'+h.attrs['src'])
    input('Press <Enter>')
    
pal7()
