import time

from utils.config import Config
from utils.smtp import SMTP
from utils.loop import Task, Loop
from utils.ssh import Server

CONFIGs = {}
CONFIGs['smtp'] = Config('smtp').conf
CONFIGs['ssh'] = Config('ssh').conf

def test():
    print(1)
    if int(time.time()) % 5 == 0:
        return True

def smtp_test():
    CONFIG = CONFIGs['smtp']
    smtp = SMTP('163')
    smtp.login_(CONFIG['from_addr'], CONFIG['password'])
    loop = Loop(1)
    loop.add_task_list(
        Task(test),
        Task(smtp.send_text, (CONFIG['to_addr'], '<message>'))
    )
    loop.run()

def ssh_test():
    CONFIG = CONFIGs['ssh']
    server = Server(
        CONFIG['host'],
        CONFIG['port'],
        CONFIG['username'],
        CONFIG['password']
        )
    print(server.exec('hostname')[0].strip('\n'))

if __name__ == '__main__':
    ssh_test()
