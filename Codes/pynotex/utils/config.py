import json

CONF_PATH = 'Codes/pynotex/config.json'

''' config.json
{
  "name": "pynotex",
  "APPs": {
    "wenku": {
      "tmp_dir": "tmp/wenku/",
      "data_dir": "data/wenku/"
    },
    "check_time": {},
  }
}
// 根据所使用的 APP 添加配置项
'''

class Config():
    def __init__(self, name, config_path=CONF_PATH):
        with open(config_path, 'r') as f:
            self._jObject = json.load(f)
        self.conf = self._jObject['APPs'].get(name)
        self.glob = {}
