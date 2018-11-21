from PIL import Image

def resize(im, size):
    im.resize(size)

def reshape(im, shape):
    size = min(im.size)
    shapes = {
        'circle': lambda x, y, size :(x-size/2)**2 + (y-size/2)**2 < (size/2)**2,
        'square': lambda x, y, size : True,
        }
    om = Image.new('RGBA', (size, size),(255,255,255,0))
    for i in range(size):
        for j in range(size):
            if shapes[shape](i, j, size):
                om.putpixel((i,j),im.getpixel((i,j)))
            else:
                om.putpixel((i,j), (0, 0, 0, 0))
    return om

im = Image.open('sigure_mo.png').convert("RGBA")
om = reshape(im, 'circle')
om.save('sigure_mo_circle.png')
