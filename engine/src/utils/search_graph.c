#ifndef SEARCH_GRAPH_C 
#define SEARCH_GRAPH_C

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

#include "./uthash.h"
#include "./string_utils.c"
#include "../types/types.c"
#include "../utils/search_utils.c"

typedef struct {
    User *user;
    UT_hash_handle hh; // Handle para a tabela hash da biblioteca uthash
} VisitedUser;

void markVisited(VisitedUser **visitedSet, User *user) {
    VisitedUser *newVisit = malloc(sizeof(VisitedUser));
    newVisit->user = user;
    HASH_ADD_PTR(*visitedSet, user, newVisit);
}

bool isVisited(VisitedUser *visitedSet, User *user) {
    VisitedUser *visit;
    HASH_FIND_PTR(visitedSet, &user, visit);
    return visit != NULL;
}

void freeVisitedSet(VisitedUser *visitedSet) {
    VisitedUser *current, *tmp;
    HASH_ITER(hh, visitedSet, current, tmp) {
        HASH_DEL(visitedSet, current);
        free(current);
    }
}

void enqueue(User ***queue, int *queueSize, int *capacity, User *user) 
{
    if (*queueSize == *capacity) {
        *capacity *= 2; // Increases capacity by doubling in size
        *queue = realloc(*queue, sizeof(User*) * (*capacity));
    }
    (*queue)[*queueSize] = user;    
    (*queueSize)++;
}

struct ResultNode* searchOnGraph(User *rootUser, char *searchTerm, int limit) 
{
    int foundCount = 0, visitedCount = 0;
    
    struct ResultNode *resultList = createResultNode(NULL, 0);

    limit = limit > MAX_LIMIT_RESULTS ? MAX_LIMIT_RESULTS : limit;

    // Fila de busca (implementada como um array dinâmico de UserNode*)
    int queueSize = 0, queueCapacity = 500;
    User **queue = malloc(queueCapacity * sizeof(User*));

    // Hash set para verificar usuários visitados
    VisitedUser *visitedSet = NULL;

    // Adiciona os amigos do usuário root à fila de busca
    struct UserNode *current = rootUser->friends;
    while (current) 
    {
        enqueue(&queue, &queueSize, &queueCapacity, current->user);
        markVisited(&visitedSet, current->user); // Marca como visitado
        current = current->next;
    }

    // Inicia a busca em largura (BFS)
    while (foundCount < limit && visitedCount < MAX_USERS_TO_VISIT) 
    {
        if(visitedCount >= queueSize - 1) break;

        // take the element from queue
        User *currentUser = queue[visitedCount];
        visitedCount++;

        if(!currentUser) continue;

        // Verifica se o usuário é semelhante ao termo de busca
        float similarity = textSimilarity(currentUser->displayName, searchTerm);
        if (similarity >= MIN_SIMILARITY_TERM) 
        {
            insertResultNode(resultList, currentUser, similarity);
            foundCount++;
        }

        // Adiciona os amigos do nó atual à fila
        struct UserNode *friendList = currentUser->friends;
        while (friendList && visitedCount < MAX_USERS_TO_VISIT) 
        {
            if (!isVisited(visitedSet, friendList->user)) 
            {
                enqueue(&queue, &queueSize, &queueCapacity, friendList->user);
                markVisited(&visitedSet, friendList->user); 
            }
            friendList = friendList->next;
        }

        if (foundCount >= limit || visitedCount >= MAX_USERS_TO_VISIT) {
            break;
        }
    }

    free(queue);

    // Libera o conjunto de usuários visitados
    freeVisitedSet(visitedSet);
  
    return resultList;
}


#endif
