#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<pthread.h>

#include<sys/times.h>

void error(char* msg){
    perror(msg);
    exit(EXIT_FAILURE);
}

int **image;
int **outImage;

typedef struct imageSize{
    int width;
    int height;
}imageSize;

imageSize imgS;

int * frequencies;
int* blockRangeStart;
int* blockRangeEnd;


void readFile(char* fileName){

    FILE * input = fopen(fileName, "r");

    int width, height;
    width = height = -1;

    size_t n;
    char* line = NULL;
    n = 0;
    // get first line
    getline(&line, &n, input);
    printf("%s", line);

    line = NULL;
    n = 0;
    getdelim(&line, &n, ' ', input);
    width = atoi(line);

    line = NULL;
    n = 0;
    getline(&line, &n, input);
    line[strlen(line)-1] = '\0';

    height = atoi(line);

    line = NULL;
    n = 0;
    getline(&line, &n, input);

    printf("width: %i height: %i\n", width, height);

    int currentPixel;
    image = (int**) calloc(height, sizeof(int*));
    

    for(int row=0; row <height; row++){
        image[row] = (int*) calloc(width, sizeof(int));
        for(int column = 0; column < width; column++){
            line = NULL;
            n = 0;

            if(column == width-1){
                getline(&line, &n, input);
            } else{
                getdelim(&line, &n, ' ', input);

                while(line[0] == ' '){
                line = NULL;
                n = 0;
                getdelim(&line, &n, ' ', input);
                }
            }
            currentPixel = atoi(line);
            ++frequencies[currentPixel];
            image[row][column] = currentPixel;   
        }   
    }
    fclose(input);
    imgS.width = width;
    imgS.height = height;
    return;
}

void saveFile(char* fileName){
    FILE * output = fopen(fileName, "w+");
    fputs("PA\n", output);
    fprintf(output, "%i %i\n%i\n", imgS.width, imgS.height, 255);
    int width = imgS.width - 1;
    for(int row = 0; row < imgS.height; row++){
        for(int column = 0; column < width; column++){
            fprintf(output, "%i ", outImage[row][column]);
        }

        fprintf(output, "%i", outImage[row][width]);
        if(row != imgS.height - 1){
            fprintf(output, "\n");
        }
    }
    fclose(output);
    return;
}

void* negateBlock(void* index){

    struct tms measureTime;
    clock_t endTime, startTime;
    startTime = times(&measureTime);

    int start = blockRangeStart[*((int*)index)];
    int end = blockRangeEnd[*((int*)index)];

    for(int row = 0; row < imgS.height; row++){
        for(int column = 0; column<imgS.width; column++){
            if(image[row][column] <= end && start >= image[row][column]){
                outImage[row][column] = 255 - image[row][column];
            }
        }
    }
    endTime = times(&measureTime) - startTime;

    pthread_exit(&endTime);

}

void block(int n, char* outputFileName){

    int numOfPixels = imgS.height * imgS.width;
    blockRangeStart = calloc(n, sizeof(int));
    blockRangeEnd = calloc(n, sizeof(int));

    int start = 0;
    int end = 256;

    void *threadExecutionTime;

    clock_t totalTime = 0;
    clock_t startTime = 0;
    struct tms measureTime;
    

    int freqPerThread = numOfPixels/n;
    int * threadNums = calloc(n, sizeof(int));

    for(int threadNum = 0; threadNum < n; threadNum++){

        int currentThreadFreq = freqPerThread;
        blockRangeStart[threadNum] = start;

        for(int currentStart = start; currentStart < end; currentStart++){

            currentThreadFreq -= frequencies[currentStart];

            if(currentThreadFreq < 0){
                blockRangeEnd[threadNum] = currentStart-1;
                if(blockRangeEnd[threadNum] < blockRangeStart[threadNum]){
                    blockRangeEnd[threadNum] = blockRangeStart[threadNum];
                    start+=1;
                }
                break;
            }
        }
        threadNums[threadNum] = threadNum;
    }
    printf("after for end: %i\n", end-1);
    blockRangeEnd[n-1] = end-1;
    printf("blockrangeend: %i\n", blockRangeEnd[n-1]);

    /////////////////
    for(int i=0; i<n; i++){
        printf("i: %i\nstart: %i end: %i\n", i, blockRangeStart[i], blockRangeEnd[i]);
    }
    ///////////////////

    startTime = times(&measureTime);

    pthread_t *threadIds = calloc(n, sizeof(pthread_t));

    int threadCreateRes, threadJoinRes;

    for(int i=0; i<n; i++){

        threadCreateRes = pthread_create(&threadIds[i], NULL, &negateBlock, &threadNums[i]);
        if(threadCreateRes<0){
            error("thread create err");
        }
        
    }

    totalTime = times(&measureTime) - startTime;


    for(int i=0; i<n; i++){

        threadJoinRes = pthread_join(threadIds[i], &threadExecutionTime);

        if(threadJoinRes < 0){
            error("thread join errr");
        }

        totalTime += *((clock_t*) threadExecutionTime);
    }    

    printf("Time:\n%li\n", totalTime);
    
    saveFile(outputFileName);

    return;
}

int main(int argc, char* argv[]){

    if(argc != 5){
        error("Zla liczba argumentow");
    }

    int threadNum = atoi(argv[1]);
    char* inputFileName = argv[3];
    char* outputFileName = argv[4];

    frequencies = (int*) calloc(256, sizeof(int));
    readFile(inputFileName);

    outImage = (int**) calloc(imgS.height, sizeof(int*));
    for(int i =0; i<imgS.height; i++) outImage[i] = (int*) calloc(imgS.width, sizeof(int));

    if(strcmp(argv[2], "numbers") == 0){

    } else if(strcmp(argv[2], "block") == 0){
        
        block(threadNum, outputFileName);

    } else{
        error("illegal argument");
    }

    return 0;
}