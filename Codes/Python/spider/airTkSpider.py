import requests
import re
import time
import random

from urllib import parse
from smtp import SMTP

class AirTkSpider():
    def __init__(self, departureCity, arrivalCity):
        self.departureCity = parse.quote(departureCity.encode())
        self.arrivalCity = parse.quote(arrivalCity.encode())

    def getMinPrice(self):
        start_date = '2019-01-11'
        pris = []
        url = 'https://lp.flight.qunar.com/api/lp_calendar?dep={}&arr={}&dep_date={}&adultCount=1&month_lp=1&tax_incl=0&direct=0'.format(self.departureCity, self.arrivalCity, start_date)
        banners = requests.get(url).json().get('data').get('banner')
        for banner in banners:
            if banner.get('price') and banner.get('price') != 9999999:
                pris.append((banner.get('depDate'), banner.get('price')))
        return pris

    def touch(self):
        for price in self.getMinPrice():
            if 10 < int(price[0][-2:]) < 20 and price[1] < 300:
                return price

if __name__ == '__main__':
    qd = AirTkSpider('青岛', '大连')
    smtp = SMTP('163')
    smtp.login_('sigure_mo@163.com', '********')
    while True:
        try:
            price = qd.touch()
            if price:
                info = '发现低于300的票价！去哪儿网！{}！{}！'.format(price[0], price[1])
                print(info)
                smtp.send_text('aaaaaaa@qq.com', info, '您有新的去哪儿网订单啦！')
            else:
                print(time.strftime('%Y-%m-%d %H:%M:%S', time.localtime()))
        except:
            info = '程序崩溃！'
            print(info)
            smtp.send_text('bbbbbbb@qq.com', info)
        time.sleep(random.randint(10, 100))
