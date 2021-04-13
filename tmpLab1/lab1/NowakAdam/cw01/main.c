#include<stdio.h>
#include<stdlib.h>
#include"mergeFilesLib.h"
#include<string.h>



int main(int argc, char** argv){

    int argNum = 1;

    MainArray *mainArray = NULL;

    FilesSequence *sequence = NULL;

    int size = -1;

    

    ////////////////////

    // for(int i = 1 ; i < argc ; i++ ){

    //     printf( "%i  %s\n", i, (char*) argv[i] );

    // }

    /////////////////////

    printf(" argnum %i         argc %i\n", argNum, argc );

    while( argNum < argc){

        // int len = strlen(argv[argNum]);

        // char * currentArg = calloc(len, sizeof(char));

        // strcpy(currentArg, argv[argNum]);

        printf("argument: %s \n", (char*) argv[argNum]);

        if (strcmp((char*) argv[argNum], "create_table") == 0) {

            printf("create\n");

            size = atoi( (char*) argv[++argNum] );

            printf("size %i\n", size);
            
            mainArray = createArray(size);

            ++argNum;
            
        } else if (strcmp((char*) argv[argNum], "merge_files") == 0){

            if (size == -1){
                exit(EXIT_FAILURE);
            }

            ++argNum;

            printf("size: %i", size);

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

            printf("print\n");

            printMergedFiles(mainArray);

            ++argNum;

        }
        

        // ++argNum;

        printf("end argnum %i \n", argNum);
    }

    freeMainArray(mainArray);
    freeFilesSequence(sequence);


    return 0;
}




// int main2(int argc, char** argv[]){

//     int argNum = 1;

//     MainArray *mainArray = NULL;

//     int size = -1;

//     ////////////////////

//     // for(int i = 1 ; i < argc ; i++ ){

//     //     printf( "%i  %s\n", i, (char*) argv[i] );

//     // }

//     /////////////////////

//     printf(" argnum %i         argc %i\n", argNum, argc );

//     while( argNum < argc){

//         // int len = strlen(argv[argNum]);

//         // char * currentArg = calloc(len, sizeof(char));

//         // strcpy(currentArg, argv[argNum]);

//         printf("argument: %s \n", (char*) argv[argNum]);

//         if (strcmp((char*) argv[argNum], "create_table") == 0) {

//             printf("create\n");

//             size = atoi( (char*) argv[++argNum] );

//             printf("size %i\n", size);
            
//             mainArray = createArray(size);

//             ++argNum;
            
//         } else if (strcmp((char*) argv[argNum], "merge_files") == 0){

//             if (size == -1){
//                 exit(EXIT_FAILURE);
//             }

//             ++argNum;

//             printf("size: %i", size);

//             int numberOfPairsToMerge = 0;

//             numberOfPairsToMerge = atoi((char*) argv[argNum]);
//             ++argNum;

//             if(numberOfPairsToMerge < 0){
//                 exit(EXIT_FAILURE);
//             }

//             int pairsRead = 0;
//             while(pairsRead < numberOfPairsToMerge && argNum < argc){

//                 printf("    czytanie nazw plikow\n");

//                 printf("argv[argNum]: %s", (char*) argv[argNum]);

//                 char * filesToMerge = (char*) calloc(strlen((char*) argv[argNum] ), sizeof(char) );

//                 strcpy(filesToMerge, (char*) argv[argNum] );

//                 printf("filesToMerge: %s \n", filesToMerge);
                
//                 char* file1Name = strtok(filesToMerge, ":");
//                 char* file2Name = strtok(NULL, ":");

//                 printf("file1: %s    file2: %s  \n", file1Name, file2Name);

//                 FILE * file1 = fopen(file1Name, "r");
//                 FILE * file2 = fopen(file2Name, "r");

//                 if(file1 == NULL || file2 == NULL){
//                     printf("error opening files\n");
//                     exit(EXIT_FAILURE);
//                 }

//                 TemporaryFile *tmp = mergeFiles(mainArray, file1, file2);

//                 fclose(file1);
//                 fclose(file2);

//                 printf("tmp file created\n");    

//                 int numOfLines = tmp->numberOfLines;

//                 free(tmp);

//                 createBlockFromFile( mainArray, numOfLines );

                

//                 ++argNum;
//                 ++pairsRead;

//                 free(filesToMerge);

//             }

            
//         } else if (strcmp((char*) argv[argNum], "remove_block") == 0){

//             int blockIndexToRemove = atoi( (char*) argv[ ++argNum] );

//             removeBlockOfLines(mainArray, blockIndexToRemove);

//             ++argNum;
            
//         } else if (strcmp((char*) argv[argNum], "remove_row") == 0)
//         {

//             int blockIndex = atoi( (char*) argv[ ++argNum] );
//             int rowIndex = atoi( (char*) argv[ ++argNum] );

//             removeLineFromBlock(mainArray, blockIndex, rowIndex);

//             ++argNum;
            
//         } else if ( strcmp((char*) argv[argNum], "print_files") == 0 ){

//             printf("print\n");

//             printMergedFiles(mainArray);

//             ++argNum;

//         }
        

//         // ++argNum;

//         printf("end argnum %i \n", argNum);
//     }

//     freeMainArray(mainArray);


//     return 0;
// }