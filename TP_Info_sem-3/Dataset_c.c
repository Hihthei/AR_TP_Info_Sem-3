#include "Dataset_h.h"
//#include <openMP.h>

void CodeError(void** freeptr, char* errormsg) {
	if(strcmp(errormsg, "") != 0 && errormsg != NULL)
		printf("\nCODE ERROR : \" %s \" \n\n", errormsg);

	if (freeptr != NULL && *freeptr != NULL) {
		free(*freeptr);
		*freeptr = NULL;
	}
}

//FONCTION : -----------------------------------------------------------------------------------------------------------

Dataset* Dataset_readFromFile(char* filename) {
	if (filename == NULL) {
		CodeError(NULL, "Dataset_readFromFile - fichier inexistant");
		return NULL;
	}
		
	FILE* pfile = NULL;
	pfile = fopen(filename, "r");

	if (pfile == NULL) {
		CodeError(NULL, "Dataset_readFromFile - fichier introuvable");
		return NULL;
	}

	Dataset* dataset = (Dataset*)calloc(1, sizeof(Dataset));

	if (!fscanf(pfile, "%d %d %d\n", &dataset->instanceCount,
									 &dataset->featureCount,
									 &dataset->classCount)) {
		CodeError(&dataset, "Dataset_readFromFile - fscanf instanceCount / featureCount / classCount");

		fclose(pfile);
		pfile = NULL;

		return NULL;
	}
	
	dataset->instances = (Instance*)calloc(dataset->instanceCount, sizeof(Instance));
	
	for (int i = 0; i < dataset->instanceCount; i++) {
		Instance* instance = &(dataset->instances[i]);

		if (!fscanf(pfile, "%d", &instance->classID)) {
			CodeError(instance, "Dataset_readFromFile - fscanf instances[].classID");
			CodeError(&dataset, "");

			fclose(pfile);
			pfile = NULL;

			return NULL;
		}

		instance->values = (int*)calloc(dataset->featureCount, sizeof(int));
		
		for (int j = 0; j < dataset->featureCount; j++) {
			if (!fscanf(pfile, "%d", &instance->values[j])) {
				int k = 0;
				while (dataset->instances[k].values != NULL || k < dataset->featureCount) {
					CodeError(dataset->instances[k].values, "");
					k++;
				}
				CodeError(&dataset->instances, "Dataset_readFromFile - fscanf instances[].values[]");
				CodeError(&dataset, "");

				fclose(pfile);
				pfile = NULL;

				return NULL;
			}
		}
	}

	fclose(pfile);
	pfile = NULL;
	
	return dataset;
}

void Dataset_destroy(Dataset* dataset) {
	if (dataset == NULL) {
		CodeError(NULL, "Dataset_destroy - dataset = NULL");
		return;
	}

	for (int i = 0; i < dataset->instanceCount; i++) {
		free(dataset->instances[i].values);
		dataset->instances[i].values = NULL;
	}

	free(dataset->instances);
	dataset->instances = NULL;

	free(dataset);
	dataset = NULL;
}

Subproblem* Dataset_getSubproblem(Dataset* dataset) {
	// TODO
	return NULL;
}

Subproblem* Subproblem_create(	int maximumCapacity,
								int featureCount,
								int classCount) {
	if (maximumCapacity <= 0 || featureCount <= 0 || classCount <= 0) {
		CodeError(NULL, "Subproblem_create - tab range < 0");
		return NULL;
	}

	Subproblem* subproblem = (Subproblem*)calloc(1, sizeof(Subproblem));
	if (subproblem == NULL) {
		CodeError(NULL, "Subproblem_create - allocation subproblem");
		return NULL;
	}

	subproblem->instances = (Instance**)calloc(maximumCapacity, sizeof(Instance*));
	if (subproblem->instances == NULL) {
		CodeError(&subproblem, "Subproblem_create - allocation subproblem->instances");
		return NULL;
	}
	
	subproblem->classCount = classCount;
	subproblem->featureCount = featureCount;
	subproblem->capacity = maximumCapacity;

	subproblem->classes = (SubproblemClass*)calloc(subproblem->classCount, sizeof(SubproblemClass));
	if (subproblem->classes == NULL) {
		CodeError(&subproblem->instances, NULL);
		CodeError(&subproblem, "Subproblem_create - allocation subproblem->classes");
		return NULL;
	}

	for (int i = 0; i < subproblem->classCount; i++) {
		subproblem->classes[i].instances = (Instance**)calloc(maximumCapacity, sizeof(Instance*));
		if (subproblem->classes[i].instances == NULL) {
			for (int j = 0; j < i; j++)
				CodeError(&subproblem->classes[j].instances, NULL);
			
			CodeError(&subproblem->instances, NULL);
			CodeError(&subproblem->classes, NULL);
			CodeError(&subproblem, "Subproblem_create - allocation subproblem->classes[].instances");
			return NULL;
		}
	}

	return subproblem;
}

void Subproblem_destroy(Subproblem* subproblem) {
	if (subproblem == NULL) {
		CodeError(NULL, "Subproblem_destroy - subproblem = NULL");
		return;
	}

	for (int i = 0; i < subproblem->classCount; i++) {
		free(subproblem->classes[i].instances);
		subproblem->classes[i].instances = NULL;
	}

	free(subproblem->classes);
	subproblem->classes = NULL;

	free(subproblem->instances);
	subproblem->instances = NULL;

	free(subproblem);
	subproblem = NULL;
}

void Subproblem_insert(	Subproblem* subproblem,
						Instance* instance) {
	// TODO
}

void Subproblem_print(Subproblem* subproblem) {
	if (subproblem == NULL) {
		CodeError(NULL, "Subproblem_print - subproblem = NULL");
		return;
	}

	printf("Nombre de classes : %d\n", subproblem->classCount);
	printf("Nombre de features par classes : %d\n", subproblem->featureCount);
	printf("Taille = %d, capacite = %d\n", subproblem->instanceCount, subproblem->capacity);								

	for (int i = 0; i < subproblem->classCount; i++)
		printf("- classe numero %d : %d instances\n", i, subproblem->classes->instances[i]);
}