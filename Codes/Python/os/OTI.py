import os
libs={'requests','pillow','xlwt','xlrd','BeautifulSoup4','pyinstaller',\
      'pywin32','scrapy','numpy','matplotlib','sklearn','jieba','wordcloud',\
      'wheel','networkx','sympuy','django','flask','werobot','pyqt5',\
      'pandas','pyopengl','pypdf2','docopt','pygame'}

libs = {
    'matplotlib',
    'h5py',
    'numpy',
    }

for lib in libs:
    try:
        os.system('pip install '+lib+' -i https://pypi.tuna.tsinghua.edu.cn/simple')
        print(lib+':Successful')
    except:
        print('Failed Somehow')
