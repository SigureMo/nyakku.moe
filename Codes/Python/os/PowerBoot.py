import os,time
from multiprocessing import Pool
def PowerBoot(path,file):
    print('开始尝试启动'+file.replace('.exe',''))
    try:
        os.chdir(path)
        os.system(file)
        print('成功启动'+file.replace('.exe',''))
    except:
        print('启动'+file.replace('.exe','')+'失败')

DeskGo=(r'D:\Program Files (x86)\Tencent\DeskGo\2.9.11.127',\
        'DesktopMgr64.exe')
CloudMusic=(r'D:\Software\CloudMusic',\
            'cloudmusic.exe')
Tim=(r'D:\Software\Tencent\TIM\Bin',\
     'Tim.exe')
QQ=(r'D:\Software\Tencent\QQ\Bin',\
     'QQ.exe')
QQPCMgr=(r'D:\Software\Tencent\QPCMgr\QQPCMgr\12.12.19420.214',\
         'QQPCTray.exe')
Dict=(r'D:\Software\Dict',\
      'YoudaoDict.exe')

pros=(DeskGo,
      CloudMusic,
      Tim,
      QQPCMgr,
      Dict,
      #QQ,
      )

def runall(pros):
    for pro in pros:
        PowerBoot(*pro)
        time.sleep(60)
    input('Press <Enter>')

if __name__=='__main__':
    pool=Pool(len(pros))
    for pro in pros:
        time.sleep(20)
        pool.apply_async(PowerBoot, args=(*pro,))
    pool.close()
    pool.join()
    print('已全部启动完成')
    input('Press <Enter>')

