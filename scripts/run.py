"""
一键快速运行各种程序语言脚本
仅支持运行单文件，不支持多文件
可以用来快速刷题~
"""

import os
import sys
import subprocess

tmp_dir = "tmp/"


def run(argv):
    """ 运行入口 """
    assert argv, "无输入文件"
    file_path = argv[0]
    args = argv[1: ]
    ext = os.path.splitext(file_path)[-1]
    cmd_list = []
    if ext == ".c":
        tmp_file = os.path.join(tmp_dir, "tmp")
        cmd_list = [
            ["gcc", file_path, "-o", tmp_file],
            [tmp_file, *args]
        ]
        run_cmds(cmd_list)
        os.remove(tmp_file)
    elif ext == ".cpp":
        tmp_file = os.path.join(tmp_dir, "tmp")
        cmd_list = [
            ["g++", file_path, "-o", tmp_file],
            [tmp_file, *args]
        ]
        run_cmds(cmd_list)
        os.remove(tmp_file)
    elif ext == ".sh":
        cmd_list = [
            ["bash", file_path, *args]
        ]
        run_cmds(cmd_list)
    elif ext == ".py":
        cmd_list = [
            ["python3", file_path, *args]
        ]
        run_cmds(cmd_list)
    elif ext == ".js":
        cmd_list = [
            ["node", file_path, *args]
        ]
        run_cmds(cmd_list)
    elif ext == ".java":
        file_path_no_ext = file_path.rstrip(ext)
        class_path = file_path_no_ext + ".class"
        cmd_list = [
            ["javac", file_path],
            ["java", file_path_no_ext, *args]
        ]
        run_cmds(cmd_list)
        os.remove(class_path)
    elif ext == ".m":
        dir_name = os.path.dirname(file_path)
        dir_name = dir_name if dir_name else "."
        file_name = os.path.basename(file_path)
        file_name_no_ext = file_name.rstrip(ext)
        cmd_list = [
            ["matlab", "-nosplash", "-nodesktop", "-r", file_name_no_ext, *args]
        ]
        run_cmds(cmd_list, cwd=dir_name)
    elif ext == ".html":
        import webbrowser
        webbrowser.open(file_path)
    elif ext == ".go":
        cmd_list = [
            ["go", "run", file_name, *args]
        ]
        run_cmds(cmd_list)
    elif ext == ".bat":
        cmd_list = [
            [file_path, *args]
        ]
        run_cmds(cmd_list)
    elif ext == ".ipynb":
        cmd_list = [
            ["jupyter", "notebook", file_path, *args]
        ]
        run_cmds(cmd_list)
    else:
        print("不支持对该文件类型的快速运行")


def run_cmds(cmd_list, *args, **kw):
    """ 使用子进程运行命令 """
    for cmd in cmd_list:
        subprocess.run(cmd, *args, **kw)

if __name__ == '__main__':
    argv = sys.argv
    run(argv[1: ])
