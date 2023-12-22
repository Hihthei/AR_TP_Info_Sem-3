#include "SaveTree.h"

//FONCTION : -----------------------------------------------------------------------------------------------------------

void SaveTree_saveTree(FILE** pfile, DecisionTreeNode* node) {
	assert(pfile);
	assert(*pfile);
	
	if (node == NULL)
		return;

	if(!fprintf(*pfile, "%d %f %d\n", node->split.featureID, node->split.threshold, node->classID))
		return;

	SaveTree_saveTree(pfile, node->left);
	SaveTree_saveTree(pfile, node->right);
}

void SaveTree_saveForest(char* fileName, RandomForest* forest) {
	assert(fileName);
	assert(forest);

	FILE* pfile = fopen(fileName, "w");

	if (!fprintf(pfile, "%d %d\n", forest->treeCount, forest->classCount));
		return;

	for (int i = 0; i < forest->treeCount; i++) {
		SaveTree_saveTree(&pfile, forest->trees[i]);

		if (!fprintf(pfile, "\n\n-1\n\n"));
			return;
	}
}
