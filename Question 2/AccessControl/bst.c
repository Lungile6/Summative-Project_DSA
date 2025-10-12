#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "bst.h"

// Helper function to get height of a node
int getHeight(NameNode* node) {
    if (node == NULL) return 0;
    return node->height;
}

// Helper function to get maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Helper function to get balance factor of a node
int getBalance(NameNode* node) {
    if (node == NULL) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Right rotation for AVL balancing
NameNode* rightRotate(NameNode* y) {
    NameNode* x = y->left;
    NameNode* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

// Left rotation for AVL balancing
NameNode* leftRotate(NameNode* x) {
    NameNode* y = x->right;
    NameNode* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

// Insert a name into the AVL BST
NameNode* insertName(NameNode* root, const char* name) {
    // 1. Perform normal BST insertion
    if (root == NULL) {
        NameNode* newNode = (NameNode*)malloc(sizeof(NameNode));
        newNode->name = strdup(name); // Duplicate the string
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->height = 1; // New node is initially at height 1
        return newNode;
    }
    
    if (strcmp(name, root->name) < 0) {
        root->left = insertName(root->left, name);
    } else if (strcmp(name, root->name) > 0) {
        root->right = insertName(root->right, name);
    } else {
        // Duplicate names not allowed
        return root;
    }

    // 2. Update height of this ancestor node
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    // 3. Get the balance factor of this ancestor node
    int balance = getBalance(root);

    // 4. If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && strcmp(name, root->left->name) < 0)
        return rightRotate(root);

    // Right Right Case
    if (balance < -1 && strcmp(name, root->right->name) > 0)
        return leftRotate(root);

    // Left Right Case
    if (balance > 1 && strcmp(name, root->left->name) > 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Left Case
    if (balance < -1 && strcmp(name, root->right->name) < 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
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
