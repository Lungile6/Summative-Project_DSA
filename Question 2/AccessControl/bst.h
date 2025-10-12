#ifndef BST_H
#define BST_H

#include "name_node.h"

// Function prototypes
NameNode* insertName(NameNode* root, const char* name);
int searchName(NameNode* root, const char* name);
void freeTree(NameNode* root);
void printTree(NameNode* root);

#endif // BST_H
