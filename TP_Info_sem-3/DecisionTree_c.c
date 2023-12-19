#include "DecisionTree_h.h"

void CodeError_DT(void** freeptr, char* errormsg) {
	if (strcmp(errormsg, "") != 0 && errormsg != NULL)
		printf("\nCODE ERROR : \" %s \" \n\n", errormsg);

	if (freeptr != NULL && *freeptr != NULL) {
		free(*freeptr);
		*freeptr = NULL;
	}
}

//FONCTION : -----------------------------------------------------------------------------------------------------------

/*
DecisionTreeNode* DecisionTreeNode_create(	DecisionTreeNode* left,
											DecisionTreeNode* right,
											Split split, int classID) {
	DecisionTreeNode* dtNode = (DecisionTreeNode*)calloc(1, sizeof(DecisionTreeNode));
	if (dtNode == NULL) {
		CodeError_DT(NULL, "DecisionTreeNode_create - alloc dtNode");
		return NULL;
	}
	dtNode->left = left;
	dtNode->right = right;
	dtNode->split = split;
	dtNode->classID = classID;

	return dtNode;
}

DecisionTreeNode* DecisionTree_create(Subproblem* subproblem,
	int currentDepth, int maxDepth,
	float prunningThreshold) {
	if (subproblem == NULL) {
		CodeError_DT(NULL, "DecisionTree_create - subproblem = null");
		return NULL;
	}

	Split null_split = { 0 };
	
	DecisionTreeNode* dtTree = DecisionTreeNode_create(NULL, NULL, null_split, 0);
	if (dtTree == NULL) {
		CodeError_DT(NULL, "DecisionTree_create - dtTree = null");
		return NULL;
	}

	float majorClassCount_sp = 0;
	int majorClassID_sp = 0;
	for (int i = 0; i < sp->classCount; i++)
	{
		if (majorClassCount_sp < sp->classes[i].instanceCount)
		{
			majorClassCount_sp = sp->classes[i].instanceCount;
			majorClassID_sp = i;
		}
	}
	float purete_sp = majorClassCount_sp / (float)(sp->instanceCount);
	if (purete_sp >= prunningThreshold)
	{
		n->classID = majorClassCount_sp;
		return n;
	}
	n->split = Split_compute(sp);
	n->left = DecisionTree_create(spl, currentDepth - 1, maxDepth, prunningThreshold);
	n->right = DecisionTree_create(spr, currentDepth - 1, maxDepth, prunningThreshold);

	return n;
}
*/

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