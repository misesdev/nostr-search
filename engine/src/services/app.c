#ifndef APPLICATION_C
#define APPLICATION_C

#include "./server.c"
#include "./router.c"
#include "../types/types.c"
#include "../filesystem/rdisk.c"
#include "../filesystem/wdisk.c"

#include "../utils/search_graph.c"
#include "../types/user_trie.c"

#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

struct TrieNode *root;

void handle_signal(int signal_command)
{
    if(signal_command == SIGTERM || 
        signal_command == SIGKILL || 
        signal_command == SIGINT)
    {
        printf("\nsaving tree on disk...\n");
        loadTrieInDisk(root);
        exit(0);
    }
}

void searchTest() 
{
    Search *search;

    strcpy(search->pubkey, "55472e9c01f37a35f6032b9b78dade386e6e4c57d80fd1d0646abb39280e5e27");
    strcpy(search->search, "fabio akita");
    search->limit = 50;

    clock_t start = clock();

    struct TrieNode *userNode = getTrieNodeFromPubkey(root, search->pubkey);

    searchOnGraph(userNode->user, search->search, search->limit);

    clock_t end = clock();
    float time = (float)(end - start) / CLOCKS_PER_SEC;

    printf("search time: %f\n", time);
}

void upApplication(int port)
{
    // signal(SIGKILL, handle_signal);
    // signal(SIGTERM, handle_signal);
    // signal(SIGINT, handle_signal);

    printf("loading tree from disk...\n");

    root = loadTrieFromDisk();

    if(!root) 
    {
        printf("\nfailed when reading from disk\n");
        exit(0);
    }

    //searchTest();

    printf("\napplication pid: %d\n\n", getpid());

    upServer(router, root, port);
}

#endif
