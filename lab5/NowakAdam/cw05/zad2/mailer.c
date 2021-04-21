#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<ctype.h>
#include<sys/wait.h>

void error(char* msg){
    perror(msg);
    exit(EXIT_FAILURE);
}

void case_nadawca(){
    FILE* f = popen("echo q | mail | sort -k 3", "w");
    if(f == NULL){
        error("nadawca err");
    }
    pclose(f);
}

void case_data(){
    FILE* f = popen("echo q | mail | sort -M", "w");
    if(f == NULL){
        error("data err");
    }
    pclose(f);
}

void case_send(char* email, char* mailTitle, char* content){

    char* command = calloc(1000, sizeof(char));

    strcat(command, "mail -s \"");
    strcat(command, mailTitle);
    strcat(command, "\" ");
    strcat(command, email);
    strcat(command, " <<< \"");
    strcat(command, content);
    strcat(command, "\"");

    printf("%s\n", command);

    FILE * f = popen(command, "r");
    pclose(f);

}

int main(int argc, char* argv[]){

    char* address;
    char* mailTitle;
    char* mailContent;

    if(argc == 2){

        if(strcmp(argv[1], "nadawca") == 0){
            
            case_nadawca();

        } else if(strcmp(argv[1], "data") == 0){
            
            case_data();

        } else{
            error("bledny argument\n");
        }

    } else if (argc == 4){

        address = argv[1];
        mailTitle = argv[2];
        mailContent = argv[3];

        case_send(address, mailTitle, mailContent);

    } else{
        error("zla liczba argumentow\n");
    }



}