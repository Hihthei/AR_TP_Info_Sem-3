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



/**
 * @brief
 *
 *
 *
 * @param  :
 *
 * @return  :
 */
DecisionTreeNode* SaveTree_loadTree(FILE** pfile);



/**
 * @brief
 *
 *
 *
 * @param  :
 *
 * @return  :
 */
RandomForest* SaveTree_loadForest(char* fileName);

#endif