#ifndef UP_USERS_C
#define UP_USERS_C

#include "../../types/types.c"
#include "../../utils/user_utils.c"
#include "../../types/user_trie.c"

#include <stdio.h>
#include <string.h>
#include <unistd.h>

HttpResponse* insertUser(char *request, struct TrieNode *root)
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


#endif


