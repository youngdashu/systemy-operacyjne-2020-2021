#include<stdlib.h>
#include<stdio.h>

#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>

#include<string.h>

#include<sys/times.h>

#define MAX_LINE_LEN 257

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


void lib(char* file1Name, char* specialCharacter){

    FILE * file1 = NULL;


    file1 = fopen(file1Name ,"r");


    char* file1Line = calloc(MAX_LINE_LEN, sizeof(char));


    int summedOffset = 0;

    while( 1 ){

        int resOfRead = fread(file1Line, sizeof(char), MAX_LINE_LEN, file1);

        if(resOfRead == 0){
            break;
        }

        int countToNextLine = count(file1Line);

        if (countToNextLine == -1){
            printf("nie znaleziono \\n !\n");
            exit(EXIT_FAILURE);
        }

        summedOffset += (countToNextLine + 1);

        fseek(file1, summedOffset, 0);

        char* trimmedLine = strdup(strtok(file1Line, "\n"));

        if (strchr(trimmedLine, *specialCharacter) != NULL){

            printf("%s\n", trimmedLine);            

        }

        memset(file1Line, 0, MAX_LINE_LEN*sizeof(char) );

        free(trimmedLine);

    }


    free(file1Line);

    fclose(file1);

}

void sys(char* file1Name, char* specialCharacter){

    int file1;


    file1 = open(file1Name , O_RDONLY);


    char* file1Line = calloc(MAX_LINE_LEN, sizeof(char));


    int summedOffset = 0;

    while( 1 ){

        int resOfRead = read(file1, file1Line,  sizeof(char)*MAX_LINE_LEN);

        if(resOfRead == 0){
            break;
        }



        int countToNextLine = count(file1Line);

        if (countToNextLine == -1){
            printf("nie znaleziono \\n !\n");
            exit(EXIT_FAILURE);
        }

        summedOffset += (countToNextLine + 1);

        lseek(file1, sizeof(char) * summedOffset, SEEK_SET);

        char* trimmedLine = strdup(strtok(file1Line, "\n"));

        if (strchr(trimmedLine, *specialCharacter) != NULL){

            printf("%s\n", trimmedLine);            

        }

        memset(file1Line, 0, MAX_LINE_LEN*sizeof(char) );

        free(trimmedLine);

    }


    free(file1Line);

    close(file1);

}

int main(int argc, char* argv[]){

    if (argc < 2){
        printf("za malo argumentow\n");
        exit(EXIT_FAILURE);
    }

    char* specialChar = strdup(argv[1]);

    char* fileName = strdup(argv[2]);

    if(strlen(specialChar) != 1){
        printf("podano zly znak!\n");
        exit(EXIT_FAILURE);
    }
    
    if(argc == 4 && strcmp(argv[3], "test") == 0){

        FILE * raport = fopen("pomiar_zad_2_tmp.txt", "w");

        long int ticks_per_second = sysconf(_SC_CLK_TCK);

        int timeStart, timeEnd;

        double cpuTime, userTime;

        struct tms *start, *end;

        start = calloc(1, sizeof(struct tms));
        end = calloc(1, sizeof(struct tms));

        fprintf(raport, "Wariant lib\n\n");

        timeStart = times(start);

        lib(fileName, specialChar);

        timeEnd = times(end);

        cpuTime = (double) (end->tms_stime - start->tms_stime)/ticks_per_second;
        userTime = (double) (end->tms_utime - start->tms_utime)/ticks_per_second;

        fprintf(raport, "Czas dzialania: rzeczywisty: %lf uzytkownika %lf CPU %lf \n\n", (double) (timeEnd - timeStart) / ticks_per_second, userTime, cpuTime );

        fprintf(raport, "Wariant sys\n\n");

        timeStart = times(start);

        sys(fileName, specialChar);

        timeEnd = times(end);

        cpuTime = (double) (end->tms_stime - start->tms_stime)/ticks_per_second;
        userTime = (double) (end->tms_utime - start->tms_utime)/ticks_per_second;

        fprintf(raport, "Czas dzialania: rzeczywisty: %lf uzytkownika %lf CPU %lf \n\n", (double) (timeEnd - timeStart) / ticks_per_second, userTime, cpuTime );

        free(start);
        free(end);

        fclose(raport);


    } else{

        lib(fileName, specialChar);

    }

    free(fileName);
    free(specialChar);
    
}