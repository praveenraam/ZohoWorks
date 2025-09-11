import subprocess
import os

BASE_PATH = "/home/praveen-pt7975/Documents/allBuilds"

def get_remote_tag():
    try:
        result = subprocess.run(
            ['git', 'ls-remote', '--tags', 'origin'],
            capture_output=True,
            text=True,
            check=True
        )
        return result.stdout
    except subprocess.CalledProcessError as e:
        print(f'Error running the git command : {e}')
        return None

def extract_rel_tag(data,input_val):
    if data:
        for line in data.strip().split('\n'):
            parts = line.split()
            if len(parts) == 2:
                if "REL" in parts[1]:
                    rel_tag = parts[1].split("REL",1)[1]
                    rel_tag = "REL" + rel_tag
                    if input_val == rel_tag:
                        return True
    return False or input_val == "master"

def check_already_exist(tag_name,base_path=BASE_PATH):
    try:
        target_path = os.path.join(base_path, f"{tag_name}_build") 
        return os.path.exists(target_path)
    except Exception as e:
        print(f"Error while checking tag in allBuilds folder: {e}")
        return False

def git_checkout_tag(tag_name):
    try:
        result = subprocess.run(
            ['git','checkout',tag_name],
            capture_output=True,
            text=True,
            check=True
        )
        return result
    except subprocess.CalledProcessError as e:
        print(f'Error running the git command : {e}')
        return None

def create_folder_for_build(tag_name,base_path=BASE_PATH):
    try:
        os.makedirs(f'{base_path}/{tag_name}_build', exist_ok=True)
        print(f'Successfully created the folder for build')
    except Exception as e:
        print(f'Error while creating folder for build : {e}')

def create_folder(folderName):
    try:
        os.makedirs(folderName, exist_ok=True)
        print("Created the pgData Folder")
    except Exception as e:
        print("Failed in creating the pgData Folder")

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

def run_configure_command(tag_name):
    try:
        prefix_path = f"{BASE_PATH}/{tag_name}_build"
        print(prefix_path)
        subprocess.run(
            ['./configure', f'--prefix={prefix_path}'],
            check=True
        )
    except Exception as e:
        print(f'Error in configure line : {e}')

def run_distclean_command():
    try:
        result = subprocess.run(
            ['make','distclean'],
            check=True
        )
        print("Ran distclean and processed")
    except subprocess.CalledProcessError as e:
        print("Moving to the next step, no need distclean command to run")

def run_cd_command(path):
    try:
        os.chdir(path)
        print(f"Changed directory to {path}")
    except Exception as e:
        print(f'Error in changing directory to : {path} : {e}')

if __name__ == "__main__":
    data = get_remote_tag()
    if not data:
        print("No tags found or error occurred")
        exit(1)
    
    input_value = ""
    while True:
        input_value = input("Enter a Tag Name : ").strip()
        if input_value and extract_rel_tag(data,input_value):
            print(f"Tag : {input_value} found")
            break
        else:
            print("Enter a valid tag name, No Tag found")

    if(check_already_exist(input_value)):
        print("Already exist")
        print("Run the start file!!")
        ## Change to run yourself
    else:
        print(f"We need build this Tag version : {input_value}")
        if git_checkout_tag(input_value):
            print("Code updated to the requested TAG")
            create_folder_for_build(input_value)

            run_distclean_command()
            run_command(['make','clean'])
            run_configure_command(input_value)
            run_command(['make'])
            run_command(['make install'])
            run_cd_command(f'/home/praveen-pt7975/Documents/allBuilds/{input_value}_build')
            create_folder('pgData')
            run_cd_command('bin')
            run_command([f'./initdb -D {BASE_PATH}/{input_value}_build/pgData'])
            run_command([f'./pg_ctl -D {BASE_PATH}/{input_value}_build/pgData -l {BASE_PATH}/{input_value}_build/pgData/logfile start'])
            # run_command([])

        else:
            print("Couldn't update the code base to requested TAG version")