#include<stdlib.h>
#include<stdio.h>
#include<string.h>

// #include<sys/shm.h>
// #include<sys/sem.h>
// #include<sys/ipc.h>
// #include<sys/types.h>

#include<semaphore.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/mman.h>


#include<unistd.h>

#include<time.h>

#include<signal.h>

#include<sys/wait.h>
// #define furnaceKey 1

#define semEmptySpaceInFurnaceName "/emptySpaceInFurnace"
#define semEmptySpaceOnTable "/emptySpaceOnTable"
#define semOccupiedSpaceOnTableName "/occupiedSpaceOnTable"

#define semAccessFName "/accessF"

#define shMemFurnaceName "/shMemFurnace"
#define shMemFurnaceIndexName "/shMemFurnaceIndex"
#define shMemTableName "/shMemTable"
#define shMemTableIndexName "/shMemTableIndex"

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short  *array;
};


void error(char* msg){
    perror(msg);
    exit(EXIT_FAILURE);
}