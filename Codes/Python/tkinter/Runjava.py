from tkinter import *
import time,os,re

def class_init(name):
    with open(name+'.java','w',encoding='gbk') as f:
        f.write('package '+os.getcwd().split(os.sep)[-1]+''';
import java.util.Scanner;
public class '''+name+''' {
    public static void main(String[] args) {
        //Scanner in = new Scanner(System.in);
        //int a = in.nextInt();
        
        //System.out.println("");
        
	}
}

''')

def exec_cmd(cmd):#可获得返回值，但这里用不到了
    r=os.popen(cmd)
    text=r.read()
    r.close()
    return text

def runjava(name):#单class时候调用
    os.system('javac '+name+'.java')
    if os.path.exists(os.getcwd()+os.sep+name+'.class'):
        print('编译成功')
        print('开始解释……')
        text=exec_cmd('java '+name)
        while text:
            print('==================')
            print(text)
            print('==================')
        if os.path.exists(os.getcwd()+os.sep+name+'.class'):
            os.remove(name+'.class')
    else:
        print('编译失败')
        
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
                  .replace('\n','').replace('.java','')
            os.chdir(path)
        else:
            file=filename.get('0.0', END)\
                  .replace('\n','').replace('.java','')
            
        filesname.delete('0.0', END)
        filesname.insert(END,unfold(0,os.getcwd()))
        global s
        s=''
        
        nm=re.compile(r'^[$_A-Za-z][$_A-Za-z0-9]*$')
        if nm.match(file):
            return file
        else:
            print('请输入正确的类名！')
            return None
    
    def newfile():
        name=getname()
        if name:
            class_init(name)
            openfile()

    def save():
        name=getname()
        if name:
            if temptext.get('0.0', END):
                with open(name+'.java','w',encoding='gbk') as f:
                    f.write(temptext.get('0.0', END))
                return True
            else:
                print('无内容！')
                return False

    def openfile():
        name=getname()
        if name:
            if os.path.exists(os.getcwd()+os.sep+name+'.java'):
                with open(name+'.java','r',encoding='gbk') as f:
                    temptext.delete('0.0', END)
                    temptext.insert(END,f.read())
            else:
                temptext.delete('0.0', END)
                temptext.insert(END,'未找到文件！')

    def run():
        name=getname()
        if name:
            #if save():#为防止直接覆盖eclipse源代码（没人会在这写代码），注释掉该操作
            if True:
                os.system('javac '+name+'.java')
                if os.path.exists(os.getcwd()+os.sep+name+'.class'):
                    print('编译成功')
                    print('开始解释……')
                    print('==================')
                    pg=re.compile(r'package ([$_A-Za-z][$_A-Za-z0-9]*\.)*([$_A-Za-z][$_A-Za-z0-9]*);')
                    if pg.search(temptext.get('0.0', END)):
                        pgname=pg.search(temptext.get('0.0', END)).group(0)\
                                .replace('package ','').replace(';','')
                        path1=os.getcwd()
                        path2=path1.replace(pgname.replace('.',os.sep),'')
                        os.chdir(path2)
                        os.system('java '+pgname+'.'+name)
                        os.chdir(path1)
                    else:
                        os.system('java '+name)
                    print('==================')
                    if os.path.exists(os.getcwd()+os.sep+name+'.class'):
                        os.remove(name+'.class')
                else:
                    print('编译失败')
                print()

  #创建窗口 
    t = Tk()
    t.title('RunJava！')
       
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
path0=os.path.expanduser("~")+os.sep+'Desktop'\
        +os.sep+'test'+os.sep+'Test.java'
path0=r'F:\Java\project\CloudNote\app\note\Memo.java'
if __name__ == '__main__':
    main()
