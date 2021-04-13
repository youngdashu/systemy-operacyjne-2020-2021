#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>

#include<signal.h>

void err_sys(const char* err){
    perror(err);
    exit(EXIT_FAILURE);
}

void case_ignore(){

    signal(SIGUSR1, SIG_IGN);

    raise(SIGUSR1);

    // signal(SIGUSR1, SIG_IGN);

    printf("FORK\n");

    if(fork() == 0){

        raise(SIGUSR1);
        printf("Child process ignored SIGUSR1\n");
        exit(EXIT_SUCCESS);

    } else{

        int res, stat;
        while( (res=  wait(&stat) ) > 0);
    }

    printf("EXEC\n");

    execl("./child", "child", "ignore");

}

void handler(int signum){
    printf("handling SIGUSR1\n");
}

void case_handler(){

    signal(SIGUSR1, handler);

    raise(SIGUSR1);

    signal(SIGUSR1, handler);

    printf("FORK\n");

    if(fork() == 0){

        raise(SIGUSR1);
        exit(EXIT_SUCCESS);

    } else{

        int res, stat;
        while( (res=  wait(&stat) ) > 0);
    }

}

void case_mask(){

    sigset_t signalSet;

    if(sigemptyset(&signalSet) == -1) exit(EXIT_FAILURE);

    if(sigaddset(&signalSet, SIGUSR1) == -1) exit(EXIT_FAILURE);

    if(sigprocmask(SIG_SETMASK, &signalSet, NULL) < 0) exit(EXIT_FAILURE);

    raise(SIGUSR1);

    printf("succesfully masked SIGUSR1\n");

    printf("FORK\n");

    if(fork() == 0){
        raise(SIGUSR1);
        printf("child has masked SIGUSR1\n");
        exit(EXIT_SUCCESS);
    } else{
        int res, stat;
        while( (res=  wait(&stat) ) > 0);
    }

    printf("EXEC\n");

    execl("./child", "child", "mask");

    return;

}

void case_pending(){

    sigset_t pendingMask, blockMask;

    if(sigemptyset(&pendingMask) == -1) exit(EXIT_FAILURE);

    if(sigemptyset(&blockMask) == -1) exit(EXIT_FAILURE);

    if(sigaddset(&blockMask, SIGUSR1) == -1) exit(EXIT_FAILURE);

    if(sigprocmask(SIG_SETMASK, &blockMask, NULL) < 0) exit(EXIT_FAILURE);

    raise(SIGUSR1);

    if(sigpending(&pendingMask) < 0) err_sys("sigpending error");

    if(sigismember(&pendingMask, SIGUSR1)) printf("SIGUSR1 is pending\n");

    printf("FORK\n");

    if(fork() == 0){

        sigset_t childPendingMask;

        if(sigemptyset(&childPendingMask) == -1) exit(EXIT_FAILURE);

        if(sigpending(&childPendingMask) < 0) err_sys("sigpending error");

        if(sigismember(&childPendingMask, SIGUSR1)) printf("SIGUSR1 is pending in child process\n");

        exit(EXIT_SUCCESS);

    } else{
        int res, stat;
        while( (res=  wait(&stat) ) > 0);
    }

    printf("EXEC\n");

    execl("./child", "child", "pending", NULL);


}




int main(int argc, char* argv[]){

    if(argc != 2){
        printf("zla liczba argumentow\n");
        exit(EXIT_FAILURE);

    }   


    char* arg = strdup(argv[1]);

    if(strcmp(arg, "ignore") == 0){
        printf("ignore\n");
        case_ignore();

    } else if(strcmp(arg, "handler") == 0){
        printf("handler\n");
        case_handler();

    } else if(strcmp(arg, "mask") == 0){
        printf("mask\n");
        case_mask();

    } else if(strcmp(arg, "pending") == 0){
        printf("pending\n");
        case_pending();

    } else{
        printf("bledny argument!\n");
        free(arg);
        exit(EXIT_FAILURE);
    }

    free(arg);

    return 0;
}