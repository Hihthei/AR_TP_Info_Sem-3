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
		SaveTree_saveTree(&pfile, forest->trees[i], -1);

		fprintf(pfile, "-2\n\n");
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

	fscanf(*pfile, "%d %f %d\n", &featureID, &threshold, &classID);
	fscanf(*pfile, "%d\n", &direction);

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
	case -2:
		break;
	default:
		break;
	}
	return node;
}

RandomForest* SaveTree_loadForest(char* fileName) {
	assert(fileName);

	FILE* pfile = fopen(fileName, "r");
	if (pfile == NULL)
		return NULL;

	RandomForest* rf = (RandomForest*)calloc(1, sizeof(RandomForest));
	assert(rf);

	fscanf(pfile, "%d %d\n", &rf->treeCount, &rf->classCount);

	rf->trees = (DecisionTreeNode**)calloc(rf->treeCount, sizeof(DecisionTreeNode*));
	assert(rf->trees);

	for (int i = 0; i < rf->treeCount; i++) {
		rf->trees[i] = SaveTree_loadTree(&pfile);
		fscanf(pfile, "\n");
	}

	fclose(pfile);

	return rf;
}