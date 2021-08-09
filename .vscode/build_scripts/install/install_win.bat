@echo off

set project_root=%1
call %project_root%/.vscode/pathes.bat

echo Start installing
cmake --install .
set build_type=%2
set install_path=%project_root%/%BIN_DIR%/%build_type%
set PATH=%QT_MINGW%\bin;%QT_TOOLS_MINGW%/bin;%PATH%
cd %install_path%
echo Loading dependencies
windeployqt.exe .
echo Done
