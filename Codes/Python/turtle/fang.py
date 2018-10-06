import turtle as t
def draw(x=1,y=1,z=1,c=0):
    d=[x*d0,y*d0,z*d0]
    t.seth(30)
    t.pendown()
    t.colormode(255)
    for i in range(3):
        color=[(c%256,c%256,c%256),(c%256,(c+127)%256,c%256),(c%256,c%256,(c+127)%256)]
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
    t.seth(30)

def l(l):
    t.seth(150)
    t.fd(l*d0)

def r(l):
    t.seth(30)
    t.fd(l*d0)

def u(l):
    t.seth(90)
    t.fd(l*d0)


t.setup(1000,1000)
t.tracer(30)
t.penup()
t.pensize(1)
d0=10
n=9

for a in range(n):
    for b in range(n):
        for e in range(n):
            draw(1,1,1,(a+b+e)*5)
            r(-1)
        r(n)
        u(1)
    u(-n)
    l(-1)
        




t.done()
