#include<mergeFilesLib.h>



MainArray *createArray(int size){

    if (size < 1){
        printf("Podano za maly rozmiar, alokuje dla rozmiaru 1");
        size = 1;
        
    }

    MainArray* res = (MainArray*) calloc(size ,sizeof(MainArray));
    res->index = 0;

    return res;

}

TemporaryFile *mergeFiles(MainArray *mainArray, FILE * file1, FILE * file2){

    TemporaryFile *resFile = calloc(1, sizeof(TemporaryFile)); 

    resFile->file = fopen("tmpFile.txt", "w");
    resFile->numberOfLines = 0;

    if(resFile->file == NULL){
        return NULL;
    }

    // int predictedNumOfLines = 10;
    // int increase = 10;

    // BlockOfLines * block = calloc(1, sizeof(BlockOfLines));
    // block->numberOfLines = 0;
    // block->arrayOfStrings = (char**)calloc(predictedNumOfLines, sizeof(char*) );

    char *file1Line = calloc(1000, sizeof(char));
    char *file2Line = calloc(1000, sizeof(char));

    int flag1 = 1;
    int flag2 = 1;

    while( (fgets(file1Line, 999, file1)) != NULL || (fgets(file2Line, 999, file2)) != NULL ){

        if(feof(file1)) flag1 = 0;
        if(feof(file2)) flag2 = 0;

        if(flag1 && file1Line != NULL){

            fputs(file1Line, resFile->file);
            resFile->numberOfLines++;
            //block->arrayOfStrings[(block->numberOfLines)++] = file1Line;

        }

        if(flag2 && file1Line != NULL){

            fputs(file2Line, resFile->file);
            resFile->numberOfLines++;
            //block->arrayOfStrings[(block->numberOfLines)++] = file2Line;

        }

        // if(block->numberOfLines == predictedNumOfLines){
        //     predictedNumOfLines+=increase;
        //     increase+=2;
        //     block->arrayOfStrings = (char**) realloc( (block->arrayOfStrings) , predictedNumOfLines));
        // }
        

        char *file1Line = calloc(1000, sizeof(char));
        char *file2Line = calloc(1000, sizeof(char));


    }

    return resFile;


}


int createBlockFromFile(TemporaryFile *tmpFile, MainArray *array){

    int numberOfLines = tmpFile->numberOfLines;

    char *line = calloc(1000, sizeof(char));

   
    

    BlockOfLines * block = calloc(1, sizeof(BlockOfLines));
    block->numberOfLines = 0;
    block->arrayOfStrings = (char**)calloc(tmpFile->numberOfLines, sizeof(char*) );

    int i = 0;

    while( (fgets(line, 999, tmpFile->file)) ){

        block->arrayOfStrings[i++] = line;

        // if(block->numberOfLines == predictedNumOfLines){
        //     predictedNumOfLines+=increase;
        //     increase+=2;
        //     block->arrayOfStrings = (char**) realloc( (block->arrayOfStrings) , predictedNumOfLines);
        // }

    }


    array->blocksOfLines[array->index] = block;
    array->index++;

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

    for(int i = 0; i < numberOfBlocks; i++){

        if(array->blocksOfLines[i] != NULL){

            BlockOfLines * tmpBlock = array->blocksOfLines[i];

            int numberOfLines = tmpBlock->numberOfLines;

            for(int line = 0; line < numberOfLines; line ++){

                if(tmpBlock->arrayOfStrings[line] != NULL){
                    printf("%s", tmpBlock->arrayOfStrings[line]);
                }

            }

        }

    }


}