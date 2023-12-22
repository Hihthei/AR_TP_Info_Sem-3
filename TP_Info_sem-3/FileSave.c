#include "FileSave.h"

//FONCTION : -----------------------------------------------------------------------------------------------------------

void FileSave_UIClear(int nodeCount, float trainScore, float testScore) {
	system("cls");

	printf(	"Veuillez rentrer une reponse valide !\n\n"

			"_________________________________\n\n"

			"Generation d'un arbre de %d noeuds\n"
			"train = %.3f, test = %.3f\n\n", nodeCount, trainScore, testScore);
}

void FileSave_overwriteUI(char* fileName) {
	assert(fileName);

	system("cls");

	printf(	"\" %s \"\n"
			"Fichier deja existant. Voulez-vous l'ecraser ? (Y/N) : ", fileName);

	char buffer[1024] = "";

	if (!scanf("%s", buffer))
		return;

	if (strlen(buffer) > 1)
		FileSave_overwriteUI(fileName);
	else if (buffer[0] == 'Y' || buffer[0] == 'y')
		FileFonction_fileOverwrite(fileName);
	else if (buffer[0] == 'N' || buffer[0] == 'n')
		return;
	else
		FileSave_overwriteUI(fileName);

	return;
}

void FileSave_createUI() {
	system("cls");

	printf("Veuillez entrer un nom de fichier pour la sauvegarde (.txt) : ");

	char buffer[1024] = "";
	char fileName[256] = "";

	if (!scanf("%s", fileName))
		return;

	printf("\" %s \" Confirmer vous votre choix ? (Y/N) : ", fileName);

	if (!scanf("%s", buffer))
		return;

	if (buffer[0] == 'Y' || buffer[0] == 'y') {
		if (FileFonction_fileExist(fileName))
			FileSave_overwriteUI(fileName);
		else
			FileFonction_createFile(fileName);
	}
	else if (buffer[0] == 'N' || buffer[0] == 'n')
		FileSave_createUI();

	return;
}

int FileSave_UserInterface(int nodeCount, float trainScore, float testScore) {
	
	printf("\n_________________________________\n\n");

	printf("Souhaitez-vous sauvegarder l'arbre ? (Y/N)\n"
			"Reponse : ");

	char buffer[1024] = "";

	if (!scanf("%s", buffer))
		return EXIT_FAILURE;

	if (strlen(buffer) > 1) {
		FileSave_UIClear(nodeCount, trainScore, testScore);
		FileSave_UserInterface(nodeCount, trainScore, testScore);
	}
	else if (buffer[0] == 'Y' || buffer[0] == 'y')
		FileSave_createUI();
	
	else if (buffer[0] == 'N' || buffer[0] == 'n')
		return 0;
	else {
		FileSave_UIClear(nodeCount, trainScore, testScore);
		FileSave_UserInterface(nodeCount, trainScore, testScore);
	}

	return 0;
}
