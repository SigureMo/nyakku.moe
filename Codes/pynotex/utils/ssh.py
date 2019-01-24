import paramiko


class LoginError(Exception):
    def __init__(self, message):
        self.message = message

class Server():
    def __init__(self, host, port, username, password):
        transport = paramiko.Transport((host, port))
        self.host = host
        self.port = port
        self.username = username
        self.password = password
        try:
            transport.connect(username=username, password=password)
        except paramiko.ssh_exception.AuthenticationException:
            raise LoginError('Authentication failed')

        self.ssh = paramiko.SSHClient()
        self.ssh._transport = transport

        self.sftp = paramiko.SFTPClient.from_transport(transport)

    def put(self, local_path, remote_path):
        self.sftp.put(local_path, remote_path)

    def get(self, remote_path, local_path):
        self.sftp.get(remote_path, local_path)

    def exec(self, command):
        stdin, stdout, stderr = self.ssh.exec_command(command)
        result = (stdout.read().decode('utf-8'), stderr.read().decode('utf-8'))
        return result

    def __del__(self):
        self.ssh.close()
        self.sftp.close()

if __name__ == '__main__':
    try:
        server = Server(
            input('host: '),
            int(input('port: ')),
            input('username: '),
            input('password: ')
            )
        print(server.exec('ls')[0])
    except LoginError as le:
        print(le.message)
