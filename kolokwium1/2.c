#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void sighandler(int signo, siginfo_t* siginfo, void* context){
    printf("Child informations sig: %d, value: %d\n", signo ,siginfo->si_value.sival_int);
}


int main(int argc, char* argv[]) {

    if(argc != 3){
        printf("Not a suitable number of program parameters\n");
        return 1;
    }

    struct sigaction action;
    action.sa_sigaction = &sighandler;
    action.sa_flags = SA_SIGINFO;
    sigemptyset(&action.sa_mask);
    
    sigset_t mask_set;
    sigemptyset(&mask_set);
    sigfillset(&mask_set);
    sigdelset(&mask_set, SIGUSR1);

    //..........


    int child = fork();
    if(child == 0) {
        //zablokuj wszystkie sygnaly za wyjatkiem SIGUSR1
        //zdefiniuj obsluge SIGUSR1 w taki sposob zeby proces potomny wydrukowal
        //na konsole przekazana przez rodzica wraz z sygnalem SIGUSR1 wartosc
        sigprocmask(SIG_BLOCK,&mask_set,NULL);
        sigaction(SIGUSR1,&action,NULL);
        pause();
    }
    else {
        //wyslij do procesu potomnego sygnal przekazany jako argv[2]
        //wraz z wartoscia przekazana jako argv[1]
        sleep(2);
        int sig = atoi(argv[2]);
        union sigval sval;
        sval.sival_int = atoi(argv[1]);
        sigqueue(child, sig, sval);
    }

    return 0;
}
