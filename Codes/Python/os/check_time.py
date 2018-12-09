"""
src：https://www.cnblogs.com/HappyXie/archive/2012/02/03/python.html
tips：使用管理员权限打开
"""

import http.client
import time
import os
def get_webservertime(host):
    conn=http.client.HTTPConnection(host)
    conn.request("GET", "/")
    r=conn.getresponse()
    #r.getheaders() #获取所有的http头
    ts=  r.getheader('date') #获取http头date部分
    #将GMT时间转换成北京时间
    ltime= time.strptime(ts[5:25], "%d %b %Y %H:%M:%S")
    ttime=time.localtime(time.mktime(ltime)+8*60*60)
    dat="date %u-%02u-%02u"%(ttime.tm_year,ttime.tm_mon,ttime.tm_mday)
    tm="time %02u:%02u:%02u"%(ttime.tm_hour,ttime.tm_min,ttime.tm_sec)
    status = not (os.system(dat) or os.system(tm))
    return status
    
print('successful' if get_webservertime('www.baidu.com') else 'failed')