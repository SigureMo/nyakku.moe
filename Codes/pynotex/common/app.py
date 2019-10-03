import os

from common.config import Config
from common.file import Dir

CONFIG = Config()
DATA_ROOT = CONFIG["data_root"]
TMP_ROOT = CONFIG["tmp_root"]

class App():
    def __init__(self, name):
        self.config = CONFIG.switch_app(name)
        self.data_dir = Dir(os.path.join(DATA_ROOT, name))
        self.tmp_dir = Dir(os.path.join(TMP_ROOT, name))
