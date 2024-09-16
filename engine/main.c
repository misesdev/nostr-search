#include <stdint.h>
#include <stdio.h>
// #include <string.h>
// #include <time.h>

#include "src/utils/utils.c"
#include "src/services/server/app.c"

void showOptions() {
    printf("Usage: nostr-find [option]\n\n");
    printf("Options for run the search egine\n");
    printf("  add-users       Executed to receive users - expected port\n");
    printf("  search-users    Executed to search for users in the tree - expected port\n\n");
    printf("Example: nostr-find add-users 8080\n");
}

int getPortParam(char *port)
{ 
    if(!port) {
        printf("Expected port number\n");
        return 0;
    }

    return parseInt(port);
}

int main(int argc, char *args[]) 
{
    // if(argc < 2) 
    // {
    //     showOptions();
    //     return -1;
    // }

    // if(textSimilarity(args[1], "add-users") > .85)
    // {
    //     int port = getPortParam(args[2]);

    //     if(port == 0) return -1;

    //     if(port < 80) {
    //         printf("Invalid port number");
    //         return -1;
    //     }

    //     upUsers(port);
    // } 
    // else if(textSimilarity(args[1], "search-users") > .85) 
    // {
    //     int port = getPortParam(args[2]);

    //     if(port == 0) return -1;

    //     if(port < 80) {
    //         printf("Invalid port number");
    //         return -1;
    //     }

    //     upSearch(port);
    // } 
    // else if(strcmp(args[1], "-h"))
    //     showOptions();
    // else 
    //     printf("Error: expected option, run nostr-find -h to help.");
    
    upApplication(8080);

    exit(0);
}


