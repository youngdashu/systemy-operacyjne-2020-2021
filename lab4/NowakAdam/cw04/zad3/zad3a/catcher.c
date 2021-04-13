#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>
#include<signal.h>

// int howManySignalsCaught = 0;
// int sigusr2Caught = 0;
// int senderPID = -1;

volatile sig_atomic_t howManySignalsCaught = 0;
volatile sig_atomic_t sigusr2Caught = 0;
volatile sig_atomic_t senderPID = -1;

void case_kill_handle(int signo, siginfo_t *info, void* context){
    if(signo==SIGUSR1){
        howManySignalsCaught++;
    } else if(signo==SIGUSR2){
        sigusr2Caught = 1;
        senderPID = info->si_pid;
    } else{
        printf("illegal sygnal caught\n");
    }
}


void case_sigqueue_handle(int signo, siginfo_t *info, void* context){

    if(signo==SIGUSR1){

        howManySignalsCaught++;
        // TO DO
        // info->si_value.sival_int

    } else if(signo==SIGUSR2){

        sigusr2Caught = 1;
        senderPID = info->si_pid;

    } else{
        printf("illegal sygnal caught\n");
    }

}

void case_kill(char* catcherPIDstr ,char* nStr ,char* sendMode){

    // przygotowanie sygnalow do zamaskowania dla sigsuspend
    sigset_t signalsToMask;
    if(sigemptyset(&signalsToMask) == -1) exit(EXIT_FAILURE);
    if(sigfillset(&signalsToMask) == -1) exit(EXIT_FAILURE);
    if(sigdelset(&signalsToMask, SIGUSR1)==-1) exit(EXIT_FAILURE);
    if(sigdelset(&signalsToMask, SIGUSR2)==-1) exit(EXIT_FAILURE);

    // przygotowanie handlera
    struct sigaction infoActionStruct;
    infoActionStruct.sa_flags = 0;
    infoActionStruct.sa_flags |= SA_SIGINFO;
    infoActionStruct.sa_sigaction = case_kill_handle;

    printf("%i\n", getpid());

    sigaction(SIGUSR1, &infoActionStruct, NULL);
    sigaction(SIGUSR2, &infoActionStruct, NULL);

    if(vfork()==0){
        execl("./sender", "sender", catcherPIDstr , nStr, sendMode, NULL);
        exit(EXIT_SUCCESS);
    }

    // lapanie sygnalow od sendera az do zlapania sigusr2
    while(sigusr2Caught==0)
        sigsuspend(&signalsToMask);

    if(senderPID == -1){
        printf("Nie odczytano PID sendera!\n");
        exit(EXIT_FAILURE);
    }

    // odeslij tyle sygnalow ile zlapales
    for(int i = 0; i < howManySignalsCaught; i++){
        kill(senderPID, SIGUSR1);
    }
    kill(senderPID, SIGUSR2);
    printf("Catcher odebral %i sygnalow\n", howManySignalsCaught);

    wait(NULL);

    return;


}

void case_siqqueue(char* catcherPIDstr ,char* nStr ,char* sendMode){

    // przygotowanie sygnalow do zamaskowania
    sigset_t signalsToMask;
    if(sigemptyset(&signalsToMask) == -1) exit(EXIT_FAILURE);
    if(sigfillset(&signalsToMask) == -1) exit(EXIT_FAILURE);
    if(sigdelset(&signalsToMask, SIGUSR1)==-1) exit(EXIT_FAILURE);
    if(sigdelset(&signalsToMask, SIGUSR2)==-1) exit(EXIT_FAILURE);

    // przygotowanie handlera
    struct sigaction infoActionStruct;
    infoActionStruct.sa_flags = 0;
    infoActionStruct.sa_flags |= SA_SIGINFO;
    infoActionStruct.sa_sigaction = &case_sigqueue_handle;

    printf("%i\n", getpid());

    sigaction(SIGUSR1, &infoActionStruct, NULL);
    sigaction(SIGUSR2, &infoActionStruct, NULL);

    if(vfork()==0){
        execl("./sender", "sender", catcherPIDstr , nStr, sendMode, NULL);
        exit(EXIT_SUCCESS);
    }
    // lapanie sygnalow od sendera az do zlapania sigusr2
    while(sigusr2Caught==0)
        sigsuspend(&signalsToMask);

    if(senderPID == -1){
        printf("Nie odczytano PID sendera!\n");
        exit(EXIT_FAILURE);
    }

    // odeslij tyle sygnalow ile zlapales
    int lastSignalSentID = 1;
    for(int i = 0; i < howManySignalsCaught; i++){
        // kill(senderPID, SIGUSR1);
        union sigval signalID;
        signalID.sival_int = lastSignalSentID++;
        sigqueue(senderPID, SIGUSR1, signalID);
    }
    // kill(senderPID, SIGUSR2);

    union sigval signalID;
    signalID.sival_int = lastSignalSentID;
    sigqueue(senderPID, SIGUSR2, signalID);

    printf("Catcher odebral %i sygnalow\n", howManySignalsCaught);

    wait(NULL);

    return;

}

void case_sigrt_handle(int signo, siginfo_t *info, void* context){
    if(signo==SIGRTMIN){
        howManySignalsCaught++;
    } else if(signo==SIGRTMIN+1){
        sigusr2Caught = 1;
        senderPID = info->si_pid;
    } else{
        printf("illegal sygnal caught\n");
    }
    return;
}



void case_sigrt(char* catcherPIDstr ,char* nStr ,char* sendMode){

    // przygotowanie sygnalow do zamaskowania
    sigset_t signalsToMask;
    if(sigemptyset(&signalsToMask) == -1) exit(EXIT_FAILURE);
    if(sigfillset(&signalsToMask) == -1) exit(EXIT_FAILURE);
    if(sigdelset(&signalsToMask, SIGRTMIN)==-1) exit(EXIT_FAILURE);
    if(sigdelset(&signalsToMask, SIGRTMIN+1)==-1) exit(EXIT_FAILURE);

    // przygotowanie handlera
    struct sigaction infoActionStructSigrtCatcher;
    infoActionStructSigrtCatcher.sa_flags = 0;
    infoActionStructSigrtCatcher.sa_flags |= SA_SIGINFO;
    infoActionStructSigrtCatcher.sa_sigaction = &case_sigrt_handle;

    printf("%i\n", getpid());

    sigaction(SIGRTMIN, &infoActionStructSigrtCatcher, NULL);
    sigaction(SIGRTMIN+1, &infoActionStructSigrtCatcher, NULL);

    if(vfork()==0){
        execl("./sender", "sender", catcherPIDstr , nStr, sendMode, NULL);
        exit(EXIT_SUCCESS);
    }

    // lapanie sygnalow od sendera az do zlapania sigusr2
    while(sigusr2Caught==0)
        sigsuspend(&signalsToMask);

    if(senderPID == -1){
        printf("Nie odczytano PID sendera!\n");
        exit(EXIT_FAILURE);
    }

    // odeslij tyle sygnalow ile zlapales
    for(int i = 0; i < howManySignalsCaught; i++){
        kill(senderPID, SIGRTMIN);
    }
    kill(senderPID, SIGRTMIN+1);
    printf("Catcher odebral %i sygnalow\n", howManySignalsCaught);
    
    wait(NULL);

    return;


}





int main(int argc, char* argv[]){


    if(argc!=3){
        printf("Zla liczba argumentow catcher\n");
        exit(EXIT_FAILURE);
    }

    // int n = atoi(argv[1]);
    char* nStr = strdup(argv[1]);

    // printf("catcher n: %s\n", nStr);

    char* sendMode = strdup(argv[2]);

    int catcherPID = getpid();
    char catcherPIDstr[12];
    sprintf(catcherPIDstr, "%d", catcherPID);

    if(strcmp(sendMode, "kill")==0){

        case_kill(catcherPIDstr ,nStr, sendMode);
        
        // execl("./sender", "sender", catcherPIDstr ,nStr, sendMode, NULL);

    } else if(strcmp(sendMode, "sigqueue")==0){

        case_siqqueue(catcherPIDstr, nStr, sendMode);

    } else if(strcmp(sendMode, "sigrt")==0){

        case_sigrt(catcherPIDstr, nStr, sendMode);

    } else{
        printf("Zly tryb wysylania\n");
    }


    free(nStr);
    free(sendMode);
    return 0;

}

