#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>

int main(int argc, char* argv[]){

    if(argc != 2){
        printf("zla liczba argumentow\n");
        exit(EXIT_FAILURE);
    }

    char* arg = argv[1];

    if(strcmp(arg, "ignore") == 0){

        raise(SIGUSR1);
        printf("exec process ignored SIGUSR1\n");


    } else if(strcmp(arg, "mask") == 0){

        raise(SIGUSR1);
        printf("exec process has masked SIGUSR1\n");


    } else if(strcmp(arg, "pending") == 0){

        sigset_t childPendingMask;

        if(sigemptyset(&childPendingMask) == -1) 
            exit(EXIT_FAILURE);

        if(sigpending(&childPendingMask) < 0) {
            printf("sigpending error");
            exit(EXIT_FAILURE);
        }

        if(sigismember(&childPendingMask, SIGUSR1)) 
            printf("SIGUSR1 is pending in child process\n");


    } else{
        printf("zly argument\n");
        exit(EXIT_FAILURE);
    }

    return 0;


}