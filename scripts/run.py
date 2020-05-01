"""
一键快速运行各种程序语言脚本
仅支持运行单文件，不支持多文件
可以用来快速刷题~
"""

import os
import sys
import subprocess

TMP_DIR = 'tmp/'


class Language():

    ext_map = {}

    def __init__(self, file_path, *args):
        self.file_path = file_path
        self.args = args

    def __call__(self):
        self.compile()
        self.run()
        self.end()

    def compile(self):
        pass

    def run(self):
        pass

    def end(self):
        pass


class C(Language):

    exts = ['.c']

    def __init__(self, file_path, *args):
        super().__init__(file_path, *args)
        self.tmp_file = os.path.join(TMP_DIR, 'tmp')

    def compile(self):
        sh(['gcc', self.file_path, '-o', self.tmp_file])

    def run(self):
        sh([self.tmp_file, *self.args])

    def end(self):
        os.remove(self.tmp_file)


class Cpp(Language):

    exts = ['.cpp', '.cc']

    def __init__(self, file_path, *args):
        super().__init__(file_path, *args)
        self.tmp_file = os.path.join(TMP_DIR, 'tmp')

    def compile(self):
        sh(['g++', self.file_path, '-o', self.tmp_file, '-std=c++11'])

    def run(self):
        sh([self.tmp_file, *self.args])

    def end(self):
        os.remove(self.tmp_file)


class Shell(Language):

    exts = ['.sh']

    def __init__(self, file_path, *args):
        super().__init__(file_path, *args)

    def run(self):
        sh(['bash', self.file_path, *self.args])


class Python(Language):

    exts = ['.py']

    def __init__(self, file_path, *args):
        super().__init__(file_path, *args)

    def run(self):
        sh(['python', self.file_path, *self.args])


class JavaScript(Language):

    exts = ['.js']

    def __init__(self, file_path, *args):
        super().__init__(file_path, *args)

    def run(self):
        sh(['node', self.file_path, *self.args])


class Java(Language):

    exts = ['.java']

    def __init__(self, file_path, *args):
        super().__init__(file_path, *args)
        self.file_path_no_ext = self.file_path.rstrip(ext)
        self.class_path = self.file_path_no_ext + '.class'

    def compile(self):
        sh(['javac', self.file_path])

    def run(self):
        sh(['java', self.file_path_no_ext, *self.args])

    def end(self):
        os.remove(self.class_path)


class MATLAB(Language):

    exts = ['.m']

    def __init__(self, file_path, *args):
        super().__init__(file_path, *args)
        dir_name = os.path.dirname(file_path)
        self.dir_name = dir_name if dir_name else '.'
        file_name = os.path.basename(file_path)
        self.file_name_no_ext = file_name.rstrip(ext)

    def run(self):
        sh(['matlab', '-nosplash', '-nodesktop', '-r',
            self.file_name_no_ext, *self.args], cwd=self.dir_name)


class Html(Language):

    exts = ['.html']

    def __init__(self, file_path, *args):
        super().__init__(file_path, *args)

    def run(self):
        import webbrowser
        webbrowser.open(self.file_path)


class Go(Language):

    exts = ['.go']

    def __init__(self, file_path, *args):
        super().__init__(file_path, *args)

    def run(self):
        sh(['go', 'run', self.file_path, *self.args])


class Bat(Language):

    exts = ['.bat']

    def __init__(self, file_path, *args):
        super().__init__(file_path, *args)

    def run(self):
        sh([self.file_path, *self.args])


class Jupyter(Language):

    exts = ['.ipynb']

    def __init__(self, file_path, *args):
        super().__init__(file_path, *args)

    def run(self):
        sh(['python', '-m', 'jupyter', 'notebook', self.file_path, *self.args])


for cls in Language.__subclasses__():
    for ext in cls.exts:
        Language.ext_map[ext] = cls


def run(argv):
    ''' 运行入口 '''
    assert argv, '无输入文件'
    file_path = argv[0]
    args = argv[1:]
    ext = os.path.splitext(file_path)[-1]

    if lang_cls:= Language.ext_map[ext]:
        lang_cls(file_path, *args)()
    else:
        print('不支持对该文件类型的快速运行')


def sh(cmd, *args, **kw):
    ''' 使用子进程运行命令 '''
    try:
        p = subprocess.run(cmd, *args, **kw)
        if p.returncode != 0:
            sys.exit(1)
    except KeyboardInterrupt:
        sys.exit(1)


if __name__ == '__main__':
    argv = sys.argv
    run(argv[1:])
