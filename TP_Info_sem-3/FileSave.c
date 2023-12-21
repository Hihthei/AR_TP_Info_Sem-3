#include "FileSave.h"

void CodeError_FILE(void** freeptr, char* errormsg) {
	if (errormsg != NULL)
		printf("\nCODE ERROR : \" %s \" \n\n", errormsg);

	if (freeptr != NULL && *freeptr != NULL) {
		free(*freeptr);
		*freeptr = NULL;
	}
}

void ClearBuffer() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF)
		continue;
}

//FONCTION : -----------------------------------------------------------------------------------------------------------

void FileSave_UIClear(int nodeCount, float trainScore, float testScore) {
	ClearBuffer();
	system("cls");

	printf(	"\nVeuillez rentrer une reponse valide !\n"

			"\n_________________________________\n\n"

			"Generation d'un arbre de %d noeuds\n"
			"train = %.3f, test = %.3f\n\n", nodeCount, trainScore, testScore);

	return;
}

bool FileSave_fileExist(char* fileName) {
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

bool FileSave_fileOverwrite(char* fileName) {
	system("cls");

	assert(fileName);

	printf("\nFichier deja existant. Voulez-vous l'ecraser ? (Y/N) : ");

	char* buffer = (char*)calloc(1024, sizeof(char));
	if (buffer == NULL) {
		CodeError_FILE(NULL, "FileSave_fileOverwrite - alloc buffer");
		return false;
	}

	if (!scanf("%s", buffer)) {
		CodeError_FILE(&buffer, "FileSave_fileOverwrite - Erreur lors de la creation du fichier.");
		return false;
	}

	if (strlen(buffer) > 1) {
		CodeError_FILE(&buffer, NULL);
		FileSave_fileOverwrite(fileName);
	}
	else if (buffer[0] == 'Y' || buffer[0] == 'y') {
		free(buffer);
		FileSave_deleteFile(fileName);

		if (FileSave_fileExist(fileName)) {
			CodeError_FILE(NULL, "FileSave_fileOverwrite - Erreur lors de la creation du fichier.");
			return false;
		}

		return true;
	}
	else if (buffer[0] == 'N' || buffer[0] == 'n') {
		free(buffer);

	}
	else {
		CodeError_FILE(&buffer, "FileSave_fileOverwrite - Erreur lors de la creation du fichier.");
		return false;
	}
}

bool FileSave_createFile(char* fileName) {
	assert(fileName);

	if (strlen(fileName) > 20) {
		system("cls");
		printf("\nNom de fichier trop long, veuillez en choisir un nouveau.\n"
			"(20 caractères maximum)\n"
			"Votre nouveau nom de fichier : ");

		free(fileName);
		char* buffer = (char*)calloc(1024, sizeof(char));
		if (!scanf("%s", buffer)) {
			CodeError_FILE(&buffer, NULL);
			return false;
		}

		FileSave_createFile(buffer);
	}

	if (FileSave_fileExist(fileName)) {
		if (FileSave_fileOverwrite(fileName)) {

		}
	}

	char command[50] = "";

	sprintf(command, "ECHO.> %s", fileName);

	system(command);

	free(command);
	
	return true;
}

int FileSave_UserInterface(int nodeCount, float trainScore, float testScore) {
	while (true) {
		printf("\n_________________________________\n\n");

		printf("Souhaitez-vous sauvegarder l'arbre ? (Y/N)\n"
				"Reponse : ");

		char* buffer = (char*)calloc(1024, sizeof(char));

		if (!scanf("%s", buffer)) {
			CodeError_FILE(&buffer, NULL);
			FileSave_UIClear(nodeCount, trainScore, testScore);
			continue;
		}

		if (strlen(buffer) > 1) {
			CodeError_FILE(&buffer, NULL);
			FileSave_UIClear(nodeCount, trainScore, testScore);
			continue;
		}
		else if (buffer[0] == 'Y' || buffer[0] == 'y') {
			free(buffer);
			FileSave_createFile("test.txt");
			break;
		}
		else if (buffer[0] == 'N' || buffer[0] == 'n') {
			free(buffer);
			break;
		}
		else {
			CodeError_FILE(&buffer, NULL);
			FileSave_UIClear(nodeCount, trainScore, testScore);
			continue;
		}

		break;
	}

	return 0;
}

FILE* FileSave_loadFile() {
	return NULL;
}

bool FileSave_clearFile() {
	return false;
}

bool FileSave_deleteFile(char* fileName) {
	assert(fileName);

	if (FileSave_fileExist(fileName)) {
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

	return true;
}

bool FileSave_writeFile() {
	return false;
}

bool FileSave_saveFile() {
	return false;
}