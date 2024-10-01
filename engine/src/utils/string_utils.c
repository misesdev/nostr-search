#ifndef STRING_UTILS_C
#define STRING_UTILS_C

#include <ctype.h>
#include <stdint.h>

#define HASH_SIZE 10000

float textSimilarity(char *origin, char *compare) 
{
    // the documentation hire: http://www.catalysoft.com/articles/StrikeAMatch.html
    uint_fast32_t intersection = 0, number = 0, sizePairs = 0; 
    uint_fast64_t hashSet[HASH_SIZE / 64] = {0};

    while(*(origin + 1)) 
    { 
        number = (uint32_t) ((tolower(*origin) * 100) + tolower(*(origin+1))) % HASH_SIZE;
        hashSet[number / 64] |= 1ULL << (number % 64);

        sizePairs++;
        origin++;
    }

    while(*(compare + 1)) 
    { 
        number = (uint32_t) ((tolower(*compare) * 100) + tolower(*(compare+1))) % HASH_SIZE;        
        if(hashSet[number / 64] & 1ULL << (number % 64)) intersection++;

        sizePairs++;
        compare++;
    }

    return sizePairs > 0 ? (2.0 * intersection) / sizePairs : 0.0;
}


#endif
