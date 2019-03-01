import time
import os
import requests

"""
ref：https://www.cnblogs.com/HappyXie/archive/2012/02/03/python.html
tips：使用管理员权限打开
"""

def get_webservertime(host):
    res = requests.get(host)
    ts = res.headers.get('Date')
    # 将GMT时间转换成北京时间
    ltime = time.strptime(ts[5:25], "%d %b %Y %H:%M:%S")
    ttime = time.localtime(time.mktime(ltime) + 60*60*8)
    # 校准时间
    dat = "date %u-%02u-%02u"%(ttime.tm_year,ttime.tm_mon,ttime.tm_mday)
    tm = "time %02u:%02u:%02u"%(ttime.tm_hour,ttime.tm_min,ttime.tm_sec)
    status = not (os.system(dat) or os.system(tm))
    return status

if __name__ == '__main__':
    print('Successful' if get_webservertime('https://www.baidu.com') else 'Failed')
