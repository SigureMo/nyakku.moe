import os

from common.config import Config
from common.file import Dir

DATA_ROOT = "data/"
TMP_ROOT = "tmp/"

class App():
    def __init__(self, name):
        self.config = Config(name)
        self.data_dir = Dir(os.path.join(DATA_ROOT, name))
        self.tmp_dir = Dir(os.path.join(TMP_ROOT, name))
