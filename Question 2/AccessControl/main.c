#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"
#include "levenshtein.h"

#define MAX_NAMES 40
#define LOG_FILE "unrecognized_names.log"

void loadNames(NameNode** root) {
    FILE* file = fopen("authorized_names.txt", "r");
    if (!file) {
        perror("Could not open authorized_names.txt");
        exit(EXIT_FAILURE);
    }

    char name[50];
    while (fgets(name, sizeof(name), file) && *root == NULL) {
        name[strcspn(name, "\n")] = 0; // Remove newline character
        *root = insertName(*root, name);
    }

    while (fgets(name, sizeof(name), file)) {
        name[strcspn(name, "\n")] = 0; // Remove newline character
        *root = insertName(*root, name);
    }

    fclose(file);
}

void logUnrecognized(const char* name) {
    FILE* logFile = fopen(LOG_FILE, "a");
    if (logFile) {
        fprintf(logFile, "%s\n", name);
        fclose(logFile);
    } else {
        perror("Could not open log file");
    }
}

void findClosest(NameNode* node, const char* inputName, int* minDistance, char* closestName, int* found) {
    if (node == NULL) return;
    int distance = levenshteinDistance(node->name, inputName);
    if (distance < *minDistance) {
        *minDistance = distance;
        strcpy(closestName, node->name);
        *found = 1;
    }
    findClosest(node->left, inputName, minDistance, closestName, found);
    findClosest(node->right, inputName, minDistance, closestName, found);
}

void suggestSimilarNames(NameNode* root, const char* inputName) {
    int minDistance = 100; // Arbitrarily large distance
    char closestName[50];
    int found = 0;

    findClosest(root, inputName, &minDistance, closestName, &found);

    if (found) {
        printf("Did you mean: %s?\n", closestName);
    }
}

int main() {
    NameNode* root = NULL;
    loadNames(&root);

    char inputName[50];
    while (1) {
        printf("Enter your name (or 'exit' to quit): ");
        fgets(inputName, sizeof(inputName), stdin);
        inputName[strcspn(inputName, "\n")] = 0; // Remove newline

        if (strcmp(inputName, "exit") == 0) {
            break; // Exit the loop
        }

        if (searchName(root, inputName)) {
            printf("Access granted.\n");
        } else {
            printf("Access denied.\n");
            logUnrecognized(inputName);
            suggestSimilarNames(root, inputName);
        }
    }

    freeTree(root); // Free the BST memory
    return 0;
}
