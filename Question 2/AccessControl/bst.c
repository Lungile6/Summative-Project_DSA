#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "bst.h"

// Insert a name into the BST
NameNode* insertName(NameNode* root, const char* name) {
    if (root == NULL) {
        NameNode* newNode = (NameNode*)malloc(sizeof(NameNode));
        newNode->name = strdup(name); // Duplicate the string
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }
    if (strcmp(name, root->name) < 0) {
        root->left = insertName(root->left, name);
    } else if (strcmp(name, root->name) > 0) {
        root->right = insertName(root->right, name);
    }
    return root; // Return the unchanged node pointer
}

// Search for a name in the BST
int searchName(NameNode* root, const char* name) {
    if (root == NULL) {
        return 0; // Not found
    }
    if (strcmp(name, root->name) == 0) {
        return 1; // Exact match
    }
    if (strcmp(name, root->name) < 0) {
        return searchName(root->left, name);
    } else {
        return searchName(root->right, name);
    }
}

// Free the memory allocated for the BST
void freeTree(NameNode* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root->name);
        free(root);
    }
}

// Print the names in the BST (in-order)
void printTree(NameNode* root) {
    if (root != NULL) {
        printTree(root->left);
        printf("%s\n", root->name);
        printTree(root->right);
    }
}
