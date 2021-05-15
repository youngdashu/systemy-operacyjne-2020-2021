#include"commonData.h"

int* furnace;
int* table;
int* furnaceIndex;
int * tableIndex;

void handleSigint(int signo){

    if(signo == SIGINT){
        
        int res;
        res = shmdt(furnace);
        if(res < 0) error("shmdt furnace");
        res = shmdt(table);
        if(res < 0) error("shmdt table");
        res = shmdt(furnaceIndex);
        if(res < 0) error("shmdt furnaceIndex");
        res = shmdt(tableIndex);
        if(res < 0) error("shmdt tableIndex");

        exit(EXIT_SUCCESS);
    }
}


int main(){

    int furnaceKey = ftok("/etc/passwd", 0);
    if(furnaceKey == -1) error("furnace key ftok");

    int shmGetRes = shmget(furnaceKey, 0, 0);
    if(shmGetRes == -1) error("shmget err");

    furnace = (int*) shmat(shmGetRes, NULL, 0);
    if(furnace == (int*)-1) error("furnace shmat err");

    int furnaceIndexKey = ftok("/etc/passwd", 1000);
    if(furnaceIndexKey == -1) error("furnace inde key ftok err");
    shmGetRes = shmget(furnaceIndexKey, 0, 0);
    if(shmGetRes == -1) error("furnaceIndex shmget err");

    furnaceIndex = shmat(shmGetRes, NULL, 0);
    if(furnaceIndex == (int*)-1) error("furnaceIndex shmat err");

    int emptySpaceInFurnaceKey = ftok("./restaurant.c", 0);
    if(emptySpaceInFurnaceKey == -1) error("emptySpaceKey ftok err");
    int emptySpaceInFurnace = semget(emptySpaceInFurnaceKey, 0, 0);
    if(emptySpaceInFurnace == -1) error("emptySpaceInFurnace semget err");

    // int currentIndexSemKey = ftok("./cook.c", 0);
    // if(currentIndexSemKey == -1) error("currentIndexSemKey ftok err");
    // int currentIndexSem = semget(currentIndexSemKey, 0, 0);
    // if(currentIndexSem == -1) error("currentIndexSem semget err");

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

    int accessFKey = ftok("./deliverer.c", 1000);
    if(accessFKey == -1) error("accessFKey ftok err");
    int accessF = semget(accessFKey, 0, 0);
    if(accessF == -1) error("accessF semget err");

    signal(SIGINT, &handleSigint);

    struct sembuf opDecr;
    opDecr.sem_op = -1;
    opDecr.sem_num = 0;

    struct timespec spec;
    int pid = getpid();
    srandom(pid);

    int pizzaType, preparePizzaTime, pizzaTakenOut;

    struct sembuf opIncr;
    opIncr.sem_op = 1;
    opIncr.sem_num = 0;

    while(1){

        pizzaType = ((int) random()) % 10;
        preparePizzaTime = (random() % 2) + 1;
        clock_gettime(CLOCK_REALTIME, &spec);

        printf("Cook (%i %i) Przygotowuje pizze %i\n", pid, (int) (spec.tv_nsec/1), pizzaType);
        sleep(preparePizzaTime);

        
        int semopRes = semop(emptySpaceInFurnace, &opDecr, 1);
        if(semopRes < 0) error("currentIndexSem semop decrement err");

        semopRes = semop(accessF, &opDecr, 1);

        furnace[furnaceIndex[0] % 5] = pizzaType;
        ++furnaceIndex[0];

        clock_gettime(CLOCK_REALTIME, &spec);
        printf("Cook (%i %i) Dodalem pizze %i. Liczba pizz w piecu: %i.\n", pid, (int) (spec.tv_nsec/1), pizzaType, furnaceIndex[0] - furnaceIndex[1]);

        semopRes = semop(accessF, &opIncr, 1);

        int waitForPizzaToBakeTime = ((int)random()%2) + 4;

        sleep(waitForPizzaToBakeTime);

        semopRes = semop(accessF, &opDecr, 1);

        semopRes = semop(emptySpaceInFurnace, &opIncr, 1);

        pizzaTakenOut = furnace[furnaceIndex[1] % 5];
        ++furnaceIndex[1];

        int currentNumOfPizzasInFurnace = furnaceIndex[0] - furnaceIndex[1];

        semopRes = semop(accessF, &opIncr, 1);

        semopRes = semop(emptySpaceOnTable, &opDecr, 1);
        // if(semopRes < 0) error("semop decrement emptySpaceOnTable err");

        // indexToPutPizzaOnTable = tableIndex[0] % 5;

        table[tableIndex[0] % 5] = pizzaTakenOut;
        ++tableIndex[0];

        semopRes = semop(occupiedSpaceOnTable, &opIncr, 1);


        clock_gettime(CLOCK_REALTIME, &spec);
        printf("Cook (%i %i) Wyjmuje pizze %i. Liczba pizz w piecu: %i. Liczba pizz na stole: %i.\n", pid, (int) (spec.tv_nsec/1), pizzaTakenOut, currentNumOfPizzasInFurnace, tableIndex[0] - tableIndex[1]);



    }

    return 0;
}