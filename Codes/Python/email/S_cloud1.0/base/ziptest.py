import zipfile,os,time
root='C:\\Users\\xi~\\Desktop\\test'
def time_now(t=time.time()):
    return time.strftime('%Y%m%d%H%M',time.localtime(t))
def zipdir(root):
    z = zipfile.ZipFile(root+time_now()+'.zip','w',zipfile.ZIP_DEFLATED)#第一个参数为压缩后文件名
    for dirpath, dirnames, filenames in os.walk(root):
        for filename in filenames:
            fpath = dirpath.replace(root,'')
            fpath = fpath and fpath + os.sep or ''
            z.write(os.path.join(dirpath, filename),root.split(os.sep)[-1]+os.sep+fpath+filename)
        for dirname in dirnames:
            fpath = dirpath.replace(root,'')
            fpath = fpath and fpath + os.sep or ''
            z.write(os.path.join(dirpath, dirname),root.split(os.sep)[-1]+os.sep+fpath+dirname)
    z.close()
    print('压缩文件夹%s成功'%root.split(os.sep)[-1]) 
zipdir(root)
 
