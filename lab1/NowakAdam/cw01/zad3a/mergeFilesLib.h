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
    int size;

}MainArray;

typedef struct TemporaryFile
{
    FILE *file;
    int numberOfLines;
}TemporaryFile;

typedef struct FilesSequence{

    char** files;
    int numOfPairs;
    int * numOfLinesInFile;

} FilesSequence;



MainArray *createArray(int size);

TemporaryFile *mergeFiles(MainArray *mainArray, FILE * file1, FILE * file2);

int createBlockFromFile(MainArray *array, int numberOfLines);

int getNumberOfLinesInBlock(MainArray *array, int index);

void removeBlockOfLines(MainArray * array, int index);

void removeLineFromBlock(MainArray * array, int arrIndex, int lineIndex);

void printMergedFiles(MainArray * array);

void freeBlock(BlockOfLines *block);

void freeMainArray(MainArray *arr);

void freeFilesSequence(FilesSequence * seq);

FilesSequence* createFilesSequence(int numberOfFiles, char** argv , int * argnum);

void saveToTmp(FilesSequence * sequence);

void createBlocksFromFile(MainArray * arr, int numOfBlocks, FilesSequence* seq);

