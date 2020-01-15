Program author : Chang Liu 101074450;Fengting Guo 101076608
Purpose :
Making a program sending a secret message to Harold using socket TCP/IP code, it assists Timmy by implementing an encrypted chat utility, this program will help Timmy and Harold send encrypted messages to each other that the evil wizard is unable to decrypt.
list of source files:
a4.c
a4_1.c
header file:
a4.h
compilation command:
make
or
gcc -Wall -o a4 a4.c a4_1.c a4-util.o
clean command:
make clean
launching and operation instruction:
  To make the peer as a server:
    ./a4
  To make the peer as a client:
    ./a4 127.0.0.1

Should run server first, and then run the client. Otherwise the client would not connect.

