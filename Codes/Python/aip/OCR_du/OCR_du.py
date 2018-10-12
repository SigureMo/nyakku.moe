import requests,base64,urllib,json,time,os


def time_now():
    return time.strftime('%Y-%m-%d %H:%M:%S',time.localtime(time.time()))

#日志模块：
def log_add(str):
    with open('log.txt','a',encoding='utf-8',newline='\r\n') as f:
        f.write(str)

def log_read():
    with open('log.txt','r',encoding='utf-8',newline='\r\n') as f:
        for line in f:
            print(line,end='')
            
def loginit():
    with open('log.txt','w',encoding='utf-8',newline='\r\n') as f:
        f.write('OCR_du日志'.center(60,'-')+'\n')

def post(url,data):
    access_token ='?access_token=24.d9583ece260671202a9883e1b44af669.2592000.1528435724.282335-11211570'
    url+=access_token
    headers={'Content-Type':'application/x-www-form-urlencoded'}
    r=requests.post(url,headers=headers,data=data).content
    return json.loads(r)

def up_to_baidu(file):
    #提交
    f = open(file, 'rb')
    img = base64.b64encode(f.read())
    body = {"image": img}
    body = urllib.parse.urlencode({"image": img})
    tx=post('https://aip.baidubce.com/rest/2.0/solution/v1/form_ocr/request',body)
    if tx.get('result'):
        print('已成功发送到百度')
        id=tx.get('result')[0].get('request_id')
    else:
        print('发送失败')
        id=''
    #获取返回
    while True:
        time.sleep(5)
        body={'request_id':id}
        tx=post('https://aip.baidubce.com/rest/2.0/solution/v1/form_ocr/get_request_result',body)
        print('解析进展：',tx.get('result').get('ret_msg'))
        if tx.get('result').get('ret_msg')=='已完成':
            excel_url=tx.get('result').get('result_data')
            break
    return excel_url

    
def load(url,name):
    r=requests.get(url)
    with open(name+'.xls','wb') as f:
        f.write(r.content)
    
def find_image():
    names=[]
    images=['jpg','bmp','jpeg','png']
    for file in os.listdir('.'):
        if file.split('.')[-1] in images:
            names.append(('.'.join(file.split('.')[:-1]),\
                          '.'+file.split('.')[-1]))
    return names

def to_excel():
    names=find_image()
    if names:
        for file in names:
            name=file[0]
            exname=file[1]
            if not os.path.exists(name+'.xls'):
                print('已发现',name+exname,'准备提交……')
                url=up_to_baidu(name+exname)
                load(url,name)
                print('已成功保存'+name+'.xls，请在本文件夹内寻找')
                log_add('{} 成功转换{}\n{}\n'.format(time_now(),name+exname,url))
            else:
                print('文件{}已存在'.format(name+'.xls'))
    else:
        print('未检测到图片文件（jpg、jpeg、png、bmp）')
        

def check(password):#密码校验
    pa='1111'
    while password!=pa:
        password=input('密码错误，请重新输入密码：')
        if password==pa:
            break
    print('欢迎使用OCR_du！')

def main():
    if not os.path.exists('log.txt'):
        loginit()
    password=input('请输入密码：')
    check(password)
    to_excel()
    input('Press <Enter>')

if __name__=='__main__':
    main()


