#include<stdio.h>
#include<stdlib.h>

#include<string.h>

#include<sys/msg.h>

#include<signal.h>
#include<unistd.h>

#define MAXMSGLEN 512

#define INIT 1
#define SERVER_ENDS_WORK 2
#define RETURN_SUCCESS_CONNECTED 3
#define RETURN_FAIL 4
#define LIST 5
#define CONNECT 6
#define DISCONNECT 7
#define STOP 8

#define msgSize sizeof(mymsg)-sizeof(long)

typedef struct mymsg {
    long mtype; /* positive message type */
    int clientID;
    char mtext[MAXMSGLEN]; /* message data, of length nbytes */
}mymsg;

// int msgSize = sizeof(mymsg) - sizeof(long);

void error(char* msg);