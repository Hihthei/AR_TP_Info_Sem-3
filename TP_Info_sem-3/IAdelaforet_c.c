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

	if ((!tree->right)&&(!tree->left))
	{
		return tree->classID;
	}
	else if (tree->split.threshold >= instance->values[tree->split.featureID])
	{
		DecisionTree_predict(tree->left, instance);
	}
	else
	{
		DecisionTree_predict(tree->right, instance);
	}
}

float DecisionTree_evaluate(DecisionTreeNode* tree, Dataset* dataset)
{
	if (!tree)
	{
		printf("No tree\n");
		return -1;
	}

	if (!dataset)
	{
		printf("No dataset\n");
		return -1;
	}

	int nb_success = 0;

	for (int i = 0; i < dataset->instanceCount; i++)
	{
		if (DecisionTree_predict(tree, &dataset->instances[i]) == dataset->instances[i].classID)
		{
			nb_success++;
		}
	}
	return (float)nb_success / (float)dataset->instanceCount;
}

Subproblem* Dataset_bagging(Dataset* data, float proportion)
{
	if (!data)
	{
		printf("No data\n");
		return NULL;
	}

	Subproblem* subproblem = Subproblem_create(data->instanceCount, data->featureCount, data->classCount);
	if (!subproblem)
	{
		printf("No subprobleù\n");
		return NULL;
	}

	for (int i = 0 ; i < data->instanceCount * proportion; i++)
	{
		
	}

	return subproblem;
}