#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "levenshtein.h"

// Calculate the Levenshtein distance between two strings
int levenshteinDistance(const char* s1, const char* s2) {
    int lenS1 = strlen(s1);
    int lenS2 = strlen(s2);
    int** d = (int**)malloc((lenS1 + 1) * sizeof(int*));
    
    for (int i = 0; i <= lenS1; i++) {
        d[i] = (int*)malloc((lenS2 + 1) * sizeof(int));
        d[i][0] = i; // Deletion
    }
    for (int j = 0; j <= lenS2; j++) {
        d[0][j] = j; // Insertion
    }
    
    for (int i = 1; i <= lenS1; i++) {
        for (int j = 1; j <= lenS2; j++) {
            int cost = (s1[i - 1] == s2[j - 1]) ? 0 : 1;
            d[i][j] = fmin(fmin(d[i - 1][j] + 1, d[i][j - 1] + 1), d[i - 1][j - 1] + cost); // Min of delete, insert, and substitute
        }
    }

    int distance = d[lenS1][lenS2];

    for (int i = 0; i <= lenS1; i++) {
        free(d[i]);
    }
    free(d);
    
    return distance;
}
