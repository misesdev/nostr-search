#ifndef ROUTER_C
#define ROUTER_C

#include "../../types/types.c"
#include "../endpoints/up_users.c"
#include "../endpoints/up_search.c"
#include "../endpoints/up_friends.c"

#include <stdlib.h>
#include <string.h>

HttpResponse* router(char *request, struct TrieNode *root) 
{ 
    if(strstr(request, "/add_user") != NULL)
        return insertUser(request, root);
    if(strstr(request, "/search") != NULL)
        return searchUsers(request, root);
    if(strstr(request, "/add_friends") != NULL)
        return insertFriends(request, root);

    HttpResponse *notFound = malloc(sizeof(HttpResponse));

    strcpy(notFound->Content, "{"
           "\"message\": \"Please use one of the following endpointes: /add_user, /add_friends, /search\""
           "}");

    notFound->StatusCode = 403;

    return notFound;
}

#endif
