#ifndef UP_SEARCH_C
#define UP_SEARCH_C

#include <stdlib.h>
#include "../../types/types.c" 
#include "../../types/user_trie.c"
#include "../../utils/user_utils.c"
#include "../../utils/search_utils.c"
#include "../../utils/search_graph.c"

HttpResponse* searchUsers(char *request, struct TrieNode *root)
{
    HttpResponse *response = calloc(1, sizeof(HttpResponse));
    
    Search *searchParams = getSearchParams(request, response->Content);

    if(!searchParams) 
    {
        response->StatusCode = 403;
        return response;
    }

    struct TrieNode *userNode = getTrieNodeFromPubkey(root, searchParams->pubkey);

    if(!userNode) 
    {
        responseMessage(response->Content, "Focal user not found, please provide a valid public key");
        response->StatusCode = 403;
        free(searchParams);
        return response;
    }

    struct UserNode *resultListUsers = searchOnGraph(userNode->user, searchParams->search, searchParams->limit);

    userListToJson(resultListUsers, response->Content);
    response->StatusCode = 200;
    free(searchParams);

    return response;
}



#endif 


