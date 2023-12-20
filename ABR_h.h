#ifndef ABR_LIBRARY_H
#define ABR_LIBRARY_H

#include "Settings.h"

typedef struct BSNode_s {
    struct BSNode_s* parent;
    struct BSNode_s* leftChild;
    struct BSNode_s* rightChild;
    int data;
} BSNode;

typedef struct BSTree_s {
    BSNode* root;
    int size;
} BSTree;


//ABR TREE -----------------------------------------
//BSTree -> Binary Search Tree
BSTree* BSTree_Create();
void BSTree_Delete(BSTree* tree);
void BSTree_Insert(BSTree* tree, int data);
bool BSTree_Contains(BSTree* tree, int data);
void BSTree_Print(BSTree* tree);
void BSTree_Print_UI(BSTree* tree);
void BSNode_SetLeft(BSNode* node, BSNode* left);
void BSNode_SetRight(BSNode* node, BSNode* right);
int BSTree_RemoveNode(BSTree *tree, BSNode *node);
bool BSTree_RemoveValue(BSTree *tree, int value);
int BSTree_nodeCount(BSTree* tree);

#endif
