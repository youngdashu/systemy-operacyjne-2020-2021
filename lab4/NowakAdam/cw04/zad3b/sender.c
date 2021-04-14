#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>

#include<signal.h>

// int signalsReceivedFromCatcher = 0;
// int sigusr2caught = 0;

volatile sig_atomic_t signalsReceivedFromCatcher = 0;
volatile sig_atomic_t sigusr2caught = 0;


void case_kill_handle_sigusr(int signo){

    // printf("sender %d\n", signo);

    if(signo == SIGUSR2){

        sigusr2caught = 1;

    } else if(signo==SIGUSR1){
        
        signalsReceivedFromCatcher++;

    } else{
        printf("illegal signal caughtn\n");
    }

}

void case_sigqueue_handle_sigusr(int signo, siginfo_t *info, void* context){


    if(signo==SIGUSR1){

        // printf("sender odbiera od catchera numerek: %i\n", info->si_value.sival_int);

        signalsReceivedFromCatcher=info->si_value.sival_int;

        // printf("sender odbiera od catchera numerek: %i\n", signalsReceivedFromCatcher);

    } else if(signo==SIGUSR2){

        sigusr2caught = 1;

    } else{
        printf("illegal signal caughtn\n");
    }


    return;

}


void case_kill(int n, int catcherPID){

    // maska do ignorowania sygnalow od catchera (oprocz sigusr 1 i 2)
    sigset_t signalsToMask;
    if(sigemptyset(&signalsToMask) == -1) exit(EXIT_FAILURE);
    if(sigfillset(&signalsToMask) == -1) exit(EXIT_FAILURE);
    if(sigdelset(&signalsToMask, SIGUSR1)==-1) exit(EXIT_FAILURE);
    if(sigdelset(&signalsToMask, SIGUSR2)==-1) exit(EXIT_FAILURE);

    

    struct sigaction infoActionStructKillSender;
    infoActionStructKillSender.sa_handler = case_kill_handle_sigusr;

    // przygotuj sie na odebranie sigusr2
    sigaction(SIGUSR2, &infoActionStructKillSender, NULL);
    sigaction(SIGUSR1, &infoActionStructKillSender, NULL);
    
    // maska blokaujaca
    sigset_t setWithSigusr12;//, setWithSigusr2;
    sigemptyset(&setWithSigusr12);
    sigaddset(&setWithSigusr12, SIGUSR1);
    sigaddset(&setWithSigusr12, SIGUSR2);
    sigprocmask(SIG_SETMASK, &setWithSigusr12, NULL);

    // wyslij n sygnalow sigusr1 do catchera i zakoncz sigusr2
    for(int i = 0; i < n; i++){
        kill(catcherPID, SIGUSR1);

        // poczekaj na potwierdzenie odbioru od catchera
        sigsuspend(&signalsToMask);
        // sigwaitinfo(&setWithSigusr1, &info);


    }
    kill(catcherPID, SIGUSR2);
    sigsuspend(&signalsToMask);



    printf("Sender odebral %i sygnalow\n", signalsReceivedFromCatcher);
    printf("Powinien odebrac %i sygnalow\n", n);
    
    return;


}

void case_sigque(int n, int catcherPID){

    // maska do ignorowania sygnalow od catchera (oprocz sigusr 1 i 2)
    sigset_t signalsToMask;
    if(sigemptyset(&signalsToMask) == -1) exit(EXIT_FAILURE);
    if(sigfillset(&signalsToMask) == -1) exit(EXIT_FAILURE);
    if(sigdelset(&signalsToMask, SIGUSR1)==-1) exit(EXIT_FAILURE);
    if(sigdelset(&signalsToMask, SIGUSR2)==-1) exit(EXIT_FAILURE);

    // przygotuj sie na odebranie sigusr1 i 2
    struct sigaction infoActionStructQueueSender;
    infoActionStructQueueSender.sa_flags = 0;
    infoActionStructQueueSender.sa_flags |= SA_SIGINFO;
    infoActionStructQueueSender.sa_sigaction = &case_sigqueue_handle_sigusr;

    sigaction(SIGUSR1, &infoActionStructQueueSender, NULL);
    sigaction(SIGUSR2, &infoActionStructQueueSender, NULL);

    // maska blokujaca
    sigset_t setWithSigusr12;
    sigemptyset(&setWithSigusr12);
    sigaddset(&setWithSigusr12, SIGUSR1);
    sigaddset(&setWithSigusr12, SIGUSR2);
    sigprocmask(SIG_BLOCK, &setWithSigusr12, NULL);

    
    // wyslij n sygnalow sigusr1 do catchera, zaczekaj na potwierdzenie i zakoncz sigusr2
    int lastSignalSentID = 1;
    for(int i = 0; i < n; i++){

        union sigval signalID;
        signalID.sival_int = lastSignalSentID++;
        sigqueue(catcherPID, SIGUSR1, signalID);

        sigsuspend(&signalsToMask);

    }
    // zakoncz wysylajac sigusr2
    union sigval signalID;
    signalID.sival_int = lastSignalSentID;
    sigqueue(catcherPID, SIGUSR2, signalID);
    // odbierz sigusr2
    sigsuspend(&signalsToMask);

    printf("Sender odebral %i sygnalow\n", signalsReceivedFromCatcher);
    printf("Powinien odebrac %i sygnalow\n", n);
    
    return;


}

void case_sigrt_handle(int signo){

    if(signo == SIGRTMIN+1){

        sigusr2caught = 1;

    } else if(signo==SIGRTMIN){
        
        signalsReceivedFromCatcher++;

    } else{
        printf("illegal signal caughtn\n");
    }
    return;

}


void case_sigrt(int n, int catcherPID){

    // maska do ignorowania sygnalow od catchera (oprocz sigrtmin i +1)
    sigset_t signalsToMask;
    if(sigemptyset(&signalsToMask) == -1) exit(EXIT_FAILURE);
    if(sigfillset(&signalsToMask) == -1) exit(EXIT_FAILURE);
    if(sigdelset(&signalsToMask, SIGRTMIN)==-1) exit(EXIT_FAILURE);
    if(sigdelset(&signalsToMask, SIGRTMIN+1)==-1) exit(EXIT_FAILURE);

    // przygotowanie struktury dla sigaction
    struct sigaction infoActionStructSigrtSender;
    infoActionStructSigrtSender.sa_handler = case_sigrt_handle;

    // przygotuj sie na odebranie sigrtmin i sigrtmin+1
    sigaction(SIGRTMIN, &infoActionStructSigrtSender, NULL);
    sigaction(SIGRTMIN+1, &infoActionStructSigrtSender, NULL);

    // maska blokaujaca
    sigset_t setWithSigrt;//, setWithSigusr2;
    sigemptyset(&setWithSigrt);
    sigaddset(&setWithSigrt, SIGRTMIN);
    sigaddset(&setWithSigrt, SIGRTMIN+1);
    sigprocmask(SIG_BLOCK, &setWithSigrt, NULL);
    
    // wyslij n sygnalow sigrtmin do catchera, zaczekaj na potwierdzenie i zakoncz sigrtmin+1
    for(int i = 0; i < n; i++){

        kill(catcherPID, SIGRTMIN);

        sigsuspend(&signalsToMask);
    }
    // zakoncz transmisje wysylajac sigrtmin+1
    kill(catcherPID, SIGRTMIN+1);
    // odbierz potwierdzenie sigrtmin+1
    sigsuspend(&signalsToMask);


    printf("Sender odebral %i sygnalow\n", signalsReceivedFromCatcher);
    printf("Powinien odebrac %i sygnalow\n", n);
    
    return;


}

int main(int argc, char* argv[]){


    if(argc!=4){
        printf("Zla liczba argumentow sender\n");
        exit(EXIT_FAILURE);
    }

    int catcherPID = atoi(argv[1]);

    int n = atoi(argv[2]);

    // printf("Sender n: %i pid: %i\n", n, catcherPID);

    char* sendMode = strdup(argv[3]);

    if(strcmp(sendMode, "kill")==0){
        
        case_kill(n, catcherPID);

    } else if(strcmp(sendMode, "sigqueue")==0){

        case_sigque(n, catcherPID);

    } else if(strcmp(sendMode, "sigrt")==0){

        case_sigrt(n, catcherPID);

    } else{
        printf("Zly tryb wysylania\n");
        exit(EXIT_FAILURE);
    }

    free(sendMode);
    return 0;
}