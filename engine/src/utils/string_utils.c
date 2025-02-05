#ifndef STRING_UTILS_C
#define STRING_UTILS_C

#include <stdint.h>
#include "./char_map.c"

#define HASH_PRIME 37
#define HASH_SIZE 10000

float textSimilarity(char *origin, char *compare) 
{
    // the documentation hire: http://www.catalysoft.com/articles/StrikeAMatch.html
    uint_fast32_t intersection = 0, number = 0, sizePairs = 0; 
    uint_fast64_t hashSet[HASH_SIZE / 64] = {0};

    unsigned char *orig = (unsigned char*) origin;
    while(*(orig + 1)) 
    { 
        unsigned char a = char_map[*orig] ? char_map[*orig]: *orig;
        unsigned char b = char_map[*(orig+1)] ? char_map[*(orig+1)]: *(orig+1);
        number = (a * HASH_PRIME + b) % HASH_SIZE; //multiplication with prime number
        hashSet[number / 64] |= 1UL << (number % 64);
        sizePairs++;
        orig++;
    }

    unsigned char *comp = (unsigned char*) compare;
    while(*(comp + 1)) 
    { 
        unsigned char a = char_map[*comp] ? char_map[*comp]: *comp;
        unsigned char b = char_map[*(comp+1)] ? char_map[*(comp+1)]: *(comp+1);
        number = (a * HASH_PRIME + b) % HASH_SIZE; //multiplication with prime number
        if(hashSet[number / 64] & 1UL << (number % 64)) 
            intersection++;
        sizePairs++;
        comp++;
    }

    return sizePairs > 0 ? (2.0 * intersection) / sizePairs : 0.0;
}


#endif
