from utils import *

def python(filename):
    local_dir = os.path.expanduser("~")+os.sep+'Desktop' + os.sep
    myserver.exec('mkdir test')
    myserver.exec('rm test.py')
    remote_path = 'test.py'
    local_path = local_dir + filename
    inputs = []
    with open(local_path, 'r', encoding='utf8') as f:
        s = f.read()
        s = 'import sys\n' + s
        i = 1
        while re.search('input\(.*?\)', s):
            span = re.search('input\(.*?\)', s).span()
            input_string = s[span[0]:span[1]]
            inputs.append(eval(input_string))
            s = s.replace(input_string, 'sys.argv[{}]'.format(i))
            i += 1
        with open(local_path + '.tmp', 'w', encoding='utf8') as f:
            f.write(s)
    myserver.put(local_path + '.tmp', remote_path)
    os.remove(local_path + '.tmp')
    result = myserver.exec('python3 test.py ' + ' '.join(inputs))
    return result

def pyshell():
    spoce = {}
    def execute(cmd):
        try:
            out = eval(cmd, spoce)
        except SyntaxError:
            try:
                exec(cmd, spoce)
                out = None
            except Exception as e:
                out = e
        except Exception as e:
            out = e
        return out
            
    def multiline(indent=1):
        k = input('... '+indent*'    ')
        if k and k[-1] == ':':
            nextline = multiline(indent+1)
        elif k:
            nextline = multiline(indent)
        else:
            nextline = ''
        return '\n' + 4*indent*' ' + k + nextline

    while True:
        k = input('>>> ')
        if k == 'exit()':
            break
        if k and k[-1] == ':':
            k += multiline()
        if k:
            out = execute(k)
            if out != None:
                print(repr(out))
        


host = input('host:')
port = eval(input('port:'))
username = input('username:')
password = input('password:')
'''
host = ' '
port =  
username = ' '
password = ' '
'''
myserver = Server(host, port, username,password)

while True:
    try:
        i = input('{}@{}:{}$ '.format(username,
                                      myserver.exec('hostname')[0].strip('\n'),
                                      myserver.exec('pwd')[0].strip('\n')))
        if i.split(' ')[0] == 'python3':
            if len(i.split(' ')) > 1 and i.split(' ')[1]:
                stdout, stderr = python(i.split(' ')[1])
            else:
                pyshell()
                stdout, stderr = (None, None)
        else:
            stdout, stderr = myserver.exec(i)
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



