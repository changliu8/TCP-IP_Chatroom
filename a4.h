#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MY_PORT 60002
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 60002




void server();
void client();
void enctryptfun(char *c);

unsigned char encrypt(unsigned char c, unsigned char k);



