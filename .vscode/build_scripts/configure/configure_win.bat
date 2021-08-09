@echo off

set qt_path=G:/Programs/Qt/6.1.2
set qt_mingw=%qt_path%/mingw81_64
set project_root=%1
set build_type=%2

echo Build type: %build_type%
echo Project root: %project_root%

call :make_and_move Windows
call :make_and_move %build_type%

cmake -G "MinGW Makefiles" ^
    -DCMAKE_BUILD_TYPE:STRING=%build_type% ^
    -DCMAKE_PROJECT_INCLUDE_BEFORE:PATH=G:/Programs/Qt/Tools/QtCreator/share/qtcreator/package-manager/auto-setup.cmake ^
    -DCMAKE_PREFIX_PATH:STRING=%qt_mingw% ^
    -DQT_DIR:PATH=%qt_mingw%/lib/cmake/Qt6 ^
    -DQt6_DIR:PATH=%qt_mingw%/lib/cmake/Qt6 ^
    -DQt6Core_DIR:PATH=%qt_mingw%/lib/cmake/Qt6Core ^
    -DQt6CoreTools_DIR:PATH=%qt_mingw%/lib/cmake/Qt6CoreTools ^
    -DQt6EntryPoint_DIR:PATH=%qt_mingw%/lib/cmake/Qt6EntryPoint ^
    -DQt6GuiTools_DIR:STRING=%qt_mingw%/lib/cmake/Qt6GuiTools ^
    -DQt6Gui_DIR:PATH=%qt_mingw%/lib/cmake/Qt6Gui ^
    -DQt6WidgetsTools_DIR:PATH=%qt_mingw%/lib/cmake/Qt6WidgetsTools ^
    -DQt6Widgets_DIR:PATH=%qt_mingw%/lib/cmake/Qt6Widgets ^
    -DQt6LinguistTools_DIR:PATH=%qt_mingw%/lib/cmake/Qt6LinguistTools ^
    -DQT_QMAKE_EXECUTABLE:STRING=%qt_mingw%/bin/qmake.exe ^
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ^
    %project_root%

:make_and_move
    set directory=%~1
    if not exist %directory% (
        mkdir %directory% 
    )
    cd %directory%
    exit /B 0

