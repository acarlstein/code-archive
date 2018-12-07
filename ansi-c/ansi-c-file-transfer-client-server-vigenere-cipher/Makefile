#########################################################################
# Author: Alejandro G. Carlstein Ramos Mejia
# Description: Client/Server File Transfer using Vergene Cipher
#
#
# make <= compile all files
# make build <= compile all files
# make all <= clean and compile all files
# make ssh <= Connect to server and go to folder cli_serv
# make upload <= Upload files on SRC_FILES list to server
# make uploadssh <= Upload files on SRC_FILES list to server and connect to server
# make submit <= Tar files on SRC_FILES list
# make zipsubmit <= Tar files on SRC_FILES list and gzip them
# make clean <= Clean all executable and *.o files
# make debug_server <= Debug server using dbg
# make debug_client <= Debug client using dbg
# make ldebug_server <= Debug for leaks on server
# make ldebug_client <= Debug for leaks on client
##########################################################################

##########################################################################
# Variables
##########################################################################

# PROJECT is the name used when preparing for sumit/
# The tar and/or zip file will be using this name
PROJECT = server_client_vergene

# SRC_FILES are list of files in the project.
# This list is used when uploading files to the server.
# Also, this list is used when tar/zipped for submit
SRC_FILES = \
	cli.c \
	serv.c\
	default.h \
	default.c \
	text.txt\
	Makefile \
	README

# OpenSSH SSH client (remote login program)
SSH = ssh

# secure copy (remote file copy program)
# SCP is used for uploading files to the server in secure mode
SCP = scp

# FOLDER_SERVER is the folder that SSH and SCP will try to access after login
FOLDER_SERVER = server_client_vergene

# SSH_SERVER is the hostname of the server
SSH_SERVER = bingsuns2.cc.binghamton.edu

# SSH_OPTION
# -t opens a pseudo-tty with in the current session.
# This flag is required to execute the commands on SSH_CD_FOLDER
SSH_OPTION = -t

# SSH_CD_FOLDER executes cd
# Then change the prompt to show the number of bash in the server
SSH_CD_FOLDER = "cd $(FOLDER_SERVER); bash; echo $PS1"

# CC indicates which compiler is going to be used
CC = gcc

# Files required for compiling the server
CODE_SERVER_FILE = serv.c default.c

# Files required for compiling the client
CODE_CLIENT_FILE = cli.c default.c

# Name of the executable file for the server
EXEC_SERVER_FILE = serv

# Name for the executable file for the client
EXEC_CLIENT_FILE = cli

# Flags for the compiler
# -g indicate to provide debuggin information
# -Wall activates the warnings.
# -lm indicate the compiler to add basic mathematics libraries
CFLAGS = -g -Wall -lm

# COMPILE is the combination of the compiler with the flags
COMPILE = $(CC) $(CFLAGS)

# MFLAGS are flags that require to be added at the end
MFLAGS =

# USERNAME is used later when required to do an upload followed with ssh
USERNAME =

# Detect if the computer is SunOS to add flags needed for compiling
UNAME := $(shell uname)
ifeq ($(UNAME), SunOS)
 MFLAGS := -lsocket -lnsl
endif

##########################################################################
# "make" options
##########################################################################

# Clean all files and compile client and server
all: clean compile_server compile_client

# Just build server and client
build: compile_server compile_client 

# Compile server
compile_server: $(CODE_SERVER_FILE)
	$(CC) $(CFLAGS) -o $(EXEC_SERVER_FILE) $(CODE_SERVER_FILE) $(MFLAGS)

# Compile client
compile_client: $(CODE_CLIENT_FILE)
	$(CC) $(CFLAGS) -o $(EXEC_CLIENT_FILE) $(CODE_CLIENT_FILE) $(MFLAGS)

# Debug server
debug_server:
	gdb $(EXEC_SERVER_FILE) 

# Debug client
debug_client:
	gdb $(EXEC_CLIENT_FILE) 

# Leak debug server
ldebug_server:
	valgrind --leak-check=full --show-reachable=yes -v $(EXEC_SERVER_FILE)

# Leak debug client
ldebug_client:
	valgrind --leak-check=full --show-reachable=yes -v $(EXEC_CLIENT_FILE)

# Upload files and connect to server
uploadssh:
	@echo -n "Upload and connect to $(SSH_SERVER)- USERNAME: ";\
	read user_name;\
	$(SCP) $(SRC_FILES) $$user_name@$(SSH_SERVER):./$(FOLDER_SERVER);\
	$(SSH) $(SSH_OPTION) $$user_name@$(SSH_SERVER) $(SSH_CD_FOLDER);\

# Upload files to server
upload:
	@echo -n "Upload to $(SSH_SERVER)- USERNAME: ";\
	read user_name;\
	$(SCP) $(SRC_FILES) $$user_name@$(SSH_SERVER):./$(FOLDER_SERVER);\

# Connect to server
ssh:
	@echo -n "Connect to $(SSH_SERVER)- USERNAME: ";\
	read user_name;\
	$(SSH) $(SSH_OPTION) $$user_name@$(SSH_SERVER) $(SSH_CD_FOLDER);\

# Makes a archive containing all the project source files for submission.
submit:	$(SRC_FILES)
	tar -cvf $(PROJECT).tar $(SRC_FILES)

# Makes a archive containing all the project source files for submission
# and zip them
zipsubmit:	$(SRC_FILES)
	tar cvfz $(PROJECT).tar.gz $(SRC_FILES)

# Clean files
.PHONY: clean
clean:
	rm -f *~ *.o $(EXEC_SERVER_FILE) $(EXEC_CLIENT_FILE)
	