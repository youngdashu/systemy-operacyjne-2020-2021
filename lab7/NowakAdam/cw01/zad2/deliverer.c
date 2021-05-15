#include"commonData.h"

int* table;
int * tableIndex;

sem_t * emptySpaceOnTable, *occupiedSpaceOnTable;

void handleSigint(int signo){

    if(signo == SIGINT){
        
        int munmapRes;
        munmapRes = munmap(table, 5*sizeof(int));
        if(munmapRes < 0) error("munmap table err");
        munmapRes = munmap(tableIndex, sizeof(int));
        if(munmapRes < 0) error("munmap tableIndex err");

        int sem_closeRes;
        sem_closeRes = sem_close(emptySpaceOnTable);
        if(sem_closeRes < 0) error("semctl close emptySpaceOnTable err");
        sem_closeRes = sem_close(occupiedSpaceOnTable);
        if(sem_closeRes < 0) error("semctl close occupiedSpaceOnTable err");

        exit(EXIT_SUCCESS);
    }
}

int main(){

    int tableFd = shm_open(shMemTableName, O_RDWR | O_CREAT, 0);
    if(tableFd < 0) error("shm_open table err");
    table = (int*)mmap(NULL, 5*sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, tableFd, 0);
    if(table == (int*)-1) error("mmap table err");

    int tableIndexFd = shm_open(shMemTableIndexName, O_RDWR | O_CREAT, 0);
    if(tableIndexFd < 0) error("shm_open table err");
    tableIndex = (int*) mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, tableIndexFd, 0);
    if(tableIndex == (int*) -1) error("mmap tableIndex err");

    emptySpaceOnTable = sem_open(semEmptySpaceOnTable, O_RDWR | O_CREAT, 0, 0);
    if(emptySpaceOnTable == SEM_FAILED) error("sem open emptySpaceOnTable err");

    occupiedSpaceOnTable = sem_open(semOccupiedSpaceOnTableName, O_RDWR | O_CREAT, 0, 0);
    if(occupiedSpaceOnTable == SEM_FAILED) error("sem open occupiedSpaceOnTable err");

    int pid = getpid();
    struct timespec spec;

    sig_t sigRes = signal(SIGINT, &handleSigint);
    if(sigRes == SIG_ERR) error("signal handler err");

    int waitRes, postRes;
    int pizzaTaken, deliveryTime, returnTime;
    
    while(1){


        waitRes = sem_wait(occupiedSpaceOnTable);
        if(waitRes < 0) error("occupiedSpaceOnTable decrement err");

        postRes = sem_post(emptySpaceOnTable);
        if(postRes < 0) error("currentIndexSem semop increment err");

        pizzaTaken = table[tableIndex[1] % 5];
        ++tableIndex[1];

        clock_gettime(CLOCK_REALTIME, &spec);
        printf("Deliverer (%i %i) Pobieram pizze %i. Liczba pizz na stole: %i.\n", pid, (int) (spec.tv_nsec/1), pizzaTaken, tableIndex[0] - tableIndex[1]);

        deliveryTime = (random() % 2) + 4;
        sleep(deliveryTime);
        
        clock_gettime(CLOCK_REALTIME, &spec);
        printf("Deliverer (%i %i) Dostarczam pizze %i.\n", pid, (int) (spec.tv_nsec/1), pizzaTaken);

        returnTime = (random() % 2) + 4;
        sleep(returnTime);



    }

    return 0;
}