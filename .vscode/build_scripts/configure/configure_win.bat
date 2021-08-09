@echo off

set project_root=%1
set build_type=%2

call "%project_root%/.vscode/pathes.bat"

call :make_and_move Windows
call :make_and_move %build_type%

cmake -G "MinGW Makefiles" ^
    -DCMAKE_BUILD_TYPE:STRING=%build_type% ^
    -DCMAKE_PROJECT_INCLUDE_BEFORE:PATH=%QT_TOOLS%/QtCreator/share/qtcreator/package-manager/auto-setup.cmake ^
    -DCMAKE_PREFIX_PATH:STRING=%QT_MINGW% ^
    -DQT_DIR:PATH=%QT_MINGW%/lib/cmake/Qt6 ^
    -DQt6_DIR:PATH=%QT_MINGW%/lib/cmake/Qt6 ^
    -DQt6Core_DIR:PATH=%QT_MINGW%/lib/cmake/Qt6Core ^
    -DQt6CoreTools_DIR:PATH=%QT_MINGW%/lib/cmake/Qt6CoreTools ^
    -DQt6EntryPoint_DIR:PATH=%QT_MINGW%/lib/cmake/Qt6EntryPoint ^
    -DQt6GuiTools_DIR:STRING=%QT_MINGW%/lib/cmake/Qt6GuiTools ^
    -DQt6Gui_DIR:PATH=%QT_MINGW%/lib/cmake/Qt6Gui ^
    -DQt6WidgetsTools_DIR:PATH=%QT_MINGW%/lib/cmake/Qt6WidgetsTools ^
    -DQt6Widgets_DIR:PATH=%QT_MINGW%/lib/cmake/Qt6Widgets ^
    -DQt6LinguistTools_DIR:PATH=%QT_MINGW%/lib/cmake/Qt6LinguistTools ^
    -DQT_QMAKE_EXECUTABLE:STRING=%QT_MINGW%/bin/qmake.exe ^
    -DCMAKE_OBJDUMP=%QT_MINGW%/bin/objdump.exe ^
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ^
    %project_root%

:make_and_move
    set directory=%~1
    if not exist %directory% (
        mkdir %directory% 
    )
    cd %directory%
    exit /B 0

