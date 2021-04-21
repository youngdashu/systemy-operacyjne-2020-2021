#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<ctype.h>
#include<sys/wait.h>

typedef struct listOfElements{

    char* element;
    struct listOfElements* nextElement;

}listOfElements;

typedef struct elementsAndOrders{

    listOfElements* elements;
    listOfElements* orders;
    int numOfElements;
    int numOfOrders;

}elementsAndOrders;

typedef struct argsAndArgNum{

    char** args;
    int numberOfArgs;

}argsAndArgNum;

void error(char* msg){
    perror(msg);
    exit(EXIT_FAILURE);
}

void freeListOfElements(listOfElements* head){

    listOfElements* tmp;

    while (head->nextElement != NULL)
    {   
        tmp = head;
        if(head->element != NULL){
            free(head->element);
        }
        head = head->nextElement;
        free(tmp);
    }
    
    return;
}

listOfElements* getNthElement(int n, listOfElements* elementsHead){

    if(n < 1){
        printf("zle n\n");
        exit(EXIT_FAILURE);
    }

    listOfElements* tmp = elementsHead;

    int i = 0;

    while (i < n )
    {
        tmp = tmp->nextElement;

        if(tmp == NULL){
            error("lista skladnikow zepsuta");
        }
        i++;
    }

    return tmp;
    
}

elementsAndOrders* readFile(char * pathToFile){

    FILE* fileWithOrders = fopen(pathToFile, "r");

    char* line = calloc(200, sizeof(char));

    listOfElements* elementsHead = calloc(1, sizeof(listOfElements));

    elementsHead->element=NULL;

    listOfElements* tmp = elementsHead;

    listOfElements* ordersHead = calloc(1, sizeof(listOfElements));
    ordersHead->element = NULL;

    listOfElements* tmpOrders = ordersHead;

    elementsAndOrders* res = calloc(1, sizeof(elementsAndOrders));

    while (1)
    {
        char* resOfFgets = fgets(line, 200, fileWithOrders);

        if(resOfFgets==NULL){
            break;
        }

        char* ptrToEqualsSign = strstr(line , "=");

        if(ptrToEqualsSign != NULL){
            
            ptrToEqualsSign+=2;

            char* ptr;
            if( (ptr = strchr(ptrToEqualsSign, '\n')) != NULL)
                *ptr = '\0';

            listOfElements* newElement = calloc(1, sizeof(listOfElements));
            newElement->nextElement = NULL;
            newElement->element = strdup(ptrToEqualsSign);

            tmp->nextElement = newElement;
            tmp = newElement;

            res->numOfElements++;

        } else{

            listOfElements* newOrder = calloc(1, sizeof(listOfElements));
            newOrder->nextElement = NULL;
            newOrder->element = strdup(line);

            tmpOrders->nextElement = newOrder;
            tmpOrders = newOrder;


            res->numOfOrders++;

        }

        memset(line, '\0', 200*sizeof(char));

    }

    free(line);
    fclose(fileWithOrders);

    res->elements = elementsHead;
    res->orders = ordersHead;

    return res;
    
}

int getNumberFromElement(char* element){

    int i =0;
    while (isdigit(element[i])==0)
    {
        i++;
    }

    return (int)element[i]-48;
    
}

argsAndArgNum* getArgs(char* commandToExecuteWithArgs){

    argsAndArgNum* res = calloc(1, sizeof(argsAndArgNum));

    char* tmpCommandToExecuteWithArgs; 
    if(commandToExecuteWithArgs[0]==' '){
        tmpCommandToExecuteWithArgs = calloc(strlen(commandToExecuteWithArgs)+1, sizeof(char));\
        memcpy(tmpCommandToExecuteWithArgs, commandToExecuteWithArgs+1, (strlen(commandToExecuteWithArgs)-1) * sizeof(char));

    } else{
        
        tmpCommandToExecuteWithArgs = strdup(commandToExecuteWithArgs);
    }

    int numberOfArgs = 0;
    for(int i = 0; tmpCommandToExecuteWithArgs[i]; i++){
        if(tmpCommandToExecuteWithArgs[i] == *" "){
            numberOfArgs++;
        }
    }

    char** args = calloc(numberOfArgs + 2, sizeof(char*));
    char* commandName = strtok(tmpCommandToExecuteWithArgs, " ");

    args[0] = strdup(commandName);

    res->numberOfArgs = numberOfArgs;

    int argNum = 1;
    while(numberOfArgs){
        
        commandName = strdup(strtok(NULL, " "));

        args[argNum] = commandName;

        argNum++;
        numberOfArgs--;
    }
    args[res->numberOfArgs+1] = NULL;

    res->args = args;

    free(tmpCommandToExecuteWithArgs);

    return res;
}


int main(int argc, char* argv[]){

    if(argc!=2){
        error("zla liczba argumentow");
    }

    elementsAndOrders* elemsAndOrders = readFile(argv[1]);
    listOfElements * elementsHead = elemsAndOrders->elements;
    listOfElements * ordersHead = elemsAndOrders->orders;

    int numOfOrders = elemsAndOrders->numOfOrders;
    free(elemsAndOrders);

    int currentOrderNumber = 0;

    while (currentOrderNumber < numOfOrders)
    {     
        currentOrderNumber++;

        listOfElements* currentOrder = getNthElement(currentOrderNumber, ordersHead);

        char* orders = strdup(currentOrder->element);
        char* FREEorders = orders;

        int numOfElementsInOrder = 1;
        for(int i = 0; orders[i]; i++){
            numOfElementsInOrder += (orders[i] == '|');
        }
        char* allElementsCommandsInCurrentOrder = calloc(400, sizeof(char));

        int currentElementnumber;
        char* elementCommand;
        char* currentElement;

        if (numOfElementsInOrder > 1){

            currentElement = strtok(orders, " | ");
            
            while(currentElement != NULL){

                currentElementnumber = getNumberFromElement(currentElement);

                listOfElements* structElementCommand;
                structElementCommand = getNthElement(currentElementnumber, elementsHead);

                elementCommand = structElementCommand->element;

                strcat(allElementsCommandsInCurrentOrder, elementCommand);
                strcat(allElementsCommandsInCurrentOrder, " | ");

                currentElement = strtok(NULL, " | ");
            }

        } else{

            currentElement = orders;
            currentElementnumber = getNumberFromElement(currentElement);

            listOfElements* structElementCommand;
            structElementCommand = getNthElement(currentElementnumber, elementsHead);
            elementCommand = structElementCommand->element;

            strcat(allElementsCommandsInCurrentOrder, elementCommand);
            strcat(allElementsCommandsInCurrentOrder, " | ");
        }

        free(FREEorders);
        
        if(vfork()==0){

            int numOfProcessesToLaunch = 0;
            for(int i = 0; allElementsCommandsInCurrentOrder[i]; i++){
                numOfProcessesToLaunch += (allElementsCommandsInCurrentOrder[i] == '|');
            }

            if (numOfProcessesToLaunch < 1){
                error("za malo procesow");
            }
            else if(numOfProcessesToLaunch==1){

                char* TMPallElementsCommandsInCurrentOrder = strdup(allElementsCommandsInCurrentOrder);

                char* tmpCommandCopy = strtok(allElementsCommandsInCurrentOrder, "|");
                char* commandToExecuteWithArgs = calloc(strlen(tmpCommandCopy), sizeof(char));
                strncpy(commandToExecuteWithArgs, tmpCommandCopy, strlen(tmpCommandCopy)-1);

                argsAndArgNum* argsAndNum = getArgs(commandToExecuteWithArgs);
                char** args = argsAndNum->args;
                int numberOfArgs = argsAndNum->numberOfArgs;

                free(argsAndNum);
                free(commandToExecuteWithArgs);


                if(vfork()==0){
                    execvp(args[0], args);
                    exit(EXIT_SUCCESS);

                } else{

                    for(int i = 0; i < numberOfArgs+2; i++){
                        if(args[i] != NULL)
                            free(args[i]);
                    }
                    free(args);
                    wait(NULL);
                }

                free(TMPallElementsCommandsInCurrentOrder);
        
            }
            else{

                int processCount = 0;

                int fd[2][2];              

                char* TMPallElementsCommandsInCurrentOrder = strdup(allElementsCommandsInCurrentOrder);

                char* tmpCommandCopy = strtok(allElementsCommandsInCurrentOrder, "|");
                char* commandToExecuteWithArgs = calloc(strlen(tmpCommandCopy), sizeof(char));
                strncpy(commandToExecuteWithArgs, tmpCommandCopy, strlen(tmpCommandCopy)-1);

                argsAndArgNum* argsAndNum = getArgs(commandToExecuteWithArgs);
                char** args = argsAndNum->args;
                int numberOfArgs = argsAndNum->numberOfArgs;

                free(argsAndNum);
                free(commandToExecuteWithArgs);
                
                if(pipe(fd[processCount%2]) < 0 ){
                    error("pipe");
                }

                // wywolujemy pierwsze dziecko
                if(vfork() == 0){

                    close(fd[processCount%2][0]);

                    if(dup2(fd[processCount%2][1], STDOUT_FILENO) < 0){
                        error("dup2");
                    }

                    execvp(args[0], args);
                    exit(EXIT_SUCCESS);

                } else{
                    for(int i = 0; i < numberOfArgs+2; i++){
                        if(args[i] != NULL){
                            free(args[i]);
                        }
                    }
                    free(args);
                }

                processCount++;
                
                while(processCount < numOfProcessesToLaunch){

                    close(fd[processCount%2][0]);
                    close(fd[processCount%2][1]);

                    if (pipe(fd[processCount % 2]) < 0){
                        error("pipe");
                    }
                    
                    free(allElementsCommandsInCurrentOrder);
                    allElementsCommandsInCurrentOrder = strdup(TMPallElementsCommandsInCurrentOrder);

                    for(int tokITimes = 0; tokITimes < processCount; tokITimes++){

                        if(tokITimes==0){
                            strtok(allElementsCommandsInCurrentOrder, "|");
                        } else{
                            strtok(NULL, "|");
                        }
                    }

                    tmpCommandCopy = strtok(NULL, "|");

                    commandToExecuteWithArgs = calloc(strlen(tmpCommandCopy), sizeof(char));
                    strncpy(commandToExecuteWithArgs, tmpCommandCopy, strlen(tmpCommandCopy)-1);

                    argsAndNum = getArgs(commandToExecuteWithArgs);
                    args = argsAndNum->args;
                    numberOfArgs = argsAndNum->numberOfArgs;

                    free(argsAndNum);
                    free(commandToExecuteWithArgs);

                    if(vfork() == 0){

                        if(processCount != numOfProcessesToLaunch-1){
                            close(fd[processCount%2][0]);
                            if(dup2(fd[processCount%2][1], STDOUT_FILENO) < 0){
                                error("dup2 stdout");
                            }
                        }

                        close(fd[(processCount+1)%2][1]);
                        if(dup2(fd[(processCount+1)%2][0], STDIN_FILENO) < 0){
                            error("dup2 stdin");
                        }

                        execvp(args[0], args);
                        exit(EXIT_SUCCESS);

                    } else{
                        // wait(NULL);
                        for(int i = 0; i < numberOfArgs+2; i++){
                            if(args[i] != NULL){
                                free(args[i]);
                            }
                        }
                        free(args);
                    }

                    processCount++;
                } // end while

                close(fd[processCount%2][0]);
                close(fd[processCount%2][1]);

                int res, stat;
                while( (res=  wait(&stat) ) > 0);

            }

            exit(EXIT_SUCCESS);

        } else{
            int status;
            wait(&status);
            if(status){
                error("error on status");
            }
        } 

    }

    freeListOfElements(elementsHead);
    freeListOfElements(ordersHead);

}