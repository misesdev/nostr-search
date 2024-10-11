#ifndef SEARCH_LIST_C
#define SEARCH_LIST_C

#include <stdint.h>
#include <stdlib.h>
#include "../types/types.c"
#include "./search_utils.c"
#include "./string_utils.c"

struct ResultNode* searchOnUserList(LinkedUsers *rootUses, char *searchTerm)
{
    struct ResultNode *resultList = createResultNode(NULL, 0);

    for(uint32_t i = 0; i < rootUses->count; i++)
    {
        float similarity = textSimilarity(searchTerm, rootUses->users[i].displayName);
        if(similarity >= MIN_SIMILARITY_TERM)
        {
            insertResultNode(resultList, &rootUses->users[i], similarity);
        }
    }

    return resultList;
}

#endif

