#ifndef TYPES_C
#define TYPES_C
#include <stdbool.h>

typedef struct {
    char name[35];
    char pubkey[65]; // 64 bytes + byte null end
    char profile[100];
} User;

typedef struct {
    char pubkey[65];
    char search[100];
} Search;

struct UserNode {
    User *user;
    struct UserNode *next;
};

struct TrieNode {
    User *user;
    struct TrieNode *children[200];
    bool isEndOfKey;
};

#endif


