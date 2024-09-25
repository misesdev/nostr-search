#ifndef UP_RELAY_C
#define UP_RELAY_C

#include "../../types/types.c"
#include "../../utils/http_utils.c"
//#include "../../types/relay_list.c"

HttpResponse* addRelayOnEngine(char *jsonRequest, HttpResponse *response, Database *root)
{
    responseMessage(response->Content, "Not implemented");
    response->StatusCode = 404;

    return response;
}

#endif 
