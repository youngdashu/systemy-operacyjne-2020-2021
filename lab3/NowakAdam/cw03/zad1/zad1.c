#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>




int main(int argc, char* argv[]){

    if(argc != 2){
        printf("zla liczba argumentow\n");
        exit(EXIT_FAILURE);

    }   


    int n = atoi(argv[1]);


    printf("Proces macierzysty ma pid: %i\n", getpid());

    for(int i = 0; i < n ; i ++){

        if(fork() == 0){

            printf("i: %i proces potomny o pid: %i jest dzieckiem procesu o pid: %i\n", i,getpid(), getppid());
            break;

        } else{
            sleep(1);
        }


    }

    



    return 0;
}