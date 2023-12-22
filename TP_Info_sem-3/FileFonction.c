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

	printf("FileFonction_fileExist - CHECK !\n");

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

	printf("FileFonction_fileOverwrite - CHECK !\n");
	FileFonction_deleteFile(fileName);
	FileFonction_createFile(fileName);

	return;
}

void FileFonction_createFile(char* fileName) {
	/*char command[50] = "";

	sprintf(command, "ECHO.> %s", fileName);

	system(command);

	free(command);

	if (!FileSave_fileExist(fileName)) {
		CodeError_FILE(NULL, "FileSave_createFile - Erreur lors de la creation du fichier");
		return false;
	}

	return true;*/
	assert(fileName);

	printf("FileFonction_createFile - CHECK !\n");
	return;
}

FILE* FileFonction_loadFile(char* fileName, char* mode) {
	return NULL;
}

void FileFonction_deleteFile(char* fileName) {
	/*assert(fileName);

	if (!FileSave_fileExist(fileName)) {
		CodeError_FILE(NULL, "FileSave_deleteFile - Fichier introuvable");
		return false;
	}

	char command[50] = "";

	sprintf(command, "DEL %s", fileName);

	system(command);

	free(command);

	if (FileSave_fileExist(fileName)) {
		CodeError_FILE(NULL, "FileSave_deleteFile - Erreur lors de la suppression du fichier");
		return false;
	}

	return true;*/
	assert(fileName);

	printf("FileFonction_deleteFile - CHECK !\n");
	return;
}

void FileFonction_writeFile() {
	return;
}

void FileFonction_saveFile() {
	return;
}