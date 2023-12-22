#include "SaveTree.h"

//FONCTION : -----------------------------------------------------------------------------------------------------------

void SaveTree_saveTree(FILE** pfile, DecisionTreeNode* node, int direction) {
	assert(pfile);
	assert(*pfile);
	
	if (node == NULL)
		return;

	if (node->left == NULL && node->right == NULL) {
		fprintf(*pfile, "%d %f %d %d\n", node->split.featureID, node->split.threshold, node->classID, 2);
		return;
	}
	else
		fprintf(*pfile, "%d %f %d %d\n", node->split.featureID, node->split.threshold, node->classID, direction);

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

		fprintf(pfile, "\n\n------------\n\n\n");
	}

	fclose(pfile);
}

DecisionTreeNode* SaveTree_loadTree(FILE** pfile) {
	return NULL;
}

RandomForest* SaveTree_loadForest(char* fileName) {
	return NULL;
}