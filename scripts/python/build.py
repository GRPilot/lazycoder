import sys
import subprocess
import platform

from build_utils import *

def main():
    build_type = sys.argv[1]
    paths = load_paths()
    os.chdir(f'{project_root()}/{paths["build_path"]}/{platform.system()}/{build_type}')
    subprocess.check_call(['cmake', '--build', '.'])

if __name__ == '__main__':
    main()
