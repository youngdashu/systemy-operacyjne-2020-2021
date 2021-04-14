#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>

#include<signal.h>

void handler(int signo, siginfo_t *info, void* context){

    printf("Obsluguje sygnal: %i\n", signo);
    printf("ID procesu ktory wyslal sygnal: %i\n", info->si_pid);

}

void case_siginfo(){
    printf("Siginfo\n");

    struct sigaction infoActionStruct;

    infoActionStruct.sa_flags = 0;
    infoActionStruct.sa_flags |= SA_SIGINFO;

    // sigset_t blockMask;
    // if(sigemptyset(&blockMask) == -1) exit(EXIT_FAILURE);
    // if(sigaddset(&blockMask, SIGUSR1) == -1) exit(EXIT_FAILURE);

    // infoActionStruct.sa_mask = blockMask;
    infoActionStruct.sa_sigaction = &handler;

    sigaction(SIGUSR1, &infoActionStruct, NULL);

    raise(SIGUSR1);
}

// volatile sig_atomic_t sumWithNodefer = 0;
// volatile sig_atomic_t  sumWithoutNodefer = 0;

int sumWithNodefer = 0;
int  sumWithoutNodefer = 0;

void nodefer_handler(int signo){

    for(int i = 0; i < 10; i++){
        sumWithNodefer++;
    }

    return;

}

void without_nodefer_handler(int signo){
    for(int i = 0; i < 10; i++){
        sumWithoutNodefer++;
    }

    return;
}

void case_nodefer(){

    printf("Nodefer\n");

    printf("Bez korzystania z sa_nodefer\n");

    struct sigaction infoActionStructWithoutNodefer;

    infoActionStructWithoutNodefer.sa_flags = 0;

    infoActionStructWithoutNodefer.sa_handler = &without_nodefer_handler;

    sigaction(SIGUSR1, &infoActionStructWithoutNodefer, NULL);

    for (int i = 0; i < 100; i++){
        raise(SIGUSR1);
    }

    printf("Suma wynosi %i\n", sumWithoutNodefer);


    printf("Korzystajac z nodefer\n");
    struct sigaction infoActionStructWithNodefer;

    infoActionStructWithNodefer.sa_flags = 0;
    infoActionStructWithNodefer.sa_flags |= SA_NODEFER;

    infoActionStructWithNodefer.sa_handler = &nodefer_handler;

    

    sigaction(SIGUSR1, &infoActionStructWithNodefer, NULL);

    for (int i = 0; i < 100; i++){
        raise(SIGUSR1);
    }

    printf("Suma wynosi %i\n", sumWithNodefer);


}

int main(int argc, char* argv[]){

    case_siginfo();

    case_nodefer();





    return 0;
}