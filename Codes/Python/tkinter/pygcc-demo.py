from tkinter import *
import time
import os
import re
import subprocess

def new_cfile(filename):
    with open(filename+'.c','w',encoding='utf8', newline = NEWLINE) as f:
        f.write('''#include<stdio.h>

int main(){
    //some codes...
    return 0;
}
''')

def run_cfile(filename):
    filename = filename.replace('.c', '')
    start_time = time.time()
    print('开始编译...')
    res = subprocess.run("gcc -o {}.out {}.c".format(filename, filename), shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    if res.returncode == 0:
        print('编译成功,耗时{:.2f}s'.format(time.time()-start_time))
        print('运行中')
        r = re.findall(r'(scanf\("(.*?(%.+?))+?.*?".+?\))|(gets\(\w+\);)|(getchar\(\))', temptext.get('0.0', END))
        if r:
            print('预计输入阻塞中，请输入参数，预计阻塞次数为{}'.format(len(r)))
        res = subprocess.run('./' + filename + '.out', shell = True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        if res.returncode == 0:
            print('==================')
            print(res.stdout.decode())
            print('==================')
    else:
        print('编译失败,错误信息：')
        print(res.stderr.decode())
        
def main():
    def unfold(i,path):
        global s
        s+='  '*i+path.split(os.sep)[-1]+':\n'
        for f in os.listdir(path):
            if '.' in f:
                s+='  '*(i+1)+f+'\n'
            else:
                unfold(i+1,path+os.sep+f)
        return s
    
    def getname():
        if len(filename.get('0.0', END).split(os.sep))>1:
            path=os.sep.join(filename.get('0.0', END).split(os.sep)[:-1])
            file=filename.get('0.0', END).split(os.sep)[-1]\
                  .replace('\n','').replace('.c','')
            os.chdir(path)
        else:
            file=filename.get('0.0', END)\
                  .replace('\n','').replace('.c','')
            
        filesname.delete('0.0', END)
        filesname.insert(END,unfold(0,os.getcwd()))
        global s
        s=''
        
        nm=re.compile(r'^[$_A-Za-z][$_A-Za-z0-9]*$')
        if nm.match(file):
            return file
        else:
            print('请输入正确的文件名！')
            return None
    
    def newfile():
        name=getname()
        if name:
            new_cfile(name)
            openfile()

    def save():
        name=getname()
        if name:
            if temptext.get('0.0', END):
                with open(name+'.c','w',encoding='utf8', newline=NEWLINE) as f:
                    f.write(temptext.get('0.0', END))
                return True
            else:
                print('无内容！')
                return False

    def openfile():
        name=getname()
        if name:
            if os.path.exists(os.getcwd()+os.sep+name+'.c'):
                with open(name+'.c','r',encoding='utf8', newline=NEWLINE) as f:
                    temptext.delete('0.0', END)
                    temptext.insert(END,f.read())
            else:
                temptext.delete('0.0', END)
                temptext.insert(END,'未找到文件！')

    def run():
        name = getname()
        if name:
            run_cfile(name)
        else:
            return

  #创建窗口 
    t = Tk()
    t.title('pygcc-demo')
       
  #创建frame容器
    frmL=Frame(width=200, height=365, bg='white')
    frmRT = Frame(width=500, height=320, bg='white')
    frmRC = Frame(width=500, height=15, bg='white')
    frmRB = Frame(width=500, height=30)


  #创建控件
    filesname=Text(frmL)
    temptext=Text(frmRT)
    filename=Text(frmRC)
    filename.insert(END,path0)
    if os.path.exists(path0):
        openfile()
    btnNew = Button(frmRB,text='New File',width = 8, command=newfile)
    btnOpen =Button(frmRB, text='Open', width = 8, command=openfile)
    btnSave = Button(frmRB, text='Save', width = 8, command=save)
    btnRun = Button(frmRB, text='Run', width = 8, command=run)



 
  #窗口布局
    frmL.grid(row=0, column=0, rowspan=3)#, padx=1, pady=3)
    frmRT.grid(row=0, column=1, columnspan=2, padx=1, pady=3)
    frmRC.grid(row=1, column=1, columnspan=2, padx=1, pady=3)
    frmRB.grid(row=2, column=1, columnspan=2)

  #固定大小
    frmL.grid_propagate(0)
    frmRT.grid_propagate(0)
    frmRC.grid_propagate(0)
    frmRB.grid_propagate(0)


    btnNew.grid(row=2, column=0)
    btnOpen.grid(row=2, column=1)
    btnSave.grid(row=2, column=2)
    btnRun.grid(row=2, column=3)
    filesname.grid()
    temptext.grid()
    filename.grid()

 
  #主事件循环
    t.mainloop()

s=''
NEWLINE = '\n'
path0=os.path.expanduser("~")+os.sep+'Desktop'\
        +os.sep+'test'+os.sep+'test.c'
# path0=r'F:\Java\project\CloudNote\app\note\Memo.java'
if __name__ == '__main__':
    main()
