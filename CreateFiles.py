import os
import subprocess
import argparse
import json


def parse_arguments():
    parser = argparse.ArgumentParser()
    parser.add_argument('-n', action='store_true',
                        help="Recreate build folder")
    parser.add_argument('-r', action='store_true',
                        help="Set build type to Release")
    parser.add_argument('-nr', action='store_true',
                        help="Disable the renderer")
    parser.add_argument('-android', action='store_true',
                        help="Build for android")
    parser.add_argument('-godot', action='store_true',
                        help="Build for android")
    parser.add_argument('-server', action='store_true',
                        help="Build for android")
    parser.add_argument('-client', action='store_true',
                        help="Build for android")
    parser.add_argument('-profiler', action='store_true',
                        help="Enable Tracy profiler")
    parser.add_argument('-wrapper', action='store_true',
                        help="Enable Tracy profiler")
    return parser.parse_args()


def remove_and_create_build_folder():
    print("Removing build folder")
    if os.path.exists("build"):
        if os.name == "nt":
            os.system("rmdir /s /q build")
        if os.name == "posix":
            os.system("rm -r build")
    print("Creating build folder")
    os.mkdir("build")


def check_dependency_installed(cmd, error_msg):
    try:
        subprocess.run([cmd, "--version"],
                       stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    except FileNotFoundError:
        print(error_msg)
        exit(1)


def save_build_settings(args, build_folder):
    settings_file = 'build_settings.json'
    data = {}

    if os.path.exists(settings_file):
        with open(settings_file, 'r') as f:
            data = json.load(f)

    data["platform"] = "android" if args.android else "native"
    if args.godot:
        data["type"] = "godot"
    if args.wrapper:
        data["type"] = "wrapper"
    data["build_folder"] = build_folder

    with open(settings_file, 'w') as f:
        json.dump(data, f, indent=4)


def run_cmake(args):
    build_type = "release" if args.r else "debug"
    platform_type = "android" if args.android else "native"
    build_folder = f"build_{build_type}_{platform_type}".rstrip("_")

    build_options = []

    # Set build type
    if args.r:
        build_options.append("-DCMAKE_BUILD_TYPE=Release")
    else:
        build_options.append("-DCMAKE_BUILD_TYPE=Debug")

    # Set server GUI options
    if args.nr:
        build_options.append("-DDISABLE_SERVER_GUI=ON")
    else:
        build_options.append("-DDISABLE_SERVER_GUI=OFF")

    # Set Godot build options
    if args.godot:
        build_options.append("-DBUILD_GODOT=ON")
    else:
        build_options.append("-DBUILD_GODOT=OFF")

    # Set server build options
    if args.server:
        build_options.append("-DBUILD_SERVER=ON")
    else:
        build_options.append("-DBUILD_SERVER=OFF")

    # Set raylib build options
    if args.client:
        build_options.append("-DBUILD_CLIENT=ON")
    else:
        build_options.append("-DBUILD_CLIENT=OFF")

    # Set Tracy profiler build_options
    if args.profiler:
        build_options.append("-DPROFILER_ENABLED=ON")
    else:
        build_options.append("-DPROFILER_ENABLED=OFF")

    # Set wrapper build_options
    if args.wrapper:
        build_options.append("-DBUILD_WRAPPER=ON")
    else:
        build_options.append("-DBUILD_WRAPPER=OFF")

    # Set Android specific options
    if args.android:
        build_folder = "build_android"
        build_options.extend([
            "-DCMAKE_SYSTEM_NAME=Android",
            "-DCMAKE_ANDROID_ARCH_ABI=arm64-v8a",
            "-DANDROID_NDK=/home/bo/Android/Sdk/ndk/26.0.10792818/",
            "-DCMAKE_SYSTEM_VERSION=31"
        ])

    # Run the command using subprocess

    cmd = ["cmake", "-GNinja", f"-B{build_folder}"] + build_options
    subprocess.run(cmd)

    # copy compile_commands.json to root build_folder
    if os.name == "posix":
        os.system(f"cp {build_folder}/compile_commands.json .")
    elif os.name == "nt":
        os.system(f"copy {build_folder}\\compile_commands.json .")

    save_build_settings(args, build_folder)


def main():
    args = parse_arguments()

    if args.n:
        remove_and_create_build_folder()

    check_dependency_installed(
        "cmake", "CMake not installed. Please install it.")
    check_dependency_installed(
        "ninja", "Ninja build system is not installed. Please install it.")

    run_cmake(args)


if __name__ == "__main__":
    main()
