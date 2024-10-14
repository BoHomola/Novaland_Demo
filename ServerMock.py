import argparse
import os
import subprocess
import threading
from time import sleep


def get_executable_path():
    working_dir = os.path.dirname(os.path.abspath(__file__))
    executable_path = os.path.join(
        working_dir, "build", "Server", "NovalandServer")
    return executable_path


def run(port):
    executable_path = get_executable_path()
    print(f"Attempting to run: {executable_path}")
    subprocess.run([executable_path, "-p", str(port)])


def main():
    print("Done")
    parser = argparse.ArgumentParser()
    parser.add_argument('-n', type=int, help="Number of servers")

    args = parser.parse_args()

    number_of_servers = 1

    if (args.n):
        number_of_servers = args.n

    for i in range(number_of_servers):
        sleep(1)
        port = 5000 + i
        thread = threading.Thread(target=run, args=(port,))
        thread.start()


if __name__ == "__main__":
    main()
