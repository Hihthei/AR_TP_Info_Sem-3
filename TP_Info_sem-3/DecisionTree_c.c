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

DecisionTreeNode* DecisionTreeNode_create(	DecisionTreeNode* left,
											DecisionTreeNode* right,
											Split split, int classID) {
	if (left == NULL) {
		CodeError_DT(NULL, "DecisionTreeNode_create - left = null");
		return NULL;
	}
	if (right == NULL) {
		CodeError_DT(NULL, "DecisionTreeNode_create - right = null");
		return NULL;
	}

	DecisionTreeNode* dtNode = (DecisionTreeNode*)calloc(1, sizeof(DecisionTreeNode));
	if (dtNode == NULL) {
		CodeError_DT(NULL, "DecisionTreeNode_create - alloc dtNode");
		return NULL;
	}

	dtNode->split = split;
	dtNode->classID = classID;

	return dtNode;
}

DecisionTreeNode* DecisionTree_create(	Subproblem* sp,
										int currentDepth, int maxDepth,
										float prunningThreshold) {
	if (sp == NULL) {
		CodeError_DT(NULL, "DecisionTree_create - sp = null");
		return NULL;
	}

	Split null_split = { 0 };

	DecisionTreeNode* dtTree = DecisionTreeNode_create(NULL, NULL, null_split, 0);
	if (dtTree == NULL) {
		CodeError_DT(NULL, "DecisionTree_create - sp = null");
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
	}
}

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