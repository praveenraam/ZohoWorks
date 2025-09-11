import os
import subprocess

BASE_PATH = "/home/praveen-pt7975/Documents/allBuilds"

def run_command(command):
    try:
        result = subprocess.run(
            command,
            check=True,
            shell=True
        )
        print(f'{command} got executed')
    except Exception as e:
        print(f'Error in executing the command : {command} : {e}')


def run_cd_command(path):
    try:
        os.chdir(path)
        print(f"Changed directory to {path}")
    except Exception as e:
        print(f'Error in changing directory to : {path} : {e}')


if __name__ == "__main__":
    version_name = input("Enter a version to start : ")

    full_path = BASE_PATH+'/'+version_name+'_build'

    run_cd_command(full_path)
    run_cd_command('bin')

    run_command([f'./pg_ctl -D {full_path}/pgData -l {full_path}/pgData/logfile stop'])