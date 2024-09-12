#ifndef DISK_UTILS_C
#define DISK_UTILS_C

#include "../types/types.c"

long getFriendsCount(struct UserNode *rootUsers)
{
    long count = 0;
    struct UserNode *current = rootUsers;
    while(current) {
        count++;
        current = current->next;
    }
    return count;
}

#endif 


