#ifndef USER_QUEUE_C
#define USER_QUEUE_C

#include <stdint.h>
#include <stdlib.h>
#include "../types/types.c"

typedef struct {
    User **queue;
    uint32_t size;
    uint32_t capacity;
} UserQueue;

UserQueue* createUserQueue()
{
    UserQueue *userQueue = malloc(sizeof(UserQueue));

    userQueue->size = 0;
    userQueue->capacity = 500;
    userQueue->queue = malloc(sizeof(User*) * userQueue->capacity);

    return userQueue;
}

void enQueueUser(UserQueue *userQueue, User *user) 
{
    if (userQueue->size == userQueue->capacity) 
    {
        userQueue->capacity *= 2; // Increases capacity by doubling in size
        userQueue->queue = realloc(userQueue->queue, sizeof(User*) * userQueue->capacity);
    }
    userQueue->queue[userQueue->size] = user;    
    userQueue->size++;
}

void freeQueueUser(UserQueue *userQueue)
{
    free(userQueue->queue);
    free(userQueue);
}


#endif


