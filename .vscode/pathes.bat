@echo off

@REM Checks whether pathes.custom.bat file exist.
if not exist pathes.custom.bat (
    echo [ERROR] Can't locate pathes.custom.bat file!
    exit /b 1
)

@REM Calls custom paths bat to get variables from it.
@REM (QT_PATH, QT_VERSION, QT_MINGW, QT_TOOLS, QT_TOOLS_MINGW)
call pathes.custom.bat

@REM Set this variables:
@REM The Qt path.
set QT_PATH=%QT_PATH_CUSTOM%

@REM In the QT_PATH you can find the folder like 6.1.0. It have to contain mingw81_64.
set QT_VERSION=%QT_VERSION_CUSTOM%

@REM The mingw pathes.
set QT_MINGW=%QT_MINGW_CUSTOM%
set QT_TOOLS=%QT_TOOLS_CUSTOM%
set QT_TOOLS_MINGW=%QT_TOOLS_MINGW_CUSTOM%

@REM Build directory.
set BUILD_DIR=build

@REM Binary directory.
set BIN_DIR=bin


@REM Generates the launch.json and c_cpp_properties.json, if you need to set paths.
@REM Usage: >>.\pathes.bat <any param>
if NOT [%1] EQU [] (
    
    @REM Generating launch.json here:
    (echo {) >> launch.json
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

    @REM Generating c_cpp_properties.json here:
    (echo {) >> c_cpp_properties.json
    (echo     "configurations": [) >> c_cpp_properties.json
    (echo         {) >> c_cpp_properties.json
    (echo             "name": "Windows Debug",) >> c_cpp_properties.json
    (echo             "includePath": [) >> c_cpp_properties.json
    (echo                 "${workspaceFolder}/**") >> c_cpp_properties.json
    (echo             ],) >> c_cpp_properties.json
    (echo             "defines": [) >> c_cpp_properties.json
    (echo                 "DEBUG") >> c_cpp_properties.json
    (echo             ],) >> c_cpp_properties.json
    (echo             "windowsSdkVersion": "10.0.19041.0",) >> c_cpp_properties.json
    (echo             "compilerPath": "%QT_TOOLS_MINGW%/bin/g++.exe",) >> c_cpp_properties.json
    (echo             "cStandard": "c17",) >> c_cpp_properties.json
    (echo             "cppStandard": "c++17",) >> c_cpp_properties.json
    (echo             "intelliSenseMode": "windows-clang-x64",) >> c_cpp_properties.json
    (echo             "compileCommands": "${workspaceFolder}/%BUILD_DIR%/Windows/Debug/compile_commands.json",) >> c_cpp_properties.json
    (echo             "browse": {) >> c_cpp_properties.json
    (echo                 "path": [) >> c_cpp_properties.json
    (echo                     "%QT_MINGW%/lib") >> c_cpp_properties.json
    (echo                 ],) >> c_cpp_properties.json
    (echo                 "limitSymbolsToIncludedHeaders": true,) >> c_cpp_properties.json
    (echo                 "databaseFilename": "${workspaceFolder}/.vscode/db/browse.vs.db") >> c_cpp_properties.json
    (echo             },) >> c_cpp_properties.json
    (echo             "configurationProvider": "ms-vscode.cmake-tools") >> c_cpp_properties.json
    (echo         },) >> c_cpp_properties.json
    (echo         {) >> c_cpp_properties.json
    (echo             "name": "Windows Release",) >> c_cpp_properties.json
    (echo             "includePath": [) >> c_cpp_properties.json
    (echo                 "${workspaceFolder}/**") >> c_cpp_properties.json
    (echo             ],) >> c_cpp_properties.json
    (echo             "defines": [) >> c_cpp_properties.json
    (echo                 "NDEBUG") >> c_cpp_properties.json
    (echo             ],) >> c_cpp_properties.json
    (echo             "windowsSdkVersion": "10.0.19041.0",) >> c_cpp_properties.json
    (echo             "compilerPath": "%QT_TOOLS_MINGW%/bin/g++.exe",) >> c_cpp_properties.json
    (echo             "cStandard": "c17",) >> c_cpp_properties.json
    (echo             "cppStandard": "c++17",) >> c_cpp_properties.json
    (echo             "intelliSenseMode": "windows-clang-x64",) >> c_cpp_properties.json
    (echo             "compileCommands": "${workspaceFolder}/%BIN_DIR%/Windows/Release/compile_commands.json",) >> c_cpp_properties.json
    (echo             "browse": {) >> c_cpp_properties.json
    (echo                 "path": [) >> c_cpp_properties.json
    (echo                     "%QT_MINGW%/lib") >> c_cpp_properties.json
    (echo                 ],) >> c_cpp_properties.json
    (echo                 "limitSymbolsToIncludedHeaders": true,) >> c_cpp_properties.json
    (echo                 "databaseFilename": "${workspaceFolder}/.vscode/db/browse.vs.db") >> c_cpp_properties.json
    (echo             },) >> c_cpp_properties.json
    (echo             "configurationProvider": "ms-vscode.cmake-tools") >> c_cpp_properties.json
    (echo         }) >> c_cpp_properties.json
    (echo     ],) >> c_cpp_properties.json
    (echo     "version": 4) >> c_cpp_properties.json
    (echo }) >> c_cpp_properties.json
)
