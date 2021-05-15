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

    sem_unlink(semEmptySpaceOnTable);
    sem_unlink(semEmptySpaceInFurnaceName);
    sem_unlink(semOccupiedSpaceOnTableName);
    sem_unlink(semAccessFName);
    shm_unlink(shMemFurnaceIndexName);
    shm_unlink(shMemFurnaceName);
    shm_unlink(shMemTableIndexName);
    shm_unlink(shMemTableName);


    int furnaceFd = shm_open(shMemFurnaceName, O_RDWR | O_CREAT | O_EXCL, 0644);
    if(furnaceFd < 0) error("shm_open furnace err");
    int ftruncateRes = ftruncate(furnaceFd, 5*sizeof(int));
    if(ftruncateRes < 0) error("ftruncate furnace err");
    int* furnace = (int*) mmap(NULL, 5*sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, furnaceFd, 0);
    if(furnace == (int*) -1) error("mmap furnace err");
    memset(furnace, -1, 5*sizeof(int));

    int furnaceIndexFd = shm_open(shMemFurnaceIndexName, O_RDWR | O_CREAT | O_EXCL, 0644);
    if(furnaceIndexFd < 0) error("shm_open furnaceIndex");
    ftruncateRes = ftruncate(furnaceIndexFd, sizeof(int));
    if(ftruncateRes < 0) error("ftruncate furnaceIndex err");

    int* furnaceIndex = (int*) mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, furnaceIndexFd, 0);
    if(furnaceIndex == (int*)-1) error("furnaceIndex shmat err");
    furnaceIndex[0] = 0;

    
    int tableFd = shm_open(shMemTableName, O_RDWR | O_CREAT | O_EXCL, 0644);
    if(tableFd < 0) error("shm_open table err");
    ftruncateRes = ftruncate(tableFd, 5*sizeof(int));
    if(ftruncateRes < 0) error("ftruncate table err");
    int* table = (int*)mmap(NULL, 5*sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, tableFd, 0);
    if(table == (int*)-1) error("mmap table err");
    memset(table, -1, 5 * sizeof(int));

    int tableIndexFd = shm_open(shMemTableIndexName, O_RDWR | O_CREAT | O_EXCL, 0644);
    if(tableIndexFd < 0) error("shm_open table err");
    ftruncateRes = ftruncate(tableIndexFd, sizeof(int));
    if(ftruncateRes < 0) error("ftruncate tableIndex err");
    int* tableIndex = (int*) mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, tableIndexFd, 0);
    if(tableIndex == (int*) -1) error("mmap tableIndex err");
    tableIndex[0] = 0;

    sem_t * emptySpaceOnTable = sem_open(semEmptySpaceOnTable, O_RDWR | O_CREAT, 0644, 5);
    if(emptySpaceOnTable == SEM_FAILED) error("sem open emptySpaceOnTable err");

    sem_t * occupiedSpaceOnTable = sem_open(semOccupiedSpaceOnTableName, O_RDWR | O_CREAT, 0644, 0);
    if(occupiedSpaceOnTable == SEM_FAILED) error("sem open occupiedSpaceOnTable err");

    sem_t * emptySpaceInFurnace = sem_open(semEmptySpaceInFurnaceName, O_RDWR | O_CREAT, 0644, 5);
    if(emptySpaceInFurnace == SEM_FAILED) error("sem open emptySpace err");   

    sem_t * accessF = sem_open(semAccessFName, O_RDWR | O_CREAT, 0644, 1);
    if(accessF == SEM_FAILED) error("sem open accessF err");

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



    int sem_closeRes = sem_close(emptySpaceOnTable);
    if(sem_closeRes < 0) error("semctl close emptySpaceOnTable err");
    sem_closeRes = sem_close(emptySpaceInFurnace);
    if(sem_closeRes < 0) error("semctl close emptySpaceInFurnace err");
    sem_closeRes = sem_close(occupiedSpaceOnTable);
    if(sem_closeRes < 0) error("semctl close occupiedSpaceOnTable err");
    sem_closeRes = sem_close(accessF);
    if(sem_closeRes < 0) error("semclose accessF err");

    int sem_unlinkRes = sem_unlink(semEmptySpaceOnTable);
    if(sem_unlinkRes < 0) error("sem_unlink  emptySpaceOnTable err");
    sem_unlinkRes = sem_unlink(semEmptySpaceInFurnaceName);
    if(sem_unlinkRes < 0) error("sem_unlink  emptySpaceInFurnace err");
    sem_unlinkRes = sem_unlink(semOccupiedSpaceOnTableName);
    if(sem_unlinkRes < 0) error("sem_unlink  occupiedSpaceOnTable err");
    sem_unlinkRes = sem_unlink(semAccessFName);

    int munmapRes = munmap(furnace, 5*sizeof(int));
    if(munmapRes < 0) error("munmap furnace err");
    munmapRes = munmap(table, 5*sizeof(int));
    if(munmapRes < 0) error("munmap table err");
    munmapRes = munmap(furnaceIndex, sizeof(int));
    if(munmapRes < 0) error("munmap furnaceIndex err");
    munmapRes = munmap(tableIndex, sizeof(int));
    if(munmapRes < 0) error("munmap tableIndex err");

    int shm_unlinkRes = shm_unlink(shMemFurnaceIndexName);
    if(shm_unlinkRes < 0) error("unlink shMemFurnaceIndexName err");
    shm_unlinkRes = shm_unlink(shMemFurnaceName);
    if(shm_unlinkRes < 0) error("unlink shMemFurnaceName err");
    shm_unlinkRes = shm_unlink(shMemTableIndexName);
    if(shm_unlinkRes < 0) error("unlink shMemTableIndexName err");
    shm_unlinkRes = shm_unlink(shMemTableName);
    if(shm_unlinkRes < 0) error("unlink shMemTableName err");

    return 0;
}