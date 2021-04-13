#include<stdio.h>
#include<stdlib.h>
#include"mergeFilesLib.h"
#include<string.h>
#include<time.h>
#include<sys/times.h>
#include<unistd.h>

#include<dlfcn.h>





#define CLOCK_REALTIME 0



void test(char* fileAName, char* fileBName, int numberOfPairs){

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
    
    arr = createArray(numberOfPairs);

    
    /////////////////////////////////////////////////////////////////////////////////////

    timeStart = times(start);
    // mierzenie czasu

    int argNum = 0;
    seq = createFilesSequence(numberOfPairs, args, &argNum);
    saveToTmp(seq);
    

    timeEnd = times(end);


    double cpuTime = (double) (end->tms_stime - start->tms_stime)/ticks_per_second;
    double userTime = (double) (end->tms_utime - start->tms_utime)/ticks_per_second;

    printf("CZAS MERGEOWANIA PAR PLIKOW\n");
    printf("czas rzeczywisty %f sekund czas CPU %lf sekund czas uzytkownika %lf\n ",
    (double) (timeEnd - timeStart)/ticks_per_second , cpuTime, userTime);

    /////////////////////////////////////////////////////////////////////////////////////

    timeStart = times(start);
    
    createBlocksFromFile(arr, numberOfPairs, seq);

    timeEnd = times(end);

    cpuTime = (double) (end->tms_stime - start->tms_stime)/ticks_per_second;
    userTime = (double) (end->tms_utime - start->tms_utime)/ticks_per_second;

    printf("CZAS TWORZENIA BLOKOW\n");
    printf("czas rzeczywisty %f sekund czas CPU %lf sekund czas uzytkownika %lf\n ",
    (double) (timeEnd - timeStart)/ticks_per_second , cpuTime, userTime);

    ////////////////////////////////////////////////////////////////////////////////////////

    timeStart = times(start);
    
    for(int i = 0; i < numberOfPairs; i++){

        removeBlockOfLines(arr, i);

    }

    timeEnd = times(end);

    cpuTime = (double) (end->tms_stime - start->tms_stime)/ticks_per_second;
    userTime = (double) (end->tms_utime - start->tms_utime)/ticks_per_second;

    printf("CZAS USUWANIA %d BLOKOW\n", numberOfPairs);
    printf("czas rzeczywisty %f sekund czas CPU %lf sekund czas uzytkownika %lf\n ",
    (double) (timeEnd - timeStart)/ticks_per_second , cpuTime, userTime);

    /////////////////////////////////////////////////////////////////////////////////////////

    freeMainArray(arr);

    freeFilesSequence(seq);

    arr = createArray(numberOfPairs);

    argNum = 0;

    seq = createFilesSequence(numberOfPairs, args, &argNum);
    saveToTmp(seq);

    timeStart = times(start);
    
    createBlocksFromFile(arr, numberOfPairs, seq);

    for(int i = 0; i < numberOfPairs; i++){

        removeBlockOfLines(arr, i);

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

    freeMainArray(arr);

    freeFilesSequence(seq);

    free(end);

    free(start);

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

    


    

    int argNum = 1;

    MainArray *mainArray = NULL;

    FilesSequence * sequence = NULL;

    int size = -1;



    while( argNum < argc){



        if(strcmp((char*) argv[argNum++], "test") == 0){

            tests();

        
        } else if (strcmp((char*) argv[argNum], "create_table") == 0) {


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