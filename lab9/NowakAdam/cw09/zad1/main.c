#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>
#include <time.h>
// #include<signal.h>

void error(char* msg){
    perror(msg);
    exit(EXIT_FAILURE);
}

int elfsWaiting, reindeersWaiting;
int wakeSanta, santaMeetsElfs, santaDeliversPresents, santaWentToSleep, lessThan3Waiting, anyWaitingElfs;
pthread_cond_t condWakeSanta = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutexWakeSanta = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexElfsWaiting = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexReindeersWaiting = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t condSantaMeetsElfs = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutexSantaMeetsElfs = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t condLessThan3ElfsWaiting = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutexLessThan3Waiting = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t condSantaDeliversPresents = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutexSantaDeliversPresents = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t condSantaWentToSleep = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutexSantaWentToSleep = PTHREAD_MUTEX_INITIALIZER;

int elfsReady, reindeersReady;
pthread_mutex_t mutexElfsReady = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexReindeersReady = PTHREAD_MUTEX_INITIALIZER;

pthread_t elfsInQueue [] = {0, 0, 0};

pthread_t *threadIds;

void santaEndsJob(){
    printf("M: konczenie pracy\n");
    int cancelThreadRes;
    for(int i = 1; i < 20; i++){
        // pthread_kill(threadIds[i], SIGINT);
        cancelThreadRes = pthread_cancel(threadIds[i]);
        if(cancelThreadRes < 0) printf("cancel thread err\n");
    }
}

void* santa(void* args){

    int presentsDeliveredCounter = 0;

    pthread_mutex_lock(&mutexSantaWentToSleep);
    santaWentToSleep = 1;
    // pthread_cond_broadcast(&condSantaWentToSleep);
    pthread_mutex_unlock(&mutexSantaWentToSleep);

    int i = 2;
    int elfsFlag, reindeersFlag;
    
    while(1){
        
        pthread_mutex_lock(&mutexWakeSanta);
        while(!wakeSanta){
            pthread_cond_wait(&condWakeSanta, &mutexWakeSanta);
        }
        pthread_mutex_unlock(&mutexWakeSanta);


        pthread_mutex_lock(&mutexSantaWentToSleep);
        santaWentToSleep = 0;
        pthread_mutex_unlock(&mutexSantaWentToSleep);

        printf("M: obudzony!\n");

        elfsFlag = reindeersFlag = 1;

        i = 2;

        while (i--)
        {
            printf("M: lock inner while\n");
            pthread_mutex_lock(&mutexReindeersReady);
            pthread_mutex_lock(&mutexElfsReady);
            if(!elfsReady && !reindeersReady){
                pthread_mutex_unlock(&mutexReindeersReady);
                pthread_mutex_unlock(&mutexElfsReady);
                printf("M: nikt nie czeka\n");
                break;
            } else{
                printf("M: ktos czeka\n");
                pthread_mutex_unlock(&mutexReindeersReady);
                pthread_mutex_unlock(&mutexElfsReady);
            }
        
        

            pthread_mutex_lock(&mutexReindeersReady);
        
            if(reindeersReady && reindeersFlag){

                --reindeersFlag;

                pthread_mutex_unlock(&mutexReindeersReady);

                pthread_mutex_lock(&mutexSantaDeliversPresents);
                santaDeliversPresents = 1;
                pthread_cond_broadcast(&condSantaDeliversPresents);
                pthread_mutex_unlock(&mutexSantaDeliversPresents);

                printf("Mikolaj: dostarczam zabawki\n");
                sleep(rand() % 3 + 2);

                pthread_mutex_lock(&mutexSantaDeliversPresents);
                santaDeliversPresents = 0;
                pthread_mutex_unlock(&mutexSantaDeliversPresents);

                presentsDeliveredCounter++;

                // printf("M: dostarczono zabawki\n");

                if(presentsDeliveredCounter == 3){
                    
                    int * res = calloc(1, sizeof(int));
                    *res = 1;
                    pthread_exit((void*)res);
                }

            } else{
                pthread_mutex_unlock(&mutexReindeersReady);
                pthread_mutex_lock(&mutexElfsReady);
                if(elfsReady && elfsFlag){
                    --elfsFlag;
                    pthread_mutex_unlock(&mutexElfsReady);

                    pthread_mutex_lock(&mutexSantaMeetsElfs);
                    santaMeetsElfs = 1;
                    pthread_cond_broadcast(&condSantaMeetsElfs);
                    // pthread_cond_signal(&condSantaMeetsElfs);
                    // pthread_cond_signal(&condSantaMeetsElfs);
                    // pthread_cond_signal(&condSantaMeetsElfs);
                    pthread_mutex_unlock(&mutexSantaMeetsElfs);

                    printf("Mikolaj: rozwiazuje problemy elfow %lu %lu %lu\n", elfsInQueue[0], elfsInQueue[1], elfsInQueue[2]);

                    // pthread_mutex_lock(&mutexSantaMeetsElfs);
                    // santaMeetsElfs = 0;
                    // pthread_mutex_unlock(&mutexSantaMeetsElfs);


                    sleep(rand() % 2 + 1);

                    // printf("M: po sleepie, santameetselfs = 0\n");

                    pthread_mutex_lock(&mutexSantaMeetsElfs);
                    santaMeetsElfs = 0;
                    pthread_mutex_unlock(&mutexSantaMeetsElfs);

                } else{
                    pthread_mutex_unlock(&mutexElfsReady);
                }

            }

            printf("M: end inner while\n");

        }

        
        pthread_mutex_lock(&mutexWakeSanta);
        printf("M: wakesanta = 0\n");
        wakeSanta = 0;
        pthread_mutex_unlock(&mutexWakeSanta);

        pthread_mutex_lock(&mutexSantaWentToSleep);
        printf("M: santaWentToSleep = 1\n");
        santaWentToSleep = 1;
        pthread_cond_broadcast(&condSantaWentToSleep);
        pthread_mutex_unlock(&mutexSantaWentToSleep);
   

        printf("Mikolaj: zasypiam.\n");

    }

    pthread_exit(NULL);
}

void* elf(void* args){

    pthread_t id = pthread_self();
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    srand((unsigned int) id);
    while (1)
    {
        sleep(rand() % 4 + 2);

        pthread_mutex_lock(&mutexElfsWaiting);
        pthread_mutex_lock(&mutexLessThan3Waiting);

        if(anyWaitingElfs || !lessThan3Waiting || elfsWaiting >= 3 ){

            pthread_mutex_unlock(&mutexElfsWaiting);

            ++anyWaitingElfs;

            printf("Elf: czeka na powrot elfow, %lu\n", id);
            while(!lessThan3Waiting) pthread_cond_wait(&condLessThan3ElfsWaiting, &mutexLessThan3Waiting);

            // printf("        E: dostalem signal\n");

            --anyWaitingElfs;
            pthread_mutex_unlock(&mutexLessThan3Waiting);
        } else{
            pthread_mutex_unlock(&mutexLessThan3Waiting);
            pthread_mutex_unlock(&mutexElfsWaiting);
        }

        pthread_mutex_lock(&mutexElfsWaiting);

        if(elfsWaiting < 3){
            elfsInQueue[elfsWaiting] = id;
            ++elfsWaiting;
            printf("Elf: czeka %i elfow na Mikolaja, %lu\n", elfsWaiting, id);
            if(elfsWaiting == 3){
                
                // printf("3E: start\n");

                pthread_mutex_lock(&mutexLessThan3Waiting);
                // printf("3E: less than 3 bool set 0\n");
                lessThan3Waiting = 0;
                pthread_mutex_unlock(&mutexLessThan3Waiting);


                pthread_mutex_unlock(&mutexElfsWaiting);

                pthread_mutex_lock(&mutexElfsReady);
                // printf("3E: set elfsReady1\n");
                elfsReady = 1;
                pthread_mutex_unlock(&mutexElfsReady);
                // pthread_mutex_lock(&mutexSantaWentToSleep);
                // while(! santaWentToSleep) pthread_cond_wait(&condSantaWentToSleep, &mutexSantaWentToSleep);
                // pthread_mutex_unlock(&mutexSantaWentToSleep);

                pthread_mutex_lock(&mutexWakeSanta);
                if(!wakeSanta){
                    printf("Elf: Wybudzam Mikolaja, %lu\n", id);
                    wakeSanta = 1;
                    pthread_cond_broadcast(&condWakeSanta);
                    pthread_mutex_unlock(&mutexWakeSanta);
                } else{
                    pthread_mutex_unlock(&mutexWakeSanta);
                }
                // } else{
                //     pthread_mutex_unlock(&mutexWakeSanta);
                //     pthread_mutex_lock(&mutexSantaWentToSleep);
                //     while(! santaWentToSleep) pthread_cond_wait(&condSantaWentToSleep, &mutexSantaWentToSleep);
                //     pthread_mutex_unlock(&mutexSantaWentToSleep);

                //     pthread_mutex_lock(&mutexWakeSanta);
                //     printf("Renifer: wybudzam Mikolaja, %lu\n", id);
                //     wakeSanta = 1;
                //     pthread_cond_broadcast(&condWakeSanta);
                //     pthread_mutex_unlock(&mutexWakeSanta);
                // }

            } else{
                pthread_mutex_unlock(&mutexElfsWaiting);
            }

            // printf("E: Czekanie na Mikolaja\n");

            pthread_mutex_lock(&mutexSantaMeetsElfs);
            while(!santaMeetsElfs) pthread_cond_wait(&condSantaMeetsElfs, &mutexSantaMeetsElfs);
            pthread_mutex_unlock(&mutexSantaMeetsElfs);

            printf("Elf: Mikolaj rozwiazuje problem, %lu\n", id);
            elfsReady = 0;
            sleep(rand() %2 + 1);

            pthread_mutex_lock(&mutexElfsWaiting);
            // printf("E: po locku\n");
            // printf("E: elfsWaiting: %i\n", elfsWaiting);
            --elfsWaiting;
            if(elfsWaiting < 1){
                pthread_mutex_lock(&mutexLessThan3Waiting);
                lessThan3Waiting = 1;
                pthread_cond_signal(&condLessThan3ElfsWaiting);
                pthread_cond_signal(&condLessThan3ElfsWaiting);
                pthread_cond_signal(&condLessThan3ElfsWaiting);
                pthread_mutex_unlock(&mutexLessThan3Waiting);
            }
            pthread_mutex_unlock(&mutexElfsWaiting);

        } 

    }
    
}

void* reindeer(void* args){

    // int id = *((int*)args);
    pthread_t id = pthread_self();
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

    srand((unsigned int) id);

    while(1){

        sleep((rand() % 6 ) + 5);

        pthread_mutex_lock(&mutexReindeersWaiting);
        ++reindeersWaiting;
        if(reindeersWaiting < 9){
            printf("Renifer: czeka %i reniferow na Mikolaja, %lu\n", reindeersWaiting, id);
            pthread_mutex_unlock(&mutexReindeersWaiting);
        } else if(reindeersWaiting == 9){
            pthread_mutex_unlock(&mutexReindeersWaiting);

            printf("9R start\n");

            pthread_mutex_lock(&mutexReindeersReady);
            printf("9R bool set\n");
            reindeersReady = 1;
            pthread_mutex_unlock(&mutexReindeersReady);

            pthread_mutex_lock(&mutexWakeSanta);
            printf("9R Stan spania mikolaja: %i santaWentToSleep: %i\n", wakeSanta, santaWentToSleep);
            if(!wakeSanta){
                printf("Renifer: wybudzam Mikolaja, %lu\n", id);
                wakeSanta = 1;
                pthread_cond_broadcast(&condWakeSanta);
                pthread_mutex_unlock(&mutexWakeSanta);
            } else{
                pthread_mutex_unlock(&mutexWakeSanta);
            }
            // } else{

            //     pthread_mutex_lock(&mutexSantaWentToSleep);
            //     while(! santaWentToSleep) pthread_cond_wait(&condSantaWentToSleep, &mutexSantaWentToSleep);
            //     pthread_mutex_unlock(&mutexSantaWentToSleep);

            //     pthread_mutex_lock(&mutexWakeSanta);

            //     printf("Renifer: wybudzam Mikolaja, %lu\n", id);
            //     wakeSanta = 1;
            //     pthread_cond_broadcast(&condWakeSanta);

            //     pthread_mutex_unlock(&mutexWakeSanta);

            // }
            
        }

        pthread_mutex_lock(&mutexSantaDeliversPresents);

        while(!santaDeliversPresents) pthread_cond_wait(&condSantaDeliversPresents, &mutexSantaDeliversPresents);
        pthread_mutex_unlock(&mutexSantaDeliversPresents);
        reindeersReady = 0;
        sleep(rand() % 3 + 2);

        pthread_mutex_lock(&mutexReindeersWaiting);
        --reindeersWaiting;
        pthread_mutex_unlock(&mutexReindeersWaiting);

        printf("R: lece na wakacje\n");

        
        
    }



}


int main(int argc, char* argv[]){

    srand(time(0));

    threadIds = calloc(1 + 9 + 10, sizeof(pthread_t));

    elfsWaiting = reindeersWaiting = wakeSanta = santaMeetsElfs = santaWentToSleep = anyWaitingElfs = 0;
    lessThan3Waiting = 1;
    elfsReady = reindeersReady = 0; 

    // pthread_mutexattr_t mutexAttrElfsWaiting;
    // pthread_mutexattr_settype(&mutexAttrElfsWaiting, PTHREAD_MUTEX_RECURSIVE);

    // pthread_mutex_init(&mutexElfsWaiting, &mutexAttrElfsWaiting);


    int i = 0;
    int threadCreateRes, threadJoinRes;
    threadCreateRes = pthread_create(&threadIds[i++], NULL, &santa, NULL);
    if(threadCreateRes<0) error("thread create err");
    for(; i < 10;){
        threadCreateRes = pthread_create(&threadIds[i++], NULL, &reindeer, NULL);
        if(threadCreateRes<0) error("thread create err");
    }
    for(; i < 20;){
        threadCreateRes = pthread_create(&threadIds[i++], NULL, &elf, NULL);
        if(threadCreateRes<0) error("thread create err");
    }

    void *santaReturn;

    for(int i=0; i<20; i++){
        if(i == 0){
            threadJoinRes = pthread_join(threadIds[i], &santaReturn);
            if(threadJoinRes < 0) error("thread join errr");
        } else{
           threadJoinRes = pthread_join(threadIds[i], NULL);
            if(threadJoinRes < 0) error("thread join errr"); 
        }

        if( *((int*)santaReturn)  == 1 ){
            return 0;
        }
        
    }

    // threadJoinRes = pthread_join(threadIds[0], NULL);
    // if(threadJoinRes < 0) error("thread join errr");

    return 0;
}