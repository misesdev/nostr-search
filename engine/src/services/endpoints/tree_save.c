#ifndef TREE_SAVE_C
#define TREE_SAVE_C

#include "../../utils/http_utils.c"
#include "../../types/types.c"
#include "../../filesystem/wdisk.c"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

HttpResponse* saveTrieOnDisk(char *request, struct TrieNode *root)
{
    HttpResponse *response = malloc(sizeof(HttpResponse));

    if(!response) {
        perror("failed to alocate memory for response");
        return NULL;
    }

    if(!isPostRequest(request))
    {
        responseMessage(response->Content, "Accept only POST request with Content-Type: application/json");
        response->StatusCode = 403;
        return response;
    }

    printf("loading tree on disk..\n");

    loadTrieInDisk(root);

    responseMessage(response->Content, "tree saved succefully");
    response->StatusCode = 200;

    return response;
}

#endif
