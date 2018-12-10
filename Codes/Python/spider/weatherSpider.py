import requests #导入模块，它是做压缩和解压缩的
import json
import re

from urllib import parse
from bs4 import BeautifulSoup
def getHTMLText(url):
    try:
        r=requests.get(url,headers={'user-agent':'Mozilla/5.0'},timeout=30)
        r.raise_for_status()
        r.encoding = 'utf8'
        return r.text
    except:
        return ''


class weatherSpider():
    def __init__(self, cityName):
        self.cityName = cityName
        self.cid = ''
        self.weather = []
        try:
            with open('data/pastFew.json','rb') as f:
                self.pastFew = json.loads(f.read().decode())
        except:
            with open('data/pastFew.json','wb') as f:
                self.pastFew = []
                f.write(json.dumps(self.pastFew).encode())
        
    def getCid(self):
        url = 'http://toy1.weather.com.cn/search?cityname={}&callback=success_jsonpCallback&_=1532249672207'\
              .format( parse.quote( self.cityName.encode()))
        response = requests.get(url)
        self.cid = re.search('\"ref\":\"(?P<cid>\d+)', response.content.decode()).group('cid')

    def getWeather(self):
        self.getCid()
        response = getHTMLText('http://www.weather.com.cn/weather/{}.shtml'.format(self.cid))
        soup=BeautifulSoup(response,'html.parser')
        c7d = soup.find('div', id='7d')
        c7dInfo = c7d.find('ul', class_='clearfix')
        days = c7dInfo.find_all('li')
        print(c7dInfo)
        for day in days:
            date = day.find('h1').string
            wea = day.find('p', class_='wea').string
            tem = day.find('p', class_='tem')
            try:
                temMax = int(tem.find('span').string.replace('℃',''))
            except:
                temMax = 99
            print(temMax)
            temMin = int(tem.find('i').string.replace('℃',''))
            win = day.find('p', class_='win')
            winDir = list(map(lambda x:x.attrs.get('title'), win.find_all('span')))
            winSca = win.find('i').string.split('转')
            if len(winSca) == 1:
                winSca += winSca
            if len(winDir) == 1:
                winDir += winDir
            if winDir[0] == winDir[1] and winSca[0] == winSca[1]:
                wind = winDir[0] + winSca[0]
            else:
                wind = winDir[0] + winSca[0] + '转' + winDir[1] + winSca[1]
            self.weather.append((date, wea, temMax, temMin, wind))
        if len(self.pastFew) <= 2:
            self.pastFew.append(list(self.weather[0][2:4]))
        else:
            self.pastFew = self.pastFew[1:] + [list(self.weather[0][2:4])]
        with open('data/pastFew.json','wb') as f:
            f.write(json.dumps(self.pastFew).encode())

    def analyze(self, offset=0):
        s = []
        self.getWeather()
        todayWeather = self.weather[0+offset]
        todayM = todayWeather[2]
        todaym = todayWeather[3]
        M = 0
        m = 0
        for dayTem in self.pastFew:
            M += dayTem[0]/len(self.pastFew)
            m += dayTem[1]/len(self.pastFew)
        if M >= 25 and todayM - M >= 3:
            s.append('升温')
        elif M <= 15 and todaym - m >= 3:
            if todaym - m >= 7:
                s.append('气温骤降，注意保暖')
            else:
                s.append('降温，注意保暖')
        if int(re.search('\d+', todayWeather[4]).group(0)) >= 5:
            s.append('风大，注意安全')
        s = todayWeather[0]+':'+todayWeather[1]+','+\
            '最高气温'+str(todayWeather[2])+'℃'+','+\
            '最低气温'+str(todayWeather[3])+'℃'+','+\
            todayWeather[4]+'\n'\
            ','.join(s)
        return s
            
if __name__ == '__main__':
    url = 'http://www.weather.com.cn/weather/101070201.shtml'
    cs = weatherSpider('长沙')
    #cs.getWeather()
    print(cs.analyze(1))
    #print(getHTMLText(url))
    input('press')
