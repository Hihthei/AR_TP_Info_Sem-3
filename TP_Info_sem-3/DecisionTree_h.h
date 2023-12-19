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


#endif