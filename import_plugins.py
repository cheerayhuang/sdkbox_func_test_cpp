#!/usr/bin/python

import os
import sys
import subprocess
import re
import traceback
import getopt

def trim_folder(f):
    return os.path.abspath(f).rstrip('/')

def import_plugins(plugins_dir, is_plugins=True):
    if not is_plugins:
        cmd = ['sdkbox', '--noupdate', '-vv', 'import', '-b', plugins_dir]
        print '# Call: ' + ' '.join(cmd)
        if subprocess.call(cmd) != 0:
            return 1
        return 0

    contents = os.listdir(plugins_dir)
    for c in contents:
        p = os.path.join(plugins_dir, c)
        if os.path.isdir(p) and c.find('for_v2') < 0:
            cmd = ['sdkbox', '--noupdate', '-vv', 'import', '-b', p]
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
Usage: import_plugins.py <-d plugins_folder | -p only_one_plugin_folder> [--import | --run]
    '''

def get_options(argv, options, long_opts):
    try:
        opts, args = getopt.getopt(argv, options, long_opts)
    except getopt.GetoptError:
        print "some options are invalid."
        print_usage()

    params = {}
    params['import'] = False
    params['run'] = False
    params['plugins'] = ''
    params['one_plugin'] = ''

    for opt, arg in opts:
        if opt == '-d':
            params['plugins'] = trim_folder(arg)
        if opt == '-p':
            params['one_plugin'] = trim_folder(arg)
        if opt == '--import':
            params['import'] = True
        if opt == '--run':
            params['run'] = True

    if not (params['run'] ^ params['import']):
        params['import'] = True
        params['run'] = True

    return params

def main(argv):
    if len(argv) == 0:
        print_usage()
        return 1

    params = get_options(argv,  'd:p:', ['run', 'import'])
    if not os.path.isdir(params['plugins']) and not os.path.isdir(params['one_plugin']) and params['import']:
        print '# ERROR: Plugin folder is null or a invalid directory.'
        print_usage()
        return 1

    if params['import']:
        if params['plugins'] != '':
            if import_plugins(params['plugins']) != 0:
                return 1
        else:
            if import_plugins(params['one_plugin'], False) != 0:
                return 1

    if params['run']:
        return run_proj()

    return 0


if __name__ == "__main__":
    try:
        sys.exit(main(sys.argv[1:]))
    except Exception as e:
        traceback.print_exc()
        sys.exit(1)
