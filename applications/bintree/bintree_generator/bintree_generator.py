import os
import getpass
import sys
import shutil

## MSG_LENGHT
## MAX_SLAVES
## NUMER OF SAVES 
## DEBUG

if len(sys.argv) < 5:
    print("USAGE: file.py MSG_LENGHT MAXSLAVES NUM.OF.SLAVES DEBUG")
    exit()

MSG_LENGHT = int(sys.argv[1])
MAX_SLAVES = int(sys.argv[2])
NUMBER_SLAVES = int(sys.argv[3])
DEBUG = int(sys.argv[4])
uName = getpass.getuser()

slaveList = ""

slaveList = "bintree_slave0"
for x in range(1,NUMBER_SLAVES):
   slaveList = slaveList + "," + "bintree_slave" + str(x)

### DELETE ALL ".c" FILES IN THE PREVIOUS FOLDER
dir_name = os.path.normpath(os.getcwd() + os.sep + os.pardir)
test = os.listdir(dir_name)
for item in test:
    if item.endswith(".c"):
        os.remove(os.path.join(dir_name, item))


### PUBLISH MASTER TO APPLICATION FOLDER
source_filepath = "bintree_master_source.c"
target_filepath = "../bintree_master.c"
targetFile_handler = open(target_filepath, "wb+")
sourceFile_handler = open(source_filepath, "r+")

line = sourceFile_handler.readline()
while line:

    if (line.__contains__("#define MSG_LENGHT")):
        line = line.rstrip('\n')
        line += (str(MSG_LENGHT) +  "\n")
    if (line.__contains__("#define NUMBER_OF_SLAVES")):
        line = line.rstrip('\n')
        line += (str(NUMBER_SLAVES) +  "\n")
    if (line.__contains__("#define MAX_SLAVES")):
        line = line.rstrip('\n')
        line += (str(MAX_SLAVES)  + "\n")
    if (line.__contains__("int Slave[MAX_SLAVES] = {};")):
        line = line.replace("{}", "{" + slaveList + "}")
        print("Created all master .c files")
        
    targetFile_handler.write(line)
    line = sourceFile_handler.readline()

sourceFile_handler.close()
targetFile_handler.close()


### GENERATE SALVES
source_file = "bintree_slave_source.c"
for x in range(0,NUMBER_SLAVES):
    target_file = "../bintree_slave" + str(x) + ".c"
    targetFile_handler = open(target_file, "wb+")
    sourceFile_handler = open(source_file, "r+")

    line = sourceFile_handler.readline()
    while line:

        if (line.__contains__("#define MSG_LENGHT")):
            line = line.rstrip('\n')
            line += (str(MSG_LENGHT)  + "\n")
        if (line.__contains__("v NUMBER_OF_SLAVES")):
            line = line.rstrip('\n')
            line += (str(NUMBER_SLAVES) + "\n")
        if (line.__contains__("#define MAX_SLAVES")):
            line = line.rstrip('\n')
            line += (str(MAX_SLAVES)  + "\n")
        if (line.__contains__("int Slave[MAX_SLAVES] = {};")):
            line = line.replace("{}", "{" + slaveList + "}")
            print("Created all slave .c files")

        targetFile_handler.write(line)
        line = sourceFile_handler.readline()

    sourceFile_handler.close()
    targetFile_handler.close()

