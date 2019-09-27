import os

# color mode
DEFAULT = 0
HIGH_LIGHT = 1
UNDER_LINE = 2
FLICKER = 3
INVERSE = 4
INVISBLE = 5

# color id
BLACK = 0
RED = 1
GREEN = 2
YELLOW = 3
BLUE = 4
FUCHSIA = 5
CYAN = 6
WHITE = 7

def color_str(string, mode=DEFAULT, font_color=WHITE, background_color=BLACK):
    return '\033[{mode};{font_color};{background_color}m{string}\033[0m'.format(
        mode = mode,
        font_color = font_color + 30,
        background_color = background_color + 40,
        string = string)

def clear_line():
    width = os.get_terminal_size().columns
    print(" " * (width-1), end="\r")

def process_bar(process, width=50, done_sign="#", undone_sign="_"):
    done_count = int(width * process)
    undone_count = width - done_count
    return done_sign * done_count + undone_sign * undone_count

def slide(count, frames=['-', '\\', '|', '/']):
    return frames[count % len(frames)]
