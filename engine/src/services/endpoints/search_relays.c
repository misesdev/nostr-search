#ifndef SEARCH_RELAYS_C
#define SEARCH_RELAYS_C

#include "../../types/types.c"
#include "../../utils/relay_utils.c"

HttpResponse* searchOnRelays(char *jsonRequest, HttpResponse *response, Database *root)
{
    RelaySearch *search = jsonToSearchTerm(jsonRequest, response->Content);

    if(!search) 
    {
        response->StatusCode = 403;
        return response;
    }

    struct RelayNode* relays = searchRelays(root->relays, search->searchTerm, search->limit);

    serializeRelayNode(relays, response->Content); 

    response->StatusCode = 200;

    free(search);

    return response;
}

#endif 
