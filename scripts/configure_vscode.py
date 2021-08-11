import json
import os
import platform

from python.build_utils import load_paths
from python.build_utils import project_root

def make_launch_json(paths):
    root = "${workspaceFolder}"
    bin = paths['install_path']
    qt_tool_mingw_path = f"{paths['qt_path']}/Tools/{paths['qt_mingw_tools']}"
    launch_json = {
        "version": "0.2.0",
        "configurations": [
            {
                "name": "g++.exe - Build and debug active file",
                "type": "cppdbg",
                "request": "launch",
                "program": f"{root}/{bin}/Debug/lazycoder.exe",
                "args": [],
                "stopAtEntry": False,
                "cwd": f"{root}/{bin}",
                "environment": [],
                "externalConsole": False,
                "MIMode": "gdb",
                "miDebuggerPath": f"{qt_tool_mingw_path}/bin/gdb.exe",
                "setupCommands": [
                    {
                        "description": "Enable pretty-printing for gdb",
                        "text": "-enable-pretty-printing",
                        "ignoreFailures": True
                    }
                ],
                "preLaunchTask": "[cmake] Configure and build"
            }
        ]
    }
    return launch_json

def make_configuration(paths, debug: bool):
    root = '${workspaceFolder}'
    build_path = paths['build_path']
    compiler_path = f"{paths['qt_path']}/Tools/{paths['qt_mingw_tools']}"
    compiler_lib = f"{paths['qt_path']}/{paths['qt_version']}/{paths['qt_mingw']}"
    config = {
        "name": f"{platform.system()}",
        "includePath": [
            "${workspaceFolder}/**"
        ],
        "defines": [],
        "windowsSdkVersion": "10.0.19041.0",
        "compilerPath": f"{compiler_path}/bin/g++.exe",
        "cStandard": "c17",
        "cppStandard": "c++17",
        "intelliSenseMode": "windows-clang-x64",
        "compileCommands": f"{root}/{build_path}/{platform.system()}/Debug/compile_commands.json",
        "browse": {
            "path": [
                f"{compiler_lib}/lib"
            ],
            "limitSymbolsToIncludedHeaders": True,
            "databaseFilename": f"{root}/.vscode/db/browse.vs.db"
        },
        "configurationProvider": "ms-vscode.cmake-tools"
    }
    if debug:
        config['name'] += ' debug'
        config['defines'] = [ 'DEBUG' ]
    else:
        config['name'] += ' release'
        config['defines'] = [ 'NDEBUG' ]
    return config

def make_c_cpp_properties_json(paths):
    debug_config = make_configuration(paths, True)
    release_config = make_configuration(paths, False)
    config = {
        'version': 4,
        'configurations': []
    }
    config["configurations"] = [ debug_config, release_config ]
    return config

def setup_config(config_json, filename):
    config = f'{project_root()}/.vscode/{filename}'
    if os.path.isfile(config):
        os.remove(config)
    try:
        with open(config, 'w') as config_file:
            config_file.write(json.dumps(config_json, indent=4, sort_keys=True))
            config_file.close()
    except:
        print(f"[ERROR] Cannot create file '{config}'")

def main():
    paths = load_paths()
    if paths == None:
        exit()
    launch_json = make_launch_json(paths)
    c_cpp_properties_json = make_c_cpp_properties_json(paths)
    setup_config(launch_json, 'launch.json')
    setup_config(c_cpp_properties_json, 'c_cpp_properties.json')

if __name__ == "__main__":
    main()
