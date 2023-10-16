
import os
import glob
import argparse
import pathlib

# https://www.digitalocean.com/community/tutorials/get-file-extension-in-python
def get_file_extension(filename):
    return pathlib.Path(filename).suffix

# os.listdir just lists the files under the directory.
# src = f"{current_dir}/{f}"

# https://stackoverflow.com/questions/7099290/how-to-ignore-hidden-files-using-os-listdir
def listdir_nohidden(path):
    return glob.glob(os.path.join(path, "*"))


def convert_file(dst):
    # convert to utf-8
    os.system(f"iconv -f cp936 -t UTF-8 {dst} -o {dst}")
    # remove ^M char by dos2unix
    os.system(f"dos2unix {dst}")
    os.system(f"git add {dst}")

def convert(current_dir):
    files = ( f for f in listdir_nohidden(current_dir) )
    for src in files:
        if ' ' in src:
            dst = src.replace(' ', '-')
            os.rename(src, dst)
            if os.path.exists(src):
                os.system(f"git rm {src}")
                #os.remove(src)
        else:
            dst = src

        if os.path.isfile(dst) and get_file_extension(dst) in ['.cpp', '.cc', '.h', '.hpp']:
            convert_file(dst)
        else:
            convert(dst)


parser = argparse.ArgumentParser(
        prog = 'format_conversion',
        description = "Convert the Windows file to unix",
        epilog = 'Text at the bottom of help')

parser.add_argument('-b', '--basedir')
parser.add_argument('-f', '--file')

if __name__ == '__main__':
    args = parser.parse_args()
    print(args)
    print(args.basedir)
    print(args.file)

    convert(args.basedir)
