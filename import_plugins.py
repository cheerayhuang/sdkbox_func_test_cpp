#!/usr/bin/python

import os
import sys
import subprocess
import re
import traceback

def trim_folder(f):
    return os.path.abspath(f).rstrip('/')

def import_plugins(plugins_dir):
    contents = os.listdir(plugins_dir)

    for c in contents:
        p = os.path.join(plugins_dir, c)
        if os.path.isdir(p) and c.find('for_v2') < 0:
            cmd = ['sdkbox.py', '--noupdate', '-vv', 'import', '-b', p]
            print '# Call: ' + ' '.join(cmd)
            if subprocess.call(cmd) != 0:
                return 1

    return 0

def run_proj():
    cmd = ['cocos', 'run', '-p', 'ios']
    print '# Build proj. Call: ' + ' '.join(cmd)

    if subprocess.call(cmd) != 0:
        return 1

    return 0

def print_usage():
    print '''Usage: import_plugins.py <plugins_folder>'''

def main(argv):
    if len(argv) == 0:
        print_usage()
        return 1

    plugins_dir = trim_folder(argv[0])
    if not os.path.isdir(plugins_dir):
        return 1


    if import_plugins(plugins_dir) != 0:
        return 1

    if run_proj() != 0:
        return 1

    return 0


if __name__ == "__main__":
    try:
        sys.exit(main(sys.argv[1:]))
    except Exception as e:
        traceback.print_exc()
        sys.exit(1)
