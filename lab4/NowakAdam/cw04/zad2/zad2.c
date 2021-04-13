#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>

#include<signal.h>

void handler(int signo, siginfo_t *info, void* context){

    printf("\nObsluguje sygnal: %i\n", signo);
    printf("ID procesu ktory wyslal sygnal: %i\n", info->si_pid);

}

int main(int argc, char* argv[]){

    struct sigaction infoActionStruct;

    infoActionStruct.sa_flags = 0;
    infoActionStruct.sa_flags |= SA_SIGINFO;

    sigset_t blockMask;
    if(sigemptyset(&blockMask) == -1) exit(EXIT_FAILURE);
    if(sigaddset(&blockMask, SIGUSR1) == -1) exit(EXIT_FAILURE);

    infoActionStruct.sa_mask = blockMask;
    infoActionStruct.sa_handler = &handler;



    sigaction(SIGUSR1, &infoActionStruct, NULL);

    raise(SIGUSR1);



    return 0;
}