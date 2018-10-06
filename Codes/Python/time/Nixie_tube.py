#SevenDigitsDrawV2.py
import turtle, time
def drawGap(): #绘制数码管间隔
    turtle.penup()
    turtle.fd(5)
def drawLine(draw):   #绘制单段数码管
    drawGap()
    turtle.pendown() if draw else turtle.penup()
    turtle.fd(40)
    drawGap()
    turtle.right(90)
def drawDigit(d): #根据数字绘制七段数码管
    drawLine(True) if d in [2,3,4,5,6,8,9] else drawLine(False)
    drawLine(True) if d in [0,1,3,4,5,6,7,8,9] else drawLine(False)
    drawLine(True) if d in [0,2,3,5,6,8,9] else drawLine(False)
    drawLine(True) if d in [0,2,6,8] else drawLine(False)
    turtle.left(90)
    drawLine(True) if d in [0,4,5,6,8,9] else drawLine(False)
    drawLine(True) if d in [0,2,3,5,6,7,8,9] else drawLine(False)
    drawLine(True) if d in [0,1,2,3,4,7,8,9] else drawLine(False)
    turtle.left(180)
    turtle.penup()
    turtle.fd(20)
def drawDate(date):
    turtle.pencolor("red")
    for i in date:
        if i == '-':
            turtle.write('年',font=("Arial", 18, "normal"))
            turtle.pencolor("green")
            turtle.fd(40)
        elif i == '=':
            turtle.write('月',font=("Arial", 18, "normal"))
            turtle.pencolor("blue")
            turtle.fd(40)
        elif i == ':':
            turtle.write(':',font=("Arial", 18, "normal"))
            turtle.fd(40)
        elif i == '+':
            turtle.write('日',font=("Arial", 18, "normal"))
            turtle.pencolor("black")
            turtle.fd(40)
        else:
            drawDigit(eval(i))
def e8time():
    t=time.strftime('%Y-%m=%d+%H:%M:%S',time.gmtime())
    h=int(t[11:13])
    d=int(t[8:10])
    h+=8
    if h>=24:
        h-=24
        d+=1
        d='{:0>2}'.format(d)
        h='{:0>2}'.format(h)
        t=t[0:8]+d+'+'+h+t[13:]
    else:
        h='{:0>2}'.format(h)
        t=t[0:11]+h+t[13:]
    return t
#t=time.strftime('%Y-%m-%d %H:%M:%S',time.localtime(time.time()))

def dataup():
    while True:
        start=time.time()
        turtle.tracer(5)
        turtle.penup()
        turtle.fd(-700)
        turtle.pensize(5)
        drawDate(e8time())
        turtle.fd(1000)
        time.sleep(start-time.time()+1)
        turtle.reset()
        

def main():
    turtle.setup(1600, 350, 0, 0)
    turtle.tracer(10)
    turtle.penup()
    turtle.fd(-700)
    turtle.pensize(5)
#    drawDate('2018-10=10+10:10:10')
    dataup()
    turtle.hideturtle()
    turtle.done()
main()
