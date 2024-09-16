#ifndef UP_FRIENDS_C
#define UP_FRIENDS_C

#include "../../types/types.c"

#include <stdlib.h>
#include <string.h>

HttpResponse* insertFriends(char *request, struct TrieNode *root)
{
    HttpResponse *response = malloc(sizeof(HttpResponse));

    strcpy(response->Content, "{ \"message\": \"Not implementd\" }");
    response->StatusCode = 400; 
    
    return response;
}

#endif
