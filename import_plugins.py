#!/usr/bin/python

import os
import sys
import subprocess
import re
import traceback
import getopt

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
    print '''
Usage: import_plugins.py <plugins_folder> [--dont_run]
NOTE: plugins_folder should be followed by the command as the 1st argument.
    '''

def get_options(argv, options, long_opts):
    try:
        opts, args = getopt.getopt(argv, options, long_opts)
    except getopt.GetoptError:
        print "some options are invalid."
        print_usage()

    params = {}
    params['dont_run'] = False

    for opt, arg in opts:
        if opt == '--dont_run':
            params['dont_run'] = True

    return params

def main(argv):
    if len(argv) == 0:
        print_usage()
        return 1

    plugins_dir = trim_folder(argv[0])
    if not os.path.isdir(plugins_dir):
        print '# ERROR: "{0}" is a invalid directory.'.format(argv[0])
        print_usage()
        return 1

    params = get_options(argv[1:],  '', ['dont_run'])

    if import_plugins(plugins_dir) != 0:
        return 1

    if params['dont_run']:
        return 0

    if run_proj() != 0:
        return 1

    return 0


if __name__ == "__main__":
    try:
        sys.exit(main(sys.argv[1:]))
    except Exception as e:
        traceback.print_exc()
        sys.exit(1)
