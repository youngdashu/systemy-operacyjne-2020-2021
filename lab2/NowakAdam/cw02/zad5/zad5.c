#include<stdlib.h>
#include<stdio.h>

#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>

#include<string.h>

#include<sys/times.h>

#define MAX_LINE_LEN 50

int count(char* str){

    int i = 0;

    char* tmp = str;

    while(*tmp != '\0'){



        if(*tmp == '\n'){

            return i;

        }

        i++;
        tmp++;

    }

    return -1;


}


void lib(char* srcName, char* destName){

    FILE * src = fopen(srcName, "r");

    FILE * dest = fopen(destName, "w");


    char* file1Line = calloc(MAX_LINE_LEN + 1, sizeof(char));


    int summedOffset = 0;

    int offsetIncrease = 0;

    while( 1 ){

        int resOfRead = fread(file1Line, sizeof(char), MAX_LINE_LEN , src);

        if(resOfRead == 0){
            break;
        }

        int countToNextLine = count(file1Line);

        if (countToNextLine == -1){


            // printf("nie znaleziono \\n !\n");

            fwrite(file1Line, sizeof(char), resOfRead, dest);
            fwrite("\n", sizeof(char), 1, dest);

            offsetIncrease = resOfRead;


        } else{

            char* trimmedLine = strdup(strtok(file1Line, "\n"));

            fwrite(trimmedLine, sizeof(char), strlen(trimmedLine), dest );
            fwrite("\n", sizeof(char),1, dest );

            free(trimmedLine);

            offsetIncrease = countToNextLine +1 ;

        }

        summedOffset += offsetIncrease;

        fseek(src, summedOffset, 0);

        memset(file1Line, 0, (MAX_LINE_LEN+1)*sizeof(char) );

    }


    free(file1Line);

    fclose(src);

    fclose(dest);

}

void sys(char* srcName, char* destName){


    int src = open(srcName, O_RDONLY);

    int dest = open(destName, O_WRONLY);


    char* file1Line = calloc(MAX_LINE_LEN + 1, sizeof(char));


    int summedOffset = 0;

    int offsetIncrease = 0;

    while( 1 ){

        int resOfRead = read(src, file1Line,  sizeof(char)*MAX_LINE_LEN);

        if(resOfRead == 0){
            break;
        }

        int countToNextLine = count(file1Line);

        if (countToNextLine == -1){
            // printf("nie znaleziono \\n !\n");
            // exit(EXIT_FAILURE);

            write(dest, file1Line, sizeof(char) * resOfRead);
            write(dest, "\n", sizeof(char));

            offsetIncrease = resOfRead;


        } else{

            char* trimmedLine = strdup(strtok(file1Line, "\n"));

            write(dest, trimmedLine, sizeof(char) * strlen(trimmedLine) );
            write(dest, "\n", sizeof(char) );

            free(trimmedLine);

            offsetIncrease = countToNextLine + 1 ;

        }

        summedOffset += offsetIncrease;

        lseek(src, summedOffset, SEEK_SET);

        memset(file1Line, 0, (MAX_LINE_LEN + 1)*sizeof(char) );



    }


    free(file1Line);

    close(src);

    close(dest);

}

int main(int argc, char* argv[]){

    if (argc < 3 || argc > 4){
        printf("zla ilosc argumentow\n");
        exit(EXIT_FAILURE);
    }

    char* srcName = argv[1];

    char* destName = argv[2];


    
    if(argc == 4 && strcmp(argv[3], "test") == 0){

       FILE * raport = fopen("pomiar_zad_5.txt", "w");

        long int ticks_per_second = sysconf(_SC_CLK_TCK);

        int timeStart, timeEnd;

        double cpuTime, userTime;

        struct tms *start, *end;

        start = calloc(1, sizeof(struct tms));
        end = calloc(1, sizeof(struct tms));

        fprintf(raport, "Wariant lib\n\n");

        timeStart = times(start);

        lib(srcName, destName);

        timeEnd = times(end);

        cpuTime = (double) (end->tms_stime - start->tms_stime)/ticks_per_second;
        userTime = (double) (end->tms_utime - start->tms_utime)/ticks_per_second;

        fprintf(raport, "Czas dzialania: rzeczywisty: %lf uzytkownika %lf CPU %lf \n\n", (double) (timeEnd - timeStart) / ticks_per_second, userTime, cpuTime );

        fprintf(raport, "Wariant sys\n\n");

        timeStart = times(start);

        sys(srcName, destName);

        timeEnd = times(end);

        cpuTime = (double) (end->tms_stime - start->tms_stime)/ticks_per_second;
        userTime = (double) (end->tms_utime - start->tms_utime)/ticks_per_second;

        fprintf(raport, "Czas dzialania: rzeczywisty: %lf uzytkownika %lf CPU %lf \n\n", (double) (timeEnd - timeStart) / ticks_per_second, userTime, cpuTime );

        free(start);
        free(end);

        fclose(raport);


    } else{

        sys(srcName, destName);

    }    
}