#ifndef TREE_SAVE_C
#define TREE_SAVE_C

#include "../../types/types.c"
#include "../../filesystem/wdisk.c"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


HttpResponse* saveTrieOnDisk(char *request, struct TrieNode *root)
{
    HttpResponse *response = malloc(sizeof(HttpResponse));

    printf("loading tree on disk..");

    loadTrieInDisk(root);

    strcpy(response->Content, "{ \"message\": \"tree saved succefully\" }");
    response->StatusCode = 200;

    return response;
}

#endif
