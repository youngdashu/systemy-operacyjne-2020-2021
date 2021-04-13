#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<dirent.h>

// #include<sys/times.h>

#include<sys/wait.h>

#include<sys/stat.h>

#include<string.h>

#define MAX_LINE_LEN 512

int doesFileContainPattern(char* fileNameWithPath, char* pattern){

    FILE * file = fopen(fileNameWithPath, "r");

    char* file1Line = calloc(MAX_LINE_LEN, sizeof(char));

    while( 1 ){

        if(feof(file)){
            break;
        }

        char* res = fgets(file1Line, MAX_LINE_LEN, file);

        if(res == NULL){
            break;
        }

        if(strstr(file1Line, pattern) != NULL){
            free(file1Line);
            fclose(file);
            return 1;
        }

        memset(file1Line, 0, MAX_LINE_LEN*sizeof(char) );

    }

    free(file1Line);
    fclose(file);

    return 0;

}


void search(char* folder, char* pattern, int maxDepth, int currentDepth){

    if(currentDepth == maxDepth){
        return;
    }

    if(fork() == 0){

        DIR * currentDirectory = opendir(folder);

        while (1){
            struct dirent * currentFile = readdir(currentDirectory);

            if(currentFile == NULL){
                break;
            }

            char* fileName = currentFile->d_name;

            if(strcmp(fileName, ".") == 0 || strcmp(fileName, "..") == 0){
                continue;
            }

            char* pathToCurrentFile = calloc(strlen(folder) + 2 + strlen(fileName), sizeof(char));

            strcat(pathToCurrentFile, folder);
            strcat(pathToCurrentFile, "/");
            strcat(pathToCurrentFile, fileName);

            struct stat buf;
            lstat(pathToCurrentFile, &buf);

            if(S_ISDIR(buf.st_mode)){
                search(pathToCurrentFile, pattern, maxDepth, currentDepth+1);
            } else if(strstr(fileName, ".txt") != NULL && doesFileContainPattern(pathToCurrentFile, pattern)){
                
                printf("directory: %s file: %s pid: %i\n", folder, fileName, getpid());

            }

            free(pathToCurrentFile);


        }

        closedir(currentDirectory);

        exit(EXIT_SUCCESS);

    } else {
        int res, stat;
        while( (res=  wait(&stat) ) > 0);
    }



}

int main(int argc, char* argv[]){


    if(argc != 4){
        printf("zla liczba argumentow\n");
        exit(EXIT_FAILURE);
    }

    char* startFolder = argv[1];

    char* pattern = argv[2];

    int maxDepth = atoi(argv[3]);

    search(startFolder, pattern, maxDepth, 0);

    return 0;

}