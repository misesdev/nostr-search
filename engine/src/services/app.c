#ifndef APPLICATION_C
#define APPLICATION_C

#include "./server.c"
#include "./router.c"
#include "../types/types.c"
#include "../filesystem/disk.c"

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

Database *database;

void handle_signal(int command)
{
    if(command == SIGTERM || command == SIGKILL || command == SIGINT)
    {
        saveDatabase(database, SCOPE_FRIENDS);
        exit(0);
    }
}

void upApplication(int port)
{
    //signal(SIGINT, handle_signal);

    database = loadDatabase();

    printf("\napplication pid: %d\n\n", getpid());

    upServer(router, database, port);
}

#endif
