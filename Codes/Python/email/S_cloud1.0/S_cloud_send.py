from email import encoders
from email.header import Header
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
from email.mime.base import MIMEBase  
from email.utils import parseaddr, formataddr
import smtplib,zipfile,os,time

backup_path=['F:\\project',\
             #os.path.join(os.path.expanduser("~"), 'Desktop\\S_Note1.0'),\
             #os.path.join(os.path.expanduser("~"), 'Desktop\\Sigure0.1'),\
             'D:\\S_cloud',\
             'F:\\S_cloud',\
             'F:\\Python\\learning',\
             'F:\\Python\\project',\
             'F:\\Python\\python进阶笔记'\
             ]
#backup_path=['C:\\Users\\xi~\\Desktop\\test']

def time_now(t=time.time()):
    return time.strftime('_%Y%m%d_%H%M',time.localtime(t))
def zipdir(root):
    z = zipfile.ZipFile(root+'.zip','w',zipfile.ZIP_DEFLATED)#第一个参数为压缩后文件名
    for dirpath, dirnames, filenames in os.walk(root):
        for filename in filenames:
            fpath = dirpath.replace(root,'')
            fpath = fpath and fpath + os.sep or ''
            z.write(os.path.join(dirpath, filename),root.split(os.sep)[-1]+os.sep+fpath+filename)
        for dirname in dirnames:
            fpath = dirpath.replace(root,'')
            fpath = fpath and fpath + os.sep or ''
            z.write(os.path.join(dirpath, dirname),root.split(os.sep)[-1]+os.sep+fpath+dirname)
    z.close()
    print('压缩文件夹%s成功'%root.split(os.sep)[-1]) 

def _format_addr(s):
    name, addr = parseaddr(s)
    return formataddr((Header(name, 'utf-8').encode(), addr))

from_addr = '240377379@qq.com'
password = ' '
to_addr = 'sigure_mo@163.com'
smtp_server = 'smtp.qq.com'

msg = MIMEMultipart()
msg['From'] = _format_addr('Sigure <%s>' % from_addr)
msg['To'] = _format_addr('S_cloud <%s>' % to_addr)
msg['Subject'] = Header('Sigure\'s Backup'+time_now(), 'utf-8').encode()
msg.attach(MIMEText('Sigure\'s Backup'+time_now(), 'plain', 'utf-8'))

for root in backup_path:
    if os.path.exists(root+os.sep):
        zipdir(root)
        with open(root+'.zip', 'rb') as f:
            # 设置附件的MIME和文件名，这里是zip类型:
            mime = MIMEBase('application', 'zip',filename='test.zip')
            # 加上必要的头信息:
            mime.add_header('Content-Disposition', 'attachment',\
                            filename=root.split(os.sep)[-1]+time_now()+'.zip')
            mime.add_header('Content-ID', '<0>')
            mime.add_header('X-Attachment-Id', '0')
            # 把附件的内容读进来:
            mime.set_payload(f.read())
            # 用Base64编码:
            encoders.encode_base64(mime)
            # 添加到MIMEMultipart:
            msg.attach(mime)
        if os.path.exists(root+'.zip'):
            os.remove(root+'.zip')

server = smtplib.SMTP_SSL(smtp_server, 465) # QQ的SMTP协议默认端口是465
server.set_debuglevel(1)
server.login(from_addr, password)
server.sendmail(from_addr, [to_addr], msg.as_string())
server.quit()
