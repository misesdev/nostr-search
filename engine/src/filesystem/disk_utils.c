#ifndef DISK_UTILS_C
#define DISK_UTILS_C

#include "../types/types.c"

void getFriendsCount(struct UserNode *rootUsers, long *count)
{
    struct UserNode *current = rootUsers;
    while(current) {
        if(current->user) *count += 1;
        current = current->next;
    }
}

#endif 


