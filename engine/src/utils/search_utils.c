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

Search* jsonToSearchParams(char *json, char *error)
{
    cJSON *jsonParams = cJSON_Parse(json);

    if(!jsonParams) {
        responseMessage(error, "Error when parsing json, expected properties 'pubkey', 'limit' and 'searchTerm'");
        return NULL;
    }

    Search *searchParams = calloc(1, sizeof(Search));
    
    cJSON *search = cJSON_GetObjectItemCaseSensitive(jsonParams, "searchTerm");
    cJSON *pubkey = cJSON_GetObjectItemCaseSensitive(jsonParams, "pubkey");
    cJSON *limit = cJSON_GetObjectItem(jsonParams, "limit");
    if(cJSON_IsString(search) && (search->valuestring != NULL) && 
        cJSON_IsString(pubkey) && (pubkey->valuestring != NULL) && 
        cJSON_IsNumber(limit) && (limit->valueint != 0)) 
    {
        snprintf(searchParams->pubkey, 65, "%s", pubkey->valuestring);
        snprintf(searchParams->search, 100, "%s", search->valuestring);        
        searchParams->limit = limit->valueint;
    } else {
        responseMessage(error, "Error when parsing search, expected properties 'pubkey', 'limit' and 'searchTerm'");
        cJSON_Delete(jsonParams);
        free(searchParams);
        return NULL;
    }

    cJSON_Delete(jsonParams);

    return searchParams;
}

Search* getSearchParams(char *json_params, char *error)
{
    Search *searchParams = jsonToSearchParams(json_params, error);

    if(!searchParams) return NULL;

    return searchParams;
}

struct ResultNode* createResultNode(User *user, float similarity)
{
    struct ResultNode *node = malloc(sizeof(struct ResultNode));
    node->similarity = similarity;
    node->user = user;
    node->next = NULL;

    return node;
}

void insertResultNode(struct ResultNode *rootUsers, User *user, float similarity)
{
    if(!rootUsers->user)
    {
        rootUsers->similarity = similarity;
        rootUsers->user = user;
        return;
    }

    struct ResultNode *current = rootUsers;
    while (current)
    {
        if(strcmp(current->user->pubkey, user->pubkey) == 0) return;

        if(!current->next) {
            current->next = createResultNode(user, similarity);
            return;
        }

        current = current->next;
    }
}

cJSON* resultUserToCJSON(User *user, float similarity)
{
    cJSON *userJson = cJSON_CreateObject();

    cJSON_AddStringToObject(userJson, "name", user->name);
    cJSON_AddStringToObject(userJson, "displayName", user->displayName);
    cJSON_AddStringToObject(userJson, "pubkey", user->pubkey);
    cJSON_AddStringToObject(userJson, "profile", user->profile);
    cJSON_AddNumberToObject(userJson, "similarity", truncate(similarity));

    return userJson;
}

void resultToJson(struct ResultNode *rootUsers, char *response)
{
    cJSON *jsonList = cJSON_CreateArray();

    struct ResultNode *current = rootUsers;
    while(current) 
    {
        if(current->user)
            cJSON_AddItemToArray(jsonList, resultUserToCJSON(current->user, current->similarity));

        current = current->next;
    }

    snprintf(response, MAX_RESPONSE_LENGTH, "%s", cJSON_Print(jsonList));

    cJSON_Delete(jsonList);

    free(rootUsers);
}

#endif


