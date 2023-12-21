#include "DecisionTree_h.h"

void CodeError_DT(void** freeptr, char* errormsg) {
	if (errormsg != NULL)
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
	DecisionTreeNode* dtNode = (DecisionTreeNode*)calloc(1, sizeof(DecisionTreeNode));
	assert(dtNode);

	dtNode->left = left;
	dtNode->right = right;
	dtNode->split = split;
	dtNode->classID = classID;

	return dtNode;
}

int DecisionTree_mainClass(Subproblem* subproblem) {
    int max = 0;
    int mainClass = 0;

    for (int i = 0; i < subproblem->classCount; i++) {
        if (subproblem->classes[i].instanceCount > max) {
            max = subproblem->classes[i].instanceCount;
            mainClass = i;
        }
    }
    return mainClass;
}

DecisionTreeNode* DecisionTree_create(Subproblem* subproblem, int currentDepth, int maxDepth, float prunningThreshold)
{
	if (subproblem == NULL)
		return NULL;

	Split null_split = { 0 };

	DecisionTreeNode* dtNode = DecisionTreeNode_create(NULL, NULL, null_split, 0);

	float pure = (float)(subproblem->classes[DecisionTree_mainClass(subproblem)].instanceCount) / (float)(subproblem->instanceCount);

	if (subproblem->instanceCount <= 0)
	{
		return NULL;
	}

	if (currentDepth >= maxDepth || pure >= prunningThreshold) {
		dtNode->classID = (int)DecisionTree_mainClass(subproblem);
		dtNode->left = NULL;
		dtNode->right = NULL;
		return dtNode;
	}

	dtNode->split = Split_compute(subproblem);

	Subproblem* Spl = Subproblem_create(subproblem->instanceCount, subproblem->featureCount, subproblem->classCount);
	Subproblem* Spr = Subproblem_create(subproblem->instanceCount, subproblem->featureCount, subproblem->classCount);

	for (int i = 0; i < subproblem->instanceCount; i++)
	{
		if (subproblem->instances[i]->values[dtNode->split.featureID] <= dtNode->split.threshold)
		{
			Subproblem_insert(Spl, subproblem->instances[i]);
		}
		else
		{
			Subproblem_insert(Spr, subproblem->instances[i]);
		}
	}

	// Construction récursive des sous-arbres gauche et droit
	dtNode->left = DecisionTree_create(Spl, currentDepth + 1, maxDepth, prunningThreshold);
	dtNode->right = DecisionTree_create(Spr, currentDepth + 1, maxDepth, prunningThreshold);

	Subproblem_destroy(Spl);
	Subproblem_destroy(Spr);

	return dtNode;
}
/*

DecisionTreeNode* DecisionTree_create(Subproblem* subproblem, int currentDepth, int maxDepth, float prunningThreshold)
{
	if (subproblem == NULL)
		return NULL;

	assert(dtNode);


	float majorClassCount_sp = 0;
	int majorClassID_sp = subproblem->classes[0].instanceCount;
	for (int i = 1; i < subproblem->classCount; i++) {
		if (subproblem->classes[i].instanceCount > majorClassID_sp) {
			majorClassCount_sp = (float)subproblem->classes[i].instanceCount;
            majorClassID_sp = i;
		}
	}

	float purete_sp = (float)majorClassCount_sp / (float)subproblem->instanceCount;

	if (subproblem->instanceCount <= 0)
		return NULL;

	if (purete_sp >= prunningThreshold || currentDepth >= maxDepth) {
		dtNode->classID = (int)majorClassCount_sp;
		dtNode->left = NULL;
		dtNode->right = NULL;
		return dtNode;
	}

	dtNode->split = Split_compute(subproblem);
	if (dtNode->split.threshold == 0 && dtNode->split.featureID == 0) {
		CodeError_DT(NULL, "DecisionTree_create - dtNode->split == NULL");
		return NULL;
	}

	Subproblem* subproblem_left = Subproblem_create(subproblem->instanceCount, subproblem->featureCount, subproblem->classCount);
	if (subproblem_left == NULL) {
		CodeError_DT((void**)&dtNode, "DecisionTree_create - subproblem_left = NULL");
		return NULL;
	}

	Subproblem* subproblem_right = Subproblem_create(subproblem->instanceCount, subproblem->featureCount, subproblem->classCount);
	if (subproblem_right == NULL) {
		CodeError_DT((void**)&dtNode, "DecisionTree_create - subproblem_right = NULL");
		return NULL;
	}

	for (int i = 0; i < subproblem->instanceCount; i++)
	{
		if (subproblem->instances[i]->values[dtNode->split.featureID] <= dtNode->split.threshold)
			Subproblem_insert(subproblem_left, subproblem->instances[i]);
		else
			Subproblem_insert(subproblem_right, subproblem->instances[i]);
	}

	dtNode->left = DecisionTree_create(subproblem_left, currentDepth + 1, maxDepth, prunningThreshold);
	if (dtNode->left == NULL) {
		CodeError_DT((void**)&dtNode, "DecisionTree_create - alloc dtNode->left == NULL");
		return NULL;
	}

	dtNode->right = DecisionTree_create(subproblem_right, currentDepth + 1, maxDepth, prunningThreshold);
  if (dtNode->right == NULL) {
		CodeError_DT((void**)&dtNode, "DecisionTree_create - alloc dtNode->right == NULL");
		return NULL;
	}

	Subproblem_destroy(subproblem_left);
    subproblem_left = NULL;

	Subproblem_destroy(subproblem_right);
    subproblem_right = NULL;

	return dtNode;
}*/

void DecisionTree_destroy(DecisionTreeNode* decisionTree) {
	if (decisionTree == NULL)
		return;

	DecisionTree_destroy(decisionTree->left);
	DecisionTree_destroy(decisionTree->right);

	free(decisionTree);
}

int DecisionTree_nodeCount(DecisionTreeNode* node) {
	if (node == NULL)
		return 0;

	int tmp = 1;

	tmp += DecisionTree_nodeCount(node->left);
	tmp += DecisionTree_nodeCount(node->right);

	return tmp;
}

int DecisionTree_predict(DecisionTreeNode* tree, Instance* instance) {
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
	else if (tree->split.threshold > instance->values[tree->split.featureID])
	{
		return DecisionTree_predict(tree->left, instance);
	}
	else
	{
		return DecisionTree_predict(tree->right, instance);
	}
}

float DecisionTree_evaluate(DecisionTreeNode* tree, Dataset* dataset) {
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
