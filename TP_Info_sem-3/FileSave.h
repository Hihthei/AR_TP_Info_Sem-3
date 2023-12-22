#ifndef FILESAVE_H
#define FILESAVE_H

#include "Settings.h"

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
int FileSave_UserInterface(int nodeCount, float trainScore, float testScore);



/**
 * @brief
 *
 *
 *
 * @param  :
 *
 * @return  :
 */
FILE* FileSave_loadFile();



/**
 * @brief
 *
 *
 *
 * @param  :
 *
 * @return  :
 */
bool FileSave_clearFile();



/**
 * @brief
 *
 *
 *
 * @param  :
 *
 * @return  :
 */
bool FileSave_deleteFile(char* fileName);



/**
 * @brief
 *
 *
 *
 * @param  :
 *
 * @return  :
 */
bool FileSave_writeFile();



/**
 * @brief
 *
 *
 *
 * @param  :
 *
 * @return  :
 */
bool FileSave_saveFile();

#endif
