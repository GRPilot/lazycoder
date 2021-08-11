import sys
import shutil

from build_utils import *

def try_delete(target):
    path = f'{project_root()}/{target}'
    print(f'[INFO] Clean {path}')
    if os.path.isdir(path):
        shutil.rmtree(path)
    print(f'[INFO] Cleaning {target} done')
    pass

def clean(target: str):
    print(f'[INFO] Start cleaning')
    cleanAll: bool = target.find('all') != -1
    if cleanAll or target.find('build') != -1:
        try_delete('build')
    if cleanAll or target.find('bin') != -1:
        try_delete('bin')
    print(f'[INFO] Cleaning done')


if __name__ == '__main__':
    clean(str(sys.argv[1]))
