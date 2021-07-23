import os
from typing import Any
from zipfile import ZipFile
import datetime
import json

password    = b"build"

build_dir   = "builds/"
bin_path    = "out/build/x64-Release/"

json_builds = {}
last_build_num : int

print("Openning builds_info.json...")

def clear_file(path):
    open(path, "w").close()

with open('builds_info.json', 'r') as build_config:
    print("Reading data...")

    json_builds = json.load(build_config)

    last_build_num = len(json_builds)
    last_build = json_builds[str(last_build_num)]
    
    print(f"Last build date: { last_build['date'] }, number: { last_build_num }")

    json_builds[str(last_build_num + 1)] = {
        "date" : str(datetime.datetime.now())
    }

with open('builds_info.json', 'w') as write_build_config:
    json.dump(json_builds, write_build_config, indent=4)
    print("Json sucessfully writed!")

build_str = f'build_{"0" if last_build_num < 10 else ""}{last_build_num}'

zip_file = ZipFile(f"{build_dir}/{build_str}.zip", 'w')

zip_files = []

def recursive_parse(dir):
    for folder_name, subfolders, filenames in os.walk(dir):
        for filename in filenames:
            file_bytes : bytes
            joined_path = os.path.join(folder_name, filename)
            with open(joined_path, "rb") as read_file:
                file_bytes = read_file.read()
            zip_files.append( [joined_path, file_bytes] )

recursive_parse(f"{bin_path}/bin/")
recursive_parse(f"{bin_path}/gamedata/")

print("Writing files in .zip...")

for file, size in zip_files:
    bad_path = "out/build/x64-Release//"
    converted_path = file.replace(bad_path, "")
    zip_file.writestr(converted_path, size)
    print(f"[+] {converted_path}")

zip_file.setpassword(pwd=password)
zip_file.close()

print("Done!")