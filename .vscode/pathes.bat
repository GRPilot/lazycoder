@echo off

@REM The qt path
set QT_PATH=G:/Programs/Qt/

@REM In the QT_PATH you can find the folder like 6.1.0. It have to consists mingw81_64
set QT_VERSION=6.1.2

@REM The mingw pathes
set QT_MINGW=G:/Programs/Qt/6.1.2/mingw81_64
set QT_TOOLS=G:/Programs/Qt/Tools
set QT_TOOLS_MINGW=G:/Programs/Qt/Tools/mingw810_64

set BUILD_DIR=build
set BIN_DIR=bin



@REM Generating the launch.json if you need set the pathes
@REM Usage: >.\pathes.bat <any param>

if NOT [%1] EQU [] (

(echo {) > launch.json
(echo     "version": "0.2.0",) >> launch.json
(echo     "configurations": [) >> launch.json
(echo         {) >> launch.json
(echo             "name": "g++.exe - Build and debug active file",) >> launch.json
(echo             "type": "cppdbg",) >> launch.json
(echo             "request": "launch",) >> launch.json
(echo             "program": "${workspaceFolder}/%BIN_DIR%/Debug/lazycoder.exe",) >> launch.json
(echo             "args": [],) >> launch.json
(echo             "stopAtEntry": false,) >> launch.json
(echo             "cwd": "${workspaceFolder}/%BIN_DIR%",) >> launch.json
(echo             "environment": [],) >> launch.json
(echo             "externalConsole": false,) >> launch.json
(echo             "MIMode": "gdb",) >> launch.json
(echo             "miDebuggerPath": "%QT_TOOLS_MINGW%/bin/gdb.exe",) >> launch.json
(echo             "setupCommands": [) >> launch.json
(echo                 {) >> launch.json
(echo                     "description": "Enable pretty-printing for gdb",) >> launch.json
(echo                     "text": "-enable-pretty-printing",) >> launch.json
(echo                     "ignoreFailures": true) >> launch.json
(echo                 }) >> launch.json
(echo             ],) >> launch.json
(echo             "preLaunchTask": "[cmake] Configure and build debug") >> launch.json
(echo         }) >> launch.json
(echo     ]) >> launch.json
(echo }) >> launch.json

)
