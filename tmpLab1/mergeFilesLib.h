#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct BlockOfLines{

    int numberOfLines;
    char **arrayOfStrings;

}BlockOfLines;

typedef struct MainArray{

    BlockOfLines **blocksOfLines;
    int index;

}MainArray;

typedef struct TemporaryFile
{
    FILE *file;
    int numberOfLines;
}TemporaryFile;



MainArray *createArray(int size);
TemporaryFile *mergeFiles(MainArray *mainArray, FILE * file1, FILE * file2);
int createBlockFromFile(TemporaryFile *tmpFile, MainArray *array);
int getNumberOfLinesInBlock(MainArray *array, int index);
void removeBlockOfLines(MainArray * array, int index);
void removeLineFromBlock(MainArray * array, int arrIndex, int lineIndex);
void printMergedFiles(MainArray * array);
