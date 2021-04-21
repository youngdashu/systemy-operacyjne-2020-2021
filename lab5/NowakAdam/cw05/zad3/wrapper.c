#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<ctype.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

#define MAX_NUM_OF_PRODUCERS 10

void error(char* msg){
    perror(msg);
    exit(EXIT_FAILURE);
}

char** createProducerFileNames(int);

void initializeConsumerFile(char* destFilePath);



int main(int argc, char* argv[]){

    unlink("./pipeFolder/namedPipe");


    int numOfProducers = atoi(argv[1]);
    int numOfConsumers = atoi(argv[2]);
    char* pipeFolder = "./pipeFolder/namedPipe"; 

    char* N = argv[3];

    char** producerFileNames = createProducerFileNames(MAX_NUM_OF_PRODUCERS);
    char* consumerFileName = "consumerFile.txt";

    initializeConsumerFile(consumerFileName);

    if( mkfifo("./pipeFolder/namedPipe", 0666) != 0){
        error("mkfifo err");
    }

    int i = 0;

    int tmpNumOfProducers = numOfProducers;
    int tmpNumOfConsumers = numOfConsumers;

    while(tmpNumOfConsumers){

        if(vfork()==0){

            // printf("run consumer\n");

            if (execl("./consumer", "consumer", pipeFolder, consumerFileName, N, NULL) == -1){
                error("exec consumer err");
            }
            exit(EXIT_SUCCESS);

        }

        tmpNumOfConsumers--;
        i++;

    }

    i = 0;

    while(tmpNumOfProducers){

        if(vfork()==0){
            char currProdNum[12];
            sprintf(currProdNum, "%d", i);

            if (execl("./producer", "producer", pipeFolder, &currProdNum, producerFileNames[i], N, NULL)==-1){
                error("exec producer err");
            }
            exit(EXIT_SUCCESS);
        }

        i++;
        tmpNumOfProducers--;

    }

    for(int i = 0; i < numOfConsumers + numOfProducers; i++){
        wait(NULL);
    }
    
    unlink(pipeFolder);

    for(int i = 0; i < 10; i++){
        free(producerFileNames[i]);
    }
    free(producerFileNames);

    return 0;
}


char** createProducerFileNames(int n){

    if(n > 10){
        error("zbyt duzo producentow");
    }

    char** res = calloc(n, sizeof(char*));

    char* template1 = "producer";
    char* template3 = ".txt";
    char* toAppend;

    for(int i = 0 ; i <n; i++){

        char template2[2];
        sprintf(template2, "%i", i);

        toAppend = calloc(strlen(template1)+strlen(template2)+strlen(template3)+1, sizeof(char));        
        strcat(toAppend, template1);
        strcat(toAppend, template2);
        strcat(toAppend, template3);

        res[i] = strdup(toAppend);

        // printf("   $$$file name %s\n", toAppend);

        free(toAppend);

    }

    return res;

}

void initializeConsumerFile(char* destFilePath){ 

    // inicjalizujemy plik destination 10 znakami konca linii
    // aby przygotowac na dzialanie funkcji

    char* toWrite = "\n\n\n\n\n\n\n\n\n\n";

    FILE* destFile = fopen(destFilePath, "w");

    fwrite(toWrite, sizeof(char), 10, destFile);

    fclose(destFile);

    return;

    
    
}