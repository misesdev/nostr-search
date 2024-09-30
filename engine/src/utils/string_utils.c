#ifndef STRING_UTILS_C
#define STRING_UTILS_C

#include <ctype.h>
#include <stdint.h>
// #include <stdio.h>
// #include <time.h>

// float textSimilarity(char *origin, char *compare)
// {
//     // the documentation hire: http://www.catalysoft.com/articles/StrikeAMatch.html
//     int intersection = 0, number = 0, sizePairs = 0; 
//     int hashMap[255] = {0};

//     while(*origin) 
//     { 
//         number = toupper(*origin) * toupper(*(origin+1));
//         hashMap[number % 255] += 1;
//         sizePairs++;
//         origin++;
//     }

//     while(*compare) 
//     { 
//         number = (toupper(*compare) * toupper(*(compare+1))) % 255;        
//         if(hashMap[number] > 0) {
//             hashMap[number]--;
//             intersection++;
//         }
//         sizePairs++;
//         compare++;
//     }

//     return sizePairs > 0 ? (2.0 * intersection) / sizePairs : 0.0;
// }

float textSimilarity(char *origin, char *compare) 
{
    // the documentation hire: http://www.catalysoft.com/articles/StrikeAMatch.html
    uint_fast16_t intersection = 0, number = 0, sizePairs = 0; 
    uint_fast64_t hashSet[4] = {0};

    while(*origin) 
    { 
        number = toupper(*origin) * toupper(*(origin+1)) % 256;
        hashSet[number / 64] |= 1 << number;

        sizePairs++;
        origin++;
    }

    while(*compare) 
    { 
        number = (toupper(*compare) * toupper(*(compare+1))) % 256;        
        if(hashSet[number / 64] & (1 << number)) intersection++;

        sizePairs++;
        compare++;
    }

    return sizePairs > 0 ? (2.0 * intersection) / sizePairs : 0.0;
}

// int main() 
// {
//     size_t start = clock();

//     float similarity = 0;

//     for(int i = 0; i < 2000000; i++) {
//         similarity = textSimilarityBit("Mises Developer", "Mises Dev");
//     }

//     size_t end = clock();
//     float time = (float)(end - start) / CLOCKS_PER_SEC;

//     printf("text similarity bitset: %f\n", similarity);
//     printf("time execution biset: %f\n\n", time);

//     start = clock();

//     for(int i = 0; i < 2000000; i++) {
//         similarity = textSimilarity("Mises Developer", "Mises Dev");
//     }

//     end = clock();
//     time = (float)(end - start) / CLOCKS_PER_SEC;

//     printf("text similarity hashmap: %f\n", similarity);
//     printf("time execution hashmap: %f\n", time);

// }


#endif
