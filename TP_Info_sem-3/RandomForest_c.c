#include "RandomForest_h.h"

RandomForest* RandomForest_create(int numberOfTrees, Dataset* data, int maxDepth, float baggingProportion, float prunningThreshold)
{
	if (!data)
	{
		printf("No data\n");
		return NULL;
	}

	RandomForest* forest = (RandomForest*)calloc(1, sizeof(RandomForest));
	forest->treeCount = numberOfTrees;
	forest->classCount = data->classCount;

	Subproblem* sp0 = Dataset_bagging(data, baggingProportion);
	forest->trees = calloc(numberOfTrees, sizeof(DecisionTreeNode*));
	for (int i = 0; i < numberOfTrees; i++)
	{
		Subproblem* sp = Dataset_bagging(data, baggingProportion);
		if (!sp)
		{
			printf("No subproblem\n");
			return NULL;
		}

		forest->trees[i] = DecisionTree_create(sp, 0, maxDepth, prunningThreshold);
		Subproblem_destroy(sp);
	}
	
	return forest;
}

int RandomForest_predict(RandomForest* rf, Instance* instance)
{
	if (!rf)
	{
		printf("No forest\n");
		return -1;
	}
	if (!instance)
	{
		printf("No instance\n");
		return -1;
	}

	int prediction = 0, prediction_value = 0, *tab = calloc(rf->classCount, sizeof(int));
	for (int i = 0 ; i < rf->treeCount ; i++)
	{
		tab[DecisionTree_predict(rf->trees[i], instance)]++;
	}
	for (int i = 0 ; i < rf->classCount ; i++)
	{
		if (prediction_value < tab[i])
		{
			prediction = i;
		}
	}
	free(tab);
	return prediction;
}

float RandomForest_evaluate(RandomForest* rf, Dataset* data) {
	
	if (!rf)
	{
		printf("No forest\n");
		return -1;
	}

	if (!data)
	{
		printf("No dataset\n");
		return -1;
	}

	int nb_success = 0;

	for (int i = 0; i < data->instanceCount; i++)
	{
		if (RandomForest_predict(rf, &data->instances[i]) == data->instances[i].classID)
		{
			nb_success++;
		}
	}
	return (float)nb_success / (float)data->instanceCount;
}

int RandomForest_nodeCount(RandomForest* rf)
{
	if (!rf)
	{
		printf("No forest\n");
		return -1;
	}

	int rf_node_sum = 0;
	for (int i = 0; i < rf->treeCount; i++)
	{
		rf_node_sum += DecisionTree_nodeCount(rf->trees[i]);
	}
}

void RandomForest_destroy(RandomForest* rf)
{
	if (!rf)
	{
		printf("No more forest in Amazonie\n");
		return;
	}

	for (int i = 0; i < rf->treeCount; i++)
	{
		DecisionTree_destroy(rf->trees[i]);
	}
	free(rf);
}