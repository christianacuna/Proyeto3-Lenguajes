#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <limits.h>
#define NUM_THREADS 4

struct Stack {
    int top;
    unsigned capacity;
    int* array;
};
void deepFirstSearch(void *laberinthInput){

    pthread_exit(NULL);
}
void breedthFirstSearch(void *laberinthInput){
    pthread_exit(NULL);
}
void randomSearch(void *laberinthInput){
    pthread_exit(NULL);
}
void aStarSearch(void *laberinthInput){
    pthread_exit(NULL);
}

int processInput(char laberinthInput[9999]){
    int dimentions[2];
    char *temp = &laberinthInput[1];
    dimentions[0] = atoi(temp);
    temp = &laberinthInput[3];
    dimentions[1] = atoi(temp);
    int matrix[dimentions[0]][dimentions[1]];
    printf("\nDimensions: %d,%d", dimentions[0],dimentions[1]);
    int acum1 = 0;
    int acum3 = 0;
    int i = 5;
    int j = 6;
    //char temp2[2] = {laberinthInput[5], laberinthInput[6]};
    //printf("\n%s",temp2);
    while (acum1 < dimentions[0]){
        int acum2 = 0;
        while (acum2 < dimentions[1]){
            char temp2[2] = {laberinthInput[i], laberinthInput[j]};
            printf("\n %s",temp2);
            matrix[acum1][acum2] = laberinthInput[acum3];
            acum2++;
            acum3++;
            i++;
            j++;
        }
        acum1++;
    }
    printf("\nMatrix: \n%d,\n%d,\n%d,\n%d", matrix[0][0],matrix[1][1],matrix[2][2],matrix[3][3]);
}
int generatePositionMatrix(char laberinthInput[9999]){
    char *temp = &laberinthInput[1];
    int nColums = atoi(temp);
    temp = &laberinthInput[3];
    int nRows = atoi(temp);
    int nElements = nRows*nColums;
    int positionMatrix[nElements][4];
    memset(positionMatrix,-1,sizeof positionMatrix);
    int acum = 0;
    int i = 0;
    int j = 0;
    while(j < nElements){
        int n = laberinthInput[acum];
        positionMatrix[j][n] = n;
    }
}
struct Stack* createStack(unsigned capacity)
{
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}
int isEmpty(struct Stack* stack)
{
    return stack->top == -1;
}

int isFull(struct Stack* stack)
{
    return stack->top == stack->capacity - 1;
}

void push(struct Stack* stack, int item)
{
    if (isFull(stack))
        return;
    stack->array[++stack->top] = item;
}

int pop(struct Stack* stack)
{
    if (isEmpty(stack))
        return INT_MIN;
    return stack->array[stack->top--];
}

int peek(struct Stack* stack)
{
    if (isEmpty(stack))
        return INT_MIN;
    return stack->array[stack->top];
}

void exitRoute(int route){
}

int main(int argc,char* argv[])
{
    int pid;
    pthread_t threads[NUM_THREADS];
    char laberinth[9999];
    int a;
    int counter;
    char input [1024];
    while (1 == scanf("%[^\n]%*C", input)){
        strcat(laberinth,input);
    }
    printf("%s", laberinth);
    char *temp = &laberinth[1];
    int temp2 = atoi(temp);
    int processedInut = processInput(laberinth);
    int resultado1;
    int resultado2;
    int resultado3;
    int resutlado4;
    pid = pthread_create(&threads[0],NULL, deepFirstSearch,(void*)laberinth);
    if(pid) {
            printf("Error Creando DFS");
    }
    pid = pthread_create(&threads[1],NULL, breedthFirstSearch,(void *)laberinth);
    if(pid) {
            printf("Error Creando BFS");
    }
    pid = pthread_create(&threads[2],NULL, randomSearch,(void *)laberinth);
    if(pid) {
            printf("Error Creando DFS");
    }
    pid = pthread_create(&threads[3],NULL, aStarSearch,(void *)laberinth);
    if(pid) {
            printf("Error Creando A*");
    }
    pthread_exit(NULL);

}
