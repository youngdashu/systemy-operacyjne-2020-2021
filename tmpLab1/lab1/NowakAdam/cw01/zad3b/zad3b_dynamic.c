#include<stdio.h>
#include<stdlib.h>

#include<string.h>
#include<time.h>
#include<sys/times.h>
#include<unistd.h>

#include<dlfcn.h>





#define CLOCK_REALTIME 0



void test(char* fileAName, char* fileBName, int numberOfPairs){


    void * handle = dlopen("./lib/libmergeFilesLibDynamic.so", RTLD_LAZY);

    if(!handle){
        printf("open error !!!!\n");
    }

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
    

    MainArray* (*createArray)(int) = dlsym(handle, "createArray");

    TemporaryFile* (*mergeFiles) (MainArray *, FILE * , FILE * ) = dlsym(handle, "mergeFiles");

    int (*createBlockFromFile) (MainArray *, int) = dlsym(handle, "createBlockFromFile");

    int (*getNumberOfLinesInBlock) (MainArray *, int ) = dlsym(handle, "getNumberOfLinesInBlock");

    void (*removeBlockOfLines) (MainArray * , int ) = dlsym(handle, "removeBlockOfLines");

    void (*removeLineFromBlock) (MainArray * , int , int ) = dlsym(handle, "removeLineFromBlock");

    void (*printMergedFiles) (MainArray *) = dlsym(handle, "printMergedFiles");

    void (*freeBlock) (BlockOfLines *) = dlsym(handle, "freeBlock");

    void (*freeMainArray) (MainArray *) = dlsym(handle, "freeMainArray");

    void (*freeFilesSequence) (FilesSequence *) = dlsym(handle, "freeFilesSequence");

    FilesSequence* (*createFilesSequence) (int , char** , int * ) = dlsym(handle, "createFilesSequence");

    void (*saveToTmp) (FilesSequence * ) = dlsym(handle, "saveToTmp");

    void (*createBlocksFromFile) (MainArray *, int , FilesSequence* ) = dlsym(handle, "createBlocksFromFile");





    long int ticks_per_second = sysconf(_SC_CLK_TCK);

    printf("test dla %i par \n", numberOfPairs);

    int timeStart, timeEnd;

    struct tms *start, *end;

    MainArray *arr = NULL;

    FilesSequence * seq = NULL;

    char* filesName = calloc(strlen(fileAName) + strlen(fileBName) + 3, sizeof(char));

    strcat(filesName, fileAName);

    strcat(filesName, ":");

    strcat(filesName, fileBName);

    char** args = (char**) calloc(numberOfPairs, sizeof(char*));

    for(int i = 0 ; i < numberOfPairs;  ++i) args[i] = filesName;

    start = calloc(1, sizeof(struct tms));
    end = calloc(1, sizeof(struct tms));
    
    arr = (*createArray)(numberOfPairs);

    /////////////////////////////////////////////////////////////////////////////////////

    timeStart = times(start);
    // mierzenie czasu

    int argNum = 0;
    seq = (*createFilesSequence)(numberOfPairs, args, &argNum);
    saveToTmp(seq);
    

    timeEnd = times(end);


    double cpuTime = (double) (end->tms_stime - start->tms_stime)/ticks_per_second;
    double userTime = (double) (end->tms_utime - start->tms_utime)/ticks_per_second;

    printf("CZAS MERGEOWANIA PAR PLIKOW\n");
    printf("czas rzeczywisty %f sekund czas CPU %lf sekund czas uzytkownika %lf\n ",
    (double) (timeEnd - timeStart)/ticks_per_second , cpuTime, userTime);

    /////////////////////////////////////////////////////////////////////////////////////

    timeStart = times(start);
    
    (*createBlocksFromFile)(arr, numberOfPairs, seq);

    timeEnd = times(end);

    cpuTime = (double) (end->tms_stime - start->tms_stime)/ticks_per_second;
    userTime = (double) (end->tms_utime - start->tms_utime)/ticks_per_second;

    printf("CZAS TWORZENIA BLOKOW\n");
    printf("czas rzeczywisty %f sekund czas CPU %lf sekund czas uzytkownika %lf\n ",
    (double) (timeEnd - timeStart)/ticks_per_second , cpuTime, userTime);

    ////////////////////////////////////////////////////////////////////////////////////////

    timeStart = times(start);
    
    for(int i = 0; i < numberOfPairs; i++){

        (*removeBlockOfLines)(arr, i);

    }

    timeEnd = times(end);

    cpuTime = (double) (end->tms_stime - start->tms_stime)/ticks_per_second;
    userTime = (double) (end->tms_utime - start->tms_utime)/ticks_per_second;

    printf("CZAS USUWANIA %d BLOKOW\n", numberOfPairs);
    printf("czas rzeczywisty %f sekund czas CPU %lf sekund czas uzytkownika %lf\n ",
    (double) (timeEnd - timeStart)/ticks_per_second , cpuTime, userTime);

    /////////////////////////////////////////////////////////////////////////////////////////

    (*freeMainArray)(arr);

    (*freeFilesSequence)(seq);

    arr = (*createArray)(numberOfPairs);

    argNum = 0;

    seq = (*createFilesSequence)(numberOfPairs, args, &argNum);
    (*saveToTmp)(seq);

    timeStart = times(start);
    
    (*createBlocksFromFile)(arr, numberOfPairs, seq);

    for(int i = 0; i < numberOfPairs; i++){

        (*removeBlockOfLines)(arr, i);

    }

    timeEnd = times(end);

    cpuTime = (double) (end->tms_stime - start->tms_stime)/ticks_per_second;
    userTime = (double) (end->tms_utime - start->tms_utime)/ticks_per_second;

    printf("CZAS DODANIA %d BLOKOW I USUWANIA %d BLOKOW \n", numberOfPairs, numberOfPairs);
    printf("czas rzeczywisty %f sekund czas CPU %lf sekund czas uzytkownika %lf\n ",
    (double) (timeEnd - timeStart)/ticks_per_second , cpuTime, userTime);

    /////////////////////////////////////////////////////////////////////////////////////////

    free(filesName);

    free(args);

    (*freeMainArray)(arr);

    (*freeFilesSequence)(seq);

    free(end);

    free(start);

    dlclose(handle);

}

void tests(){

    printf("pliki krotkie\n");
    
    test("test1_ashort.txt", "test1_bshort.txt", 3);
    test("test1_ashort.txt", "test1_bshort.txt", 100);
    test("test1_ashort.txt", "test1_bshort.txt", 1000);

    printf("pliki srednie\n");

    test("test1_amed.txt", "test1_bmed.txt", 3);
    test("test1_amed.txt", "test1_bmed.txt", 100);
    test("test1_amed.txt", "test1_bmed.txt", 1000);

    printf("pliki dlugie\n");

    test("test1_along.txt", "test1_blong.txt", 3);
    test("test1_along.txt", "test1_blong.txt", 100);
    test("test1_along.txt", "test1_blong.txt", 1000);
}



int main(int argc, char** argv){

    
    printf("\n\nRodzaj biblioteki: %s Poziom kompilacji: %s \n\n\n", (char*) argv[2], (char*) argv[3]);

    tests();

    return 0;
}