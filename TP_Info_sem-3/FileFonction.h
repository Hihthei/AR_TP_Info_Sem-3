#ifndef FILEFONCTION_H
#define FILEFONCTION_H

#include "SaveTree.h"

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
bool FileFonction_fileExist(char* fileName);



/**
 * @brief
 *
 *
 *
 * @param  :
 *
 * @return  :
 */
void FileFonction_fileOverwrite(char* fileName);



/**
 * @brief
 *
 *
 *
 * @param  :
 *
 * @return  :
 */
void FileFonction_createFile(char* fileName);



/**
 * @brief
 *
 *
 *
 * @param  :
 *
 * @return  :
 */
FILE* FileFonction_loadFile(char* fileName, char* mode);



/**
 * @brief
 *
 *
 *
 * @param  :
 *
 * @return  :
 */
void FileFonction_deleteFile(char* fileName);



/**
 * @brief
 *
 *
 *
 * @param  :
 *
 * @return  :
 */
void FileFonction_writeFile();



/**
 * @brief
 *
 *
 *
 * @param  :
 *
 * @return  :
 */
void FileFonction_saveFile();

#endif
