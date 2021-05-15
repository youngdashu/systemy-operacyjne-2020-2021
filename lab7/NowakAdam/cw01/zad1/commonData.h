#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include<sys/shm.h>
#include<sys/sem.h>
#include<sys/ipc.h>
#include<sys/types.h>

#include<unistd.h>

#include<time.h>

#include<signal.h>

#include<sys/wait.h>
// #define furnaceKey 1

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short  *array;
};


void error(char* msg){
    perror(msg);
    exit(EXIT_FAILURE);
}