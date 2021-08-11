import os
import os.path
import json

PROJECT_NAME = 'lazycoder'

def load(filename: str):
    if len(filename) == 0 or not os.path.isfile(filename):
        print(f"[ERROR] Invalid path to file: {filename}")
        return None

    paths = {}
    try:
        with open(filename, "r") as json_file:
            paths = json.load(json_file)
            json_file.close()
    except:
        print(f"[ERROR] Cannot read a file '{filename}'")
        return None

    return paths

def load_paths():
    return load(f"{project_root()}/scripts/paths.custom.json")

def project_root():
    cwd = str(os.path.dirname(os.path.realpath(__file__)))
    pos = cwd.find(PROJECT_NAME)
    if pos == -1:
        print("[ERROR] Cannot detect project file. Is your project name is 'lazycoder'?")
        return None

    pos += len(PROJECT_NAME)
    return cwd[:pos]

def change_dir(dir):
    path = f"{os.getcwd()}/{dir}"
    if not os.path.isdir(path):
        os.mkdir(path)
    os.chdir(path)
