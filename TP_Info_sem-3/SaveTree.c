#include "SaveTree.h"

//FONCTION : -----------------------------------------------------------------------------------------------------------

void SaveTree_saveTree(FILE** pfile, DecisionTreeNode* node, int direction) {
	assert(pfile);
	assert(*pfile);
	
	if (node == NULL)
		return;

	if (node->left == NULL && node->right == NULL) {
		fprintf(*pfile, "%d\t%d\n", 2, node->classID);
		return;
	}
	else {
		fprintf(*pfile, "%d\t%d %f\n", direction, node->split.featureID, node->split.threshold);
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
		SaveTree_saveTree(&pfile, forest->trees[i], -1);
		fprintf(pfile, "\n");
	}

	fclose(pfile);
}

DecisionTreeNode* SaveTree_loadTree(FILE** pfile) {
	assert(pfile);
	assert(*pfile);

	int direction = 0, featureID = 0, classID = 0;
	float threshold = 0;

	DecisionTreeNode* node = (DecisionTreeNode*)calloc(1, sizeof(DecisionTreeNode));
	assert(node);

	int noWarning = fscanf(*pfile, "%d\t", &direction);

	switch (direction)
	{
	case 2:
		noWarning = fscanf(*pfile, "%d\n", &node->classID);
		break;
	/*case 1:
		node->split.featureID = featureID;
		node->split.threshold = threshold;

		node->right = SaveTree_loadTree(pfile);
		break;
	case 2:
		node->classID = classID;
		break;*/
	default:
		noWarning = fscanf(*pfile, "%d %f\n", &node->split.featureID, &node->split.threshold);
		node->left = SaveTree_loadTree(pfile);
		node->right = SaveTree_loadTree(pfile);
		break;
	}
	return node;
}

RandomForest* SaveTree_loadForest(char* fileName) {
	if (fileName == NULL || fileName == "")
		return NULL;

	FILE* pfile = fopen(fileName, "r");
	if (pfile == NULL)
		return NULL;

	RandomForest* rf = (RandomForest*)calloc(1, sizeof(RandomForest));
	if (rf == NULL)
		return NULL;

	int noWarning= fscanf(pfile, "%d %d\n", &rf->treeCount, &rf->classCount);

	rf->trees = (DecisionTreeNode**)calloc(rf->treeCount, sizeof(DecisionTreeNode*));
	if (rf->trees == NULL)
		return NULL;

	for (int i = 0; i < rf->treeCount; i++) {
		rf->trees[i] = SaveTree_loadTree(&pfile);
		noWarning = fscanf(pfile, "\n");
	}

	fclose(pfile);

	return rf;
}