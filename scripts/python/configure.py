import os
import sys
import platform
import subprocess
from build_utils import *

def cmake_configure(paths, build_type):
    qt_tools = f'{paths["qt_path"]}/Tools'
    qt_mingw = f'{paths["qt_path"]}/{paths["qt_version"]}/{paths["qt_mingw"]}'
    cmake_cmd = [
        "cmake",
        f'-G', 'MinGW Makefiles',
        f'-DCMAKE_BUILD_TYPE:STRING={build_type}',
        f'-DCMAKE_PROJECT_INCLUDE_BEFORE:PATH={qt_tools}/QtCreator/share/qtcreator/package-manager/auto-setup.cmake',
        f'-DCMAKE_PREFIX_PATH:STRING={qt_mingw}',
        f'-DQT_DIR:PATH={qt_mingw}/lib/cmake/Qt6',
        f'-DQt6_DIR:PATH={qt_mingw}/lib/cmake/Qt6',
        f'-DQt6Core_DIR:PATH={qt_mingw}/lib/cmake/Qt6Core',
        f'-DQt6CoreTools_DIR:PATH={qt_mingw}/lib/cmake/Qt6CoreTools',
        f'-DQt6EntryPoint_DIR:PATH={qt_mingw}/lib/cmake/Qt6EntryPoint',
        f'-DQt6GuiTools_DIR:STRING={qt_mingw}/lib/cmake/Qt6GuiTools',
        f'-DQt6Gui_DIR:PATH={qt_mingw}/lib/cmake/Qt6Gui',
        f'-DQt6WidgetsTools_DIR:PATH={qt_mingw}/lib/cmake/Qt6WidgetsTools',
        f'-DQt6Widgets_DIR:PATH={qt_mingw}/lib/cmake/Qt6Widgets',
        f'-DQt6LinguistTools_DIR:PATH={qt_mingw}/lib/cmake/Qt6LinguistTools',
        f'-DQT_QMAKE_EXECUTABLE:STRING={qt_mingw}/bin/qmake.exe',
        f'-DCMAKE_OBJDUMP={qt_mingw}/bin/objdump.exe',
        f'-DCMAKE_EXPORT_COMPILE_COMMANDS=ON',
        f'{project_root()}'
    ]
    if sys.platform.startswith('win'):
        shell = True
    else:
        shell = False
    return subprocess.check_call(cmake_cmd, stderr=subprocess.STDOUT, shell=shell)

def main():
    build_type = sys.argv[1]
    paths = load_paths()
    change_dir(paths['build_path'])
    change_dir(str(platform.system()))
    change_dir(str(build_type))
    cmake_configure(paths, build_type)

if __name__ == '__main__':
    main()

