#include<stdlib.h>
#include<stdio.h>

#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>

#include<string.h>

#include<sys/times.h>

#include<math.h>

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


void lib(char* file1Name){

    FILE * file1 = fopen(file1Name, "r");

    FILE * a = fopen("a.txt", "w");

    FILE* b = fopen("b.txt", "w");

    FILE *c = fopen("c.txt", "w");


    char* file1Line = calloc(MAX_LINE_LEN, sizeof(char));


    int summedOffset = 0;

    int countEvenNumbers = 0;

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

        char* trimmedLine = calloc(25, sizeof(char));

        strcpy( trimmedLine, strtok(file1Line, "\n"));

        int len = strlen(trimmedLine);

        long liczba = atol(trimmedLine);

        strcat(trimmedLine, "\n");


        if(liczba >= 100){
            liczba /= 10;
            if(liczba % 10 == 0 || liczba % 10 == 7){
                fwrite(trimmedLine, sizeof(char), strlen(trimmedLine), b);
            }
        } else if(liczba >= 70 && liczba < 80){
            fwrite(trimmedLine, sizeof(char), strlen(trimmedLine), b);
        }

        if(liczba % 2 == 0){
            countEvenNumbers++;
        }



        int pierwLiczba = (int) sqrt((double) liczba);

        if(pierwLiczba * pierwLiczba == liczba){
            fwrite(trimmedLine, sizeof(char), len, c);
            fwrite("\n", sizeof(char), 1, c);
        }

        free(trimmedLine);



        memset(file1Line, 0, MAX_LINE_LEN*sizeof(char) );

    }

    char* res = calloc(50 , sizeof(char));

    strcat(res, "Liczb parzystych jest ");

    char* liczbaStr = calloc(20 , sizeof(char));

    sprintf(liczbaStr, "%d.", countEvenNumbers);

    strcat(res, liczbaStr);

    fwrite(res, strlen(res), sizeof(char), a);


    free(res);

    free(liczbaStr);

    free(file1Line);

    fclose(file1);

    fclose(a);

    fclose(b);

    fclose(c);

}

void sys(char* file1Name){

    int file1 = open(file1Name, O_RDONLY);

    int a = open("a.txt", O_WRONLY);

    int b = open("b.txt", O_WRONLY);

    int c = open("c.txt", O_WRONLY);


    char* file1Line = calloc(MAX_LINE_LEN, sizeof(char));


    int summedOffset = 0;

    int countEvenNumbers = 0;

    while( 1 ){

        int resOfRead = read(file1, file1Line, sizeof(char)*MAX_LINE_LEN);

        if(resOfRead ==  0){
            break;
        }

        int countToNextLine = count(file1Line);

        if (countToNextLine == -1){
            printf("nie znaleziono \\n !\n");
            exit(EXIT_FAILURE);
        }

        summedOffset += (countToNextLine + 1);

        lseek(file1, summedOffset, 0);

        char* trimmedLine = calloc(25, sizeof(char));

        strcpy( trimmedLine, strtok(file1Line, "\n"));


        long liczba = atol(trimmedLine);

        strcat(trimmedLine, "\n");

        if(liczba >= 100){
            liczba /= 10;
            if(liczba % 10 == 0 || liczba % 10 == 7){
                write(b, trimmedLine, sizeof(char) * strlen(trimmedLine) );
            }
        } else if(liczba >= 70 && liczba < 80){
            write(b, trimmedLine, sizeof(char) * strlen(trimmedLine) );
        }

        if(liczba % 2 == 0){
            countEvenNumbers++;
        }

        long pierwLiczba = (long) sqrt((double) liczba);

        if(pierwLiczba * pierwLiczba == liczba){
            write(c, trimmedLine, sizeof(char) * strlen(trimmedLine) );
        }



        memset(file1Line, 0, MAX_LINE_LEN*sizeof(char) );

    }

    char* res = calloc(50 , sizeof(char));

    strcat(res, "Liczb parzystych jest ");

    char* liczbaStr = calloc(20 , sizeof(char));

    sprintf(liczbaStr, "%d.", countEvenNumbers);

    strcat(res, liczbaStr);

    write(a, res, strlen(res) * sizeof(char));


    free(res);

    free(liczbaStr);

    free(file1Line);

    close(file1);

    close(a);

    close(b);

    close(c);

}

int main(int argc, char* argv[]){

    if (argc < 2){
        printf("za malo argumentow\n");
        exit(EXIT_FAILURE);
    }

    char* fileName = strdup(argv[1]);
    
    if(argc == 3 && strcmp(argv[2], "test") == 0){


        FILE * raport = fopen("pomiar_zad_3.txt", "w");

        long int ticks_per_second = sysconf(_SC_CLK_TCK);

        int timeStart, timeEnd;

        double cpuTime, userTime;

        struct tms *start, *end;

        start = calloc(1, sizeof(struct tms));
        end = calloc(1, sizeof(struct tms));

        fprintf(raport, "Wariant lib\n\n");

        timeStart = times(start);

        lib(fileName);

        timeEnd = times(end);

        cpuTime = (double) (end->tms_stime - start->tms_stime)/ticks_per_second;
        userTime = (double) (end->tms_utime - start->tms_utime)/ticks_per_second;

        fprintf(raport, "Czas dzialania: rzeczywisty: %lf uzytkownika %lf CPU %lf \n\n", (double) (timeEnd - timeStart) / ticks_per_second, userTime, cpuTime );

        fprintf(raport, "Wariant sys\n\n");

        timeStart = times(start);

        sys(fileName);

        timeEnd = times(end);

        cpuTime = (double) (end->tms_stime - start->tms_stime)/ticks_per_second;
        userTime = (double) (end->tms_utime - start->tms_utime)/ticks_per_second;

        fprintf(raport, "Czas dzialania: rzeczywisty: %lf uzytkownika %lf CPU %lf \n\n", (double) (timeEnd - timeStart) / ticks_per_second, userTime, cpuTime );

        free(start);
        free(end);

        fclose(raport);


    } else{

        lib(fileName);

    }    

    free(fileName);
}