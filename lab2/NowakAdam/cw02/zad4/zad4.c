#include<stdlib.h>
#include<stdio.h>

#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>

#include<string.h>

#include<sys/times.h>

#define MAX_LINE_LEN 200


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



void lib(char* srcName, char* destName, char* pattern, char* replace){

    FILE * src = fopen(srcName, "r");

    FILE * dest = fopen(destName, "w");


    char* file1Line = calloc(MAX_LINE_LEN, sizeof(char));

    int lenOfReplace = strlen(replace);

    int lenOfPattern = strlen(pattern);


    int summedOffset = 0;

    int offsetIncrease = 0;

    while( 1 ){

        int resOfRead = fread(file1Line, sizeof(char), MAX_LINE_LEN, src);

        if(resOfRead == 0){
            break;
        }

        int countToNextLine = count(file1Line);

        char* trimmedLine = calloc(countToNextLine + 2, sizeof(char));

        strncpy(trimmedLine, file1Line, countToNextLine+1);

        int textStart = 0;

        char* strToWrite = calloc(MAX_LINE_LEN, sizeof(char));

        int s;

        for (s = 0; s < strlen(trimmedLine) - lenOfPattern + 1 ; s++){

            char* pieceOfStr = calloc( lenOfPattern + 1, sizeof(char));

            memcpy(pieceOfStr, trimmedLine + s, lenOfPattern*sizeof(char));

            if(strcmp(pieceOfStr, pattern) == 0){

                // przepisz tekst wystepujacy przed wzorem
                memcpy(strToWrite, trimmedLine + textStart, s - textStart);

                fwrite(strToWrite, sizeof(char), strlen(strToWrite), dest);

                fwrite(replace, sizeof(char), lenOfReplace, dest);

                textStart = ( s + lenOfPattern );

                s = textStart;

                memset(strToWrite, 0, MAX_LINE_LEN*sizeof(char));
            }

            free(pieceOfStr);

        }

        

        memcpy(strToWrite, trimmedLine + textStart, s-textStart + 2);

        fwrite(strToWrite, sizeof(char), strlen(strToWrite), dest);

        offsetIncrease = countToNextLine + 1;

        summedOffset += offsetIncrease;

        fseek(src, summedOffset, 0);

        memset(file1Line, 0, MAX_LINE_LEN*sizeof(char) );

        free(trimmedLine);

    }


    free(file1Line);

    fclose(src);

    fclose(dest);

}

void sys(char* srcName, char* destName, char* pattern , char* replace){


    int src = open(srcName, O_RDONLY);

    int dest = open(destName, O_WRONLY);


    char* file1Line = calloc(MAX_LINE_LEN, sizeof(char));

    int lenOfReplace = strlen(replace);

    int lenOfPattern = strlen(pattern);


    int summedOffset = 0;

    int offsetIncrease = 0;

    while( 1 ){

        int resOfRead = read(src, file1Line, sizeof(char) * MAX_LINE_LEN);

        if(resOfRead == 0){
            break;
        }

        int countToNextLine = count(file1Line);

        char* trimmedLine = calloc(countToNextLine + 2, sizeof(char));

        strncpy(trimmedLine, file1Line, countToNextLine + 1);

        int textStart = 0;

        char* strToWrite = calloc(MAX_LINE_LEN, sizeof(char));

        int s;

        for (s = 0; s < strlen(trimmedLine) - lenOfPattern + 1 ; s++){

            char* pieceOfStr = calloc( lenOfPattern + 1, sizeof(char));

            memcpy(pieceOfStr, trimmedLine + s, lenOfPattern);

            if(strcmp(pieceOfStr, pattern) == 0){

                // przepisz tekst wystepujacy przed wzorem
                memcpy(strToWrite, trimmedLine + textStart, s - textStart);

                write(dest, strToWrite, sizeof(char) * strlen(strToWrite));

                write(dest, replace, sizeof(char) * lenOfReplace);

                textStart = ( s + lenOfPattern );

                s = textStart;

                memset(strToWrite, 0, MAX_LINE_LEN*sizeof(char));
            }

            free(pieceOfStr);

        }

        memcpy(strToWrite, trimmedLine + textStart, s-textStart + 2);

        write(dest, strToWrite, sizeof(char) * strlen(strToWrite) );

        offsetIncrease = countToNextLine + 1;

        summedOffset += offsetIncrease;

        lseek(src, summedOffset, SEEK_SET);

        memset(file1Line, 0, MAX_LINE_LEN*sizeof(char) );

        free(trimmedLine);

    }


    free(file1Line);

    close(src);

    close(dest);

}

int main(int argc, char* argv[]){

    if (argc < 5 || argc > 6){


        printf("zla ilosc argumentow\n");
        exit(EXIT_FAILURE);
    }

    char* srcName = argv[1];

    char* destName = argv[2];

    char * pattern = argv[3];

    char* replace = argv[4];


    
    if(argc == 6 && strcmp(argv[5], "test") == 0){

        FILE * raport = fopen("pomiar_zad_4.txt", "w");

        long int ticks_per_second = sysconf(_SC_CLK_TCK);

        int timeStart, timeEnd;

        double cpuTime, userTime;

        struct tms *start, *end;

        start = calloc(1, sizeof(struct tms));
        end = calloc(1, sizeof(struct tms));

        fprintf(raport, "Wariant lib\n\n");

        timeStart = times(start);

        lib(srcName, destName, pattern, replace);

        timeEnd = times(end);

        cpuTime = (double) (end->tms_stime - start->tms_stime)/ticks_per_second;
        userTime = (double) (end->tms_utime - start->tms_utime)/ticks_per_second;

        fprintf(raport, "Czas dzialania: rzeczywisty: %lf uzytkownika %lf CPU %lf \n\n", (double) (timeEnd - timeStart) / ticks_per_second, userTime, cpuTime );

        fprintf(raport, "Wariant sys\n\n");

        timeStart = times(start);

        sys(srcName, destName, pattern, replace);

        timeEnd = times(end);

        cpuTime = (double) (end->tms_stime - start->tms_stime)/ticks_per_second;
        userTime = (double) (end->tms_utime - start->tms_utime)/ticks_per_second;

        fprintf(raport, "Czas dzialania: rzeczywisty: %lf uzytkownika %lf CPU %lf \n\n", (double) (timeEnd - timeStart) / ticks_per_second, userTime, cpuTime );

        free(start);
        free(end);

        fclose(raport);


    } else{


        lib(srcName, destName, pattern, replace);

    }    
}