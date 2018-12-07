/**
 * Author: Alejandro G. Carlstein
 * Description: FTP Server
 */

#include "default.h"

/*max. length queue of pending connections may grow. */
#define MAX_BACKLOG							5
#define SETSOCKOPT_VAL  				1

#define MSG_SERVER_NAME 				"Server Name: ACARLSTEIN Server Version 1.0"
#define MSG_WAIT_CLIENT					"Waiting client...\n"
#define MSG_WAIT_CLIENT_ON_PORT	"\nTCPServer Waiting for client on port %d\n"

#define MSG_ERR_NO_SOCKET_OPT		"Couldn't set and/or get socket options"
#define MSG_ERR_UNABLE_BIND    	"Unable to bind"
#define MSG_ERR_UNABLE_LISTEN  	"Unable to Listen"
#define MSG_ERR_CANT_SEND_LIST  "Can't send server list\n"

struct Connection{
	int sock;
	int bytes_recieved;
	int port_number;
	int socket_descriptor;
	char send_data[DATA_PACKET_SIZE];
	char recv_data[DATA_PACKET_SIZE];
  struct sockaddr_in server_addr;
  struct sockaddr_in client_addr;
};

void setUpConnection(struct Connection *new_connection,
										 int port_number);
int menuDriver(struct Connection *new_connection);
void sendData(struct Connection *new_connection,
							const char* data);
int recieveData(struct Connection *new_connection);
void handShake(struct Connection* new_connection);
void sendListDirectoryContents(struct Connection* new_connection);
int receiveFileFromClient(struct Connection* new_connection);
int strdecrypt(const char* str_in,
							 char* str_out);

/**
 * MAIN
 */
int main(int argc, char *argv[]){
	debug(DBG_LV0, "argc: %d", argc); 	

	short DO_QUIT_PROGRAM;
	int i;
	int port_number;
	socklen_t sin_size = sizeof(struct sockaddr_in);
	struct Connection connection;

	for(i = 0; DBG_LV1 && i < argc; ++i)
		debug(DBG_LV1, "argv[%d]: %s", i, argv[i]); 		

	if (argc > 2)	errorDoExit(MSG_PORT_NUMBER_ONLY, argv[0]);

	port_number = (argc == 2) ? atoi(argv[1]) : DEFAULT_PORT;

	DO_QUIT_PROGRAM = QUIT_FALSE;
	while(DO_QUIT_PROGRAM){

		fflush(stdout);

		setUpConnection(&connection, port_number);

		printf(MSG_WAIT_CLIENT_ON_PORT, port_number);

		connection.socket_descriptor = accept(connection.sock,
													  						  (struct sockaddr *)&connection.client_addr,
																				  &sin_size);

		if (connection.socket_descriptor  == -1)
			errorDoExit(MSG_ERR_COULDNT_CONNECT);

		handShake(&connection);

 		menuDriver(&connection);

		close(connection.sock); 		

	}

  return 0;
}

/**
 * Menu driver waiting for instructions
 */
int menuDriver(struct Connection *new_connection){

	short DO_QUIT_CONNECTION;
	int bytes_received = 1;

	DO_QUIT_CONNECTION = QUIT_FALSE;
 	while (DO_QUIT_CONNECTION){  

		if(bytes_received == 0){
			DO_QUIT_CONNECTION = QUIT_TRUE;
		}else{

			printf(MSG_WAIT_CLIENT);

			bytes_received = recieveData(new_connection);
			if (strcmp(new_connection->recv_data, CODE_LS) == 0){
				sendListDirectoryContents(new_connection);
			}else
			if (strcmp(new_connection->recv_data, CODE_PUT) == 0){
				bytes_received = receiveFileFromClient(new_connection);
			}else{
				close(new_connection->sock);
				fprintf(stderr, MSG_ERR_WRONG_PROTOCOL " - PUT\n");
				DO_QUIT_CONNECTION = QUIT_TRUE;
			}
		}
	}
	return 0;
}

/**
 * Set up connection with the client
 */
void setUpConnection(struct Connection *new_connection,
										 int port_number){
	debug(DBG_LV0, "setUpConnection(port_number: %d)", port_number);

	int opt_val = SETSOCKOPT_VAL;
	new_connection->port_number = port_number;

  if ((new_connection->sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		errorDoExit(MSG_ERR_COULDNT_SOCKET, new_connection->sock);

	if (setsockopt(new_connection->sock, SOL_SOCKET, SO_REUSEADDR, &opt_val, sizeof(int)) == -1)
		errorDoExit(MSG_ERR_NO_SOCKET_OPT);

	debug(DBG_LV1, "Got socket!");

  new_connection->server_addr.sin_family = AF_INET;
 	debug(DBG_LV1,"sin_family");      

  new_connection->server_addr.sin_port = htons(port_number);
	debug(DBG_LV1,"sin_port");

  new_connection->server_addr.sin_addr.s_addr = INADDR_ANY;
	debug(DBG_LV1, "sin_addr");

  bzero(&(new_connection->server_addr.sin_zero), NUM_BYTES);
	debug(DBG_LV1,"sin_zero");

	// bind a name to a socket
  if (bind(new_connection->sock,
  				(struct sockaddr *)&new_connection->server_addr,
  				sizeof(struct sockaddr)) == -1){
		close(new_connection->sock);
		errorDoExit(MSG_ERR_UNABLE_BIND);
	}

	// Listen for connection on the socket
  if (listen(new_connection->sock, MAX_BACKLOG) == -1){
		close(new_connection->sock);
   	errorDoExit(MSG_ERR_UNABLE_LISTEN);
  }
	debug(DBG_LV1, "Listening...");	

}

/**
 * Send data to client
 */
void sendData(struct Connection *new_connection,
							const char* data){
	debug(DBG_LV0, "sendData(data: %s)", data);

 	int data_length;

	bzero(new_connection->send_data, DATA_PACKET_SIZE);
 	strcpy(new_connection->send_data, data);
 	data_length = strlen(new_connection->send_data);

 	debug(DBG_LV1, "new_connection->send_data: %s",
 	      new_connection->send_data);

	if (send(new_connection->socket_descriptor,
					 new_connection->send_data,
					 data_length, 0) != data_length){
		close(new_connection->sock);
		fprintf(stderr, MSG_ERR_SENDING_DATA "\n");
	}
}

/**
 * Receive data from client
 */
int recieveData(struct Connection *new_connection){
	debug(DBG_LV0, "recieveData()");

	bzero(new_connection->recv_data, DATA_PACKET_SIZE);
	int bytes_recieved = recv(new_connection->socket_descriptor,
														new_connection->recv_data,
														DATA_PACKET_SIZE,
														0);		

	debug(DBG_LV1, "Check bytes received");

	if(bytes_recieved < 1){

		close(new_connection->sock);

		if(bytes_recieved == 0){
			fprintf(stderr, MSG_ERR_CONNECTION_FAIL "\n");
		}else{
			fprintf(stderr,MSG_ERR_RECEIVING_DATA "\n");
		}

	}else{

		debug(DBG_LV1, "Received: %s", new_connection->recv_data);

		new_connection->bytes_recieved = bytes_recieved;
  	new_connection->recv_data[bytes_recieved] = '\0';
  }

  return bytes_recieved;
}

/**
 * Hand shake with client to test own protocol
 */
void handShake(struct Connection* new_connection){
	debug(DBG_LV0, "handShake()");

	printf("Connection from (%s , %d)...\n",
         inet_ntoa(new_connection->client_addr.sin_addr),
         ntohs(new_connection->client_addr.sin_port));

	debug(DBG_LV1," If client say HELLO, Greed client with WELCOME");
 	recieveData(new_connection);
	if (strcmp(new_connection->recv_data, CODE_HELLO) == 0){
		debug(DBG_LV1, "Client handshake with server");
		sendData(new_connection, CODE_WELCOME);
	}else{
		close(new_connection->sock);
		fprintf(stderr, MSG_ERR_WRONG_PROTOCOL " - HELLO/WELCOME \n");
	}

	debug(DBG_LV0,"If client ask for server name send server name to client");
 	recieveData(new_connection);
	if (strcmp(new_connection->recv_data, CODE_REQ_SERVER_NAME) == 0){
		debug(DBG_LV1, "Client asking for server name");
		sendData(new_connection, MSG_SERVER_NAME);
	}else{
		close(new_connection->sock);
		fprintf(stderr, MSG_ERR_WRONG_PROTOCOL " - SERVER NAME\n");
	}
}

/**
 * Send list of directory contents to client
 */
void sendListDirectoryContents(struct Connection* new_connection){
	debug(DBG_LV0, "void displayLocalListDirectoryContents()");
	int bytes_received;
	struct dirent *dirent_struct_ptr;
	DIR *directory_stream_ptr;

	if ((directory_stream_ptr = opendir("./")) != NULL){

  	while ((dirent_struct_ptr = readdir(directory_stream_ptr))){
			sendData(new_connection, dirent_struct_ptr->d_name);				

			bytes_received = recieveData(new_connection);
			if (strcmp(new_connection->recv_data, CODE_OK) != 0){
				fprintf(stderr, MSG_ERR_CANT_SEND_LIST);
			}
   	}
		sendData(new_connection, CODE_EOF);			  		

	}else{
		sendData(new_connection, CODE_ERROR_LS);
		errorDoExit(MSG_ERR_NO_DIR_STREAM);
	}

}

/**
 * Receive encrypted file from client
 */
int receiveFileFromClient(struct Connection* new_connection){
	debug(DBG_LV0, "void receiveFileFromClient(is_encrypted: %s)");											

	int bytes_received;

	char filename[DATA_PACKET_SIZE];
	char filename_se[DATA_PACKET_SIZE];
	char filename_sd[DATA_PACKET_SIZE];
	char str_unencrypted[DATA_PACKET_SIZE];
	FILE *fp_se, *fp_sd;

	/* Request filename */
	debug(DBG_LV1, "Request filename from client");
	sendData(new_connection, CODE_REQUEST_FILENAME);

	/* receive filename */
	bytes_received = recieveData(new_connection);
	strcpy(filename, new_connection->recv_data);
	sprintf(filename_se, "%s_se", filename);
	sprintf(filename_sd, "%s_sd", filename);

	debug(DBG_LV1, "filename: %s", filename);
	debug(DBG_LV1, "filename_se: %s", filename_se);
	debug(DBG_LV1, "filename_sd: %s", filename_sd);	

	fp_se = fopen(filename_se, "w");
	fp_sd = fopen(filename_sd, "w");
	debug(DBG_LV1, "Files open");

	if (fp_se == NULL || fp_sd == NULL){
		debug(DBG_LV1, "Error, closing files");
		fclose(fp_se);
		fclose(fp_sd);
		errorDoExit(MSG_ERROR_CREAT_FILE);
	}else{

		debug(DBG_LV1, "Download file...");
		/* Send code request file */
		sendData(new_connection, CODE_REQUEST_FILE);				

		bytes_received = recieveData(new_connection);

  	/* while loop until eof */
  	while (strcmp(new_connection->recv_data, CODE_EOF) != 0){

			debug(DBG_LV1, "Saving: %s", new_connection->recv_data);
	  	/* save encrypted package */
			fprintf(fp_se, "%s", new_connection->recv_data);

			/* Decencrypt package */
			bzero(str_unencrypted, DATA_PACKET_SIZE);
			strdecrypt(new_connection->recv_data, str_unencrypted);
			debug(DBG_LV1, "Decrypt: %s\n", new_connection->recv_data);

			/* Save unecrypted package */
			debug(DBG_LV1, "DECRYPT: %s", str_unencrypted);

			fprintf(fp_sd, "%s", str_unencrypted);

			debug(DBG_LV1, "Sending OK...");
	  	/*send ok */
			sendData(new_connection, CODE_OK);
			bytes_received = recieveData(new_connection);
  	}

	}	

	fclose(fp_se);
	fclose(fp_sd);
	return 0;
}

/**
 * Decrypt string
 */
int strdecrypt(const char* str_in,
							 char* str_out){
	debug(DBG_LV0, "strdencrypt(str_in: %s)", str_in);

	int i, j;
	int i_cipher, i_key, i_temp;
	char str_key[DATA_PACKET_SIZE];
	strcpy(str_key, ENCRYPTION_KEY);
	char char_temp;
	for (i = 0, j = 0; i < strlen(str_in); ++i, ++j){

		i_cipher = str_in[i] - CHAR_CIPHER_A;
		i_key = str_key[j] - CHAR_KEY_A;
		i_temp = i_cipher - i_key;

		debug(DBG_LV1, "Ci([%c]%d): %d, Ki([%c]%d): %d, Ci - Ki: %d",
					str_in[i], i, i_cipher, str_key[j], j, i_key, i_temp);

		if (i_temp > -1){
			//COMMON KNOWN DECRYPT ALGORIGHTM
			i_temp = ((i_temp) % 26);
		}else{
			//DECRYPT ALGORITHM FOR UNCOMMON CASES WHERE I_TEMP IS NEGATIVE
			i_temp = ((i_temp + 26) % 26);
		}

		char_temp = i_temp + CHAR_PLAIN_A;
		if (isalpha(char_temp)){
			str_out[i] = char_temp;
		}else{
			str_out[i] = '\0';
		}

		if ( (j + 1) >= strlen(str_key)) j = -1;
	}

	return 0;
}
