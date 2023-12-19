#include "DecisionTree_h.h"

//DECISION TREE -----------------------------------------

DecisionTreeNode* DecisionTreeNode_create(DecisionTreeNode* left, DecisionTreeNode* right, Split split, int classID)
{
	DecisionTreeNode* node = (DecisionTreeNode*)calloc(1, sizeof(DecisionTreeNode));
	node->left = node->right = NULL;
	node->split = split;
	node->classID = classID;

	return node;
}

DecisionTreeNode* DecisionTree_create(Subproblem* sp, int currentDepth, int maxDepth, float prunningThreshold)
{
	Split null_split = { .featureID = 0, .threshold = 0 };
	DecisionTreeNode* n = DecisionTreeNode_create(NULL, NULL, null_split, 0);
	if (!n)
	{
		printf("No node\n");
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