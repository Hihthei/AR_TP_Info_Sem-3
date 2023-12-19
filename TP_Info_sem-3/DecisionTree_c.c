#include "DecisionTree_h.h"

//void CodeError(void** freeptr, char* errormsg) {
//	if (strcmp(errormsg, "") != 0 && errormsg != NULL)
//		printf("\nCODE ERROR : \" %s \" \n\n", errormsg);
//
//	if (freeptr != NULL && *freeptr != NULL) {
//		free(*freeptr);
//		*freeptr = NULL;
//	}
//}

//FONCTION : -----------------------------------------------------------------------------------------------------------

void DecisionTree_destroy(DecisionTreeNode* decisionTree) {
	if (decisionTree == NULL)
		return;

	DecisionTree_destroy(decisionTree->left);
	DecisionTree_destroy(decisionTree->right);
	free(decisionTree);
}

int Decision_nodeCount(DecisionTreeNode* node) {
	if (node == NULL)
		return 0;

	int tmp = 1;

	tmp += Decision_nodeCount(node->left);
	tmp += Decision_nodeCount(node->right);

	return tmp;
}