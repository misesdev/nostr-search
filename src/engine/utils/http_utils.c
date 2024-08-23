#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../types/types.c"

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

char* responseJsonResult(User users[])
{
    int length = sizeof(*users);

    char *response = malloc(1000 * sizeof(char));

    return response; 
}


