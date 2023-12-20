#include "IAdelaforet_h.h"

int DecisionTree_predict(DecisionTreeNode* tree, Instance* instance)
{
	if (!tree)
	{
		printf("No tree\n");
		return -1;
	}

	if (!instance)
	{
		printf("No instance\n");
		return -1;
	}

	if ((!tree->right) && (!tree->left))
	{
		return tree->classID;
	}
	else if (tree->split.threshold <= instance->values[tree->split.featureID])
	{
		DecisionTree_predict(tree->left, instance);
	}
	else
	{
		DecisionTree_predict(tree->right, instance);
	}
}