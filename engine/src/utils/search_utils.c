#ifndef SEARCH_UTILS_C 
#define SEARCH_UTILS_C

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

#include "./utils.c"
#include "./http_utils.c"
#include "../types/types.c"
#include "../types/user_list.c"

Search* jsonToSearchParams(char *json, char *error)
{
    cJSON *jsonParams = cJSON_Parse(json);

    if(!jsonParams) {
        strcpy(error, "{ \"message\": \"Error when parsing json, expected properties 'pubkey', 'limit' and 'searchTerm'\" }");
        return NULL;
    }

    Search *searchParams = malloc(sizeof(Search));
    
    cJSON *search = cJSON_GetObjectItemCaseSensitive(jsonParams, "searchTerm");
    cJSON *pubkey = cJSON_GetObjectItemCaseSensitive(jsonParams, "pubkey");
    cJSON *limit = cJSON_GetObjectItem(jsonParams, "limit");
    if(cJSON_IsString(search) && (search->valuestring != NULL) && 
        cJSON_IsString(pubkey) && (pubkey->valuestring != NULL) && 
        cJSON_IsNumber(limit) && (limit->valueint != 0)) 
    {
        snprintf(searchParams->pubkey, 65, "%s", pubkey->valuestring);
        snprintf(searchParams->search, 100, "%s", search->valuestring);
        // guarantees that the last byte of the string is null 
        searchParams->pubkey[strlen(searchParams->pubkey) - 1] = '\0';
        searchParams->search[strlen(searchParams->search) - 1] = '\0';
        searchParams->limit = limit->valueint;
    } else {
        strcpy(error, "{ \"message\": \"Error when parsing json, expected properties 'pubkey', 'limit' and 'searchTerm'\" }");
        free(searchParams);
        cJSON_Delete(jsonParams);
        return NULL;
    }

    return searchParams;
}

Search* getSearchParams(char *request, char *error)
{
    char *jsonParams = requestParams(request, error);

    printf("reccept json: \n%s", jsonParams);

    if(!jsonParams) return NULL;

    Search *searchParams = jsonToSearchParams(jsonParams, error);

    if(!searchParams) return NULL;

    return searchParams;
}

void enqueue(struct UserNode ***queue, int *queueSize, User *user)
{
    *queue = realloc(*queue, sizeof(struct UserNode*) * (*queueSize + 1));
    (*queue)[*queueSize] = (struct UserNode*) malloc(sizeof( struct UserNode));
    (*queue)[*queueSize]->user = user;
    (*queue)[*queueSize]->next = NULL;
    (*queueSize)++;
}

struct UserNode* searchOnGraph(User *rootUser, char *searchTerm, int limit)
{
    int foundCount = 0, visitedCount = 0;
    struct UserNode *resultList = createUserNode(NULL);
    limit = limit > MAX_LIMIT_RESULTS ? MAX_LIMIT_RESULTS : limit;

    // Fila de busca (implementada como um array dinâmico de UserNode*)
    struct UserNode **queue = NULL;
    int queueSize = 0;

    // Add all users of initial list to the search queue
    struct UserNode *current = rootUser->friends;
    while (current != NULL) {
        enqueue(&queue, &queueSize, current->user);
        current = current->next;
    }

    // start breadth-first search 
    while (queueSize > 0 && foundCount < limit && visitedCount < MAX_USERS_TO_VISIT) 
    {
        // Remove the first element of queue
        struct UserNode *currentNode = queue[0];
        for (int i = 0; i < queueSize - 1; i++) {
            queue[i] = queue[i + 1];
        }
        queueSize--;

        visitedCount++;

        if (textSimilarity(currentNode->user->name, searchTerm) > MIN_SIMILARITY_TERM) {
            insertUniqueUserNode(resultList, currentNode->user);
            foundCount++;  
        }

        struct UserNode *friendList = currentNode->user->friends;
        while (friendList != NULL && visitedCount < MAX_USERS_TO_VISIT) {
            enqueue(&queue, &queueSize, friendList->user);
            friendList = friendList->next;
        }

        // Free the memory of current node of queue
        free(currentNode);

        // If you reach the limit of results or users visited, the search ends
        if (foundCount >= limit || visitedCount >= MAX_USERS_TO_VISIT) {
            break;
        }
    }

    // Free the memory of queue
    for (int i = 0; i < queueSize; i++) {
        free(queue[i]);
    }
    free(queue);

    return resultList;
}


#endif 
