#ifndef SEARCH_USERS_C
#define SEARCH_USERS_C

#include <stdlib.h>

#include "../../types/types.c" 
#include "../../types/user_trie.c"
#include "../../utils/search_utils.c"
#include "../../utils/search_graph.c"

HttpResponse* searchUsers(char *jsonRequest, HttpResponse *response, Database *root)
{
    Search *searchParams = getSearchParams(jsonRequest, response->Content);

    if(!searchParams) 
    {
        response->StatusCode = 403;
        return response;
    }

    struct TrieNode *userNode = getTrieNodeFromPubkey(root->tree, searchParams->pubkey);

    if(!userNode) 
    {
        responseMessage(response->Content, "Focal user not found, please provide a valid public key");
        response->StatusCode = 403;
        free(searchParams);
        return response;
    }

    if(!userNode->user->friends)
        userNode = getTrieNodeFromPubkey(root->tree, "55472e9c01f37a35f6032b9b78dade386e6e4c57d80fd1d0646abb39280e5e27");

    struct ResultNode *resultListUsers = searchOnGraph(userNode->user, searchParams->search, searchParams->limit);

    resultToJson(resultListUsers, response->Content);

    response->StatusCode = 200;
    
    free(searchParams);

    return response;
}



#endif 


