#include<stdio.h>
#include<stdlib.h>
#include<mergeFilesLib.h>
#include<string.h>


int main(int argc, char **argv[]){

    int argNum = 1;

    MainArray *mainArray = NULL;

    int size = NULL;

    while( argNum < argc){

        if (strcmp(argv[argNum], "create_table"))
        {
            int size = ++argNum;
            
            mainArray = createArray(size);
            
        } else if (strcmp(argv[argNum], "merge_files"))
        {
            if (size == NULL){
                exit(EXIT_FAILURE);
            }

            ++argNum;

            int pairsRead = 0;
            while(pairsRead < size){

                
                char* file1Name = strtok(argv[argNum], ":");
                char* file2Name = strtok(argv[argNum], ":");

                FILE * file1 = fopen(file1Name, "r");
                FILE * file2 = fopen(file2Name, "r");

                TemporaryFile *tmp = mergeFiles(mainArray, file1, file2);
                createBlockFromFile(tmp, mainArray);

                ++argNum;
                ++pairsRead;

            }

            
        } else if (strcmp(argv[argNum], "remove_block"))
        {

            int blockIndexToRemove = ++argNum;

            removeBlockOfLines(mainArray, blockIndexToRemove);
            
        } else if (strcmp(argv[argNum], "remove_row"))
        {

            int blockIndex = ++argNum;
            int rowIndex = ++argNum;

            removeLineFromBlock(mainArray, blockIndex, rowIndex);
            
        } 
        

        ++argNum;
    }


    return 0;
}