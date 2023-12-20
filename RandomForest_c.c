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
	forest->classCount = 0;

	for (int i = 0; i < numberOfTrees; i++)
	{
		Subproblem* sp = Dataset_bagging(data, baggingProportion);

		if (!sp)
		{
			printf("No subproblem\n");
			return NULL;
		}

		forest->trees[i] = DecisionTree_create(sp, 0, maxDepth, prunningThreshold * baggingProportion);
	}
	
	return forest;
}