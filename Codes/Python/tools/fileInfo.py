import os

def traversal_dir(tree):
    tree['path'] = os.path.normpath(tree['path'])
    for basename in os.listdir(tree['path']):
        subpath = tree['path'] + os.sep + basename
        if os.path.isdir(subpath):
            tree['dirs'].append(traversal_dir({'path': subpath, 'name': basename, 'files': [], 'dirs': [], 'type':'Dir'}))
        else:
            tree['files'].append({'path': subpath, 'name': basename, 'type': 'File'})
    return tree

path = r'C:\Users\asus\Desktop\新建文件夹'
dirTree = {
    'path': path,
    'name': os.path.basename(path),
    'files': [],
    'dirs': [],
    'type': 'Dir',
        }
for k, v in traversal_dir(dirTree).items():
    print(v)
input()
