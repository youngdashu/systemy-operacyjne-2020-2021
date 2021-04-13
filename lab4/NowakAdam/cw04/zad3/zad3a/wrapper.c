#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>
#include<signal.h>


int main(int argc, char* argv[]){


    if(argc!=3){
        printf("Zla liczba argumentow wrapper\n");
        exit(EXIT_FAILURE);
    }



    // int n = atoi(argv[1]);

    char* sendMode = strdup(argv[2]);

    char* nStr = strdup(argv[1]);

    if(strcmp(sendMode, "kill")==0 || strcmp(sendMode, "sigqueue")==0 || strcmp(sendMode, "sigrt") ==0 ){
        
        if(vfork()==0){
            execl("./catcher", "catcher",  nStr, sendMode, NULL );
            exit(EXIT_SUCCESS);
        }
        

     } // else if(strcmp(sendMode, "sigqueue")==0){

    //     execl("./catcher", "catcher",  nStr, sendMode, NULL );

    // } else if(strcmp(sendMode, "sigrt")==0){

    // } 
    else{
        printf("Zly tryb wysylania\n");
        free(nStr);
        exit(EXIT_FAILURE);
    }

    free(nStr);

    wait(NULL);

    return 0;



}
