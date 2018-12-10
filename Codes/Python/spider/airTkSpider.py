import requests #导入模块，它是做压缩和解压缩的
import json
import re
import pickle
import smtplib
import time

from urllib import parse
from bs4 import BeautifulSoup
from email import encoders
from email.header import Header
from email.mime.text import MIMEText
from email.utils import parseaddr, formataddr

class AirTkSpider():
    def __init__(self, departureCity, arrivalCity):
        self.departureCity = parse.quote( departureCity.encode())
        self.arrivalCity = parse.quote( arrivalCity.encode())

    def getMinPrice(self):
        ms = ['07', '08']
        pris = []
        for m in ms:
            url = 'https://lp.flight.qunar.com/api/lp_calendar?dep={}&arr={}&dep_date=2018-{}-01&adultCount=1&month_lp=1&tax_incl=0&direct=0'.format(self.departureCity, self.arrivalCity, m)
            banners = requests.get(url).json().get('data').get('banner')
            for banner in banners:
                if banner.get('price') and banner.get('price') != 9999999:
                    pris.append((banner.get('depDate'), banner.get('price')))
        return pris[:15]

    def remind(self):
        pris = self.getMinPrice()
        minPri = min(list(map(lambda x:x[1],pris)))
        try:
            with open('data/minTer.dat', 'rb') as f:
                pastMinPri = pickle.load(f)
        except:
            with open('data/minTer.dat', 'wb') as f:
                pastMinPri = minPri
                pickle.dump(pastMinPri, f)
        if minPri < pastMinPri:
            date = pris[list(map(lambda x:x[1],pris)).index(minPri)][0]
            s = '出现最低价{},在{}'.format(minPri, date)
            smtp_send('最近15天机票出现最低价', s)
            print(s)
        with open('data/minTer.dat', 'wb') as f:
            pickle.dump(minPri, f)

#smtp
def _format_addr(s):
    name, addr = parseaddr(s)
    return formataddr((Header(name, 'utf-8').encode(), addr))

def smtp_send(h,s):
    from_addr = 'sigure_mo@163.com'
    password = 'xxxxxx'
    to_addr = 'xxx'
    smtp_server = 'smtp.163.com'
    msg = MIMEText(s, 'plain', 'utf-8')
    msg['From'] = _format_addr('AirTkSpider <%s>' % from_addr)
    msg['To'] = _format_addr('Nuage <%s>' % to_addr)
    msg['Subject'] = Header(h, 'utf-8').encode()
    server = smtplib.SMTP(smtp_server, 25)
    server.set_debuglevel(1)
    server.login(from_addr, password)
    server.sendmail(from_addr, [to_addr], msg.as_string())
    server.quit()


if __name__ == '__main__':
    qd = AirTkSpider('青岛', '大连')
    while True:
        qd.remind()
        time.sleep(60)
    '''
    while True:
        qd = AirTkSpider('青岛', '大连')
        pris = qd.getMinPrice()
        t = time.strftime('%Y-%m-%d %H:%M:%S',time.localtime(time.time()))
        try:
            with open('data/statistics.csv', 'r') as f:
                l = 0
                dats = []
                for line in f:
                    if l == 0:
                        header = line.replace('\n', '').split(',')
                    else:
                        dats.append(line.replace('\n', '').split(','))
                    l += 1
        except IOError:
            header = list(map(lambda x:x[0], pris))[:-1]
            dats = [list(range(14))]
        newHeader = list(map(lambda x:x[0], pris))
        if ['']+newHeader != header:
            header.append(newHeader[-1])
            for i in range(len(dats)):
                dats[i] = dats[i] + ['']
            dats.append([t, ''] + list(map(lambda x:x[1], pris)))
        else:
            dats.append([t] + list(map(lambda x:x[1], pris)))
        data = [header] + dats
        with open('data/statistics.csv', 'w') as f:
            s = ''
            for i in data:
                s += ','.join(list(map(lambda x:str(x), i)))+'\n'
            f.write(s)
        time.sleep(60*15)
        '''
        
            
