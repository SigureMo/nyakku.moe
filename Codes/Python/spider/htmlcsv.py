import requests
from bs4 import BeautifulSoup
import io,sys
  
def getHTMLText(url):
    try:
        r=requests.get(url,headers={'user-agent':'Mozilla/5.0'},timeout=30)
        r.raise_for_status()
        return r.text
    except:
        return ''

def getlist(url):
    soup=BeautifulSoup(getHTMLText(url),'html.parser')
    tbody=soup.find_all('tbody')
    t=tbody[0]
    lines=t.find_all('tr')
    tt2=[]
    for line in lines:
        tt1=[]
        for s in line.find_all('span',attrs={"style":"font-size:medium"}):
            if s.string:
                tt1.append(s.string.replace(u'\xa0',u' '))
            else:
                tt1.append('')
            '''if s.string:
                print(s.string.center(20,chr(12288))+',',end='')
            else:
                print(chr(12288)*20+',',end='')
        print('')'''
        tt2.append(tt1)

    
    return tt2

def output(url):
    with open('0.csv','w',encoding='gb2312') as f:
        for i in getlist(url):
            if i:
                f.write(','.join(i))
            else:
                f.write(',')
            f.write('\n')

url='http://202.118.65.2/app/portals/newspage.html?id=72edd432-3871-4bdd-8f87-d8bca61210c6'
output(url)
