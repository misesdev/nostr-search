#ifndef GET_STATS_C
#define GET_STATS_C

#include "../../types/types.c"
#include <stdio.h>

HttpResponse* getNostrStats(char *jsonRequest, HttpResponse *response, Database *root)
{
    snprintf(response->Content, 
             MAX_RESPONSE_LENGTH, 
             "{ \"users\": %d, \"relays\": %d }", 
             root->users->count,
             root->relays->count);

    return response;
}



#endif


