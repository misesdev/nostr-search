#ifndef TREE_SAVE_C
#define TREE_SAVE_C

#include "../../utils/http_utils.c"
#include "../../utils/save_utils.c"
#include "../../types/types.c"
#include "../../filesystem/disk.c"
#include <stdio.h>

HttpResponse* saveTrieOnDisk(char *json_request, HttpResponse *response, Database *root)
{
    int scope = getScopeFromJson(json_request, response->Content);

    if(scope == 0) {
        response->StatusCode = 403;
        return response;
    }

    saveDatabase(root, scope);

    printf("save database succefully\n");

    responseMessage(response->Content, "data saved succefully");
    response->StatusCode = 200;

    return response;
}

#endif
