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

Dataset* Dataset_dynamicAlloc(FILE* pfile) {
	if (pfile == NULL) {
		CodeError(NULL, "Dataset_dynamicAlloc - fichier introuvable");
		return NULL;
	}

	Dataset* dataset = (Dataset*)calloc(1, sizeof(Dataset));

	if (!fscanf(pfile, "%d %d %d\n",	&dataset->instanceCount,
										&dataset->featureCount,
										&dataset->classCount)) {
		CodeError(&dataset, "Dataset_dynamicAlloc - fscanf instanceCount / featureCount / classCount");

		fclose(pfile);
		pfile = NULL;

		return NULL;
	}

	return dataset;
}

Instance* Dataset_instanceAlloc(Dataset* dataset, FILE* pfile) {
	if (dataset == NULL) {
		CodeError(NULL, "Dataset_instanceAlloc - dataset = NULL");
		return NULL;
	}

	if (pfile == NULL) {
		CodeError(NULL, "Dataset_instanceAlloc - pfile = NULL");
		return NULL;
	}

	Instance* instances = (Instance*)calloc(dataset->instanceCount, sizeof(Instance));

	for (int i = 0; i < dataset->instanceCount; i++) {
		Instance* inst_tmp = &instances[i];

		if (!fscanf(pfile, "%d\t", &inst_tmp->classID)) {
			CodeError(inst_tmp, "Dataset_instanceAlloc - fscanf inst_tmp[].classID");
			CodeError(&instances, "");

			fclose(pfile);
			pfile = NULL;

			return NULL;
		}
		printf("classID : %d\n", inst_tmp->classID);

		inst_tmp->values = (int*)calloc(dataset->featureCount, sizeof(int));

		for (int j = 0; j < dataset->featureCount; j++) {
			if (!fscanf(pfile, "%d", &inst_tmp->values[j])) {
				int k = 0;
				while (instances[k].values != NULL || k < dataset->featureCount) {
					CodeError(&instances[k].values, "");
					k++;
				}
				CodeError(inst_tmp, "Dataset_instanceAlloc - fscanf inst_tmp[].values[]");
				CodeError(&instances, "");

				fclose(pfile);
				pfile = NULL;

				return NULL;
			}
		}
	}

	return instances;
}

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

	Dataset* dataset = Dataset_dynamicAlloc(pfile);
	if (dataset == NULL) {
		CodeError(NULL, "Dataset_readFromFile - dynamic alloc");
		return NULL;
	}
	
	dataset->instances = Dataset_instanceAlloc(dataset, pfile);
	if (dataset->instances == NULL) {
		CodeError(NULL, "Dataset_readFromFile - dynamic alloc dataset->instances");
		return NULL;
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
	if (dataset == NULL) {
		CodeError(NULL, "Dataset_getSubproblem - dataset = NULL");
		return NULL;
	}

	Subproblem* subproblem = Subproblem_create(dataset->instanceCount, dataset->featureCount, dataset->classCount);
	if (subproblem == NULL) {
		CodeError(&subproblem, "Dataset_getSubproblem - allocation subproblem");
		return NULL;
	}
	/*
	for (int i = 0; i < dataset->instanceCount; i++) {
		if (!Subproblem_insert(subproblem, &dataset->instances[i])) {
			CodeError(&subproblem, NULL);

			return NULL;
		}
	}*/

	return subproblem;
}

SubproblemClass* Subproblem_createClass(Subproblem* subproblem) {
	SubproblemClass* subproblem_class = (SubproblemClass*)calloc(subproblem->classCount, sizeof(SubproblemClass));
	if (subproblem_class == NULL) {
		CodeError(&subproblem_class, "Subproblem_createClass - allocation subproblem_class");
		return NULL;
	}

	for (int i = 0; i < subproblem->classCount; i++) {
		subproblem_class[i].instances = (Instance**)calloc(subproblem->capacity, sizeof(Instance*));
		if (subproblem_class[i].instances == NULL) {
			for (int j = 0; j < i; j++)
				CodeError(&subproblem_class[j].instances, NULL);

			CodeError(NULL, "Subproblem_create - allocation subproblem->classes[].instances");

			return NULL;
		}
	}

	return subproblem_class;
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

	subproblem->classes = Subproblem_createClass(subproblem);
	if (subproblem->classes == NULL) {
		CodeError(&subproblem->instances, NULL);
		CodeError(&subproblem->classes, NULL);
		CodeError(&subproblem, "Subproblem_create - allocation subproblem->classes");

		return NULL;
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

bool Subproblem_insert(	Subproblem* subproblem,
						Instance* instance) {
	if (subproblem == NULL) {
		CodeError(NULL, "Subproblem_insert - subproblem = NULL");
		return false;
	}
	if (instance == NULL) {
		CodeError(NULL, "Subproblem_insert - instance = NULL");
		return false;
	}
	if (subproblem->instanceCount >= subproblem->capacity) {
		CodeError(NULL, "Subproblem_insert - capacite limite depassee");
		return false;
	}
	if (instance->classID < 0 || instance->classID >= subproblem->classCount) {
		CodeError(NULL, "Subproblem_insert - instance->classID hors limite");
		return false;
	}

	subproblem->instances[subproblem->instanceCount] = instance;
	subproblem->instanceCount++;

	subproblem->classes[instance->classID].instances[subproblem->classes[instance->classID].instanceCount] = instance;
	subproblem->classes[instance->classID].instanceCount++;

	return true;
}

void Subproblem_print(Subproblem* subproblem) {
	if (subproblem == NULL) {
		CodeError(NULL, "Subproblem_print - subproblem = NULL");
		return;
	}

	printf("Capacite = %d\nTaille = %d\n", subproblem->capacity, subproblem->instanceCount);
	printf("Nombre de Features par classes : %d\n", subproblem->featureCount);
	printf("Nombre de Classes : %d\n", subproblem->classCount);

	for (int i = 0; i < subproblem->classCount; i++)
		printf("- classe numero %d : %d instances\n", i, subproblem->classes->instances[i]);
}