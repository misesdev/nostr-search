#ifndef SEARCH_USERS_C
#define SEARCH_USERS_C

#include <stdlib.h>

#include "../../types/types.c" 
#include "../../utils/search_utils.c"
#include "../../utils/search_list.c"

HttpResponse* searchUsers(char *jsonRequest, HttpResponse *response, Database *root)
{
    Search *searchParams = jsonToSearchParams(jsonRequest, response->Content);

    if(!searchParams) 
    {
        response->StatusCode = 403;
        return response;
    }

    struct ResultNode *resultListUsers = searchOnUserList(root->users, searchParams->search, searchParams->limit);

    resultToJson(resultListUsers, response->Content);

    response->StatusCode = 200;
    
    free(searchParams);

    return response;
}



#endif 


