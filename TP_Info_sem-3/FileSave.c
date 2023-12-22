#include "FileSave.h"

//FONCTION : -----------------------------------------------------------------------------------------------------------

void FileSave_UIClear(int nodeCount, float trainScore, float testScore) {
	system("cls");

	printf(	"Veuillez rentrer une reponse valide !\n\n"

			"_________________________________\n\n"

			"Generation d'une foret de %d noeuds\n"
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

void FileSave_createUI(RandomForest* forest) {
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
		if (FileFonction_fileExist(fileName)) {
			FileSave_overwriteUI(fileName);
			SaveTree_saveForest(fileName, forest);
		}
		else {
			FileFonction_createFile(fileName);
			SaveTree_saveForest(fileName, forest);
		}
	}
	else if (buffer[0] == 'N' || buffer[0] == 'n')
		FileSave_createUI(forest);

	return;
}

int FileSave_UserInterface(int nodeCount, float trainScore, float testScore, RandomForest* forest) {
	
	printf("\n_________________________________\n\n");

	printf("Souhaitez-vous sauvegarder la random forest ? (Y/N)\n"
			"Reponse : ");

	char buffer[1024] = "";

	if (!scanf("%s", buffer))
		return EXIT_FAILURE;

	if (strlen(buffer) > 1) {
		FileSave_UIClear(nodeCount, trainScore, testScore);
		FileSave_UserInterface(nodeCount, trainScore, testScore, forest);
	}
	else if (buffer[0] == 'Y' || buffer[0] == 'y')
		FileSave_createUI(forest);
	
	else if (buffer[0] == 'N' || buffer[0] == 'n')
		return 0;
	else {
		FileSave_UIClear(nodeCount, trainScore, testScore);
		FileSave_UserInterface(nodeCount, trainScore, testScore, forest);
	}

	return 0;
}

char* FileLoad_loadUI() {
	printf("Veuillez entrer un nom de fichier a charger (.txt) : ");

	char buffer[1024] = "";
	char fileName[256] = "";

	if (!scanf("%s", fileName))
		return NULL;

	printf("\" %s \" Confirmer vous votre choix ? (Y/N) (N pour quitter) : ", fileName);

	if (!scanf("%s", buffer))
		return NULL;

	if (buffer[0] == 'Y' || buffer[0] == 'y') {
		if (FileFonction_fileExist(fileName)) {
			char* file = (char*)calloc(strlen(fileName)+1, sizeof(char));
			if (file == NULL)
				return NULL;

			strcpy(file, fileName);

			return file;
		}
		else {
			system("cls");
			printf("Fichier introuvable ou inexistant.\n");

			return FileLoad_loadUI();
		}
	}
	else if (buffer[0] == 'N' || buffer[0] == 'n')
		return NULL;

	return NULL;
}

char* FileLoad_UserInterface() {
	printf("Souhaitez-vous charger une foret existante ? (Y/N)\n"
		"Reponse : ");

	char buffer[1024] = "";

	if (!scanf("%s", buffer))
		return NULL;

	if (strlen(buffer) > 1) {
		system("cls");
		printf("Veuillez rentrer une reponse valide.\n\n");
		return FileLoad_UserInterface();
	}
	else if (buffer[0] == 'Y' || buffer[0] == 'y') {
		system("cls");
		return FileLoad_loadUI();
	}

	else if (buffer[0] == 'N' || buffer[0] == 'n')
		return NULL;
	else {
		system("cls");
		printf("Veuillez rentrer une reponse valide.\n\n");
		return FileLoad_UserInterface();
	}

	return NULL;
}
