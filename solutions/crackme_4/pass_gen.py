
import psutil


proc_name = "PIDXploit.exe"

for p in psutil.process_iter():

    if p.name() == proc_name:
        
        print("EndIsNear-"+str(p.pid))