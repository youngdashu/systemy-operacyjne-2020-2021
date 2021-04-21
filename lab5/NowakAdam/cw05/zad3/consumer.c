#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<ctype.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/file.h>

#define MAX_LINE_LEN 500


void error(char* msg){
    perror(msg);
    exit(EXIT_FAILURE);
}

void replaceFileWithArrContent(char*, char**, FILE* );

char** prepareConsumerFileArr(int);

void readDestFileAndFillArr(char* , char**, FILE* );

// void initializeConsumerFile(char*);

int main(int argc, char* argv[]){

    
    char* pipePath = argv[1];
    char* writeFilePath = argv[2];
    int numOfCharsToRead = atoi(argv[3]);

    char** consumerFileArr = prepareConsumerFileArr(10);

    // printf("consumer pipePath %s\n", pipePath);
    // printf("writeFile %s\n", writeFilePath);

    FILE* readPipe = fopen(pipePath, "r");

    if(readPipe == NULL){
        error("err open pipe consumer");
    }
    
    char* line = calloc(numOfCharsToRead+10, sizeof(char));

    char* readChars = NULL;
    // int writtenChars = 0;


    while(1){

        sleep((random()%2)+1);

        readChars = fgets(line, (numOfCharsToRead+9), readPipe);
        if(readChars==NULL){
            break;
        }

        FILE* destFile = fopen(writeFilePath, "a+");
        flock(fileno(destFile), LOCK_EX);


        readDestFileAndFillArr(writeFilePath, consumerFileArr, destFile);

        // zdobadz numer producenta
        int producerNumber =atoi(&line[0]);

        // printf("producer number: %i\n", producerNumber);


        // printf("podmieniany znak: |%c|", line[strlen(line)-1]);

        // pozbadz sie konca linii z line
        line[strlen(line)-1] = '\0';

        // pozbadz sie 2 pierwszych znakow z linii (nr producenta i spacja)

        char* trimmedLine = strdup(line+2);

        // printf("skrocona linia: %s|\n",trimmedLine );

        // append trimmedLine do lini odpowiadajacej producentowi

        if(consumerFileArr[producerNumber][strlen(consumerFileArr[producerNumber]) - 1] == '\n'){
            // printf("podmianka\n");
            consumerFileArr[producerNumber][strlen(consumerFileArr[producerNumber]) - 1] = '\0';
        }

        strcat(consumerFileArr[producerNumber], trimmedLine);
        strcat(consumerFileArr[producerNumber], "\n");

        // printf("po scatowaniu: %s|", );

        // zastap plik zawartoscia tablicy

        // printf("$$$$$$$$$$$\n");
        // printf("%s|", consumerFileArr[0]);
        // printf("%s|", consumerFileArr[1]);
        // printf("$$$$$$$$$$\n");

        replaceFileWithArrContent(writeFilePath, consumerFileArr, destFile);

        fclose(destFile);

        memset(line, '\0', numOfCharsToRead*sizeof(char));
        free(trimmedLine);

        // printf("$$$$$$$$$$$\n");
        // printf("%s\n", consumerFileArr[0]);
        // printf("%s\n", consumerFileArr[1]);
        // printf("$$$$$$$$$$\n");

        
    }
    fclose(readPipe);

    free(line);

}

// void initializeConsumerFile(char* destFilePath){ 

//     // inicjalizujemy plik destination 10 znakami konca linii
//     // aby przygotowac na dzialanie funkcji

//     char* toWrite = "\n\n\n\n\n\n\n\n\n\n";

//     FILE* destFile = fopen(destFilePath, "w");

//     fwrite(toWrite, sizeof(char), 10, destFile);

//     fclose(destFile);

//     return;
    
// }


void replaceFileWithArrContent(char* pathToDestFile, char** consumerFileArr, FILE* destFile){

    // czyscimy plik
    //fclose(fopen(pathToDestFile, "w"));
    ftruncate(fileno(destFile), 0);

    fseek(destFile, 0, SEEK_SET);

    // FILE* destFile = fopen(pathToDestFile, "w");

    // wypelniamy plik
    for(int i = 0; i < 10; i++){
        fputs(consumerFileArr[i], destFile);
        memset(consumerFileArr[i], '\0', MAX_LINE_LEN*sizeof(char));
    }
    //funlockfile(destFile);
    // flock(fileno(destFile), LOCK_UN);
    // fclose(destFile);
    

}

char** prepareConsumerFileArr(int numOfProducers){

    char** consumerFileArr = calloc(numOfProducers, sizeof(char*));

    for(int i = 0 ; i < numOfProducers; i++){
        consumerFileArr[i] = calloc(MAX_LINE_LEN, sizeof(char));
    }

    return consumerFileArr;


}

void readDestFileAndFillArr(char* pathToDestFile, char** consumerFileArr, FILE* fToRead){

    //FILE* fToRead = fopen(pathToDestFile, "r");
    //flockfile(fToRead);
    //flock(fileno(fToRead), LOCK_EX);

    fseek(fToRead, 0, SEEK_SET);

    char* line = calloc(MAX_LINE_LEN, sizeof(char));

    char* resOfFgets;

    int currLineNumber = -1;

    // printf("--------------------------------------\n");

    while(1){

        resOfFgets = fgets(line, MAX_LINE_LEN, fToRead);

        if(resOfFgets == NULL){
            break;
        }

        // printf("|%s\n", line);

        currLineNumber++;

        strcat(consumerFileArr[currLineNumber], line);

        memset(line, '\0', MAX_LINE_LEN*sizeof(char));
    
    }

    // printf("---------------------------\n");

    free(line);
    // fclose(fToRead);

}