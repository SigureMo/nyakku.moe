import requests,json
#https://www.ted.com/talks/stephen_cave_the_4_stories_we_tell_ourselves_about_death#t-985455
#上述网站视频的抓取
#fiddler抓包，把需要的链接抓下来
d={
    'video':'http://pb.tedcdn.com\
/talk/hls/video/2013X/StephenCave_2013X-950k-260831bf.ts',
    'audio':'http://pb.tedcdn.com\
/talk/hls/audio/2013X/StephenCave_2013X-600k-260831bf.aac',
    'sub':'http://hls.ted.com/talks/1891/subtitles/en/full.vtt',
    }
def load(url):
    r=requests.get(url)
    return r.content

for t,url in d.items():
    print(t+' is downloading...')
    content=load(url)
    with open(t+'.'+url.split('.')[-1],'wb') as f:
        f.write(content)
    print('succeed')

input('Press <Enter>')
