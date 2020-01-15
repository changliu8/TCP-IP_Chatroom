#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "a4.h"


int main(int argc, char *argv[]) {
	if(argc >= 2){
	if(strcmp(argv[1],SERVER_IP) == 0){
		printf("Connecting Server...\n");
		client();
	}
}
	else{
		printf("Waiting for Connection request...\n");
		server();
	}
	return 0;
}

