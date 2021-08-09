@echo off

echo Start installing
cmake --install .
set install_path=%1
set PATH=G:\Programs\Qt\6.1.2\mingw81_64\bin;G:/Programs/Qt/Tools/mingw810_64\bin;%PATH%
cd %install_path%
echo Loading dependencies
windeployqt.exe .
echo Done
