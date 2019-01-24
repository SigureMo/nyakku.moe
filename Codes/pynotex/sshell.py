import argparse

from utils.config import Config
from utils.ssh import Server, LoginError


CONFIG = Config('ssh').conf

def login(host, port, username, password):
    try:
        server = Server(
            host,
            port,
            username,
            password
            )
        return server
    except LoginError as le:
        print(le.message)
        return None

def loop(server):
    try:
        i = input('{}@{}:{}$ '.format(server.username,
                                    server.exec('hostname')[0].strip('\n'),
                                    server.exec('pwd')[0].strip('\n')))
        stdout, stderr = server.exec(i)
        if stdout:
            print(stdout)
        if stderr:
            print('Err:\n' + stderr)
    except (SystemExit, KeyboardInterrupt):
        raise
    except SyntaxError as se:
        print('SyntaxError:'+se)
    except IOError:
        print('命令错误！')

def main():
    parser = argparse.ArgumentParser(description='sshell')
    parser.add_argument('--host', default = None, help='主机 IP')
    parser.add_argument('--port', help='端口号')
    parser.add_argument('--username', help='用户名')
    parser.add_argument('--password', help='密码')
    args = parser.parse_args()
    if args.host is not None:
        host = args.host
        port = int(args.port)
        username = args.username
        password = args.password
    else:
        host = CONFIG['host']
        port = CONFIG['port']
        username = CONFIG['username']
        password = CONFIG['password']
    server = login(host, port, username, password)
    if server is None:
        return
    while True:
        loop(server)

if __name__ == '__main__':
    main()
