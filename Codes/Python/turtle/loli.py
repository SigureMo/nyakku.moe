import turtle as t
'''
color=[u,l,r]
d0
'''
def draw(x=1,y=1,z=1,c=0):
    d=[x*d0,y*d0,z*d0]
    t.seth(30)
    t.pendown()
    for i in range(3):
        t.color(color[i],color[i])
        t.begin_fill()
        t.fd(d[(i+1)%3])
        t.left(120)
        t.fd(d[(i+2)%3])
        t.left(60)
        t.fd(d[(i+1)%3])
        t.left(120)
        t.fd(d[(i+2)%3])
        t.end_fill()
        t.left(180)
    t.penup()
    t.seth(150)

def l(l):
    t.seth(150)
    t.fd(l*d0)

def r(l):
    t.seth(30)
    t.fd(l*d0)

def u(l):
    t.seth(90)
    t.fd(l*d0)

 
if __name__=='__main__':
    t.setup(300,300)
    t.penup()

    d0=15
    color=["DeepSkyBlue","cyan","blue"]
    colorline=["Green","LimeGreen","Lime"]

#    t.pensize(1)
#    t.pendown()
#    for i in range(500):
#        t.color(colorline[i%3],colorline[i%3])
#        t.fd(i)
#        t.left(125)
#        t.tracer((i/25)%10+1)
#    t.penup()

    t.tracer(2)
    t.pensize(1)
    t.goto(0,0)
    draw()

    u(-2)
    draw(4,1,1)#i

    u(2)
    l(7)
    draw(6,1,1)

    u(-5)
    l(-3)
    draw(1,1,3)#l1

    l(-4)
    r(7)
    u(5)
    draw(6,1,1)

    u(-5)
    r(-3)
    draw(1,3,1)#l2

    t.hideturtle()
    t.done()
