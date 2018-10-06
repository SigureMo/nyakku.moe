import requests,bs4,sys,random,time,re
from bs4 import BeautifulSoup
from multiprocessing import Process
def getHTMLText(url):
    try:
        r=requests.get(url,headers={'user-agent':'Mozilla/5.0'},timeout=30)
        r.raise_for_status()
        non_bmp_map = dict.fromkeys(range(0x10000, sys.maxunicode + 1), 0xfffd)
        return r.text.translate(non_bmp_map)
    except:
        return ''

def post(url):
    soup=BeautifulSoup(getHTMLText(url)[20000:190000],'html.parser')
    ul=soup.find_all('ul',attrs={'id': 'thread_list', 'class': ['threadlist_bright', 'j_threadlist_bright']})
    lis=[]
    if not len(ul):
        print('未抓取到ul')
        return []
    for li in ul[0].children:
        if isinstance(li,bs4.element.Tag):
            lis.append(li)
    newtheme=[]
    tis=[]
    tiss=[]
    for them in lis:
        tis+=them.find_all('a',attrs={'class':['j_th_tit',''],'href':re.compile(r'^/p/5')})
    for t in tis:
        if t.attrs.get('href'):
            newtheme.append(t.attrs.get('title'))
    return newtheme

def advertising(url):
    k=0
    l=['变态','BT','自动返还','百度一下','玩一玩','出号','卖号','最低3折','破解']
    ads=[]
    for title in post(url):
        for adword in l:
            if adword in title:
                ads.append(title)
    return ads

def capture(url):
    ads=advertising(url)
    if len(ads)>0:
        print('已检测到有以下{}个疑似问题主题：'.format(len(ads)))
        for i in ads:
            print(i)
        print('请尽快处理！')

def monitoring(url):
    i=1
    while True:
        time.sleep(random.randint(6, 10))
        print('第{}次爬取：'.format(i))
        capture(url)
        print('')
        i+=1

def tieba():
    url="https://tieba.baidu.com/f?kw=%CF%C9%BD%A3%C6%E6%CF%C0%B4%AB%BB%C3%C1%A7%BE%B5"
    a=True
    while a:
        a=input('''请选择您需要的操作：
1.列出最近的主题
2.最近有问题帖子
3.实时监控问题帖子（暂时不能进行其他操作）
0.返回上一级

''')
        if a=='1' or a=='ls':
            for i in post(url):
                print(i)
        elif a=='2' or a=='ad':
            capture(url)
        elif a=='3' or a=='del_type':
            monitoring(url)
            #p1=Process(target=monitoring,args=(getHTMLText(url)[32500:170000],))
            #p2=Process(target=spider)
            #p2.start()
            #p1.start()
        elif a=='0' or not a or a=='exit()':
            break
        else:
            print('输入错误，无法处理！')
        print('')


def spider():
    a=True
    while a:
        a=input('''请选择您需要的操作：
1.贴吧信息爬取
2.简单百度搜索（尚不可用）
本模块暂时未开发，且仅为试用版
0.返回上一级

''')
        if a=='1' or a=='ls':
            tieba()
        elif a=='0' or not a or a=='exit()':
            break
        else:
            print('输入错误，无法处理！')
        print('')



if __name__=='__main__':
    spider()
    

#post(url="https://tieba.baidu.com/f?kw=%CF%C9%BD%A3%C6%E6%CF%C0%B4%AB%BB%C3%C1%A7%BE%B5")
