/**
 * Author: Alejandro G. Carlstein
 * Description: File Transfer Client/Server
 */

#include "default.h"

void debug(int debugLevel, char *fmt, ...){
	if (debugLevel == 1){
		va_list argp;
		fprintf(stdout, "[DBG] ");
		va_start(argp, fmt);
		vfprintf(stdout, fmt, argp);
		va_end(argp);
		fprintf(stdout, "\n");
	}
}

void errorDoExit(char *fmt, ...){
	va_list argp;
	fprintf(stderr, "[Error] ");
	va_start(argp, fmt);
	vfprintf(stderr, fmt, argp);
	va_end(argp);
	if (errno){
		fprintf(stderr, "=> %s\n", strerror(errno));
	}else{
		fprintf(stderr, "\n");
	}
	exit(1);
}
