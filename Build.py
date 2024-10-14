import os
import subprocess
import argparse
import shutil
import threading
import json
import sys


class NovalandProject:
    def __init__(self, project_name, application_name):
        self.project_name = project_name
        self.application_name = application_name
        self.build_dir = self.get_build_directory()
        self.project_path = os.path.join(self.build_dir, project_name)

    @staticmethod
    def get_build_settings():
        with open("build_settings.json", "r") as f:
            return json.load(f)

    def get_build_directory(self):
        build_settings = NovalandProject.get_build_settings()
        build_folder = build_settings.get("build_folder")
        return os.path.abspath(build_folder)

    @staticmethod
    def delete_all_libraries_from_dir(dir):
        for file in os.listdir(dir):
            if file.endswith(('.dll', '.so', '.dylib')):
                try:
                    os.remove(os.path.join(dir, file))
                except Exception as e:
                    print(f"Error deleting {file}: {e}")

    @staticmethod
    def copy_lib_files_to_dir(build_dir, dest_dir):
        for file in os.listdir(build_dir):
            if file.endswith(('.dll', '.so', '.dylib')):
                dest_path = os.path.join(dest_dir, file)
                if os.path.exists(dest_path):
                    os.remove(dest_path)
                try:
                    shutil.copy(os.path.join(build_dir, file), dest_path)
                except Exception as e:
                    print(f"Error copying {file}: {e}")

    def get_executable_path(self):
        if os.name == "nt":
            return os.path.join(self.project_path, f"{self.application_name}.exe")
        elif os.name == "posix":
            return os.path.join(self.project_path, self.application_name)

    def run(self):
        if os.path.exists(self.project_path):
            executable_path = self.get_executable_path()
            print(f"Attempting to run: {executable_path}")
            subprocess.run([executable_path])
        else:
            print(f"{self.project_name} path does not exist!")

    @ staticmethod
    def run_command(cmd, error_message):
        try:
            # We directly connect to sys.stdout and sys.stderr to preserve colors
            process = subprocess.Popen(
                cmd, stdout=sys.stdout, stderr=sys.stderr)

            # Wait for the process to complete and fetch the return code
            returncode = process.wait()

            if returncode != 0:
                print(error_message)
                exit(1)
        except FileNotFoundError:
            print(error_message)
            exit(1)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('-s', action='store_true', help="Run server")
    parser.add_argument('-c', action='store_true', help="Run client")
    parser.add_argument('-n', type=int, help="Number of clients to run")

    args = parser.parse_args()

    server = NovalandProject("Server", "NovalandServer")
    client = NovalandProject("ClientGui", "NovalandClientGUI")

    NovalandProject.delete_all_libraries_from_dir(server.build_dir)

    NovalandProject.run_command(
        ["ninja", "--version"], "Ninja build system is not installed. Please install it.")
    NovalandProject.run_command(
        ["ninja", "-C", client.build_dir], "Ninja build failed.")

    settings = NovalandProject.get_build_settings()
    if 'type' in settings:
        if 'wrapper' in settings['type']:
            NovalandProject.copy_lib_files_to_dir(
                server.build_dir, settings['wrapper_lib_dir'])
        if 'godot' in settings['type']:
            NovalandProject.copy_lib_files_to_dir(
                server.build_dir, settings['godot_lib_dir'])

    if args.s:
        t_server = threading.Thread(target=server.run)
        t_server.start()
        print("Server is running...")

    if args.c:
        number_of_clients = 1
        if args.n:
            number_of_clients = args.n

        for i in range(number_of_clients):
            t_client = threading.Thread(target=client.run)
            t_client.start()

    if args.s:
        t_server.join()

    if args.c:
        t_client.join()

    if not args.s and not args.c:
        print("Build has been successful!")


if __name__ == "__main__":
    main()
