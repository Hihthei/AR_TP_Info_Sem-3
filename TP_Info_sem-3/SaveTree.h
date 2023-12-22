#ifndef SAVETREE_H
#define SAVETREE_H

#include "Settings.h"
#include "DecisionTree_h.h"
#include "RandomForest_h.h"

/**
 * @brief
 *
 *
 *
 * @param  :
 *
 * @return  :
 */

 //FONCTION : -----------------------------------------------------------------------------------------------------------

/**
 * @brief
 *
 *
 *
 * @param  :
 *
 * @return  :
 */
void SaveTree_saveTree(FILE** pfile, DecisionTreeNode* node, int direction);



/**
 * @brief
 *
 *
 *
 * @param  :
 *
 * @return  :
 */
void SaveTree_saveForest(char* fileName, RandomForest* forest);

#endif