import smtplib

from email.header import Header
from email.mime.text import MIMEText


class SMTP(smtplib.SMTP_SSL):
    PARAMS = {
        '163': {
            'server': 'smtp.163.com',
            'port': 994,
            }
        }

    def __init__(self, operator):
        self._server = SMTP.PARAMS[operator]['server']
        self._port = SMTP.PARAMS[operator]['port']
        self.from_addr = None
        self.password = None
        super().__init__(self._server, self._port)

    # def __del__(self):
    #     self.quit()

    def login_(self, from_addr=None, password=None):
        self.from_addr = from_addr or self.from_addr
        self.password = password or self.password
        self.login(self.from_addr, self.password)

    def send_text(self, to_addr, text, title='Title', appName='AppName', userName='UserName'):
        self.login_()
        msg = MIMEText(text, 'plain', 'utf-8')
        msg['From'] = Header(f'{appName} <{self.from_addr}>')
        msg['To'] = Header(f'{userName} <{to_addr}>')
        msg['Subject'] = Header(title, 'utf-8')
        self.sendmail(self.from_addr, to_addr, msg.as_string())

    def send_html(self, to_addr, html, title='Title', appName='AppName', userName='UserName'):
        self.login_()
        msg = MIMEText(html, 'html', 'utf-8')
        msg['From'] = Header(f'{appName} <{self.from_addr}>')
        msg['To'] = Header(f'{userName} <{to_addr}>')
        msg['Subject'] = Header(title, 'utf-8')
        self.sendmail(self.from_addr, to_addr, msg.as_string())

if __name__ == "__main__":
    smtp = SMTP('163')
    smtp.login_('<from_addr>', '<password>')
    smtp.send_text('<to_addr>', '<message>')


