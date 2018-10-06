import requests,json
#https://www.ted.com/talks/stephen_cave_the_4_stories_we_tell_ourselves_about_death#t-985455
#上述网站视频的抓取
#fiddler抓包，把需要的链接抓下来
def get_video():
    url='http://pb.tedcdn.com\
/talk/hls/video/2013X/StephenCave_2013X-950k-260831bf.ts'
    r=requests.get(url)
    return r.content

def get_audio():
    url='http://pb.tedcdn.com\
/talk/hls/audio/2013X/StephenCave_2013X-600k-260831bf.aac'
    r=requests.get(url)
    return r.content

def get_sub():
    url='http://hls.ted.com/talks/1891/subtitles/en/full.vtt'
    r=requests.get(url)
    return r.content

#with open('test.ts','wb') as f:
#    f.write(get_video())
with open('test.aac','wb') as f:
    f.write(get_audio())
#with open('test.vtt','wb') as f:
#    f.write(get_sub())

input('Press <Enter>')
