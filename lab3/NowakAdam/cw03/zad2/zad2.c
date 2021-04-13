#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>

#include<sys/times.h>

#include"mergeFilesLib.h"

#include<sys/wait.h>


void timeTest( /* char* file1Name, char* file2Name, */   FILE * file1,  FILE * file2,  int n){


    for(int i = 0; i < n ; i ++){

        if(fork() == 0){

            // printf("i: %i proces potomny o pid: %i jest dzieckiem procesu o pid: %i\n", i,getpid(), getppid());


            MainArray* arr = createArray(1);

            fseek(file1, 0, SEEK_SET);
            fseek(file2, 0, SEEK_SET);

            // FILE * file1 = fopen(file1Name, "r");
            // FILE * file2 = fopen(file2Name, "r");

            // long int ticks_per_second = sysconf(_SC_CLK_TCK);

            // int timeStart, timeEnd;

            // double cpuTime, userTime;

            // struct tms *start, *end;

            // start = calloc(1, sizeof(struct tms));
            // end = calloc(1, sizeof(struct tms));


            // timeStart = times(start);

            TemporaryFile *tmpFile = mergeFiles(arr, file1, file2);

            createBlockFromFile(arr, tmpFile->numberOfLines);
            

            // timeEnd = times(end);

            // cpuTime = (double) (end->tms_stime - start->tms_stime)/ticks_per_second;
            // userTime = (double) (end->tms_utime - start->tms_utime)/ticks_per_second;
            // double realTime = (double) (timeEnd - timeStart) / ticks_per_second;
            // fprintf(raport, "PID %i\n", getpid());
            // fprintf(raport, "%lf:%lf:%lf\n", realTime, userTime, cpuTime );


            // fclose(file1);
            // fclose(file2);

            freeMainArray(arr);
            free(tmpFile);

            // free(start);
            // free(end);

            // break;
            exit(EXIT_SUCCESS);

         }  else{
            int res, stat;
            while( (res=  wait(&stat) ) > 0);

        }

    }




}

void mergeNPairsInNProcesses(int n, char* fileNames[]){

    for(int i = 0; i < n ; i ++){

        if(fork() == 0){

            printf("i: %i proces potomny o pid: %i jest dzieckiem procesu o pid: %i\n", i,getpid(), getppid());

            MainArray* arr = createArray(1);

            char* file1Name = strtok(fileNames[i], ":");
            char* file2Name = strtok(NULL, ":");

            FILE * file1 = fopen(file1Name, "r");
            FILE* file2 = fopen(file2Name, "r");


            TemporaryFile *tmpFile = mergeFiles(arr, file1, file2);

            createBlockFromFile(arr, tmpFile->numberOfLines);

            printMergedFiles(arr);

            fclose(file1);
            fclose(file2);

            freeMainArray(arr);

            

            break;

        } else{
            sleep(1);
        }


    }
}

int main(int argc, char* argv[]){

    int n;

    if(strcmp(argv[1], "test") == 0){

        FILE * summedReports = fopen("suma_raport_zad2.txt", "w+");

        char * fileNames[] = {"test1_ashort.txt", "test1_bshort.txt", "test1_amed.txt", "test1_bmed.txt", "test1_along.txt", "test1_blong.txt" };
        char * types[] = {"short", "med", "long"};

        int typeOfTest = 0;
        int type = 0;

         while(typeOfTest < 6) {

            FILE * file1 = fopen(fileNames[typeOfTest], "r");
            FILE * file2 = fopen(fileNames[typeOfTest + 1], "r");

            for(int n = 3 ; n <= 300 ; n*=10 ) {


                long int ticks_per_second = sysconf(_SC_CLK_TCK);

                int timeStart, timeEnd;

                double cpuTime, userTime;

                struct tms *start, *end;

                start = calloc(1, sizeof(struct tms));
                end = calloc(1, sizeof(struct tms));


                timeStart = times(start);                

                timeTest( file1, file2 , n);

                timeEnd = times(end);

                cpuTime = (double) (end->tms_stime - start->tms_stime)/ticks_per_second;
                userTime = (double) (end->tms_utime - start->tms_utime)/ticks_per_second;
                double realTime = (double) (timeEnd - timeStart) / ticks_per_second;

                fprintf(summedReports, "%s n: %i Czas rzeczywisty: %lf, czas uzytkownika: %lf, czas cpu: %lf pid: %i\n", types[type], n ,realTime, userTime, cpuTime, getpid());

                fseek(summedReports, 0, SEEK_END);

            }

            typeOfTest+=2;
            type++; 
        
        }
        
        fclose(summedReports);

        return 0;

    } else{

        n = atoi(argv[1]);

        if(argc != 2 + n){

            printf("zla liczba argumenttow\n");
            exit(EXIT_FAILURE);

        }

        char** fileNames = (char**) calloc(n , sizeof(char*));

        for(int i = 0; i < n; i++){

            fileNames[i] = strdup(argv[i+2]);

        }

        
        mergeNPairsInNProcesses(n , fileNames);
        

        for(int i = 0; i < n; i++){

            free(fileNames[i]);

        }

    }



}