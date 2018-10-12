import paramiko
import os
import re
import time
import platform
from io import StringIO

def traversal_dir(path,local_root,remote_root,manage_dir,manage_file,pass_paths=[]):
    path=os.path.normpath(path)
    for basename in os.listdir(path):
        if len(local_root)==3:
            local_root=local_root[:-1]
        subpath=path+os.sep+basename
        subpath=os.path.normpath(subpath)
        print('正在检查：'+subpath+' '*20,end='\r')
        if subpath in pass_paths:
            continue
        if os.path.isdir(subpath):
            manage_dir(subpath.replace(local_root,remote_root))
            traversal_dir(subpath,local_root,remote_root,manage_dir,manage_file,pass_paths)
        else:
            manage_file(subpath.replace(local_root,remote_root),subpath)

class Cloud():
    def __init__(self,host,port,username,pkey):
        transport = paramiko.Transport((host, port))
        transport.connect(username=username, pkey=pkey)

        self.ssh = paramiko.SSHClient()
        self.ssh._transport = transport

        self.sftp = paramiko.SFTPClient.from_transport(transport)
    def exec(self,command):
        stdin, stdout, stderr = self.ssh.exec_command(command)
        result = stdout.read().decode('utf-8')
        return result

    def put(self,local_path,remote_path):
        self.sftp.put(local_path,remote_path)

    def get(self,remote_path,local_path):
        self.sftp.get(remote_path,local_path)

    def close(self):
        self.ssh.close()
        self.sftp.close()

    def check_dir(self,remote_dir):
        remote_dir=remote_dir.replace(os.sep,'/')
        if not self.exec('find ' + remote_dir):
            self.exec('mkdir '+remote_dir)

    def check_file(self,remote_file,local_file):
        remote_file=remote_file.replace(os.sep,'/')
        flag=1
        if os.path.getsize(local_file)>1024*1024:
            flag=0
        if self.exec('find '+remote_file):
            size=int(self.exec('du -b '+remote_file).split('\t')[0])
            if size==os.path.getsize(local_file):
                flag=0
        if flag:
            print('正在备份{}'.format(local_file))
            self.put(local_file,remote_file)

    def upload(self,local_root,remote_root,pass_paths=[]):
        local_root=os.path.normpath(local_root)
        remote_root=os.path.normpath(remote_root)
        self.check_dir(remote_root)
        traversal_dir(local_root,local_root,remote_root,self.check_dir,self.check_file,pass_paths)
        print('\n备份已完成')


    def download(self,remote_root,local_root,pass_paths=[]):
        local_root=os.path.normpath(local_root)
        remote_root=os.path.normpath(remote_root)
        if os.path.exists(local_root):
            os.mkdir(local_root)

def win2linuxpath(path):
    if platform.system()=='Linux':
        path=path.replace('\\','/')\
            .replace(r'F:/','/media/xxjmiao/Codes/')\
            .replace(r'D:/','/media/xxjmiao/DATA/')\
            .replace(r'C:/','/media/xxjmiao/OS/')
    return path

key_str = """-----BEGIN RSA PRIVATE KEY-----
MIICdQIBADANBgkqhkiG9w0BAQEFAASCAl8wggJbAgEAAoGBAKy0ogutIXgjRkp8
GuYL****************************************52qwGfUGdaEsaZISMIqV
+QarSlJX+gHknDb9gRx2KT5jXs4wDKnP93Kw+aFtSLNW+s11WjsCQQCY+6C7RpMs
RTHT2duRZsjPbvn+LrwrDPuEXtKW+yWgc7wACVTLr5B7nbMvSAiq827dh3vWxpVh
LIUr0tC2HoVE
-----END RSA PRIVATE KEY-----"""

private_key = paramiko.RSAKey(file_obj=StringIO(key_str))

cloud=Cloud('255.255.255.255',8000,'xxxx',private_key)

pass_paths=[
    r'F:/$RECYCLE.BIN',
    r'F:/Python/project/tieba_cleaner/tieba_cleaner1.1',
    r'F:/Java/JavaWorkspace',
    r'F:/Java/J_DE',
    r'F:/Python/learning/pyqt5learn',
    r'F:/Python/project/Django/DjangoPracticeProject-master',
    r'F:/System Volume Information',
    r'F:/tools',
    r'F:/Python/P_DE/Windows/phantomjs-2.1.1-windows',
    r'F:/Python/learning/file/15*15.txt',
    r'F:/C/C_DE',
    ]

local_root=r'F:/'
remote_root='/home/sigure/Codes'
pass_paths=list(os.path.normpath(pass_path) for pass_path in pass_paths)

for n in range(len(pass_paths)):
    pass_paths[n]=win2linuxpath(pass_paths[n])
local_root=win2linuxpath(local_root)

cloud.upload(local_root,remote_root,pass_paths)
cloud.close()

input('Press <Enter>')






