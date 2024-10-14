import argparse
import os
import subprocess
import threading
from time import sleep


def get_executable_path():
    working_dir = os.path.dirname(os.path.abspath(__file__))
    executable_path = os.path.join(
        working_dir, "build", "ClientMock", "NovalandClientMock")
    return executable_path


def run(ip, port):
    executable_path = get_executable_path()
    print(f"Attempting to run: {executable_path}")
    subprocess.run([executable_path, "-a", ip, "-p", str(port)])


def main():
    print("Done")
    parser = argparse.ArgumentParser()
    parser.add_argument('-c', type=int,
                        help="Number of clients for one server")
    parser.add_argument('-n', type=int, help="Number of servers")
    parser.add_argument('-ip', action="store", help="IP address")

    args = parser.parse_args()

    number_of_clients = 1
    number_of_servers = 1
    port = 5000
    ip = "127.0.0.1"

    if (args.c):
        number_of_clients = args.c
    if (args.n):
        number_of_servers = args.n
    if (args.ip):
        ip = args.ip

    for i in range(number_of_servers):
        for j in range(number_of_clients):
            sleep(1)
            port = 5000 + i
            thread = threading.Thread(target=run, args=(ip, port))
            thread.start()


if __name__ == "__main__":
    main()
