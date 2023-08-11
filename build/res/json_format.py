#!/usr/bin/python3

import json

files = ["settings.json", "strings.json"]

def make_readable(filename):
    with open(filename, "r") as file:
        content = file.read()
    with open(filename, "w") as file:
        file.write(json.dumps(json.loads(content), indent=4))

for file in files:
    make_readable(file)
