#include "ABR_h.h"

//ABR TREE -----------------------------------------

BSTree* BSTree_Create() {
    BSTree* treeRoot = (BSTree*)calloc(1, sizeof(BSTree));

    if (treeRoot != NULL) {
        treeRoot->size = 0;
        return treeRoot;
    }
    return NULL;
}

void Tree_DeleteNode(BSNode* node) {
    if(node == NULL)
        return;

    Tree_DeleteNode(node->leftChild);
    Tree_DeleteNode(node->rightChild);
    free(node);
}

void BSTree_Delete(BSTree* tree) {
    if(tree == NULL)
        return;

    Tree_DeleteNode(tree->root);
    tree->root = NULL;
    free(tree);
}

BSNode* Tree_NewNode(int data) {
    BSNode* node = (BSNode*)calloc(1, sizeof(BSNode));
    if(node != NULL) {
        node->data = data;
        return node;
    }
    return NULL;
}

bool Tree_Find(BSTree* tree, int data, BSNode** node) {
    if(tree == NULL || tree->root == NULL)
        return false;

    BSNode* current = tree->root;

    while (1) {
        if(data == current->data){
            *node = current->parent;
            return true;
        }

        if(data < current->data) {
            if(current->leftChild == NULL) {
                *node = current;
                return false;
            }
            current = current->leftChild;
            continue;
        }
        else if(data > (int)current->data) {
            if(current->rightChild == NULL) {
                *node = current;
                return false;
            }
            current = current->rightChild;
            continue;
        }

        break;
    }

    return false;
}

void BSTree_Insert(BSTree* tree, int data) {
    if (tree == NULL)
        return;

    if (tree->root == NULL){
        tree->root = Tree_NewNode(data);
        tree->size++;
        return;
    }

    BSNode* node = NULL;

    if(!Tree_Find(tree, data, &node)) {
        if (data < node->data) {
            node->leftChild = Tree_NewNode(data);
            node->leftChild->parent = node;
        }
        else if (data > node->data) {
            node->rightChild = Tree_NewNode(data);
            node->rightChild->parent = node;
        }

        tree->size++;
    }
}

bool BSTree_Contains(BSTree* tree, int data) {
    if(tree == NULL || tree->root == NULL)
        return false;

    BSNode* current = tree->root;

    while (1) {
        if(data == current->data){
            return true;
        }

        if(data < current->data) {
            if(current->leftChild == NULL)
                break;

            current = current->leftChild;
            continue;
        }
        else if(data > (int)current->data) {
            if(current->rightChild == NULL)
                break;

            current = current->rightChild;
            continue;
        }

        break;
    }

    return false;
}

void Tree_Print(BSNode* node) {
    if (node == NULL)
        return;

    Tree_Print(node->leftChild);

    printf("%d ", node->data);

    Tree_Print(node->rightChild);
}

void BSTree_Print(BSTree* tree) {
    if (tree != NULL){
        Tree_Print(tree->root);
        printf("\n");
    }
}

void Tree_Print_UI(BSNode* node, int deed, int flag) {
    if(node != NULL){
        Tree_Print_UI(node->rightChild, deed+1, 0);

        for(int i = 0; i < deed-1; i++)
            printf("\t");

        if(deed > 0) {
            if(flag)
                printf("\t \\_");
            else
                printf("\t /_");
        }

        if(node->parent == NULL)
            printf("%d\t----------------------\n", node->data);
        else
            printf("%d\n", node->data);

        Tree_Print_UI(node->leftChild, deed+1, 1);
    }
}

void BSTree_Print_UI(BSTree* tree) {
    if(tree != NULL) {
        Tree_Print_UI(tree->root, 0, 0);
        printf("\n");
    }
}

void BSNode_SetLeft(BSNode* node, BSNode* left) {
    if(node != NULL) {
        node->leftChild = left;
    }
}

void BSNode_SetRight(BSNode* node, BSNode* right) {
    if(node != NULL) {
        node->rightChild = right;
    }
}

int BSTree_RemoveNode(BSTree *tree, BSNode *node) {
    if(tree != NULL && node != NULL) {
        int tmp = node->data;
        if(node == tree->root) {
            BSTree_Delete(tree);
            return tmp;
        }
        Tree_DeleteNode(node);
        return tmp;
    }
    return EXIT_FAILURE;
}

bool Tree_RemoveValue(BSTree* tree, BSNode* node) {
    if(tree != NULL && node != NULL) {
        if(node == tree->root) {
            BSTree_Delete(tree);
            return true;
        }
        Tree_DeleteNode(node);
        return true;
    }
    return false;
}

bool BSTree_RemoveValue(BSTree* tree, int value) {
    if(tree != NULL) {
        BSNode* node = NULL;
        return Tree_Find(tree, value, &node) ? Tree_RemoveValue(tree, node) : false;
    }
    return false;
}

int Tree_nodeCount(BSNode* node) {
    if (node == NULL)
        return 0;

    int tmp = 1;

    tmp += Tree_nodeCount(node->leftChild);
    tmp += Tree_nodeCount(node->rightChild);

    return tmp;
}

int BSTree_nodeCount(BSTree* tree)
{
    return tree != NULL ? Tree_nodeCount(tree->root) : -1;
}