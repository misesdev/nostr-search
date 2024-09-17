#ifndef APPLICATION_C
#define APPLICATION_C

#include "./server.c"
#include "./router.c"
#include "../../types/types.c"
#include "../../filesystem/rdisk.c"
#include "../../filesystem/wdisk.c"

#include <signal.h>
#include <stdio.h>
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

void upApplication(int port)
{
    signal(SIGKILL, handle_signal);
    signal(SIGTERM, handle_signal);
    signal(SIGINT, handle_signal);

    printf("loading tree from disk...\n");

    root = loadTrieFromDisk();

    printf("\napplication pid: %d\n\n", getpid());

    upServer(router, root, port);
}

#endif
