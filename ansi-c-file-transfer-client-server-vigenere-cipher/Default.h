/**
 * Author: Alejandro G. Carlstein
 * Description: File Transfer Client/Server
 */

#ifndef ACARLS_DEFAULT_H
#define ACARLS_DEFAULT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>

/* Required for linux */
#include <string.h>

/* Required for SunOS */
#include <strings.h>

#include <ctype.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>

#define DEFAULT_PORT 					8414
#define DATA_PACKET_SIZE 			1024
#define NUM_BYTES							8
#define ENCRYPTION_KEY		    "security"
#define CHAR_KEY_A						97
#define CHAR_PLAIN_A					97
#define CHAR_CIPHER_A					65

#define DBG_LV0 0
#define DBG_LV1 0
#define DBG_LV2 0
#define DBG_LV3 0

#define TRUE									1
#define FALSE									0

#define QUIT_TRUE							0
#define QUIT_FALSE						1

#define CODE_FAIL							"0FAIL"
#define CODE_OK								"1OK"

#define CODE_HELLO						"100HELLO"
#define CODE_WELCOME 					"101WELCOME"
#define CODE_REQ_SERVER_NAME 	"102REQ_SERVER_NAME"

#define CODE_MSG 							"200MSG"

#define CODE_DATA							"300DATA"
#define CODE_EOF							"301EOF"
#define CODE_PUT						  "302PUT"
#define CODE_REQUEST_FILENAME	"303REQ_FILENAME"
#define CODE_REQUEST_ENCRYPT  "304REQ_ENCRYPT"
#define CODE_ENCRYPT					"305ENCRYPT"
#define CODE_REQUEST_FILE     "306REQUEST_FILE"

#define CODE_CMD							"400CMD"
#define CODE_LS								"401LS"

#define CODE_ERROR            "500ERROR"
#define CODE_ERROR_LS					"501ERROR_LS"
#define CODE_ERROR_CREAT_FILE "502ERROR_CREAT_FILE"

#define CODE_EXIT							"600EXIT"

#define MSG_ERR_WRONG_PROTOCOL  "Wrong protocol!"
#define MSG_ERROR_CREAT_FILE 		"Couldn't create file"
#define MSG_PORT_NUMBER_ONLY 		"Need port number only! \n%s <Port Number>"
#define MSG_ERR_COULDNT_SOCKET  "Couldn't obtain socket - %d"
#define MSG_ERR_COULDNT_CONNECT "Couldn't connect!"
#define MSG_ERR_SENDING_DATA 		"Couldn't send data!"
#define MSG_ERR_RECEIVING_DATA	"Couln't recieve data!"
#define MSG_ERR_CONNECTION_FAIL "Connection failed."
#define MSG_ERR_NO_DIR_STREAM 	"Could not obtain the directory stream"

void debug(int debugLevel, char *fmt, ...);
void errorDoExit(char *fmt, ...);

#endif