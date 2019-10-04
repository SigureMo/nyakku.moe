import requests
import re
import time
import random

from urllib import parse


class Qunar():
    def __init__(self, departureCity, arrivalCity):
        self.departureCity = parse.quote(departureCity.encode())
        self.arrivalCity = parse.quote(arrivalCity.encode())

    def get_min_price(self):
        start_date = time.strftime("%Y-%m-%d", time.localtime())
        pris = {}
        url = 'https://lp.flight.qunar.com/api/lp_calendar?dep={}&arr={}&dep_date={}&adultCount=1&month_lp=1'.format(
            self.departureCity, self.arrivalCity, start_date)
        banners = requests.get(url).json().get('data').get('banner')
        for banner in banners:
            if banner.get('price') and banner.get('price') != 9999999:
                pris[banner.get('depDate')] = banner.get('price')
        return pris


class Ctrip():
    def __init__(self, departureCity, arrivalCity):
        self.departureCity = departureCity
        self.arrivalCity = arrivalCity

    def get_min_price(self):
        data = {
            "acity": self.arrivalCity,
            "dcity": self.departureCity,
            "flightWay": "Oneway"
        }
        res = requests.post(
            "https://flights.ctrip.com/itinerary/api/12808/lowestPrice", data=data)
        return res.json()["data"]["oneWayPrice"][0]


if __name__ == '__main__':
    qunar = Qunar('青岛', '大连')
    print(qunar.get_min_price())
    ctrip = Ctrip("TAO", "DLC")
    print(ctrip.get_min_price())
