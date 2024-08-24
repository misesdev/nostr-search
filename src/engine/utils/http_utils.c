#ifndef HTTP_UTILS_C
#define HTTP_UTILS_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../types/types.c"
#include "../types/linked_lists.c"

Search* requestParams(char *hexBytes) {
    
    Search *search = malloc(sizeof(Search));

    // populate the pubkey hexadecimal
    for(int i = 0; i < strlen(search->pubkey); i++) {
        search->pubkey[i] = hexBytes[i];
    }

    // populate the search term
    for (int i = strlen(search->pubkey); i < strlen(hexBytes); i++) {
        search->term[i] = hexBytes[i];
    }
    
    return search; 
}

char* responseJsonResult(struct UserNode *linkedUser)
{
    char *response = malloc(1000 * sizeof(char));

    strcat(response, "[");
    
    struct UserNode *current = linkedUser;
    
    while (current) 
    {      
        // build property username
        strcat(response, "{ \"username\": \""); 
        strcat(response, current->user->name); 
        strcat(response, "\", ");

        // build the property pubkey
        strcat(response, "\"pubkey\": \"");
        strcat(response, current->user->npub); 
        strcat(response, "\"}");
        
        if(current->next != NULL) {
            strcat(response, ",");
        }

        current = current->next;
    }

    strcat(response, "]");

    return response; 
}

#endif
