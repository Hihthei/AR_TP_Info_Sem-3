#include "FileSave.h"

//FONCTION : -----------------------------------------------------------------------------------------------------------

void FileSave_UIClear(int nodeCount, float trainScore, float testScore) {
	system("cls");

	printf(	"\nVeuillez rentrer une reponse valide !\n"

			"\n_________________________________\n\n"

			"Generation d'un arbre de %d noeuds\n"
			"train = %.3f, test = %.3f\n\n", nodeCount, trainScore, testScore);
}

void FileSave_overwriteUI(char* fileName) {
	assert(fileName);

	system("cls");

	printf(	"\n\" %s \"\n"
			"Fichier deja existant. Voulez-vous l'ecraser ? (Y/N) : ", fileName);

	char buffer[1024] = "";

	if (!scanf("%s", buffer)) {
		free(buffer);
		return;
	}

	if (strlen(buffer) > 1) {
		free(buffer);
		FileSave_overwriteUI(fileName);
	}
	else if (buffer[0] == 'Y' || buffer[0] == 'y') {
		free(buffer);
		FileFonction_fileOverwrite(fileName);
		return;
	}
	else if (buffer[0] == 'N' || buffer[0] == 'n') {
		free(buffer);
		return;
	}
	else {
		free(buffer);
		return;
	}

	return;
}

void FileSave_createUI() {
	system("cls");

	printf("Veuillez entrer un nom de fichier pour la sauvegarde (.txt) : ");

	char buffer[1024] = "";
	char fileName[256] = "";

	if (!scanf("%s", fileName)) {
		free(buffer);
		return;
	}

	printf("\" %s \" Confirmer vous votre choix ? (Y/N) : ", fileName);

	if (!scanf("%s", buffer)) {
		free(buffer);
		free(fileName);
		return;
	}

	if (buffer[0] == 'Y' || buffer[0] == 'y') {
		free(buffer);
		if (FileFonction_fileExist(fileName)) {
			free(buffer);
			FileSave_overwriteUI(fileName);
			return;
		}
		else {
			free(buffer);
			FileFonction_createFile(fileName);
			return;
		}
		return;
	}
	else if (buffer[0] == 'N' || buffer[0] == 'n') {
		free(buffer);
		free(fileName);
		FileSave_createUI();
		return;
	}
	else {
		free(buffer);
		free(fileName);
		return;
	}
	return;
}

int FileSave_UserInterface(int nodeCount, float trainScore, float testScore) {
	
	printf("\n_________________________________\n\n");

	printf("Souhaitez-vous sauvegarder l'arbre ? (Y/N)\n"
			"Reponse : ");

	char buffer[1024] = "";

	if (!scanf("%s", buffer)) {
		free(buffer);
		return EXIT_FAILURE;
	}

	printf("%s", buffer);

	if (strlen(buffer) > 1) {
		free(buffer);
		FileSave_UIClear(nodeCount, trainScore, testScore);
		FileSave_UserInterface(nodeCount, trainScore, testScore);
	}
	else if (buffer[0] == 'Y' || buffer[0] == 'y') {
		free(buffer);
		FileSave_createUI();
	}
	else if (buffer[0] == 'N' || buffer[0] == 'n') {
		free(buffer);
	}
	else {
		free(buffer);
		FileSave_UIClear(nodeCount, trainScore, testScore);
		FileSave_UserInterface(nodeCount, trainScore, testScore);
	}

	return 0;
}