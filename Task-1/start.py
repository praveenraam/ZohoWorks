import subprocess
import os
import script

PORT = 5432
BASE_PATH = "/home/praveen-pt7975/Documents/allBuilds"

def check_on_process_on_port(port):
    try:
        result = subprocess.run(
            ['lsof','-i',f':{port}'],
            check=True,
            capture_output=True,
            text=True
        )
        print(f"DEBUG: lsof output for port {port}:\n{result.stdout}")
        return result.stdout.strip()
    except subprocess.CalledProcessError:
        return False
    except Exception as e:
        print(f"Error in checking default port for starting the process : {e}")
        return False
    
def folder_exist(folder_name):
    path = os.path.join(BASE_PATH,folder_name)
    return os.path.isdir(path)

# def run_command(command):
#     try:
#         result = subprocess.run(
#             command,
#             check=True,
#             shell=True
#         )
#         print(f'{command} got executed')
#     except Exception as e:
#         print(f'Error in executing the command : {command} : {e}')

def run_cd_command(path):
    try:
        os.chdir(path)
        print(f"Changed directory to {path}")
    except Exception as e:
        print(f'Error in changing directory to : {path} : {e}')

def run_createDB_command(db_name):
    try:
        subprocess.run(
            f'./createdb {db_name}', shell=True, check=True
        )
        print("Created DB")
    except subprocess.CalledProcessError as e:
        print(f"Already exist or failed : {e}" )

if __name__ == "__main__":
    input_value = ""
    while check_on_process_on_port(PORT):
        print(f"Another process is running on the {PORT}")

        option_for_port = int(input("Enter 1 to exit Or Any other port number to run on it\n"))
        
        if option_for_port == 1:
            print("At exit()")
            exit()
        PORT = option_for_port
    
    version_name = input("Enter a version to start : ")
    version_name = version_name+"_build"
    
    if not folder_exist(version_name):
        print(f'The Version is not yet built')
        exit()
    
    full_path = BASE_PATH+'/'+version_name

    script.run_cd_command(full_path)
    script.run_cd_command('bin')
    
    #starts
    script.run_command([f'./pg_ctl -D {BASE_PATH}/{version_name}/pgData -l {BASE_PATH}/{version_name}/pgData/logfile -o "-p {PORT}" start'])
    
    option_ans = int(input('Enter \n1 for custom named DB \nAny Number else for version name to be default\n'))
    db_name = version_name
    if option_ans == 1:
        db_name = input_value(f"Enter your custom DB Name")
    
    run_createDB_command(db_name)
    
    # handle if the DB already exist or not, if yes inform
    # else create
    script.run_command(f'./psql {db_name}')

    # Stops
    script.run_command([f'./pg_ctl -D {BASE_PATH}/{version_name}/pgData -l {BASE_PATH}/{version_name}/pgData/logfile stop'])

            
