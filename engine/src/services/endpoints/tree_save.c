#ifndef TREE_SAVE_C
#define TREE_SAVE_C

#include "../../utils/http_utils.c"
#include "../../types/types.c"
#include "../../filesystem/wdisk.c"

#include <stdio.h>

HttpResponse* saveTrieOnDisk(char *json_request, HttpResponse *response, Database *root)
{
    printf("loading tree on disk..\n");

    loadTrieInDisk(root->tree);

    printf("loaded tree succefully\n");

    responseMessage(response->Content, "tree saved succefully");
    response->StatusCode = 200;

    return response;
}

#endif
