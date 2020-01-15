#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "a4.h"


unsigned char counter = 87;
unsigned char key = 101;

/*
  Function:  server
  Purpose:   generate a server
  Parameters:
    in:      doesn't have
    return:  not returning, but will generate a server to let client connects.
*/
void server(){
	int myListenSocket, clientSocket;
	struct sockaddr_in  myAddr, clientAddr;
	int i, addrSize, bytesRcv;
	int mySocket;

	char buffer[80];
	char inStr[80];

/* create socket */



	myListenSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (myListenSocket < 0) {
		printf("eek! couldn't open socket\n");
		exit(-1);
	}

	mySocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (mySocket < 0) {
		printf("eek! couldn't open socket\n");
		exit(-1);
	}



/* setup my server address */
	memset(&myAddr, 0, sizeof(myAddr));
	myAddr.sin_family = AF_INET;
	myAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	myAddr.sin_port = htons((unsigned short) MY_PORT);

/* bind my listen socket */

	i = bind(myListenSocket, (struct sockaddr *) &myAddr,sizeof(myAddr));
	if (i < 0) {
		printf("eek! couldn't bind socket\n");
		exit(-1);
	}
	else{
	printf("Connection Accepted...\n");
	}


/* listen */
	i = listen(myListenSocket, 5);
	if (i < 0) {
		printf("eek! couldn't listen\n");
		exit(-1);
	}


/* wait for connection request */

	addrSize = sizeof(clientAddr);

	clientSocket = accept(myListenSocket,(struct sockaddr *) &clientAddr,&addrSize);
	if (clientSocket < 0) {
		printf("eek! couldn't accept the connection\n");
		exit(-1);
	}

/* read message from client and do something with it */
	while (1) {
		bytesRcv = recv(clientSocket, buffer, sizeof(buffer), 0);
		printf("Received->%s\n", buffer);
		enctryptfun(buffer);
		buffer[bytesRcv] = 0;
		buffer[bytesRcv] = 0;
		printf("Received->%s\n", buffer);
		if(strcmp(buffer,"quit") == 0)
			break;
		printf("Your message->");
		fgets(inStr, sizeof(inStr), stdin);
		inStr[strlen(inStr)-1] = 0;
		strcpy(buffer, inStr);
		enctryptfun(buffer);
		send(clientSocket, buffer, strlen(buffer), 0);
		printf("...waiting to receive...\n");
		if(strcmp(inStr, "quit") == 0)
			break;
	} 

/* close sockets */

	close(myListenSocket);
	close(clientSocket);


}

/*
  Function:  client
  Purpose:   generate a client and make connection to a existed server.
  Parameters:
    in:      doesn't have
    return:  not returning, but will generate a client and make connection to a existed server.
*/


void client(){
	int mySocket;
	struct sockaddr_in  addr;
	int myListenSocket;
	int i, bytesRcv;

	char inStr[80];
	char buffer[80];


/* create socket */
	mySocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (mySocket < 0) {
		printf("eek! couldn't open socket\n");
		exit(-1);
	}

	myListenSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (myListenSocket < 0) {
		printf("eek! couldn't open socket\n");
		exit(-1);
	}



/* setup address */
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(SERVER_IP);
	addr.sin_port = htons((unsigned short) SERVER_PORT);

/* connect to server */

	i = connect(mySocket, (struct sockaddr *) &addr,sizeof(addr));
	if (i<0) {
		printf("client could not connect!\n");
		exit(-1);
	}
	else{
		printf("Connected...\n");
	}


/* get input from user and send to server */
	while (1) {
		printf("Your message->");

		fgets(inStr, sizeof(inStr), stdin);
		inStr[strlen(inStr)-1] = 0;
		strcpy(buffer, inStr);
		enctryptfun(buffer);
		send(mySocket, buffer, strlen(buffer), 0);
		printf("...waiting to receive ...\n");
		if(strcmp(inStr, "quit") == 0)
			break;
		bytesRcv = recv(mySocket, buffer, sizeof(buffer), 0);
		printf("Received->%s\n", buffer);
		enctryptfun(buffer);
		buffer[bytesRcv] = 0;

		printf("Received->%s\n", buffer);
		if(strcmp(buffer,"quit") == 0)
			break;
	}


/* close the socket */

	close(mySocket);

}

/*
  Function:  enctryptfun
  Purpose:   enctrypt/decrypt the message
  Parameters:
    in:       an array of the message that you want to encrypt.
    return:  not returning ,but will encrypt/decrypt the message you've send.
*/

void enctryptfun(char *c){
	counter = 87;
	key = 101;
    for (int j=0;j<80;j++){
	if(c[j] == '\0'){
		break;
	}
	else{
	c[j] = encrypt(counter, key)^c[j];
	counter++;
		}
	}
}
