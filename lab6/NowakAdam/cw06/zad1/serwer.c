#include "commonData.h"

typedef struct clientStruct{

    int q;
    int available;

}clientStruct;

int sqID;
clientStruct *clients[10] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
int activeClients;

void endWork(){

    for(int i = 0; i < 10; i++){

        if(clients[i] != NULL){

            mymsg msgToSnd;
            msgToSnd.mtype = SERVER_ENDS_WORK;
            int clientQueue = clients[i]->q;

            mymsg msgToRcv;

            msgsnd(clientQueue, &msgToSnd, msgSize, 0);
            msgrcv(sqID, &msgToRcv, msgSize, SERVER_ENDS_WORK, 0);

            free(clients[i]);

        }

    }

    msgctl(sqID, IPC_RMID, NULL);

    exit(EXIT_SUCCESS);


}

void handleSigint(int signo){

    if(signo == SIGINT){

        endWork();

    }

}


void receiveMessage(mymsg* msgToRcv){

    int res = -1;

    res = msgrcv(sqID, msgToRcv, msgSize, STOP, IPC_NOWAIT);


    if(res == -1) {
        res = msgrcv(sqID, msgToRcv, msgSize, DISCONNECT, IPC_NOWAIT);
        
    }

    if(res == -1) {
        res = msgrcv(sqID, msgToRcv, msgSize, LIST, IPC_NOWAIT);
    
    }

    if(res == -1){
        res = msgrcv(sqID, msgToRcv, msgSize, 0, 0);
    }

    // return msgToRcv;

}

void stop(mymsg* msgToProcess){

    int clientStoppingWork = msgToProcess->clientID;

    free(clients[clientStoppingWork]);

    activeClients--;



}

void disconnect(mymsg* msgToProcess){

    int clientToMakeAvailable = msgToProcess->clientID;

    clients[clientToMakeAvailable]->available = 1;
    
}

void connect(mymsg* msgToProcess){

    char* ptr;
    int clientToConnectTo = (int)strtol((msgToProcess->mtext), &ptr, 10);
    int clientConnecting = msgToProcess->clientID;

    mymsg returnMsg;
    

    char toAppend[40];

    if(clients[clientToConnectTo]->available == 1 && clients[clientConnecting]->available == 1){

        sprintf(toAppend, "success connecting %i to %i\n", clientConnecting, clientToConnectTo);
        strcat(returnMsg.mtext, toAppend);
        returnMsg.mtype = RETURN_SUCCESS_CONNECTED;

    } else{

        sprintf(toAppend, "error connecting\n");
        strcat(returnMsg.mtext, toAppend);
        returnMsg.mtype = RETURN_FAIL;

    }

    msgsnd(clients[clientConnecting]->q, &returnMsg, msgSize, 0);
    msgsnd(clients[clientToConnectTo]->q, &returnMsg, msgSize, 0);
    
}

void list(mymsg* msgToProcess){

    mymsg msgToSendToClient;
    int qClientToSend = clients[msgToProcess->clientID]->q;
    // msgToSendToClient.mtext
    
    char toAppend[30];

    for(int i=0; i < 10; i++){
        if(clients[i] != NULL){
            if(clients[i]->available){
                printf("Klient %i jest dostepny\n", i);
                sprintf(toAppend, "Klient %i jest dostepny\n", i);
            } else{
                printf("Klient %i nie jest dostepny\n", i);
                sprintf(toAppend, "Klient %i jest dostepny\n", i);
            }
            strcat(msgToSendToClient.mtext, toAppend);
        }
    }

    msgsnd(qClientToSend, &msgToSendToClient, msgSize, 0);

}

void init(mymsg* msgToProcess){

    char* ptr;
    long cqID = strtol((msgToProcess->mtext), &ptr, 10);

    int i = 0;
    for(i = 0; i < 10; i++){
        if(clients[i] == NULL){
            break;
        }
    }

    clientStruct *clientToAdd = calloc(1, sizeof(clientStruct));
    clientToAdd->q = cqID;
    clientToAdd->available = 1;

    clients[i] = clientToAdd;

    if(activeClients == -1){
        activeClients += 2;
    } else{
        activeClients++;
    }

}

void processMessage(mymsg* msgToProcess){
    switch(msgToProcess->mtype){
    case STOP:
        stop(msgToProcess);
        break;
    case DISCONNECT:
        disconnect(msgToProcess);
        break;
    case CONNECT:
        connect(msgToProcess);
        break;
    case LIST:
        list(msgToProcess);
        break;
    case INIT:
        init(msgToProcess);
        break;
    default:
        break;
    }
}
    





int main(int argc, char* argv[]){

    // for(int i = 0; i < 10; i++){
    //     clients[i] = NULL;
    // }

    // stworz kolejke komunikatow
    key_t serverKey = ftok("/usr/bin", 0);
    sqID = msgget(serverKey, IPC_CREAT | IPC_EXCL);
    if(sqID == -1) error("server queue creation failed");

    activeClients = -1;

    while(1){


        mymsg msgToRcv;
        
        receiveMessage(&msgToRcv);

        if(activeClients == 0){
            // endWork();
            break;
        } 

    }

    endWork();

    return 0;

}

