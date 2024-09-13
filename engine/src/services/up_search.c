#ifndef UP_SEARCH_C
#define UP_SEARCH_C

#include <stdlib.h>
#include <string.h>
#include "./server.c"
#include "../types/types.c" 
#include "../types/user_trie.c"
#include "../utils/user_utils.c"
#include "../utils/search_utils.c"
#include "../filesystem/rdisk.c"

HttpResponse* requestProcessInsert(char *request, struct TrieNode *root)
{
    HttpResponse *response = malloc(sizeof(HttpResponse));
    
    Search *searchParams = getSearchParams(request, response->Content);

    if(!searchParams) {
        response->StatusCode = 403;
        return response;
    }

    struct UserNode *resultListUsers = searchOnTrie(root, searchParams->pubkey, searchParams->search, searchParams->limit);

    strcpy(response->Content, userListToJson(resultListUsers));
    response->StatusCode = 200;

    free(resultListUsers);

    return response;
}

void upSearch()
{
    struct TrieNode *root = loadTrieFromDisk();

    upServer(requestProcessInsert, root);
}

#endif 
