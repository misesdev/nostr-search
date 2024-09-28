#ifndef SEARCH_RELAYS_C
#define SEARCH_RELAYS_C

#include <string.h>

#include "../../types/types.c"
#include "../../utils/relay_utils.c"

HttpResponse* searchOnRelays(char *jsonRequest, HttpResponse *response, Database *root)
{
    char *searchTerm = jsonToSearchTerm(jsonRequest, response->Content);

    if(strlen(searchTerm) <= 0) 
    {
        response->StatusCode = 403;
        return response;
    }

    struct RelayNode* relays = searchRelays(root->relays, searchTerm);

    serializeRelayNode(relays, response->Content);        
    response->StatusCode = 200;
    return response;
}

#endif 
