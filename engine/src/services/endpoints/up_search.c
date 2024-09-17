#ifndef UP_SEARCH_C
#define UP_SEARCH_C

#include <stdlib.h>
#include <string.h>
#include "../../types/types.c" 
#include "../../types/user_trie.c"
#include "../../utils/user_utils.c"
#include "../../utils/search_utils.c"

HttpResponse* searchUsers(char *request, struct TrieNode *root)
{
    HttpResponse *response = malloc(sizeof(HttpResponse));
    
    Search *searchParams = getSearchParams(request, response->Content);

    if(!searchParams) {
        response->StatusCode = 403;
        return response;
    }

    struct TrieNode *userNode = getTrieNodeFromPubkey(root, searchParams->pubkey);

    if(!userNode) {
        responseMessage(response->Content, "Focal user not found, please provide a valid public key");
        response->StatusCode = 403;
        return response;
    }

    struct UserNode *resultListUsers = searchOnGraph(userNode->user, searchParams->search, searchParams->limit);

    strcpy(response->Content, userListToJson(resultListUsers));
    response->StatusCode = 200;

    return response;
}


#endif 


