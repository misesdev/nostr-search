#ifndef TREE_SAVE_C
#define TREE_SAVE_C

#include "../../utils/http_utils.c"
#include "../../utils/save_utils.c"
#include "../../types/types.c"
#include "../../filesystem/wdisk.c"
#include "../../filesystem/relays.c"

#include <stdio.h>

HttpResponse* saveTrieOnDisk(char *json_request, HttpResponse *response, Database *root)
{
    int scope = getScopeFromJson(json_request, response->Content);

    if(scope == 0) {
        response->StatusCode = 403;
        return response;
    }

    printf("saving data on disk..\n");

    switch(scope) {
        case SCOPE_USERS:
            loadTrieInDisk(root->tree);
        case SCOPE_FRIENDS:
            loadTrieInDisk(root->tree);
        case SCOPE_RELAYS:
            loadRelaysOnDisk(root->relays); 
    }

    printf("save data succefully\n");

    responseMessage(response->Content, "data saved succefully");
    response->StatusCode = 200;

    return response;
}

#endif
