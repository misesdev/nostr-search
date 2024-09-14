#ifndef UP_USERS_C
#define UP_USERS_C

#include "./server.c"
#include "../types/types.c"
#include "../utils/user_utils.c"
#include "../filesystem/rdisk.c"
#include <stdio.h>
#include <string.h>

HttpResponse* requestProcessSearch(char *request, struct TrieNode *root)
{
    HttpResponse *response = malloc(sizeof(HttpResponse));

    User *user = getUserFromRequest(request, response->Content);
    
    if(!user) {
        response->StatusCode = 403;
        return response;
    }

    insertTrieNode(root, user);

    printf("user inserted: %s\n", user->displayName);

    strcpy(response->Content, "{ \"message\": \"User added successfully\" }");
    response->StatusCode = 200;

    return response;
}

void upUsers(int port) 
{
    struct TrieNode *root = loadTrieFromDisk();

    upServer(requestProcessSearch, root, port);
}

#endif


