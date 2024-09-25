#ifndef SEARCH_RELAYS_C
#define SEARCH_RELAYS_C

#include "../../types/types.c"
#include "../../utils/http_utils.c"
//#include "../../types/relay_list.c"

HttpResponse* searchRelays(char *jsonRequest, HttpResponse *response, Database *root)
{
    responseMessage(response->Content, "Not implemented");
    response->StatusCode = 404;

    return response;
}

#endif 
