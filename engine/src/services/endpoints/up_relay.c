#ifndef UP_RELAY_C
#define UP_RELAY_C

#include "../../types/types.c"
#include "../../utils/http_utils.c"
#include "../../types/relay_list.c"
#include "../../utils/relay_utils.c"

HttpResponse* addRelayOnEngine(char *jsonRequest, HttpResponse *response, Database *root)
{
    char *relay_address = jsonToRelay(jsonRequest, response->Content);

    if(!relay_address) {
        response->StatusCode = 403;
        return response;
    }

    insertRelayNode(root->relays, relay_address);

    responseMessage(response->Content, "relay added succefully");
    response->StatusCode = 200;
    free(relay_address);

    return response;
}

#endif 
