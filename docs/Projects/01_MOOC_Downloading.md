# MOOC_Downloading

项目地址 https://github.com/SigureMo/MOOC_Downloading

## 1 初探
### 1.1 从中国大学MOOC到中国大学MOOC

唔，总结什么的最讨厌了，但看了看桌面上存了好几周的文本文档，这不是要让强迫症晚期的我难受死嘛……还是尽快总结完删了的好。

最开始想做这个是因为嵩天老师的python课程突然开放了一个找彩蛋的活动（虽然活动都结束了还没更新），然后我就想做一个对课件一键爬取、解析并上传的脚本，但是……碰到了很多技术上的难题，耽搁了很久。因为想要全天运行，所以拟运行在自己的termux上，但也带来了很多问题。

![01_MOOC_Downloading01.png](../Images/01_MOOC_Downloading01.png)

我的第一个方案是抓取电脑上下载时发送的request，但是因为找不到js动态加载的课件url而宣告失败。虽然把一个一个课件url都复制粘贴下来可能也行，但是那和直接下载的工作量几乎一样，根本没有实现自动化。第二个方案是使用selenium+phantomjs实现页面点击抓取课件url，但是测试几次就发现这种操作并不适合频繁切换页面的爬取（测试时候用的Chrome driver），而且我的虚拟硬盘用几次就满了……也许是我学的还是不好吧，两种方法都失败了确实有点心灰意冷，这个计划暂时搁置起来了。

### 1.2 手机端才是王道

之后的某一天，突然在MOOC上选了一堆课，在手机上下载了一些，但是很占手机空间的啊，而且手机屏幕那么小，看起来效果也不是很好诶。咦？手机上可以下载视频？那……我可以试试抓下手机上的包呀，想到这个我就马上跑回寝室开始写，刚开始还是碰到了之前一样的问题，但是经过一晚上的折腾，总算还是让我找到了下载的方法，话不多说（貌似已经说了很多？），开始爬~

### 1.3 Try!

本例工具：fiddler

环境：python3.6.5

测试课程：翁凯老师的《面向对象程序设计——Java语言》（课程号1001542001）

预备知识：requests库、os库的基本运用

手机抓包的就不赘述了，随便baidu、Google都能找到教程。配置好之后打开MOOCAPP，点击下载自己想要下载的课件，fiddler中马上抓到一堆request，很容易可以找到刚刚点击下载时候发送的request：

![01_MOOC_Downloading02.png](../Images/01_MOOC_Downloading02.png)

没错，就是上面的240号，就算不会找看着左面的视频小图标也能猜到是这个，在fiddler右侧选择inspectors-选项卡，然后在request部分选择webform、response部分选择json，以便查看发送和返回的数据：

![01_MOOC_Downloading03.png](../Images/01_MOOC_Downloading03.png)

我们可以清楚地看到在请求视频资源时候发送了key和Xtask，先不要管他们从哪里来的，先模拟一下看看能不能下载：
```Python
headers={'User-Agent': 'AndroidDownloadManager'}#headers从request下的header选项卡下找，有的不加headers也是可以的
params={
    'key':'a07f96ef72844ca60f299a10b095345d9cb8581dbcbda913e261cdf982df8ccd3969805f640925434f532a9a6b6ac39ab238ec5190a9260bc3c18a326aabb93d8d297b0f7703de153437d6f0094f1ac769c3b66bcf6298d2d6b87ab7287557bf8c1f289b9e77d6f861f9a045ba735298dae3070f62128a029f5d4c798f8df62e8d527559dfc298f46da8ad5f53c2548f0797ab0443b0ce0c1b07fa8415bc5e265f33a26f5b1c3ca6c5fb7b88ad4b8b178013d7bc1f2cb0e9f38473fe9805ab10dfe53fcabde1bb2e857bf88181d32042’,
    'Xtask':’ 1001542001_1002776001_1004984443’}
r=requests.get(self.vurl,params=params,headers=headers).content
with open(‘test.mp4’,’rb’) as f:
    f.write(r)
```

很轻松嘛，我们的视频就这样下载下来了，key和Xtask但是都是从哪里得到的呢？如果你刚刚不止点击下载一个视频的话，不难发现每次点击后都发送了很多请求，而下载请求只是其中的最后一个，那么我们猜想下载请求是依赖前面请求的，试着点击下前面几个请求，你会发现其中有一个请求返回的就是key的值（在我这里就是239号），那么我们只需要模拟239号请求就好啦。

![01_MOOC_Downloading04.png](../Images/01_MOOC_Downloading04.png)

等等！模拟239号的话还有一个未知的参数mob-token呀……唔，这个要怎么得到嘛。这个不难，再向前翻翻，不难发现，很多request中都带这个参数，而且值是一模一样的，既然这个值不是动态的，不如先复制下来，这个是怎么得来的以后再说，其实再仔细想想不难猜到这个值是登录用户的凭证。

我们再模拟这个request试试：
```Python
headers={'User-Agent': 'Dalvik/2.1.0 (Linux; U; Android 7.0; SM-G9300 Build/NRD90M)',
          'mob-token': xxxxx#你的mob-token
         }
        url='http://www.icourse163.org/mob/course/getVideoAuthorityToken/v1'
r=requests.post(url,headers=headers).content
k=json.loads(r).get("results").get("videoKey")
```
很成功嘛，那么我们下载视频就差Xtask了，咦？这个怎么翻了半天也没找到，搜索也搜不到，不过我们可以试试分开搜，第一串数字不用搜了吧，很明显就是我们的课程号

![01_MOOC_Downloading05.png](../Images/01_MOOC_Downloading05.png)

这个其实我刚开始也不知道，但是用电脑版打开某个课程之后会发现有两串数字是一直不变的，前面的那串就是课程号，后面的暂不知，那就叫他tid好了。咦？Xtask里前两串数字正好就是课程号和tid诶！那么我们只需要搜第三串数字好了。按Ctrl+F：

![01_MOOC_Downloading06.png](../Images/01_MOOC_Downloading06.png)

噫！找到了！点开237号，会失望的发现这个request只是在发送了这串数字，获得了这个课件的信息而已，不过聊胜于无，至少知道课件信息从这里得到的嘛。貌似线索一下子全断了？不要灰心，再往前找找。咦？231号……返回的json里……

哇！这居然是整个课程的所有信息！

![01_MOOC_Downloading07.png](../Images/01_MOOC_Downloading07.png)

其实总会有这样的一个response的，不然视频请求里面的Xtask也是发不出去的，我当时以为测试request已经关掉fiddler了，又因为熄灯路由器没电已经不能重新抓包了，只留下了几个保存下来的文本文档进行分析，因为文档里的json是不可视的，所以只能一点一点测试，不过还好我运气好，第一个就测试到了。

从这个json里面可以找到很多信息，比如tid其实是termid（本学期课程号，之前课程号是指该课程名字对应的号码，以后就叫courseid，简写cid），还有课程名、课程简介以及老师简介什么的，我们都可以先记下来，也许等会可以用到。


![01_MOOC_Downloading08.png](../Images/01_MOOC_Downloading08.png)

上图是刚刚下载的那个课件的信息，id一项便是我们一直苦苦寻找的Xtask最后一串数字，下面各种url记录着不同清晰度的视频链接，所有需要的都！找！到！啦！我们试着把这个数据下载下来：
```Python
def get_courseinfo(cid,mob_token):
    headers={'User-Agent': 'Dalvik/2.1.0 (Linux; U; Android 7.0; SM-G9300 Build/NRD90M)'}
    data={'cid':’1001542001’,#可缺省
          'tid': ‘1002776001’,#tid
          'mob-token':mob_token}
    url='https://www.icourse163.org/mob/course/courseLearn/v1'
    r=requests.post(url,data=data,timeout=30).content
    return json.loads(r)#.get('results').get('termDto').get('chapters')#.keys()
```

啊，至此大部分代码都已经写完了，剩下的就是我们组合了：
```Python
def gettid(cid):#这里我嫌每次去找tid比较麻烦，就直接在课程页面匹配寻找了下
    url='https://www.icourse163.org/learn/DUT-'+cid
    r=requests.get(url)
    if re.search(r'"currentTermId": \d{10}',r.text):
        return re.search(r'"currentTermId": \d{10}',r.text).group(0)[-10:]
    else:
        print('未找到currentTermId')
        return ''
def get_courseinfo(cid,mob_token):
    headers={'User-Agent': 'Dalvik/2.1.0 (Linux; U; Android 7.0; SM-G9300 Build/NRD90M)'}
    data={'cid':cid,#可缺省\
          'tid':gettid(cid),\
          'mob-token':mob_token}
    url='https://www.icourse163.org/mob/course/courseLearn/v1'
    r=requests.post(url,data=data,timeout=30).content
    return json.loads(r)#.get('results').get('termDto').get('chapters')#.keys()
def getvideo(cid,tid,unitid,mob_token):
    headers={'User-Agent': 'Dalvik/2.1.0 (Linux; U; Android 7.0; SM-G9300 Build/NRD90M)',\
             'mob-token': mob_token\
             }
    url='http://www.icourse163.org/mob/course/getVideoAuthorityToken/v1'
    r=requests.post(url,headers=headers).content
    k=json.loads(r).get("results").get("videoKey")

    headers={'User-Agent': 'AndroidDownloadManager'}
    params={'key':k,\
            'Xtask':str(cid)+'_'+str(tid)+'_'+str(unitid)}
    return requests.get(self.vurl,params=params,headers=headers).content
```
之后就是通过调用get_courseinfo(cid,mob_token)获得全部课程信息，然后调用getvideo(cid,tid,unitid,mob_token)，填入相应参数就好。

就这样，我们就完成了视频的爬取任务，在课程信息加上循环便可以实现连续爬取。

## 2 再探
由于发现上次的课程没有PDF课件，所以这次换一个课程，正好也证明我们的脚本不是只针对某一门课程的，任何课程都能爬取。282
### Try again!
本例测试课程：黄天羽老师的《Python科学计算三维可视化》（课程号1001871001）

和上次一样，我们在手机上点击下载想要的文档，回到fiddler查找最近抓到的包：

![01_MOOC_Downloading09.png](../Images/01_MOOC_Downloading09.png)

很容易根据返回的数据量看出，282号就是实际下载的请求，让我们看下它发送的数据：

![01_MOOC_Downloading10.png](../Images/01_MOOC_Downloading10.png)

……什么鬼嘛，怎么一个都看不懂……别急别急，看不懂往前找嘛，咦？他的上一个请求里面返回了好多的关键数据，看看能不能找到什么有用的：

![01_MOOC_Downloading11.png](../Images/01_MOOC_Downloading11.png)

咦，这个textOri gUrl貌似刚好把所有数据都包含了呀，什么NOSAccessKeyId、Expires、Signature全都已经包含在url了呀，而且282号是get方法：

![01_MOOC_Downloading12.png](../Images/01_MOOC_Downloading12.png)

那么可以直接向这个textOri gUrl发送text就好啦（get时候的数据会直接显示在url中，相应地，在url中包含键值对也就相当于直接发送了数据），我们先试下是否可行吧：
```Python
import requests
r=requests.get('http://nos.netease.com/edu-lesson-pdfsrc/7A88BECD1F2F492522ABCF0D9AC20096-1498306080727?\
NOSAccessKeyId=7ba71f968e4340f1ab476ecb300190fa&Expires=1528821687&\
Signature=v3PzW01p4p%2FBWMvFA5oU6ySTDX0sfzCEZsDWVvrYLps%3D&\
download=SV06-Mayavi%E5%8F%AF%E8%A7%86%E5%8C%96%E5%AE%9E%E4%BE%8B.pdf')
with open('test.pdf','wb') as f:
    f.write(r.content)
```

![01_MOOC_Downloading13.png](../Images/01_MOOC_Downloading13.png)

很好，很成功，这个pdf这么容易下的？不对，刚刚的关键是获得textOri gUrl，可是textOri gUrl又要怎么获得呢？我们再看下281号数据的header和webform：

![01_MOOC_Downloading14.png](../Images/01_MOOC_Downloading14.png)

![01_MOOC_Downloading15.png](../Images/01_MOOC_Downloading15.png)

Headers等会再看，先看webform的参数。mob-token已经说过了，这是一个固定参数，暂时先直接复制过来就好；cid就是课程号，这个现在看已经很明了了；t是个什么呢，居然只有一位数，既然只有一位数那肯定不是什么关键的参数啦，关键的参数一位数是表示不清的；最后，unitid，有点熟悉啊，好像上次视频也用到这个了，上次视频的各种参数都是在课程总信息里面找的，我们再找下这个课程的总信息，这次我的就比较远了，但是你要坚信只要我们client发送了这个参数，server就一定曾经发过来这些参数，我在151号找到了它：

![01_MOOC_Downloading16.png](../Images/01_MOOC_Downloading16.png)

还是熟悉的数据，很容易翻到这个课件的数据，也很容易找到了unitid，那只剩下t了呀，等等，这里的contentType=3？？？这大概就是我们要找的吧？那这个参数是什么呢？很容易猜到就是内容的类型（嗯……不会英文可以查有道），不信你再多下几个PDF就会发现t永远是3，这里对应的contentType也永远是3，那……没错，你已经猜到了，pdf（文档）对应的类型号就是3！那视频是什么呢，你可以全课程信息返回的json中其他课件信息，很容易得出结论：1：视频，3：文档，4：富文本，5：测验，6：讨论（2和7及以后暂未知，如果你发现了可以分享下）。好了，我们已经从这里面找到自己想要的东西了，下一步就是组合了：
```Python
#首先发送请求获得PDFurl
url='http://www.icourse163.org/mob/course/learn/v1'
data={'t':3,\
      'cid':'1001871001',\
      'unitId': '',\#填入从课程全信息里面提取出来的unitid
      'mob-token': ''}#填入你的mob-token
r=requests.post(url,data=data).content
pdfurl=json.loads(r).get("results").get('learnInfo').get("textOrigUrl")#获得url

加上第一段代码组合起来就是这样：
def getpdf():
    url='http://www.icourse163.org/mob/course/learn/v1'
    data={'t':3,\
          'cid':'',\
          'unitId': '',\
          'mob-token':''}
    r=requests.post(url,data=data).content
    pdf=json.loads(r).get("results").get('learnInfo').get("textOrigUrl")    
    return requests.get(pdf).content
```

现在只需要将这一步获得的url填入上一步的那一串url就完成了pdf的爬取啦。
### 继续爬附件！
为什么也要爬取附件呢？最开始是因为发现有的课程基本上只有附件（富文本），基本没有pdf的（比如上个示例中的java进阶课），而且有很多附件对课程来说是很重要的，所以，为了保证下载课程的完整性（主要是为了以后课程关闭时候方便回顾），我便又开始了附件下载的探索。

很明显，我们手机上是下载不了附件的，我就不得不试着在电脑上下载。和之前一样，先点击一下然后分析抓到的包：

![01_MOOC_Downloading17.png](../Images/01_MOOC_Downloading17.png)

![01_MOOC_Downloading18.png](../Images/01_MOOC_Downloading18.png)

有了刚刚下pdf的经验，很容易分析出这是下它时候的包，而且根据刚刚的经验，我们看看他的headers中的url是什么：

![01_MOOC_Downloading19.png](../Images/01_MOOC_Downloading19.png)

这次和上次其实基本一样的，直接向这个url发送get就好了，不过这次我就先不写了，然后我们看下这些参数是怎么得来的，翻翻前后的返回json发现根本没有什么有关联的，难道线索就这样断了？当然不会，这里找不到，我们还有全课件信息呢，重新找到我的151号，翻开这个课件的信息：

![01_MOOC_Downloading20.png](../Images/01_MOOC_Downloading20.png)

就是它，我们只需要它就够了，剩下的也没啥了，把代码组合一下就行：
```Python
def getenclosure():
    url='http://www.icourse163.org/mob/course/attachment.htm'
    headers={'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/66.0.3359.139 Safari/537.36'}
    params=''#填入该课件信息的jsonContent
    return requests.get(url,headers=headers,params=params).content
```
那么，我们的主体就这样完成了……没错我们的下载的核心都已经完成了，剩下的就是把上面各个课件的下载组装成一个自动化的脚本就行，但是怎么让它知道沿着什么路径下载呢？或者说，如何让它知道都需要下哪些课件呢，之前都是输进去一个参数下载一个课件，现在我们要让它自动获取参数自动下载。既然要获取全部的数据，自然就又想到了全课件信息了，这是整个脚本的核心，没有它整个脚本的各个地方都没有关键的数据，也就无法运行。

先理一理思路，首先调用get_courseinfo获取课程全信息，然后我们可以很容易用几层for循环嵌套从全课件信息取出一个一个课件的数据，然后根据不同的类型调用不同的课件下载函数，将各种课件下载下来，很好，现在你已经可以自己写一个简易的爬取脚本了，由于这些都很容易实现，整合的代码就不贴出来了。

# Amendant Record
1. 180610 Add #1
2. 180613 Add #2
3. 180909 Update #1 #2

[goto S_Note;](../README.md)

[return 0;](#mooc_downloading)
