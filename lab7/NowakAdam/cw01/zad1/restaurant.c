#include"commonData.h"

int cooksNum, deliverersNum;
int* cooksArr, *deliverersArr;

void handleSigint(int signo){
    if(signo == SIGINT){
        
        for(int i = 0; i< cooksNum; i++){
            kill(cooksArr[i], SIGINT);
        }
        for(int i = 0; i< deliverersNum; i++){
            kill(deliverersArr[i], SIGINT);
        }

    }
}


int main(int argc, char* argv[]){

    if(argc != 3) error("zla liczba argumentow");

    cooksNum = atoi(argv[1]);
    deliverersNum = atoi(argv[2]);

    cooksArr = calloc(cooksNum, sizeof(int));
    deliverersArr = calloc(deliverersNum, sizeof(int));

    // create furnace
    int furnaceKey = ftok("/etc/passwd", 0);
    if(furnaceKey == -1) error("furnace key ftok");
    int furnaceId = shmget(furnaceKey, 5*sizeof(int), IPC_CREAT | IPC_EXCL | 0666);
    if(furnaceId == -1) error("furnace shmget err");

    int* furnace = shmat(furnaceId, NULL, 0);
    if(furnace == (int*) -1) error("shmat furnace err");
    memset(furnace, -1, 5*sizeof(int));

    int furnaceIndexKey = ftok("/etc/passwd", 1000);
    if(furnaceIndexKey == -1) error("furnace inde key ftok err");
    int furnaceIndexId = shmget(furnaceIndexKey, 2*sizeof(int), IPC_CREAT | IPC_EXCL | 0666);
    if(furnaceIndexId == -1) error("furnaceIndexId shmget err");

    int* furnaceIndex = shmat(furnaceIndexId, NULL, 0);
    if(furnaceIndex == (int*)-1) error("furnaceIndex shmat err");
    furnaceIndex[0] = 0;
    furnaceIndex[1] = 0;


    int emptySpaceInFurnaceKey = ftok("./restaurant.c", 0);
    if(emptySpaceInFurnaceKey == -1) error("emptySpaceKey ftok err");
    int emptySpaceInFurnace = semget(emptySpaceInFurnaceKey, 1, IPC_CREAT | IPC_EXCL | 0666);
    if(emptySpaceInFurnace == -1) error("emptySpaceInFurnace semget err");


    int tableKey = ftok("/etc/group", 0);
    if(tableKey == -1) error("furnace key ftok");
    int tableId = shmget(tableKey, 5*sizeof(int), IPC_CREAT | IPC_EXCL | 0666);
    if(tableId == -1) error("table shmget err");

    int* table = (int*)shmat(tableId, NULL, 0);
    if(table == (int*)-1) error("shmat table err");
    memset(table, -1, 5 * sizeof(int));

    int tableIndexKey = ftok("/etc/group", 1000);
    if(tableIndexKey == -1) error("furnace key ftok");
    int tableIndexId = shmget(tableIndexKey, 2*sizeof(int), IPC_CREAT | IPC_EXCL | 0666);
    if(tableIndexId == -1) error("tableIndexId shmget err");

    int* tableIndex = (int*) shmat(tableIndexId, NULL, 0);
    if(tableIndex == (int*) -1) error("shmat table err");
    tableIndex[0] = 0;
    tableIndex[1] = 0;

    int emptySpaceOnTableKey = ftok("./restaurant.c", 1000);
    if(emptySpaceOnTableKey == -1) error("emptySpaceOnTableKey ftok err");
    int emptySpaceOnTable = semget(emptySpaceOnTableKey, 1, IPC_CREAT | IPC_EXCL | 0666);
    if(emptySpaceOnTable == -1) error("emptySpaceOnTable semget err");

    int accessFKey = ftok("./deliverer.c", 1000);
    if(accessFKey == -1) error("accessFKey ftok err");
    int accessF = semget(accessFKey, 1, IPC_CREAT | IPC_EXCL | 0666);
    if(accessF == -1) error("accessF semget err");


    union semun setValArg1;
    setValArg1.val = 5;
    
    int semctlRes = semctl(emptySpaceOnTable, 0, SETVAL, setValArg1);
    if(semctlRes == -1) error("semctl emptySpaceOnTable SETVAL err");

    union semun setValArg2;
    setValArg2.val = 5;
    semctlRes = semctl(emptySpaceInFurnace, 0, SETVAL, setValArg2);
    if(semctlRes == -1) error("semctl emptySpaceInFurnace SETVAL err");

    int occupiedSpaceOnTableKey = ftok("./cook.c", 100);
    if(occupiedSpaceOnTableKey == -1) error("occupiedSpaceOnTableKey ftok err");
    int occupiedSpaceOnTable = semget(occupiedSpaceOnTableKey, 1, IPC_CREAT | IPC_EXCL | 0666);
    if(occupiedSpaceOnTable == -1) error("occupiedSpaceOnTable semget err");


    union semun setValArg3;
    setValArg3.val = 0;
    semctlRes = semctl(occupiedSpaceOnTable, 0, SETVAL, setValArg3);
    if(semctlRes < 0) error("");

    union semun setValArg4;
    setValArg4.val = 1;
    semctlRes = semctl(accessF, 0, SETVAL, setValArg4);
    if(semctlRes < 0) error("semctl setval accessF");



    signal(SIGINT, &handleSigint);

    for(int i = 0; i < cooksNum; i++){

        int newCook = fork();
        if(newCook == -1) error("cook fork err");
        if(newCook == 0){
            execl("./cook", "cook", NULL);
            exit(EXIT_SUCCESS);       
        } else{
            cooksArr[i] = newCook;
        }
    }

    for(int i =0; i < deliverersNum; i++){

        int newDeliverer = fork();
        if(newDeliverer == -1) error("deliverer fork err");
        if(newDeliverer == 0){
            execl("./deliverer", "deliverer", NULL);
            exit(EXIT_SUCCESS);        
        } else{
            deliverersArr[i] = newDeliverer;
        }
    }

    sigset_t set;
    sigfillset(&set);
    sigdelset(&set, SIGINT);
    sigsuspend(&set);

    for(int i = 0; i < cooksNum + deliverersNum; i++){
        wait(NULL);
    }

    int shmdtRes = shmdt(furnace);
    if(shmdtRes < 0) error("shmdt furnace err");
    shmdtRes = shmdt(table);
    if(shmdtRes < 0) error("shmdt table err");
    shmdtRes = shmdt(furnaceIndex);
    if(shmdtRes < 0) error("shmdt furnaceIndex err");
    shmdtRes = shmdt(tableIndex);
    if(shmdtRes < 0) error("shmdt tableIndex err");

    semctlRes = semctl(emptySpaceOnTable, 0, IPC_RMID);
    if(semctlRes < 0) error("semctl remove emptySpaceOnTable err");
    semctlRes = semctl(emptySpaceInFurnace, 0, IPC_RMID);
    if(semctlRes < 0) error("semctl remove emptySpaceInFurnace err");
    semctlRes = semctl(occupiedSpaceOnTable, 0, IPC_RMID);
    if(semctlRes < 0) error("semctl remove occupiedSpaceOnTable err");
    semctlRes = semctl(accessF, 0, IPC_RMID);
    if(semctlRes < 0) error("semctl remove accessF err");

    int shmctlRes = shmctl(furnaceId, IPC_RMID, NULL);
    if(shmctlRes < 0) error("shmctl remove furnaceId err");
    shmctlRes = shmctl(tableId, IPC_RMID, NULL);
    if(shmctlRes < 0) error("shmctl remove tableId err");
    shmctlRes = shmctl(furnaceIndexId, IPC_RMID, NULL);
    if(shmctlRes < 0) error("shmctl remove furnaceIndexId err");
    shmctlRes = shmctl(tableIndexId, IPC_RMID, NULL);
    if(shmctlRes < 0) error("shmctl remove tableIndexId err");

    return 0;
}