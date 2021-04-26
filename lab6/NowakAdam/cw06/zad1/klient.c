#include "commonData.h"

int serverQueueId = -1;
int cqID = -1;
int clientID = -1;
int sqid = -1;

int connectedTo = -1;




int connectWithServer(int cqID){

    int clientid = -1;

    key_t skey = ftok("/etc/passwd", MAXMSGLEN);
    sqid = msgget(skey, 0);
    if(sqid < 0) error("cannot connect to servers queue");
    
    mymsg msgToSnd;
    msgToSnd.mtype = INIT;
    
    sprintf((msgToSnd.mtext), "%i", cqID);
    mymsg msgToRcv;

    if(msgsnd(sqid, &msgToSnd, msgSize, 0) < 0)
        error("connectWithServer msgsnd");
    
    if(msgrcv(cqID, &msgToRcv, msgSize, 0, 0) < 0)
        error("connectWithServer msgrcv");
    
    char* ptr;
    clientid = (int) strtol(msgToRcv.mtext, &ptr, 10);

    printf("client id : %i\n", clientid);

    return clientid;

}

void stop(){

    mymsg msgToSnd;
    msgToSnd.mtype = STOP;
    msgToSnd.clientID = clientID;

    msgsnd(sqid, &msgToSnd, msgSize, 0);

    msgctl(cqID, IPC_RMID, NULL);

    exit(EXIT_FAILURE);

}

void disconnect(){

    mymsg msgToSnd;
    msgToSnd.mtype = DISCONNECT;
    msgToSnd.clientID = clientID;

    msgsnd(sqid, &msgToSnd, msgSize, 0);

    connectedTo = -1;

}

void connect(char* clientToConnect){

    mymsg msgToSnd;
    msgToSnd.mtype = CONNECT;
    msgToSnd.clientID = clientID;

    mymsg returnMsg;

    strcat((msgToSnd.mtext), clientToConnect);

    msgsnd(sqid, &msgToSnd, msgSize, 0);

    msgrcv(cqID, &returnMsg, msgSize, 0, 0);

    printf("%s", returnMsg.mtext);

    if(returnMsg.mtype == RETURN_SUCCESS_CONNECTED){

        connectedTo = atoi(clientToConnect);

    } else if(returnMsg.mtype == RETURN_FAIL){

        return;

    } else{
        printf("error: wrong message received: %i\n", (int)returnMsg.mtype);
    }

    return;

}

void list(){

    mymsg msgToSnd;
    msgToSnd.mtype = LIST;
    msgToSnd.clientID = clientID;

    msgsnd(sqid, &msgToSnd, msgSize, 0);
}

void do_action(char* typeOfAction){

    if(strcmp(typeOfAction, "STOP") == 0){
        
        stop();

    } else if(strcmp(typeOfAction, "DISCONNECT") == 0){

        disconnect();

    } else if(strcmp(typeOfAction, "CONNECT") == 0){

        char* clientToConnectToIdStr = strtok(NULL, " ");
        if(clientToConnectToIdStr == NULL){
            printf("brak klient id\n");
            return;
        }
        // char* ptr;
        // long clientToConnectToId = strtol(clientToConnectToIdStr, &ptr, 10);
        connect(clientToConnectToIdStr);

    } else if(strcmp(typeOfAction, "LIST") == 0){

        list();

    } else{
        error("unknown action type");
    }

}

void processReceivedMessage(mymsg *msgToProcess){

    if(msgToProcess->mtype == SERVER_ENDS_WORK){

        mymsg msgToSnd;
        msgToSnd.mtype = SERVER_ENDS_WORK;
        msgsnd(sqid, &msgToSnd, msgSize, 0);
        msgctl(cqID, IPC_RMID, NULL);

        exit(EXIT_FAILURE);

    }

}

void hangleSigint(int signo){

    if(signo == SIGINT){

        stop();

    }

}



int main(int argc, char* argv[]){

    signal(SIGINT, hangleSigint);

    // kolejka klienta
    key_t key = ftok("/etc/passwd", getpid());
    cqID = msgget(key, IPC_CREAT | IPC_EXCL);
    if(cqID == -1) error("client queue create error");

    clientID = connectWithServer(cqID);

    fd_set readSet;
    FD_ZERO(&readSet);
    FD_SET(STDIN_FILENO, &readSet);

    char* line;

    while(1){

        line = NULL;
        long unsigned len; // , lineSize;

        mymsg msgToRcv;

        int selectRes = select(STDIN_FILENO+1, &readSet, NULL, NULL, NULL);

        if(selectRes == -1){
            error("select error");
        } else if(selectRes == 1){

        

            getline(&line, &len, stdin);
            char* tmpLine; // , *toTok;
            //tmpLine = toTok = line;
            tmpLine = line;
            // toTok = line;

            char* type = strtok(line, " ");

            if(strcmp(type, "STOP") == 0){
                free(tmpLine);
                stop();
            }

            do_action(type);

            free(tmpLine);

        }

        msgrcv(sqid, &msgToRcv, msgSize, 0, IPC_NOWAIT);

        processReceivedMessage(&msgToRcv);
    
    return 0;
    


    }





    
    



}

