#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<ctype.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>


void error(char* msg){
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]){

    char* pipePath = argv[1];
    //int number = atoi(&argv[2]);
    char* number = argv[2];
    char* readFilePath = argv[3];
    int numOfCharsToRead = atoi(argv[4]);

    // printf("num of chars to read: %i\n", numOfCharsToRead);

    // printf("file to read dir: %s\n", readFilePath);

    // printf("producer number: %s\n", number);

    int writePipe = open(pipePath, O_WRONLY);
    FILE* readFile = fopen(readFilePath, "r");
    if(writePipe==-1){
        error("err open write pipe producer");
    }
    if(readFile == NULL){
        error("err open file to read producer");
    }

    char* line = calloc(numOfCharsToRead, sizeof(char));

    int readChars = 0;

    // srand(time(NULL));
    long sleepTime;

    while(1){

        sleepTime = random();
        sleepTime %= 3;
        sleepTime += 1;
        sleepTime = 1;
        sleep(sleepTime);
        
        // printf("sleep time for %lds\n", sleepTime);
        
        readChars = fread(line, sizeof(char), numOfCharsToRead, readFile);

        if(readChars==0){
            // printf("break\n");
            break;
        }
        
        // fwrite(number, );
        // writtenChars = fwrite(line, sizeof(char), numOfCharsToRead, writePipe);

        char* toWrite = calloc(numOfCharsToRead + 10, sizeof(char));
        strcat(toWrite, number);
        strcat(toWrite, " ");
        strcat(toWrite, line);
        strcat(toWrite, "\n");

        // printf("producer line to write to pipe: %s\n", toWrite);

        // fputs(toWrite, writePipe);

        write(writePipe, toWrite, strlen(toWrite)*sizeof(char));


        memset(line, '\0', numOfCharsToRead*sizeof(char));
        
    }

    fclose(readFile);
    close(writePipe);

    free(line);

}