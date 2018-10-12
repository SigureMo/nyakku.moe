import paramiko
import re
import os

class Server():
    def __init__(self, host, port, username,password):
        transport = paramiko.Transport((host, port))
        transport.connect(username=username, password=password)

        self.ssh = paramiko.SSHClient()
        self.ssh._transport = transport

        self.sftp = paramiko.SFTPClient.from_transport(transport)

    def put(self,local_path,remote_path):
        self.sftp.put(local_path,remote_path)

    def get(self,remote_path,local_path):
        self.sftp.get(remote_path,local_path)

    def exec(self, command):
        stdin, stdout, stderr = self.ssh.exec_command(command)
        result = (stdout.read().decode('utf-8'), stderr.read().decode('utf-8'))
        return result

    def close(self):
        self.ssh.close()
        self.sftp.close()

