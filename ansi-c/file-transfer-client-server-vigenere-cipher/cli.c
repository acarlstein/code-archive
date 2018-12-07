/**
 * Author: Alejandro G. Carlstein
 * Description: Transfer Encrypted File Client
 */

#include "default.h"

#define DEFAULT_HOST 									"localhost"
#define EXIT_PROGRAM 									0
#define DONT_EXIT_PROGRAM 						1

#define CMD_QUIT											"quit"
#define CMD_HELP											"help"
#define CMD_LS												"ls"
#define CMD_LLS												"lls"
#define CMD_LPWD											"lpwd"
#define CMD_PUT												"put"

#define MSG_DISPLAY_MENU 							"User help:\n"\
																			"help - Display help option\n"\
																		  "lls  - Display local directory list contents\n"\
                    				          "lpwd - Display local current directory\n"\
                    				          "put  - Transfer local file to server\n"\
                    				          "  put <file to transfer>\n"\
                    				          "quit - Quit program\n"

#define MSG_ERROR_UNKNOWN_COMMAND			"[X] Command not recognized: %s\n"
#define MSG_ERROR_GETTING_HOSTNAME 		"Couln't get hostname!"
#define MSG_ERROR_SERVER_DISCONNECTED "Server disconnected...\n"

enum TOKENS{
	TOKEN_COMMAND,
	TOKEN_FILENAME,
	MAX_TOKENS
};

struct Connection{
	int sock;
	int bytes_received;
	int port_number;
	char send_data[DATA_PACKET_SIZE];
	char recv_data[DATA_PACKET_SIZE];
	struct hostent *host;
  struct sockaddr_in server_addr;
};

void getConnection(struct Connection *new_connection,
									 char *hostname,
									 int port_number);
void menuDriver(struct Connection *new_connection);
int receiveData(struct Connection *new_connection);
int sendData(struct Connection* new_connection, const char* data);
void handShake(struct Connection* new_connection);
void promptUser(char* tokens[]);
void displayHelp(void);
void displayLocalListDirectoryContents(void);
void printNameCurrentDirectory(void);
void receiveListDirectoryContents(struct Connection *new_connection);
void putFileOnServer(struct Connection *new_connection,
										 const char* filename);
int strencrypt(const char* str_in,
               char* str_out);
/**
 * MAIN
 */
int main(int argc, char* argv[]){
	debug(DBG_LV0, "argc: %d", argc); 	

	int i;
	int port_number = (argc >= 3 ) ? atoi(argv[2]) : DEFAULT_PORT;
	char* host_name = (argc >= 2) ? argv[1] : DEFAULT_HOST;

	struct Connection connection;

	for(i = 0; i < argc; ++i)
		debug(DBG_LV0, "argv[%d]: %s", i, argv[i]); 		

	if (argc > 3)
		errorDoExit(MSG_PORT_NUMBER_ONLY, argv[0]);

	debug(DBG_LV1, "host: %s", host_name);

	getConnection(&connection, host_name, port_number);

	handShake(&connection);

	menuDriver(&connection);

	return 0;

}

/**
 * Driver menu
 */
void menuDriver(struct Connection *new_connection){
	debug(DBG_LV0, "menuDriver()");

	short doExit = DONT_EXIT_PROGRAM;
	int i;
	char* tokens[MAX_TOKENS] = {NULL, NULL};
	char command[DATA_PACKET_SIZE];
	char filename[DATA_PACKET_SIZE];

  while(doExit){

		promptUser(tokens);				

		for (i = 0; DBG_LV1 && i < MAX_TOKENS; ++i)
			debug(DBG_LV1, "TOKEN[%d]: %s", i, tokens[i]);

		/* Must copy string to work on SunOS */
		if (tokens[TOKEN_COMMAND] != NULL){
			strcpy(command, tokens[TOKEN_COMMAND]);
   		debug(DBG_LV1, "[Command: %s]", command);
		}

		if (tokens[TOKEN_FILENAME] != NULL){
    	strcpy(filename, tokens[TOKEN_FILENAME]);
	    debug(DBG_LV1, "[Filename: %s]", filename);
    }

		/* MENU */

		if (strcmp(command, CMD_QUIT) == 0){
			debug(DBG_LV1, "COMMAND> %s: ", CMD_QUIT);
			close(new_connection->sock);
			printf("Bye Bye\n");
			doExit = EXIT_PROGRAM;

		}else
		if (strcmp(command, "help") == 0){
			debug(DBG_LV1, "COMMAND> %s ", CMD_HELP);
			displayHelp();

		}else
		if (strcmp(command, CMD_LLS) == 0){
			debug(DBG_LV1, "COMMAND> %s ", CMD_LLS);
			displayLocalListDirectoryContents();

		}else
		if (strcmp(command, CMD_LLS) == 0){
			debug(DBG_LV1, "COMMAND> %s ", CMD_LLS);
			displayLocalListDirectoryContents();

		}else
		if (strcmp(command, CMD_LS) == 0){
			debug(DBG_LV1, "COMMAND> %s ", CMD_LS);
			receiveListDirectoryContents(new_connection);

		}else
		if (strcmp(command, CMD_LPWD) == 0){
			debug(DBG_LV1, "COMMAND> %s ", CMD_LPWD);
			printNameCurrentDirectory();

		}else
		if (strcmp(command, CMD_PUT) == 0){
			debug(DBG_LV1, "COMMAND> %s ", CMD_PUT);
			putFileOnServer(new_connection, filename);

		}else{
			printf(MSG_ERROR_UNKNOWN_COMMAND, command);
		}

	}

}

/**
 * Obtain connection with server
 */
void getConnection(struct Connection *new_connection,
									 char *hostname,
									 int port_number){
	debug(DBG_LV0, "getConnection(hostname: %s, port_number: %d)", hostname, port_number);

	if ((new_connection->host = gethostbyname(hostname)) == NULL)
		errorDoExit(MSG_ERROR_GETTING_HOSTNAME);

	new_connection->port_number = port_number;	

	if ((new_connection->sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		errorDoExit(MSG_ERR_COULDNT_SOCKET, new_connection->sock);

	debug(DBG_LV1, "Got socket!");

  new_connection->server_addr.sin_family = AF_INET;
	debug(DBG_LV1,"sin_family");

  new_connection->server_addr.sin_port = htons(port_number);
	debug(DBG_LV1,"sin_port");

  new_connection->server_addr.sin_addr = *((struct in_addr *)new_connection->host->h_addr);
	debug(DBG_LV1, "sin_addr");

	// bzero() is used only for setting the values to zero
	bzero(&(new_connection->server_addr.sin_zero), NUM_BYTES);
	debug(DBG_LV1,"sin_zero");

  if (connect(new_connection->sock,
  					  (struct sockaddr *)&new_connection->server_addr,
  					  sizeof(struct sockaddr)) == -1)
		errorDoExit(MSG_ERR_COULDNT_CONNECT);

	debug(DBG_LV1, "Got connection!");
}

/**
 * Receive data
 * @Return: Number of bytes received
 */
int receiveData(struct Connection *new_connection){
	debug(DBG_LV0, "receiveData()");

	bzero(new_connection->recv_data, DATA_PACKET_SIZE);
	int bytes_received = recv(new_connection->sock,
														new_connection->recv_data,
														DATA_PACKET_SIZE,
														0);		

	if(bytes_received < 1){
		close(new_connection->sock);
		if(bytes_received == 0){
			close(new_connection->sock);
			printf(MSG_ERROR_SERVER_DISCONNECTED);
			errorDoExit(MSG_ERR_CONNECTION_FAIL);		

		}else{
			errorDoExit(MSG_ERR_RECEIVING_DATA);
		}
	}

	debug(DBG_LV1, "Received (%d): %s",
				strlen(new_connection->recv_data), new_connection->recv_data);	

	new_connection->bytes_received = bytes_received;
  new_connection->recv_data[bytes_received] = '\0'; 

  return bytes_received;
}

/**
 * Send data
 * @Return: Number of bytes sended
 */
int sendData(struct Connection* new_connection,
						const char* data){
	debug(DBG_LV0, "sendData(%s)", data);
	int data_length;

	bzero(new_connection->send_data, DATA_PACKET_SIZE);
	strcpy(new_connection->send_data, data);
	data_length = strlen(new_connection->send_data);

	if (send(new_connection->sock, new_connection->send_data,
					 data_length, 0) != data_length){
		close(new_connection->sock);
		errorDoExit(MSG_ERR_SENDING_DATA);
	}

	return data_length;
}

/**
 * Hand shake with the server to verify own protocol
 */
void handShake(struct Connection* new_connection){
	debug(DBG_LV0, "handShake()");

	debug(DBG_LV1, "Sending HELLO message...");
	sendData(new_connection, CODE_HELLO);

	debug(DBG_LV1, "Getting WELCOME message...");
	receiveData(new_connection);  		

	if (strcmp(new_connection->recv_data, CODE_WELCOME) > -1){
		debug(DBG_LV1, "Got WELCOME!");

		debug(DBG_LV1, "Request server name");
		sendData(new_connection, CODE_REQ_SERVER_NAME);

		receiveData(new_connection);
		printf("Server Name: %s\n", new_connection->recv_data);
	}else{
		errorDoExit(MSG_ERR_WRONG_PROTOCOL);
	}
}

/**
 * Prompt user for input
 */
void promptUser(char* tokens[]){
	char str_input[DATA_PACKET_SIZE];
	char *p;
	int i;

	printf("\nftp> ");
	fgets(str_input, DATA_PACKET_SIZE, stdin);		

	p = strtok(str_input, " \n");
  for (i = 0; p != NULL; (p = strtok(NULL, " \n")), i++)
		tokens[i] = p;
}

/**
 * Display help message
 */
void displayHelp(void){
	debug(DBG_LV0, "displayHelp()");
	printf(MSG_DISPLAY_MENU);
}

/**
 * Display local list directory contents
 */
void displayLocalListDirectoryContents(void){
	debug(DBG_LV0, "void displayLocalListDirectoryContents()");

	struct dirent *dirent_struct_ptr;
	DIR *directory_stream_ptr;

	if ((directory_stream_ptr = opendir("./")) != NULL){
		printNameCurrentDirectory();

  	while ((dirent_struct_ptr = readdir(directory_stream_ptr))){
	  	printf(" %s\n",dirent_struct_ptr->d_name);
   	}
	}else{
		errorDoExit(MSG_ERR_NO_DIR_STREAM);
	}

}

/**
 * Print the name of the current directory
 */
void printNameCurrentDirectory(void){
	debug(DBG_LV0, "void printNameCurrentDirectory()");

	long size;
	char *buf;
	char *ptr;
	size = pathconf(".", _PC_PATH_MAX);
	if ((buf = (char *)malloc((size_t)size)) != NULL){
		ptr = getcwd(buf, (size_t)size);
	}else{
		errorDoExit("Could not obtain the current directory");
	}
	printf("Current Directory: %s\n", ptr);
}

/**
 * Receive the list of directory contents from the server
 */
void receiveListDirectoryContents(struct Connection *new_connection){
	debug(DBG_LV0, "receiveListDirectoryContents()");

	sendData(new_connection, CODE_LS);

	receiveData(new_connection);
	while (strcmp(new_connection->recv_data, CODE_EOF) != 0){

		if (strcmp(new_connection->recv_data, CODE_ERROR_LS) == 0){
			fprintf(stderr, "Couldn't read list directory contents!\n");
			break;
		}else{
			printf("%s\n", new_connection->recv_data);
			sendData(new_connection, CODE_OK);
		}
		receiveData(new_connection);
	}

}

/**
 * Put an encrypted file on the server
 */
void putFileOnServer(struct Connection *new_connection,
										 const char* filename){
	debug(DBG_LV0, "void putFileOnServer(filename: %s)", filename);

	char str_filename[DATA_PACKET_SIZE];
	char filename_ce[DATA_PACKET_SIZE];
	char str_in_file[DATA_PACKET_SIZE];
	char str_in_file_encrypt[DATA_PACKET_SIZE];
	FILE *fp, *fp_ce;

	strcpy(str_filename, filename);

	debug(DBG_LV1, "str_filename: %s", str_filename);

	sprintf(filename_ce, "%s_ce", str_filename);

	debug(DBG_LV1, "filename_ce: %s", filename_ce);

	debug(DBG_LV1, "OPEN FILE TO READ");
	fp = fopen(str_filename, "r");

	debug(DBG_LV1, "OPEN FILE TO WRITE");
	fp_ce = fopen(filename_ce, "w");

	if (fp == NULL || fp_ce == NULL){
		fclose(fp_ce);
		fclose(fp);
		errorDoExit("Couldn't open file");
	}else{

		/* Send PUT code to server */
		sendData(new_connection, CODE_PUT);

		debug(DBG_LV0, "Waiting for CODE_REQUEST_FILENAME");
		/* Receive filename request form server */
		receiveData(new_connection);
		if (strcmp(new_connection->recv_data, CODE_REQUEST_FILENAME) == 0){

			debug(DBG_LV0, "Send filename");
			/* Send filename to server */
			sendData(new_connection, str_filename);

			/* Receive request to send file */
			receiveData(new_connection);
			if (strcmp(new_connection->recv_data, CODE_REQUEST_FILE) == 0){
				printf("Sending file: %s.\n", filename);
					/* Encrypt file */
				while(fgets(str_in_file, DATA_PACKET_SIZE, fp) != NULL){
					debug(DBG_LV2, "Reading (Len: %d): %s", strlen(str_in_file), str_in_file);						

					/* encrypt package */
					strencrypt(str_in_file, str_in_file_encrypt);

					/* Save it in <filename>_ce */
					fprintf(fp_ce, "%s", str_in_file_encrypt);					

					/* send packages */
					sendData(new_connection, str_in_file_encrypt);

					/* Waiting for ok */
					receiveData(new_connection);
					if (strcmp(new_connection->recv_data, CODE_OK) == 0){
						printf("OK");
					}else{
						errorDoExit("Wrong protocol - Waiting OK");
					}	

				}
				sendData(new_connection, CODE_EOF);			

			}else{
				errorDoExit("Wrong protocol - Waiting request for file ");
			}

		}else{
			errorDoExit("Wrong protocol - Waiting for request of filename");
		}

	}

	fclose(fp);
	fclose(fp_ce);

}

/**
 * Encrypt the string using key
 * @Return: Number of bytes encrypted
 */
int strencrypt(const char* str_in,
               char* str_out){
	debug(DBG_LV0, "strencrypt(str_in: %s)", str_in);

	int i, j;
	int i_plain, i_key;

	char str_key[DATA_PACKET_SIZE];

	strcpy(str_key, ENCRYPTION_KEY);

	for (i = 0, j = 0; i < strlen(str_in) - 1; ++i, ++j){

		i_plain = (unsigned int)str_in[i] - CHAR_PLAIN_A;
		i_key = (unsigned int)str_key[j] - CHAR_KEY_A;

		str_out[i] = (char)((i_plain + i_key) % 26 + CHAR_CIPHER_A);

		debug(DBG_LV1, "(str_out: %d) [%c:%d] = (str_in:%d)[%c:%d], (key:%d)[%c:%d]",
					i, str_out[i], (int)str_out[i],
					i, str_in[i], (int) str_in[i],
					j, str_key[j], (int)str_key[j]);

		if ( (j + 1) >= strlen(str_key)) j = -1;
	}

	return strlen(str_in);
}