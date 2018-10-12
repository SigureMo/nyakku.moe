import requests,base64,urllib,json,time,os,pickle,xlwt,re
from PIL import Image
from PIL import ImageEnhance

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
    access_token ={'access_token':'24.d9583ece260671202a9883e1b44af669.2592000.1528435724.282335-11211570'}
    headers={'Content-Type':'application/x-www-form-urlencoded'}
    r=requests.post(url,params=access_token,headers=headers,data=data).content
    return json.loads(r)

def up_to_baidu(file):
    #提交
    f = open(file, 'rb')
    img = base64.b64encode(f.read())
    body = {"image": img,'detect_direction': True}#增加自动检测图片朝向
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
    with open(temp+os.sep+name+'.dat','wb') as f:
        pickle.dump(json,f)
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
    num_qian=re.compile(r'-?([1-9]\d{0,2})(,\d{3})*(\.(\d+))?$')
    num=re.compile(r'-?(([1-9]\d*)|0)(\.(\d+))?$')
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
        flag=False
    finally:
        wb.save(xlsOutput+os.sep+name+'.xls')
        return flag

def find_image():
    names=[]
    images=['jpg','bmp','jpeg','png']
    for file in os.listdir(imageInput):
        if file.split('.')[-1] in images:
            names.append(('.'.join(file.split('.')[:-1]),\
                          '.'+file.split('.')[-1]))
    return names


def to_excel(enhance):
    names=find_image()
    if names:
        for file in names:
            name=file[0]
            exname=file[1]
            if not os.path.exists(xlsOutput+os.sep+name+'.xls'):
                print('已发现',name+exname,'开始审核……')
                if not image_check(file):
                    continue
                print('审核完毕，',end='')
                if enhance:
                    print('开始增强处理……')
                    if image_enhance(file):
                        json=up_to_baidu(temp+os.sep+name+'_en.jpg')
                    else:
                        json=up_to_baidu(temp+os.sep+name+exname)
                else:
                    print('准备提交……')
                    json=up_to_baidu(temp+os.sep+name+exname)
                if json2xls(eval(json),name):
                    print('已成功保存'+name+'.xls，请在{}内寻找'.format(xlsOutput))
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

def image_check(file):
    try:
        im=Image.open(imageInput+os.sep+file[0]+file[1])
        if os.path.getsize(imageInput+os.sep+file[0]+file[1])>4*1024*1024:
            print('图像数据量过大，正在处理……')
            while os.path.getsize(imageInput+os.sep+file[0]+file[1])>4*1024*1024:
                im.resize(int(im.size[0]/2),int(im.size[1]/2))
            print('处理完毕')
        if im.size[0]<15 or im.size[1]<15 or \
           im.size[0]>4096 or im.size[1]>4096:
            print('图片大小不符，正在处理……')
            im.resize((4000,int(im.size[1]/im.size[0]*4000)))
            print('处理完毕')
        im.save(temp+os.sep+file[0]+'.jpg')
        return True
    except:
        print('处理失败，请自行改变格式（具体格式详见readme）')
        return False

def image_enhance(file):
    try:
        im=Image.open(temp+os.sep+file[0]+file[1])
        om=ImageEnhance.Contrast(im)
        om.enhance(10).save(temp+os.sep+file[0]+'_en.jpg')
        print('成功对图片进行增强处理，准备提交……')
        return True
    except:
        print('处理失败，将提交原图片')
        return False

def debug_body(name):
    with open(temp+os.sep+name+'.dat','rb') as f:
        json=pickle.load(f)
    j=json.get('forms')[0]
    bodys=j.get('body')
    for body in bodys:
        print(body)

def debug_output(name):
    with open(temp+os.sep+name+'.dat','rb') as f:
        json=pickle.load(f)
    json2xls(json,name)

def main():
    '''if not os.path.exists('log.txt'):
        loginit()'''
    if not os.path.exists(temp):
        os.mkdir(temp)
    if not os.path.exists(imageInput):
        os.mkdir(imageInput)
    if not os.path.exists(xlsOutput):
        os.mkdir(xlsOutput)
    password=input('请输入密码：')
    check(password)
    k=input('是否对图像进行增强处理？[y/n]')
    if k and k[0] in 'Yy':
        enhance=True
    else:
        enhance=False
    to_excel(enhance)
    input('Press <Enter>')

temp='Temp'
imageInput='Input'
xlsOutput='Output'


if __name__=='__main__':
    main()

'''
debug_output('1')
input()
'''

