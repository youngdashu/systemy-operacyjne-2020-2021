#include"commonData.h"

int* furnace;
int* table;
int* furnaceIndex;
int * tableIndex;

sem_t * emptySpaceOnTable, *occupiedSpaceOnTable, *emptySpaceInFurnace, *accessF;

void handleSigint(int signo){

    if(signo == SIGINT){
        
        

        int munmapRes = munmap(furnace, 5*sizeof(int));
        if(munmapRes < 0) error("munmap furnace err");
        munmapRes = munmap(table, 5*sizeof(int));
        if(munmapRes < 0) error("munmap table err");
        munmapRes = munmap(furnaceIndex, 2*sizeof(int));
        if(munmapRes < 0) error("munmap furnaceIndex err");
        munmapRes = munmap(tableIndex, 2*sizeof(int));
        if(munmapRes < 0) error("munmap tableIndex err");

        int sem_closeRes = sem_close(emptySpaceOnTable);
        if(sem_closeRes < 0) error("close emptySpaceOnTable err");
        sem_closeRes = sem_close(emptySpaceInFurnace);
        if(sem_closeRes < 0) error("close emptySpaceInFurnace err");
        sem_closeRes = sem_close(occupiedSpaceOnTable);
        if(sem_closeRes < 0) error("close occupiedSpaceOnTable err");
        sem_closeRes = sem_close(accessF);
        if(sem_closeRes < 0) error("close accessF err");



        exit(EXIT_SUCCESS);
    }
}


int main(){


    int furnaceFd = shm_open(shMemFurnaceName, O_RDWR, 0644);
    if(furnaceFd < 0) error("shm_open furnace err");
    furnace = (int*) mmap(NULL, 5*sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, furnaceFd, 0);
    if(furnace == (int*) -1) error("mmap furnace err");

    int furnaceIndexFd = shm_open(shMemFurnaceIndexName, O_RDWR | O_CREAT , 0);
    if(furnaceIndexFd < 0) error("shm_open furnaceIndex");
    furnaceIndex = (int*) mmap(NULL, 2*sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, furnaceIndexFd, 0);
    if(furnaceIndex == (int*)-1) error("furnaceIndex shmat err");
    
    int tableFd = shm_open(shMemTableName, O_RDWR | O_CREAT, 0);
    if(tableFd < 0) error("shm_open table err");
    table = (int*)mmap(NULL, 5*sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, tableFd, 0);
    if(table == (int*)-1) error("mmap table err");

    int tableIndexFd = shm_open(shMemTableIndexName, O_RDWR | O_CREAT, 0);
    if(tableIndexFd < 0) error("shm_open table err");
    tableIndex = (int*) mmap(NULL, 2*sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, tableIndexFd, 0);
    if(tableIndex == (int*) -1) error("mmap tableIndex err");

    emptySpaceOnTable = sem_open(semEmptySpaceOnTable, O_RDWR | O_CREAT, 0, 0);
    if(emptySpaceOnTable == SEM_FAILED) error("sem open emptySpaceOnTable err");

    occupiedSpaceOnTable = sem_open(semOccupiedSpaceOnTableName, O_RDWR | O_CREAT, 0, 0);
    if(occupiedSpaceOnTable == SEM_FAILED) error("sem open occupiedSpaceOnTable err");

    emptySpaceInFurnace = sem_open(semEmptySpaceInFurnaceName, O_RDWR | O_CREAT, 0, 0);
    if(emptySpaceInFurnace == SEM_FAILED) error("sem open emptySpace err");   

    accessF = sem_open(semAccessFName, O_RDWR, 0, 0);
    if(accessF == SEM_FAILED) error("sem open accessF err");



    signal(SIGINT, &handleSigint);



    struct timespec spec;
    int pid = getpid();
    srandom(pid);

    int pizzaType, preparePizzaTime, waitRes;
    int currentEmptySpaceInFurnace;
    int postRes;

    while(1){

        pizzaType = ((int) random()) % 10;
        preparePizzaTime = (random() % 2) + 1;
        clock_gettime(CLOCK_REALTIME, &spec);

        printf("Cook (%i %i) Przygotowuje pizze %i\n", pid, (int) (spec.tv_nsec/1), pizzaType);
        sleep(preparePizzaTime);
        
        waitRes = sem_wait(emptySpaceInFurnace);
        // if(waitRes < 0) error("emptySpaceInFurnace decrement err");

        waitRes = sem_wait(accessF);


        furnace[furnaceIndex[0] % 5] = pizzaType;
        ++furnaceIndex[0];

        int sem_getvalueRes = sem_getvalue(emptySpaceInFurnace, &currentEmptySpaceInFurnace);
        if(sem_getvalueRes < 0) error("currentIndexSem getvalue 2 err");

        clock_gettime(CLOCK_REALTIME, &spec);
        printf("Cook (%i %i) Dodalem pizze %i. Liczba pizz w piecu: %i.\n", pid, (int) (spec.tv_nsec/1), pizzaType, furnaceIndex[0]-furnaceIndex[1]);

        postRes = sem_post(accessF);

        sleep(((int)random()%2) + 4);

        waitRes = sem_wait(accessF);        

        postRes = sem_post(emptySpaceInFurnace);
        if(postRes < 0) error("currentIndexSem semop increment err");

        int pizzaTakenOut = furnace[furnaceIndex[1] % 5];
        ++furnaceIndex[1];

        postRes = sem_post(accessF);

        
        // furnace[indexOfPizzaToTakeOutFromFurnace] = -1;
        // sem_getvalueRes = sem_getvalue(emptySpaceInFurnace, &currentEmptySpaceInFurnace);
        // if(sem_getvalueRes < 0) error("semctl currentIndexSem getval 2 err");
        // numOfPizzasInFurnace = furnaceIndex[0] - furnaceIndex[1];
        waitRes = sem_wait(emptySpaceOnTable);
        if(waitRes < 0) error("decrement emptySpaceOnTable err");

        table[tableIndex[0] % 5] = pizzaTakenOut;
        ++tableIndex[0];

        postRes = sem_post(occupiedSpaceOnTable);
        if(postRes < 0) error("increment occupiedSpaceOnTable err");

        

        // int currentEmptySpaceOnTable;
        // sem_getvalueRes = sem_getvalue(emptySpaceOnTable, &currentEmptySpaceOnTable);
        // if(sem_getvalueRes < 0) error(" getval currentEmptySpaceOnTable err");

        clock_gettime(CLOCK_REALTIME, &spec);
        printf("Cook (%i %i) Wyjmuje pizze %i. Liczba pizz w piecu: %i. Liczba pizz na stole: %i.\n", pid, (int) (spec.tv_nsec/1), pizzaTakenOut, furnaceIndex[0] - furnaceIndex[1], tableIndex[0]-tableIndex[1]);



    }

    return 0;
}