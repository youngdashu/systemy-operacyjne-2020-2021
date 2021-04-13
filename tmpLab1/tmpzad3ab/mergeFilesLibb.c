#include"mergeFilesLib.h"
# define MAX_LINE_LEN 102

void checkForMissingNextLineSign(char* str){

    int len = strlen(str);

    int i = 0;

    char* tmp = strdup(str);

    


    if (strchr(tmp, '\n') == NULL){

        strcat(str, "\n");
    }


free(tmp);
    

}


MainArray *createArray(int size){

    if (size < 1){
        printf("Podano za maly rozmiar, alokuje dla rozmiaru 1");
        size = 1;
        
    }

    MainArray* res = (MainArray*) calloc(1 ,sizeof(MainArray));
    res->blocksOfLines = (BlockOfLines**) calloc(size, sizeof(BlockOfLines));
    res->index = 0;

    return res;

}



TemporaryFile *mergeFiles(MainArray *mainArray, FILE * file1, FILE * file2){

    printf("merdzujemy \n");

    TemporaryFile *resFile =  calloc(1, sizeof(struct TemporaryFile)); 

    resFile->file = fopen("tmpFile.txt", "w");
    resFile->numberOfLines = 0;

    printf("otwarto res plik \n");

    if(resFile->file == NULL){
        return NULL;
    }

    // int predictedNumOfLines = 10;
    // int increase = 10;

    // BlockOfLines * block = calloc(1, sizeof(BlockOfLines));
    // block->numberOfLines = 0;
    // block->arrayOfStrings = (char**)calloc(predictedNumOfLines, sizeof(char*) );

    char *file1Line = calloc(MAX_LINE_LEN, sizeof(char));
    char *file2Line = calloc(MAX_LINE_LEN, sizeof(char));

    // char file1Line[100];
    // char file2Line[100];

    

    printf("zalokowano bufer \n");

    int flag1 = 1;
    int flag2 = 1;

    int i = 1;

    while( 1 ){

        printf("    while %i \n", i);


        if ( fgets(file1Line, MAX_LINE_LEN, file1) == NULL ){

            printf("set flag1 to 0\n");

            flag1 = 0;

        }

        if ( fgets(file2Line, MAX_LINE_LEN, file2) == NULL ){
            
            printf("set flag2 to 0\n");
            flag2 = 0;

        }




        printf("file1Line: %s#file2Line %s#koniec\n", file1Line, file2Line);

        // if(i==5){

        //     printByChar(file1Line, 100);
        //     printf("\n");
        //     printf("\n");
        //     printf("___________________________");
        //     printByChar(file2Line, 100);
        //     printf("\n");

        // }

        if(flag1 && file1Line != NULL){

            printf("fputs file1\n");

            fputs(file1Line, resFile->file);
            resFile->numberOfLines = resFile->numberOfLines + 1;
            //block->arrayOfStrings[(block->numberOfLines)++] = file1Line;

        }

        if(flag2 && file1Line != NULL){

            printf("fputs file2\n");

            fputs(file2Line, resFile->file);
            resFile->numberOfLines = resFile->numberOfLines + 1;
            //block->arrayOfStrings[(block->numberOfLines)++] = file2Line;

        }

        // if(block->numberOfLines == predictedNumOfLines){
        //     predictedNumOfLines+=increase;
        //     increase+=2;
        //     block->arrayOfStrings = (char**) realloc( (block->arrayOfStrings) , predictedNumOfLines));
        // }

        if(flag1 && feof(file1)) flag1 = 0;
        if(flag2 && feof(file2)) flag2 = 0;

        // if(checkIfEOFInString(file1Line)) flag1 = 0;
        // if(checkIfEOFInString(file2Line)) flag2 = 0;

        if(flag1 == 0 && flag2 == 0){

            break;

        }
        
        // free(file1Line);
        // free(file2Line);

        memset(file1Line, 0, MAX_LINE_LEN*sizeof(char) );
        memset(file2Line, 0, MAX_LINE_LEN*sizeof(char) );

        printf("free\n");

        // char *file1Line = (char*) calloc(MAX_LINE_LEN, sizeof(char));
        // char *file2Line = (char*) calloc(MAX_LINE_LEN, sizeof(char));

        i++;

    }

    printf("exit while\n");

    free(file1Line);
    free(file2Line);

    // printf("return\n");

    fclose(resFile->file);

    printf("return\n");

    printf(" ### %i \n", resFile->numberOfLines);

    return resFile;


}


int createBlockFromFile( MainArray *array, int numberOfLines){

    printf("start create block\n");

    //int numberOfLines = numOfLines;

    // TemporaryFile *tmpFile = (TemporaryFile*) calloc(1, sizeof(TemporaryFile));


    

    printf("num of lines: %i\n", numberOfLines);

    TemporaryFile *tmpFile = (TemporaryFile*) calloc(1, sizeof(TemporaryFile));
    tmpFile->numberOfLines = numberOfLines;

    char *line = calloc(MAX_LINE_LEN, sizeof(char));

    tmpFile->file = fopen("tmpFile.txt", "r");
    

    BlockOfLines * block = calloc(1, sizeof(BlockOfLines));
    block->numberOfLines = 0;
    block->arrayOfStrings = (char**)calloc(tmpFile->numberOfLines, sizeof(char*) );

    int i = 0;

    while( (fgets(line, MAX_LINE_LEN, tmpFile->file)) ){

        printf("saving to block chars: %s  \n", line);

        // block->arrayOfStrings[i++] = line;
        // block->arrayOfStrings[i++] = (char*) calloc(MAX_LINE_LEN, sizeof(char) );

        block->arrayOfStrings[i++] = strdup(line);

        // strcpy( block->arrayOfStrings[i++], line );

        block->numberOfLines = block->numberOfLines + 1;

        // char *line = calloc(MAX_LINE_LEN, sizeof(char));

        // if(block->numberOfLines == predictedNumOfLines){
        //     predictedNumOfLines+=increase;
        //     increase+=2;
        //     block->arrayOfStrings = (char**) realloc( (block->arrayOfStrings) , predictedNumOfLines);
        // }

        memset(line, 0, MAX_LINE_LEN*sizeof(char));


        printf("chars saved at block[i]: %s \n", block->arrayOfStrings[i-1] );

    }

    // printf("############\n");
    // printf("block being added to main array\n");
    // printf("")


    array->blocksOfLines[array->index] = block;
    array->index = array->index + 1;

    fclose(tmpFile->file);

    printf("%%%%%%%%%%%%%%%%%%%%\n");
    printf("internal printmergedfiles\n");
    printMergedFiles(array);
    printf("%%%%%%%%%%%%%%%%\n");

    return array->index - 1;


}

int getNumberOfLinesInBlock(MainArray *array, int index){

    return array->blocksOfLines[index]->numberOfLines;

}

void removeBlockOfLines(MainArray * array, int index){

    int numOfLinesInBlock = array->blocksOfLines[index]->numberOfLines;

    for(int i = 0; i < numOfLinesInBlock; i++){
        free(array->blocksOfLines[index]->arrayOfStrings[i]);
    }

    free(array->blocksOfLines[index]->arrayOfStrings);

    free(array->blocksOfLines[index]);

    /// rozwiazanie niepewne ale chyba ujdzie
    array->blocksOfLines[index] = NULL;
    ///

}

void removeLineFromBlock(MainArray * array, int arrIndex, int lineIndex){

    free(array->blocksOfLines[arrIndex]->arrayOfStrings[lineIndex]);
    ///////
    array->blocksOfLines[arrIndex]->arrayOfStrings[lineIndex] = NULL;
    ///////

}

void printMergedFiles(MainArray * array){

    int numberOfBlocks = array->index;

    printf("    numberOfblocks in mainArray: %i\n", numberOfBlocks);

    for(int i = 0; i < numberOfBlocks; i++){

        if(array->blocksOfLines[i] != NULL){

            printf("blocksOfLines[i] is not NULL\n");

            BlockOfLines * tmpBlock = array->blocksOfLines[i];

            int numberOfLines = tmpBlock->numberOfLines;

            printf("number of lines in current block: %i\n", numberOfLines);

            for(int line = 0; line < numberOfLines; line ++){

                if(tmpBlock->arrayOfStrings[line] != NULL){
                    printf("%s", tmpBlock->arrayOfStrings[line]);
                }

            }

        }

    }


}

void freeBlock(BlockOfLines *block){

    if(block == NULL){
        return;
    }

    int size = block->numberOfLines;

    for(int i = 0 ; i < size ; i++){

        if(block->arrayOfStrings[i] != NULL){

            free(block->arrayOfStrings[i]);

            block->arrayOfStrings[i] = NULL;
        }
    }

    free(block->arrayOfStrings);

    free(block);
}

void freeMainArray(MainArray *arr){

    if(arr == NULL){
        return;
    }

    int size = arr->size;

    for(int i = 0 ; i < size; i++){

        if(arr->blocksOfLines[i] != NULL){

            freeBlock(arr->blocksOfLines[i]);

        }

    }

    free(arr->blocksOfLines);
    free(arr);
}

void freeFilesSequence(FilesSequence * seq){

    if(seq == NULL){
        return;
    }

    int size = seq->numOfPairs;

    for(int i = 0 ; i < size; i++){

        free(seq->files[i]);

    }

    free(seq->files);

    free(seq->numOfLinesInFile);
    free(seq);

}

FilesSequence* createFilesSequence(int numberOfPairs, char** argv , int * argNum){

    // printf("create files sequence\n");

    FilesSequence * seq = calloc(1, sizeof(FilesSequence));

    seq->files = (char**) calloc(numberOfPairs * 2, sizeof(char*));
    seq->numOfPairs = 0;
    seq->numOfLinesInFile = calloc(numberOfPairs, sizeof(int));

    int i = 0;

    while(i < numberOfPairs){

        char* filesToMerge = strdup(argv[*argNum]);

        // printf("sequence filesToMerge: %s \n", filesToMerge);        

        (*argNum)++;

        seq->files[i++] = strdup(filesToMerge);

        free(filesToMerge);
        

        seq->numOfPairs++;

    }

    return seq;


}

void saveToTmp(FilesSequence * sequence){

    FILE * resFile = fopen("tmpFile.txt", "w");

    
    for(int i = 0 ; i < sequence->numOfPairs; i++){

        char* filesToMerge =  strdup((char*) sequence->files[i]);

        // printf("save to tmp filesToMerge %s", filesToMerge);

        char* file1Name = strdup(strtok(filesToMerge, ":"));
        char* file2Name = strdup(strtok(NULL, ":"));

        free(filesToMerge);

        FILE * file1 = fopen(file1Name, "r");
        FILE * file2 = fopen(file2Name, "r");

        if(file1 == NULL || file2 == NULL){
            printf("otwierane pliki nie istnieja!!! \n");
            exit(EXIT_FAILURE);
        }

        char *file1Line = calloc(MAX_LINE_LEN, sizeof(char));
        char *file2Line = calloc(MAX_LINE_LEN, sizeof(char));


        int flag1 = 1;
        int flag2 = 1;

    
        while( 1 ){


            if ( fgets(file1Line, MAX_LINE_LEN, file1) == NULL ){

                flag1 = 0;

            }

            if ( fgets(file2Line, MAX_LINE_LEN, file2) == NULL ){
                flag2 = 0;

            }


            if(flag1 && file1Line != NULL){


                checkForMissingNextLineSign(file1Line);

                fputs(file1Line, resFile);

                sequence->numOfLinesInFile[i]++;

            }

            if(flag2 && file1Line != NULL){

                checkForMissingNextLineSign(file2Line);

                fputs(file2Line, resFile);

                 sequence->numOfLinesInFile[i]++;

            }

            if(flag1 && feof(file1)) flag1 = 0;
            if(flag2 && feof(file2)) flag2 = 0;

            if(flag1 == 0 && flag2 == 0){

                break;

            }

            memset(file1Line, 0, MAX_LINE_LEN*sizeof(char) );
            memset(file2Line, 0, MAX_LINE_LEN*sizeof(char) );


        }

        fputs("###\n", resFile);


        free(file1Line);
        free(file2Line);

        free(file1Name);
        free(file2Name);

        fclose(file1);
        fclose(file2);


    }

    fclose(resFile);

}

void createBlocksFromFile(MainArray * arr, int numOfBlocks, FilesSequence* seq){

    // printf("num of blocks %i \n", numOfBlocks);

    FILE * tmpFile = fopen("tmpFile.txt", "r");

    for(int i = 0; i < numOfBlocks ; i++){

        BlockOfLines *block = calloc(1, sizeof(BlockOfLines));

        // printf("num of lines in file %i \n", seq->numOfLinesInFile[i]);

        block->numberOfLines = seq->numOfLinesInFile[i];
        block->arrayOfStrings = calloc(block->numberOfLines, sizeof(char*));

        char* line = calloc(MAX_LINE_LEN, sizeof(char));

        char* endOfMergedFile = "###\n";

        int j = 0;

        while (strcmp( fgets(line , MAX_LINE_LEN, tmpFile), endOfMergedFile  ) != 0  )
        {
            
            block->arrayOfStrings[j++] = strdup(line);

            memset(line, 0, MAX_LINE_LEN);

        }

        arr->blocksOfLines[arr->index++] = block;

        free(line);


    }

}