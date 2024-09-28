#ifndef APPLICATION_C
#define APPLICATION_C

#include "./server.c"
#include "./router.c"
#include "../types/types.c"
#include "../filesystem/rdisk.c"
#include "../filesystem/wdisk.c"
#include "../filesystem/relays_disk.c"

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

Database *database;

void handle_signal(int signal_command)
{
    if(signal_command == SIGTERM || 
        signal_command == SIGKILL || 
        signal_command == SIGINT)
    {
        printf("\nsaving tree on disk...\n");
        loadTrieInDisk(database->tree);
        exit(0);
    }
}

void upApplication(int port)
{
    database = malloc(sizeof(Database));

    printf("loading tree from disk...\n");

    //database->tree = loadTrieFromDisk();
    database->relays = loadRelaysFromDisk();

    // if(!database->tree) 
    // {
    //     printf("\nfailed when reading from disk\n");
    //     exit(-1);
    // }

    printf("\napplication pid: %d\n\n", getpid());

    upServer(router, database, port);
}

#endif
