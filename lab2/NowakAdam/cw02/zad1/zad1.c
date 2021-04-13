#include<stdlib.h>
#include<stdio.h>

#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>

#include<string.h>

#include<sys/times.h>

#define MAX_LINE_LEN 110

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


void lib(char* file1Name, char* file2Name){

    FILE * file1 = NULL;
    FILE * file2 = NULL;

    if(strcmp(file1Name, "") == 0 && strcmp(file2Name, "") == 0 ){
        
    file1 = fopen("zad1atest.txt" ,"r");
    file2 = fopen("zad1btest.txt", "r");

    }
    else{

        file1 = fopen(file1Name ,"r");
        file2 = fopen(file2Name, "r");

    }

    char* file1Line = calloc(MAX_LINE_LEN, sizeof(char));
    char* file2Line = calloc(MAX_LINE_LEN, sizeof(char));

    int flag1 = 1;
    int flag2 = 1;

    int offset1 = 0;
    int offset2 = 0;

    while( 1 ){


        if ( fread(file1Line, sizeof(char), MAX_LINE_LEN, file1) == 0 ){

            flag1 = 0;

        }

        if ( fread(file2Line, sizeof(char), MAX_LINE_LEN, file2) == 0 ){

            flag2 = 0;

        }

        int count1 = count(file1Line);
        int count2 = count(file2Line);

        if(flag1 && file1Line != NULL){

           printf("%.*s", count1+1, file1Line);


        }

        if(flag2 && file1Line != NULL){

            printf("%.*s", count2+1, file2Line);

        }


        if(flag1 == 0 && flag2 == 0){

            break;

        }

        offset1 += (count1 + 1);
        offset2 += (count2 + 1);

        fseek(file1, offset1, 0 );
        fseek(file2, offset2, 0);

        memset(file1Line, 0, MAX_LINE_LEN*sizeof(char) );
        memset(file2Line, 0, MAX_LINE_LEN*sizeof(char) );


    }


    free(file1Line);
    free(file2Line);


    fclose(file1);
    fclose(file2);


}

void sys(char* file1Name, char* file2Name){

    int file1;
    int file2;

    if(strcmp(file1Name, "") == 0 && strcmp(file2Name, "") == 0 ){
        
        file1 = open("zad1atest.txt" , O_RDONLY);
        file2 = open("zad1btest.txt", O_RDONLY);

    }
    else{

        file1 = open(file1Name, O_RDONLY);
        file2 = open(file2Name, O_RDONLY);

    }

    char* file1Line = calloc(MAX_LINE_LEN, sizeof(char));
    char* file2Line = calloc(MAX_LINE_LEN, sizeof(char));

    int flag1 = 1;
    int flag2 = 1;

    int offset1 = 0;
    int offset2 = 0;

    while( 1 ){


        if ( read(file1, file1Line, sizeof(char) * MAX_LINE_LEN) == 0 ){

            flag1 = 0;

        }

        if ( read(file2, file2Line, sizeof(char) * MAX_LINE_LEN) == 0 ){

            flag2 = 0;

        }

        int count1 = count(file1Line);
        int count2 = count(file2Line);

        if(flag1 && file1Line != NULL){

           printf("%.*s", count1+1, file1Line);


        }

        if(flag2 && file1Line != NULL){

            printf("%.*s", count2+1, file2Line);

        }


        if(flag1 == 0 && flag2 == 0){

            break;

        }

        offset1 += (count1 + 1);
        offset2 += (count2 + 1);

        lseek(file1, offset1, SEEK_SET);
        lseek(file2, offset2, SEEK_SET);

        memset(file1Line, 0, MAX_LINE_LEN*sizeof(char) );
        memset(file2Line, 0, MAX_LINE_LEN*sizeof(char) );


    }


    free(file1Line);
    free(file2Line);


   close(file1);
   close(file2);


}

int main(int argc, char* argv[]){

    int argNum = 1;

    while (argNum < argc)
    {
        
        if(strcmp(argv[argNum], "test") == 0){

            FILE * raport = fopen("raport_zad_1_tmp.txt", "w");

            long int ticks_per_second = sysconf(_SC_CLK_TCK);

            int timeStart, timeEnd;

            double cpuTime, userTime;

            struct tms *start, *end;

            start = calloc(1, sizeof(struct tms));
            end = calloc(1, sizeof(struct tms));

            fprintf(raport ,"Wariant lib\n\n");

            timeStart = times(start);

            lib("", "");

            timeEnd = times(end);

            cpuTime = (double) (end->tms_stime - start->tms_stime)/ticks_per_second;
            userTime = (double) (end->tms_utime - start->tms_utime)/ticks_per_second;

            fprintf(raport, "Czas dzialania: rzeczywisty: %lf uzytkownika %lf CPU %lf \n\n", (double) (timeEnd - timeStart) / ticks_per_second, userTime, cpuTime );

            fprintf(raport ,"Wariant sys\n\n");

            timeStart = times(start);

            sys("", "");

            timeEnd = times(end);

            cpuTime = (double) (end->tms_stime - start->tms_stime)/ticks_per_second;
            userTime = (double) (end->tms_utime - start->tms_utime)/ticks_per_second;

            fprintf(raport, "Czas dzialania: rzeczywisty: %lf uzytkownika %lf CPU %lf \n\n", (double) (timeEnd - timeStart) / ticks_per_second, userTime, cpuTime );

            free(start);
            free(end);

            fclose(raport);


        } else if(strcmp(argv[argNum], "merge_files") == 0){

            if(argNum + 1 == argc){

                sys("", "");

            } else{
            
                char * file1Name = strdup(argv[++argNum]);
                char* file2Name = strdup(argv[++argNum]);

                lib(file1Name, file2Name);

                free(file1Name);
                free(file2Name);

            }
            

        }

        ++argNum;

    }
    




    
}