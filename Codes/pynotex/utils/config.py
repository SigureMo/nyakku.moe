import json

class Config():
    def __init__(self, name, config_path='Codes/pynotex/config.json'):
        with open(config_path, 'r') as f:
            self._jObject = json.load(f)
        self.conf = self._jObject['APPs'].get(name)
