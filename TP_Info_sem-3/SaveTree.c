#include "SaveTree.h"

//FONCTION : -----------------------------------------------------------------------------------------------------------

void SaveTree_saveTree(FILE** pfile, DecisionTreeNode* node, int direction) {
	assert(pfile);
	assert(*pfile);
	
	if (node == NULL)
		return;

	if (node->left == NULL && node->right == NULL) {
		fprintf(*pfile, "%d\n", 2);
		fprintf(*pfile, "%d %f %d\n", node->split.featureID, node->split.threshold, node->classID);
		return;
	}
	else {
		fprintf(*pfile, "%d\n", direction);
		fprintf(*pfile, "%d %f %d\n", node->split.featureID, node->split.threshold, node->classID);
	}

	SaveTree_saveTree(pfile, node->left, 0);
	SaveTree_saveTree(pfile, node->right, 1);
}

void SaveTree_saveForest(char* fileName, RandomForest* forest) {
	assert(fileName);
	assert(forest);

	FILE* pfile = fopen(fileName, "w");

	fprintf(pfile, "%d %d\n", forest->treeCount, forest->classCount);

	for (int i = 0; i < forest->treeCount; i++) {

		fprintf(pfile, "%d\n", DecisionTree_nodeCount(forest->trees[i]));

		SaveTree_saveTree(&pfile, forest->trees[i], -1);

		fprintf(pfile, "-2\n\n");
	}

	fclose(pfile);
}

DecisionTreeNode* SaveTree_loadTree(FILE** pfile) {
	assert(pfile);
	assert(*pfile);

	int direction = 0, featureID = 0, threshold = 0, classID = 0;

	DecisionTreeNode* node = (DecisionTreeNode*)calloc(1, sizeof(DecisionTreeNode));
	assert(node);

	fscanf(*pfile, "%d %f %d\n", &featureID, &threshold, &classID);
	fscanf(pfile, "%d\n", &direction);

	switch (direction)
	{
	case 0:
		node->split.featureID = featureID;
		node->split.threshold = threshold;
		node->left = SaveTree_loadTree(pfile);
		break;
	case 1:
		node->split.featureID = featureID;
		node->split.threshold = threshold;
		node->right = SaveTree_loadTree(pfile);
		break;
	case 2:
		node->classID = classID;
		break;
	default:
		break;
	}

	else
	{
		assert(node != NULL);
		fscanf(file, "%d\t%f\n", &node->split.featureID, &node->split.threshold);
		node->left = ReadBillyLaNode(file);
		node->right = ReadBillyLaNode(file);
	}
	return node;

	if (node == NULL)
		return;

	if (node->left == NULL && node->right == NULL) {
		fprintf(*pfile, "%d\n", 2);
		return;
	}
	else {
		fprintf(*pfile, "%d\n", direction);
		fprintf(*pfile, "%d %f %d\n", node->split.featureID, node->split.threshold, node->classID);
	}

	SaveTree_saveTree(pfile, node->left, 0);
	SaveTree_saveTree(pfile, node->right, 1);

	return NULL;
}

RandomForest* SaveTree_loadForest(char* fileName) {
	assert(fileName);

	FILE* pfile = fopen(fileName, "r");

	int treeCount = 0, classCount = 0, nodeCount = 0;



	fscanf(pfile, "%d %d\n", &treeCount, &classCount);

	for (int i = 0; i < treeCount; i++) {

		fscanf(pfile, "%d\n", &nodeCount);

		int tmp = 0;

		fscanf(pfile, "%d\n", &tmp);

		if (tmp != -1) {
			fclose(pfile);
			return NULL;
		}

		SaveTree_loadTree(&pfile);
	}

	fclose(pfile);

	return NULL;
}