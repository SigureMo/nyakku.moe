import json

CONF_PATH = 'Codes/pynotex/config.json'

''' config.json
{
  "name": "pynotex",
  "data_root": "data/",
  "tmp_root": "tmp/",
  "APPs": {
    "wenku": {},
    "markdown-mail": {
      "footer": "footer.md",
      "username": "SigureMo"
    }
  }
}
// 根据所使用的 APP 添加配置项
'''

class Config(dict):
    def __init__(self, config_path=CONF_PATH):
        with open(config_path, 'r') as f:
            _jObject = json.load(f)
        super().__init__(_jObject)

    def switch_app(self, name):
        return self['APPs'].get(name, {})
