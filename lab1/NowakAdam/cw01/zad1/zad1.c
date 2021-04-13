#include<stdio.h>
#include<stdlib.h>
#include"mergeFilesLib.h"
#include<string.h>



int main(int argc, char** argv[]){

    int argNum = 1;

    MainArray *mainArray = NULL;

    FilesSequence *sequence = NULL;

    int size = -1;

    while( argNum < argc){

        if (strcmp((char*) argv[argNum], "create_table") == 0) {

            size = atoi( (char*) argv[++argNum] );
            
            mainArray = createArray(size);

            ++argNum;
            
        } else if (strcmp((char*) argv[argNum], "merge_files") == 0){

            if (size == -1){
                exit(EXIT_FAILURE);
            }

            ++argNum;

            int numberOfPairsToMerge = 0;

            numberOfPairsToMerge = atoi((char*) argv[argNum]);
            ++argNum;

            if(numberOfPairsToMerge < 0){
                exit(EXIT_FAILURE);
            }

            sequence = createFilesSequence(numberOfPairsToMerge, argv, &argNum);

            saveToTmp(sequence);

            createBlocksFromFile(mainArray, numberOfPairsToMerge, sequence);

            
        } else if (strcmp((char*) argv[argNum], "remove_block") == 0){

            int blockIndexToRemove = atoi( (char*) argv[ ++argNum] );

            removeBlockOfLines(mainArray, blockIndexToRemove);

            ++argNum;
            
        } else if (strcmp((char*) argv[argNum], "remove_row") == 0)
        {

            int blockIndex = atoi( (char*) argv[ ++argNum] );
            int rowIndex = atoi( (char*) argv[ ++argNum] );

            removeLineFromBlock(mainArray, blockIndex, rowIndex);

            ++argNum;
            
        } else if ( strcmp((char*) argv[argNum], "print_files") == 0 ){

            printMergedFiles(mainArray);

            ++argNum;

        }
        
    }

    freeMainArray(mainArray);

    freeFilesSequence(sequence);

    return 0;
}