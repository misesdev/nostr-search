#ifndef TYPES_C
#define TYPES_C

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    char name[35];
    char pubkey[65]; // 64 bytes + byte null end
    char profile[100];
} User;

typedef struct {
    uint8_t address[16];
} Follower;

struct FollowerNode {
    Follower *follower;
    struct FollowerNode *next;
};

struct UserNode {
    User *user;
    struct UserNode *next;
};

struct TrieNode {
    User *user;
    struct TrieNode *children[200];
    bool isEndOfKey;
};

typedef struct {
    char pubkey[65];
    char search[100];
} Search;

#endif



