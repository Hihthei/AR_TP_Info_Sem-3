#include "DecisionTree_h.h"

void CodeError_DT(void** freeptr, char* errormsg) {
	if (strcmp(errormsg, "") != 0 && errormsg != NULL)
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
	if (dtNode == NULL) {
		CodeError_DT(NULL, "DecisionTreeNode_create - alloc dtNode");
		return NULL;
	}
	dtNode->left = left;
	dtNode->right = right;
	dtNode->split = split;
	dtNode->classID = classID;

	return dtNode;
}

DecisionTreeNode* DecisionTree_create(Subproblem* subproblem,
	int currentDepth, int maxDepth,
	float prunningThreshold) {
	if (subproblem == NULL) {
		CodeError_DT(NULL, "DecisionTree_create - subproblem = NULL");
		return NULL;
	}

	Split null_split = { 0 };
	
	DecisionTreeNode* dtNode = DecisionTreeNode_create(NULL, NULL, null_split, 0);
	if (dtNode == NULL) {
		CodeError_DT(NULL, "DecisionTree_create - dtNode = NULL");
		return NULL;
	}

	float majorClassCount_sp = 0;
	int majorClassID_sp = subproblem->classes[0].instanceCount;
	for (int i = 1; i < subproblem->classCount; i++) {
		if (subproblem->classes[i].instanceCount > majorClassCount_sp) {
			majorClassCount_sp = subproblem->classes[i].instanceCount;
			majorClassID_sp = i;
		}
	}
	float purete_sp = (float)majorClassCount_sp / (float)subproblem->instanceCount;;
	
	if (purete_sp >= prunningThreshold) {
		dtNode->classID = majorClassCount_sp;
		return dtNode;
	}

	dtNode->split = Split_compute(subproblem);

	Subproblem* subproblem_left = Subproblem_create(subproblem->capacity, subproblem->featureCount, subproblem->classCount);
	if (subproblem_left == NULL) {
		CodeError_DT(NULL, "DecisionTree_create - subproblem_left = NULL");
		CodeError_DT(&dtNode, NULL);
		return NULL;
	}
	
	Subproblem* subproblem_right = Subproblem_create(subproblem->capacity, subproblem->featureCount, subproblem->classCount);
	if (subproblem_right == NULL) {
		CodeError_DT(NULL, "DecisionTree_create - subproblem_right = NULL");
		CodeError_DT(&dtNode, NULL);
		return NULL;
	}

	for (int i = 0; i < subproblem->instanceCount; i++) {
		Instance* current_instance = &(subproblem->instances[i]);

		int feature_value = current_instance->values[dtNode->split.featureID];

		if (feature_value <= dtNode->split.threshold) {
			if (!Subproblem_insert(subproblem_left, current_instance)) {
				CodeError_DT(&subproblem_left, "DecisionTree_create - echec Subproblem_insert pour subproblem_left");
				CodeError_DT(&dtNode, NULL);
				Subproblem_destroy(subproblem_right);

				return NULL;
			}
		}
		else {
			if (!Subproblem_insert(subproblem_right, current_instance)) {
				CodeError_DT(&subproblem_right, "DecisionTree_create - echec Subproblem_insert pour subproblem_right");
				CodeError_DT(&dtNode, NULL);
				Subproblem_destroy(subproblem_left);
				return NULL;
			}
		}
	}

	dtNode->left = DecisionTree_create(subproblem_left, currentDepth - 1, maxDepth, prunningThreshold);
	dtNode->right = DecisionTree_create(subproblem_right, currentDepth - 1, maxDepth, prunningThreshold);

	return dtNode;
}

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