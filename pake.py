import argparse
import os
import shutil
from pathlib import Path
import subprocess

# --- Config ---
project_name = 'qlib'
build_dir_path = 'build'
# --- End Config ---

def clean():
    """Remove the `build` directory and everything in it

    Raises:
        RuntimeError: Build path exists, but is not a directory
    """
    build_dir = Path(build_dir_path)
    if build_dir.is_dir():
        shutil.rmtree(build_dir_path)
        print("clean: '{}' directory deleted".format(build_dir_path))
    elif build_dir.is_file():
        raise RuntimeError("'{}' exists, but is not a directory".format(build_dir_path))
    else:
        print("clean: '{}' dir does not exist".format(build_dir_path))

def make_build_dir():
    """Create the build directory if it does not already exist

    Raises:
        RuntimeError: Build path exists, but is not a directory
    """
    build_dir = Path(build_dir_path)
    if build_dir.is_dir():
        print("make_build_dir: '{}' already exists".format(build_dir_path))
    elif build_dir.is_file():
        raise RuntimeError("'{}' exists, but is not a directory".format(build_dir_path))
    else:
        build_dir.mkdir()
        print("make_build_dir: '{}' directory created".format(build_dir_path))

def change_dir(path):
    """Change the current working directory

    Args:
        path (string): The path to change to

    Returns:
        string: The old path
    """
    old_path = os.getcwd()
    os.chdir(path)
    print("changed directory to '{}'".format(os.getcwd()))
    return old_path

def run_conan():
    """Run conan to install / build dependencies

    Raises:
        RuntimeError: conan returned non-zero exit code
    """
    make_build_dir()
    old_path = change_dir(build_dir_path)

    error = os.system("conan install .. --build=missing")
    if error != 0:
        raise RuntimeError("running conan returned exit code {}".format(error))

    print("conan: installation / build executed")        

    change_dir(old_path)

def run_cmake():
    """Run the cmake utility to create build / project files

    Raises:
        RuntimeError: cmake returned non-zero error code
    """
    old_path = change_dir(build_dir_path)
    error = os.system("cmake ..")
    if error != 0:
        raise RuntimeError("running cmake returned exit code {}".format(error))

    print("cmake: created project files")        

    change_dir(old_path)

def build_binaries():
    """Run cmake to build the binary targets (in Release mode)

    Raises:
        RuntimeError: The cmake operation returned a non-zero exit code
    """
    old_path = change_dir(build_dir_path)
    error = os.system("cmake --build . --config Release")
    if error != 0:
        raise RuntimeError("running cmake to build binaries returned exit code {}".format(error))

    print("cmake: Release binaries built")        

    change_dir(old_path)

def run_tests():
    """Run the test executable

    Raises:
        RuntimeError: The test executable returned a non-zero exit code
    """
    test_command = Path(build_dir_path) / Path("bin") / Path("test-{}".format(project_name))
    error = os.system("{}".format(test_command))
    if error != 0:
        raise RuntimeError("running tests returned exit code {}".format(error))

def show_include_paths():
    """Retrieve the conan package paths to use in include files
    """
    cmd = "conan info --paths --only package_folder ."
    result = subprocess.run(cmd, stdout=subprocess.PIPE).stdout.decode()

    for line in result.split('\n'):
        if ':' in line:
            print("\"{}/**\",".format(line.split(': ')[1].strip().replace('\\', '/')))

# Parse command line and execute
parser = argparse.ArgumentParser(
    formatter_class=argparse.RawDescriptionHelpFormatter,
    description="""
Lightweight make / build tool"

Any number of targets may be requested.

    clean       Clean the build directory
    conan       Run conan installation
    cmake       Run cmake to create build files (runs 'conan')
    build       Build the binaries (runs 'cmake')
    test        Run the test binary (runs 'build')
    includes    Retrieve the locations of conan packages for the include list in vscode
""")
parser.add_argument('targets',
    metavar='T',
    nargs='+',
    help='target(s) to make')
args = parser.parse_args()

for t in args.targets:
    if t == 'clean':
        clean()
    elif t == 'conan':
        run_conan()
    elif t == 'cmake':
        run_conan()
        run_cmake()
    elif t == 'build':
        run_conan()
        run_cmake()
        build_binaries()
    elif t == 'test':
        run_conan()
        run_cmake()
        build_binaries()
        run_tests()
    elif t == 'includes':
        show_include_paths()
    else:
        raise argparse.ArgumentError(None, "unrecognised target '{}'".format(t))
