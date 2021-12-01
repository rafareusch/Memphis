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

# ## PUBLISH MASTER TO APPLICATION FOLDER
print( "Generating master .c files")
source_filepath = "bintree_master_SOURCE.c"
target_filepath = "../bintree_master.c"
targetFile_handler = open(target_filepath, "wb+")
sourceFile_handler = open(source_filepath, "r+")

line = sourceFile_handler.readline()
while line:

    if (line.__contains__(" MSG_LENGHT")):
        line = line.rstrip('\n')
        line += (str(MSG_LENGHT) + ";" + "\n")
    if (line.__contains__(" NUMBER_OF_SLAVES")):
        line = line.rstrip('\n')
        line += (str(NUMBER_SLAVES) + ";"+ "\n")
    if (line.__contains__(" MAX_SLAVES")):
        line = line.rstrip('\n')
        line += (str(MAX_SLAVES) + ";" + "\n")
    if (line.__contains__("int Slave[MAX_SLAVES] = {};")):
        line = line.replace("{}", "{" + slaveList + "}")
        print("entrou")
        
    targetFile_handler.write(line)
    line = sourceFile_handler.readline()

sourceFile_handler.close()
targetFile_handler.close()


### GENERATE SALVES
print( "Generating slave .c files")
source_file = "bintree_slave_SOURCE.c"
for x in range(0,NUMBER_SLAVES):
    target_file = "../bintree_slave" + str(x) + ".c"
    targetFile_handler = open(target_file, "wb+")
    sourceFile_handler = open(source_file, "r+")

    line = sourceFile_handler.readline()
    while line:

        if (line.__contains__(" MSG_LENGHT")):
            line = line.rstrip('\n')
            line += (str(MSG_LENGHT) + ";" + "\n")
        if (line.__contains__(" NUMBER_OF_SLAVES")):
            line = line.rstrip('\n')
            line += (str(NUMBER_SLAVES) + ";"+ "\n")
        if (line.__contains__(" MAX_SLAVES")):
            line = line.rstrip('\n')
            line += (str(MAX_SLAVES) + ";" + "\n")
        if (line.__contains__("int Slave[MAX_SLAVES] = {};")):
            line = line.replace("{}", "{" + slaveList + "}")
            print("entrou")

        targetFile_handler.write(line)
        line = sourceFile_handler.readline()

    sourceFile_handler.close()
    targetFile_handler.close()

