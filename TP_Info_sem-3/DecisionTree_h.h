#ifndef DECISIONTREE_H
#define DECISIONTREE_H

#include "Settings.h"
#include "Split_h.h"

typedef struct sDecisionTreeNode {
	struct sDecisionTreeNode* left;
	struct sDecisionTreeNode* right;
	Split split;
	int classID;
} DecisionTreeNode;

// Impl�mente l�algorithme donn� plus haut, tout en ajoutant une profondeur maximum qui sert de cas d�arr�t suppl�mentaire.
//On a �galement prunningThreshold qui repr�sente le seuil de puret� � atteindre pour qu�un n�ud soit une feuille;
DecisionTreeNode* DecisionTree_create(Subproblem* sp, int currentDepth, int maxDepth, float prunningThreshold);

DecisionTreeNode* DecisionTreeNode_create(DecisionTreeNode* left, DecisionTreeNode* right, Split split, int classID);

#endif