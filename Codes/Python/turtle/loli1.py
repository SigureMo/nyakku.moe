import turtle as t

def draw(x,y,z):
    t.color("cyan","cyan")
    t.pendown()
    t.begin_fill()
    t.fd(x)
    t.left(60)
    t.fd(z)
    t.left(120)
    t.fd(x)
    t.left(60)
    t.fd(z)
    t.end_fill()         #左

    t.color((0,0.5,1),(0,0.5,1))
    t.right(120)
    t.begin_fill()
    t.fd(y)
    t.right(60)
    t.fd(z)
    t.right(120)
    t.fd(y)
    t.end_fill()        #上

    t.color("blue","blue")
    t.left(60)
    t.begin_fill()
    t.fd(x)
    t.left(120)
    t.fd(y)
    t.left(60)
    t.fd(x)
    t.end_fill()      #右

t.setup(300,300)
t.penup()
t.seth(150)
t.pensize(1)          #笔 窗口初始化

t.fd(10)
t.seth(-90)           #方向 位置初始化

draw(10,10,10)       #i_.

t.penup()
t.bk(10)
t.seth(-150)
t.fd(20)
t.seth(-90)      #再次初始化

draw(40,10,10)       #i_1

t.penup()
t.fd(10)
t.seth(150)
t.fd(90)
t.seth(-90)      #初始化

draw(60,10,10)#L_1

t.penup()
t.bk(60)
t.seth(150)
t.fd(10)
t.seth(-90)    #初始化

draw(10,10,30)#L_\

t.penup()
t.seth(-30)
t.fd(30)
t.seth(30)
t.fd(60)
t.seth(90)
t.fd(50)
t.seth(-90)#初始化

draw(60,10,10)#L_1

t.penup()
t.bk(40)
t.seth(-150)
t.fd(50)
t.seth(-90)

draw(10,30,10)

t.done()
