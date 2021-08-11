import sys
import subprocess
import platform

from build_utils import *

def cmake_install():
    subprocess.check_call(['cmake', '--install', '.'])
    pass

def install_dependencies(paths):
    mingw_path = f'{paths["qt_path"]}/{paths["qt_version"]}/{paths["qt_mingw"]}'
    subprocess.check_call([f'{mingw_path}/bin/windeployqt.exe', '.'])
    pass

def main():
    build_type = sys.argv[1]
    paths = load_paths()
    change_dir(f"{paths['build_path']}/{platform.system()}/{build_type}")

    cmake_install()

    os.chdir(project_root())
    change_dir(f"{paths['install_path']}/{build_type}")
    install_dependencies(paths)

if __name__ == '__main__':
    main()
