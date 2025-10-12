#ifndef NAME_NODE_H
#define NAME_NODE_H

typedef struct NameNode {
    char* name;                  // Authorized personnel name
    struct NameNode* left;       // Pointer to left child
    struct NameNode* right;      // Pointer to right child
    int height;                  // Height of the node for AVL balancing
} NameNode;

#endif // NAME_NODE_H
