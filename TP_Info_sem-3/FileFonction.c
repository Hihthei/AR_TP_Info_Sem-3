#include "FileFonction.h"

void CodeError_FILE(void** freeptr, char* errormsg) {
	if (errormsg != NULL)
		printf("\nCODE ERROR : \" %s \" \n\n", errormsg);

	if (freeptr != NULL && *freeptr != NULL) {
		free(*freeptr);
		*freeptr = NULL;
	}
}

//FONCTION : -----------------------------------------------------------------------------------------------------------

bool FileFonction_fileExist(char* fileName) {
	assert(fileName);

	FILE* pfile = NULL;
	pfile = fopen(fileName, "r");

	if (pfile == NULL)
		return false;
	else {
		fclose(pfile);
		return true;
	}
}

void FileFonction_fileOverwrite(char* fileName) {
	assert(fileName);

	FileFonction_deleteFile(fileName);
	FileFonction_createFile(fileName);

	return;
}

void FileFonction_createFile(char* fileName) {
	assert(fileName);

	char command[256] = "";

	sprintf(command, "ECHO.> %s", fileName);

	system(command);
}

void FileFonction_deleteFile(char* fileName) {
	assert(fileName);

	if (!FileFonction_fileExist(fileName))
		return;

	char command[256] = "";

	sprintf(command, "DEL %s", fileName);

	system(command);
}