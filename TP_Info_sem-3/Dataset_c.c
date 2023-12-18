#include "Dataset_h.h"

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
		CodeError(NULL, "readFromFile - fichier inexistant");
		return NULL;
	}
		
	FILE* pfile = NULL;
	pfile = fopen(filename, "r");

	if (pfile == NULL) {
		CodeError(NULL, "readFromFile - fichier introuvable");
		return NULL;
	}

	Dataset* dataset = (Dataset*)calloc(1, sizeof(Dataset));

	if (!fscanf(pfile, "%d %d %d\n", &dataset->instanceCount,
									 &dataset->featureCount,
									 &dataset->classCount)) {
		CodeError(&dataset, "readFromFile - fscanf instanceCount / featureCount / classCount");

		fclose(pfile);
		pfile = NULL;

		return NULL;
	}
	
	dataset->instances = (Instance*)calloc(dataset->instanceCount, sizeof(Instance));
	
	for (int i = 0; i < dataset->instanceCount; i++) {
		Instance* instance = &(dataset->instances[i]);

		if (!fscanf(pfile, "%d", &instance->classID)) {
			CodeError(instance, "readFromFile - fscanf instances[].classID");
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
				CodeError(&dataset->instances, "readFromFile - fscanf instances[].values[]");
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
		CodeError(NULL, "destroy - dataset = NULL");
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
	// TODO
	return NULL;
}

void Subproblem_destroy(Subproblem* subproblem) {
	// TODO
}

void Subproblem_insert(	Subproblem* subproblem,
						Instance* instance) {
	// TODO
}

void Subproblem_print(Subproblem* subproblem) {
	// TODO
}