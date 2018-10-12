from email.parser import Parser
from email.header import decode_header
from email.utils import parseaddr

import poplib,email,os
attachment_files = []
def save(filename,data):
#    try:
    root=os.path.join(os.path.expanduser("~"), 'Desktop\\Backup\\')
    path=root+filename
    if not os.path.exists(root):
        os.mkdir(root)
    if not os.path.exists(path):
        with open(path,'wb') as f:
            attachment_files.append(filename) 
            f.write(data)
            print('保存%s成功'%filename)
    else:
        print('文件%s已存在'%filename)
#    except:
#        print('保存%s失败'%filename)

def decode_str(s):
    value, charset = decode_header(s)[0]
    if charset:
        value = value.decode(charset)
    return value

def get_att(msg):  
    import email  
    for part in msg.walk():  
        file_name = part.get_filename()#获取附件名称类型  
        contType = part.get_content_type()  
          
        if file_name:   
            h = email.header.Header(file_name)  
            dh = email.header.decode_header(h)#对附件名称进行解码  
            filename = dh[0][0]  
            if dh[0][1]:  
                filename = decode_str(str(filename,dh[0][1]))#将附件名称可读化  
                #filename = filename.encode("utf-8")
            print('准备保存%s'%filename)  
            data = part.get_payload(decode=True)#下载附件  
            save(filename,data)
    return attachment_files  
    
    
# 输入邮件地址, 口令和POP3服务器地址:
email = 'sigure_mo@163.com'
password = ' '
pop3_server = 'pop.163.com'

# 连接到POP3服务器:
server = poplib.POP3(pop3_server)
# 可以打开或关闭调试信息:
server.set_debuglevel(1)
# 可选:打印POP3服务器的欢迎文字:
print(server.getwelcome().decode('utf-8'))

# 身份认证:
server.user(email)
server.pass_(password)

# stat()返回邮件数量和占用空间:
print('Messages: %s. Size: %s' % server.stat())
# list()返回所有邮件的编号:
resp, mails, octets = server.list()
# 可以查看返回的列表类似[b'1 82923', b'2 2184', ...]
print(mails)

# 获取最新一封邮件, 注意索引号从1开始:
index = len(mails)
resp, lines, octets = server.retr(index)

# lines存储了邮件的原始文本的每一行,
# 可以获得整个邮件的原始文本:
msg_content = b'\r\n'.join(lines).decode('utf-8')
# 稍后解析出邮件:
msg = Parser().parsestr(msg_content)
print('成功下载'+','.join(get_att(msg)))

# 可以根据邮件索引号直接从服务器删除邮件:
# server.dele(index)
# 关闭连接:
server.quit()
