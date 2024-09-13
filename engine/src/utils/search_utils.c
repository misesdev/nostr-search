#ifndef SEARCH_UTILS_C 
#define SEARCH_UTILS_C

#include "../types/types.c"
#include "./http_utils.c"
#include <cjson/cJSON.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

Search* jsonToSearchParams(char *json, char *error)
{
    cJSON *jsonParams = cJSON_Parse(json);

    if(!jsonParams) {
        strcpy(error, "Error when parsing json, expected properties 'pubkey', 'limit' and 'searchTerm'");
        return NULL;
    }

    Search *searchParams = malloc(sizeof(Search));
    
    cJSON *search = cJSON_GetObjectItemCaseSensitive(jsonParams, "searchTerm");
    cJSON *pubkey = cJSON_GetObjectItemCaseSensitive(jsonParams, "pubkey");
    cJSON *limit = cJSON_GetObjectItem(jsonParams, "limit");
    if(search->valuestring && pubkey->valuestring && limit->valueint) {
        snprintf(searchParams->pubkey, 65, "%s", pubkey->valuestring);
        snprintf(searchParams->search, 100, "%s", search->valuestring);
        // guarantees that the last byte of the string is null 
        searchParams->pubkey[strlen(searchParams->pubkey) - 1] = '\0';
        searchParams->search[strlen(searchParams->search) - 1] = '\0';
        searchParams->limit = limit->valueint;
    } else {
        strcpy(error, "Error when parsing json, expected properties 'pubkey', 'limit' and 'searchTerm'");
        free(searchParams);
        cJSON_Delete(jsonParams);
        return NULL;
    }

    return searchParams;
}

Search* getSearchParams(char *request, char *error)
{
    char *jsonParams = requestParams(request, error);

    if(!jsonParams) return NULL;

    Search *searchParams = jsonToSearchParams(jsonParams, error);

    if(!searchParams) return NULL;

    return searchParams;
}

#endif 
