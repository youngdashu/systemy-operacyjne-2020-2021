#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>


void sighandler(int signo, siginfo_t* info, void* context){

    printf("Wartosc od rodzica %i\n", info->si_value.sival_int);

}



int main(int argc, char* argv[]) {

    if(argc != 3){
        printf("Not a suitable number of program parameters\n");
        return 1;
    }

    struct sigaction act;
    act.sa_flags = SA_SIGINFO;
    act.sa_sigaction = &sighandler;

    //..........
    printf("%s %s\n", argv[1], argv[2]);


    int child = fork();
    printf("child: %i", child);
    if(child == 0) {
        
        sigset_t set;
        sigfillset(&set);
        sigdelset(&set, SIGUSR1);
        sigprocmask(SIG_SETMASK, &set, NULL);



        sigaction(SIGUSR1, &act,NULL);
        //zablokuj wszystkie sygnaly za wyjatkiem SIGUSR1
        //zdefiniuj obsluge SIGUSR1 w taki sposob zeby proces potomny wydrukowal
        //na konsole przekazana przez rodzica wraz z sygnalem SIGUSR1 wartosc
    }
    else {
        //wyslij do procesu potomnego sygnal przekazany jako argv[2]
        //wraz z wartoscia przekazana jako argv[1]

        union sigval valToSend;
        valToSend.sival_int = atoi(argv[1]);

        sigqueue(child, atoi(argv[2]), valToSend);
        wait(NULL);
    }

    return 0;
}
