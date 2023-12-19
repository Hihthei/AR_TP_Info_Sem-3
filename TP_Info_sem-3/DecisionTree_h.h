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

/**
 * @brief
 *
 *
 *
 * @param  :
 *
 * @return
 */

 //FONCTION : -----------------------------------------------------------------------------------------------------------

// Implémente l’algorithme donné plus haut, tout en ajoutant une profondeur maximum qui sert de cas d’arrêt supplémentaire.
//On a également prunningThreshold qui représente le seuil de pureté à atteindre pour qu’un nœud soit une feuille;
DecisionTreeNode* DecisionTree_create(Subproblem* sp, int currentDepth, int maxDepth, float prunningThreshold);

DecisionTreeNode* DecisionTreeNode_create(DecisionTreeNode* left, DecisionTreeNode* right, Split split, int classID);

#endif