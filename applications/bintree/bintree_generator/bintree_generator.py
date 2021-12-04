import os
import getpass
import sys
import shutil

## MSG_LENGHT
## MAX_SLAVES
## NUMER OF SAVES 
## DEBUG

if len(sys.argv) < 5:
    print("USAGE: python " + sys.argv[0] + " MSG_LENGHT MAXSLAVES NUM.OF.SLAVES DEBUG")
    exit()

MSG_LENGHT = int(sys.argv[1])
MAX_SLAVES = int(sys.argv[2])
NUMBER_SLAVES = int(sys.argv[3])
DEBUG = int(sys.argv[4])
uName = getpass.getuser()


# Create slave list to input to .c header
slaveList = ""
slaveList = "bintree_slave0"
for x in range(1,NUMBER_SLAVES):
   slaveList = slaveList + "," + "bintree_slave" + str(x)

### DELETE ALL ".c" AND ".h" FILES IN THE PREVIOUS FOLDER
dir_name = os.path.normpath(os.getcwd() + os.sep + os.pardir)
test = os.listdir(dir_name)
for item in test:
    if item.endswith(".c"):
        os.remove(os.path.join(dir_name, item))
    if item.endswith(".h"):
        os.remove(os.path.join(dir_name, item))

### PUBLISH MASTER TO APPLICATION FOLDER
source_filepath = "bintree_master_source.c"
target_filepath = "../bintree_master.c"
targetFile_handler = open(target_filepath, "wb+")
sourceFile_handler = open(source_filepath, "r+")
print("Creating master files")
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
    targetFile_handler.write(line)
    line = sourceFile_handler.readline()

sourceFile_handler.close()
targetFile_handler.close()

### PUBLISH HEADER TO APPLICATION FOLDER
source_filepath = "bintree.h"
target_filepath = "../bintree.h"
targetFile_handler = open(target_filepath, "wb+")
sourceFile_handler = open(source_filepath, "r+")
print("Creating master files")
line = sourceFile_handler.readline()
while line:
  
    targetFile_handler.write(line)
    line = sourceFile_handler.readline()

sourceFile_handler.close()
targetFile_handler.close()


### GENERATE SLAVES
source_file = "bintree_slave_source.c"
for x in range(0,NUMBER_SLAVES):
    print("Creating slave " + str(x) + "file...")
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
        targetFile_handler.write(line)
        line = sourceFile_handler.readline()

    sourceFile_handler.close()
    targetFile_handler.close()

