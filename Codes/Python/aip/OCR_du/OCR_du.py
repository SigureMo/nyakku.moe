import requests,base64,urllib,json,time,os,pickle,xlwt,re

#时间处理模块：
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
        body={'request_id':id,'result_type':'json'}
        tx=post('https://aip.baidubce.com/rest/2.0/solution/v1/form_ocr/get_request_result',body)
        print('解析进展：',tx.get('result').get('ret_msg'))
        if tx.get('result').get('ret_msg')=='已完成':
            json=tx.get('result').get('result_data')
            break
    return json



def json2xls(json,name):
    wb=xlwt.Workbook()
    j=json.get('forms')[0]
    headers=j.get('header')
    bodys=j.get('body')
    for header in headers:
        if header.get('word') in ['现金流量表','利润表','资产负债表']:
            sheetname=header.get('word')
            break
        else:
            sheetname='Temp'
    sheet=wb.add_sheet(sheetname)
    num_qian=re.compile(r'-?(\d{1,3},)?(\d{3},)*(\d{3})(.(\d+))?')
    num=re.compile(r'\d+(.(\d+))?$')
    try:
        for body in bodys:
            if num_qian.match(body.get('word')):
                n=num_qian.match(body.get('word')).group(0).replace(',','')
                sheet.write(body.get('row')[0],body.get('column')[0],eval(n))
            elif num.match(body.get('word')):
                n=num.match(body.get('word')).group(0)
                sheet.write(body.get('row')[0],body.get('column')[0],eval(n))
            else:
                sheet.write(body.get('row')[0],body.get('column')[0],body.get('word'))
        flag=True
    except:
        with open(name+'.dat','wb') as f:
            pickle.dump(json,f)
        flag=False
    finally:
        wb.save(name+'.xls')
        return flag

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
                json=up_to_baidu(name+exname)
                if json2xls(eval(json),name):
                    print('已成功保存'+name+'.xls，请在本文件夹内寻找')
                else:
                    print('保存'+name+'.xls时发生未知错误，请联系开发人员')
            else:
                print('文件{}已存在'.format(name+'.xls'))
    else:
        print('未检测到图片文件（jpg、jpeg、png、bmp）')

def check(password):#密码校验
    pd='****'
    while password!=pd:
        password=input('密码错误，请重新输入密码：')
        if password==pd:
            break
    print('欢迎使用OCR_du！')

def main():
    '''if not os.path.exists('log.txt'):
        loginit()'''
    password=input('请输入密码：')
    check(password)
    to_excel()
    input('Press <Enter>')

if __name__=='__main__':
    main()

