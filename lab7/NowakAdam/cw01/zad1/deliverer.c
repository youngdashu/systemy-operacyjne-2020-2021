#include"commonData.h"

int* table;
int * tableIndex;

void handleSigint(int signo){

    if(signo == SIGINT){
        
        int res;
        res = shmdt(table);
        if(res < 0) error("shmdt furnaceIndex");
        res = shmdt(tableIndex);
        if(res < 0) error("shmdt tableIndex");

        exit(EXIT_SUCCESS);
    }
}

int main(){

    int tableKey = ftok("/etc/group", 0);
    if(tableKey == -1) error("furnace key ftok");
    int tableId = shmget(tableKey, 0, 0);
    if(tableId == -1) error("table shmget err");

    table = shmat(tableId, NULL, 0);
    if(table == (int*)-1) error("shmat tableId err");

    int tableIndexKey = ftok("/etc/group", 1000);
    if(tableIndexKey == -1) error("furnace key ftok");
    int tableIndexId = shmget(tableIndexKey, 0, 0);
    if(tableIndexId == -1) error("tableIndex shmget err");

    tableIndex = (int* ) shmat(tableIndexId, NULL, 0);
    if(tableIndex == (int*) -1) error("shmat tableIndrex err");

    int emptySpaceOnTableKey = ftok("./restaurant.c", 1000);
    if(emptySpaceOnTableKey == -1) error("emptySpaceOnTableKey ftok err");
    int emptySpaceOnTable = semget(emptySpaceOnTableKey, 0, 0);
    if(emptySpaceOnTable == -1) error("emptySpaceOnTable semget err");

    int occupiedSpaceOnTableKey = ftok("./cook.c", 100);
    if(occupiedSpaceOnTableKey == -1) error("occupiedSpaceOnTableKey ftok err");
    int occupiedSpaceOnTable = semget(occupiedSpaceOnTableKey, 0, 0);
    if(occupiedSpaceOnTable == -1) error("occupiedSpaceOnTable semget err");

    struct sembuf opIncr;
    opIncr.sem_op = 1;
    opIncr.sem_num = 0;

    struct sembuf opDecr;
    opDecr.sem_op = -1;
    opDecr.sem_num = 0;

    int pid = getpid();
    struct timespec spec;

    sig_t sigRes = signal(SIGINT, &handleSigint);
    if(sigRes == SIG_ERR) error("signal handler err");

    int pizzaTaken, semctlRes, deliveryTime, returnTime, semopRes;

    while(1){

        semopRes = semop(occupiedSpaceOnTable, &opDecr, 1);
        if(semopRes < 0) error("occupiedSpaceOnTable decrement error");

        semopRes = semop(emptySpaceOnTable, &opIncr, 1);
        if(semopRes < 0) error("currentIndexSem semop increment err");

        pizzaTaken = table[tableIndex[1] % 5];
        ++tableIndex[1];

        

        semctlRes = semctl(emptySpaceOnTable, 0, GETVAL);
        if(semctlRes < 0) error("semctl emptySpaceOnTable err");
        clock_gettime(CLOCK_REALTIME, &spec);
        printf("Deliverer (%i %i) Pobieram pizze %i. Liczba pizz na stole: %i.\n", pid, (int) (spec.tv_nsec/1), pizzaTaken, tableIndex[0]-tableIndex[1]);

        deliveryTime = (random() % 2) + 4;
        sleep(deliveryTime);
        
        clock_gettime(CLOCK_REALTIME, &spec);
        printf("Deliverer (%i %i) Dostarczam pizze %i.\n", pid, (int) (spec.tv_nsec/1), pizzaTaken);

        returnTime = (random() % 2) + 4;
        sleep(returnTime);



    }

    return 0;
}