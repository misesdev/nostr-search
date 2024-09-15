#include <stdint.h>
#include <stdio.h>
#include <string.h>
// #include <time.h>

#include "./src/services/up_users.c"
#include "./src/services/up_search.c"
#include "src/utils/utils.c"

void showOptions() {
    printf("Usage: nostr-find [option]\n\n");
    printf("Options for run the search egine\n");
    printf("  add-users       Executed to receive users - expected port\n");
    printf("  search-users    Executed to search for users in the tree - expected port\n\n");
    printf("Example: nostr-find add-users 8080\n");
}

int getPortParam(char *portDigited)
{ 
    if(!portDigited) {
        printf("Expected port number\n");
        return 0;
    }

    char port[5];
    for(int i = 0; portDigited[i] != '\0' && i < 5; i++) {
        port[i] = portDigited[i];
    }

    return 8080;//parseInt(port);
}

int main(int argc, char *args[]) 
{
    // float similarity = 0;

    // clock_t start = clock();

    // for(int i = 0; i < 10000; i++)
    // {
    //     similarity = textSimilarity("Misos Devo", "Mises Developer");
    // }

    // clock_t end = clock();
    // double time = (double)(end - start) / CLOCKS_PER_SEC;

    // printf("similarity: %f\n", similarity);
    // printf("execution: %f\n\n\n", time);

    if(argc < 2) 
    {
        showOptions();
        return -1;
    }

    if(textSimilarity(args[1], "add-users") > .95)
    {
        int port = getPortParam(args[2]);

        if(port == 0) return -1;

        if(port < 80) {
            printf("Invalid port number");
            return -1;
        }

        upUsers(port);
    } 
    else if(textSimilarity(args[1], "search-users") > .95) 
    {
        int port = getPortParam(args[2]);

        if(port == 0) return -1;

        if(port < 80) {
            printf("Invalid port number");
            return -1;
        }

        upSearch(port);
    } 
    else if(strcmp(args[1], "-h"))
        showOptions();
    else 
        printf("Error: expected option, run nostr-find -h to help.");

    return 0;
}


