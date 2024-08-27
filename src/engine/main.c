#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//#include "./trie.c"
#include "./utils/utils.c"
//#include "./filesystem/load.c"
//#include "./types/linked_lists.c"
#include "./utils/http_utils.c"
#include "./types/linked_lists.c"

int main(int argc, char *args[]) 
{
    int result;
    float similarity;
    float startTime = (float)clock()/CLOCKS_PER_SEC;

    for(int i = 0; i < 1000001; i++) {        
        //similarity = textSimilarity("Elisson Lima", "Elisson Vale");
        similarity = stringSimilarity("Elisson Lima", "Elisson Vale");
    }

    float endTime = (float)clock()/CLOCKS_PER_SEC;
    
    float timeElapsed = endTime - startTime;

    printf("similarity: %f\n", similarity);
    printf("time s: %f", timeElapsed);

    //User *user = malloc(sizeof(User));

    //strcpy(user->name, "Mises Dev");
    //strcpy(user->npub, "6e468422dfb74a5738702a8823b9b28168abab8655faacb6853cd0ee15deee93");

    //struct UserNode *first = createUserNode(user);
    //strcpy(user->name, "Iaco Vale");
    //first->next = createUserNode(user);
    //strcpy(user->name, "Elisson Vale");
    //first->next->next = createUserNode(user);

    //char *response = responseJsonResult(first);

    //printf("%s", response);

    //free(user);
    //free(first->next->next);
    //free(first->next);
    //free(first);
    //free(response);

    //char npub[] = "ff22";

    //uint8_t *numbers = hexToBytes(npub);

    //printf("first: %d, second: %d", numbers[0], numbers[1]);

    //User *user = loadData();

    //if(!user) {
        //printf("File 'database.bin' not found!");
    //}

    //printf("The user is: %s", user->name);

    //free(numbers);
    //free(user);
}


