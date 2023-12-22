#include "Dataset_h.h"
//#include <openMP.h>

void CodeError_DATA(void** freeptr, char* errormsg) {
	if(errormsg != NULL)
		printf("\nCODE ERROR : \" %s \" \n\n", errormsg);

	if (freeptr != NULL && *freeptr != NULL) {
		free(*freeptr);
		*freeptr = NULL;
	}
}

//FONCTION : -----------------------------------------------------------------------------------------------------------

//----------------------------------------DATASET-----------------------------------------------------------------------

Dataset* Dataset_dynamicAlloc(FILE* pfile) {
	if (pfile == NULL) {
		CodeError_DATA(NULL, "Dataset_dynamicAlloc - fichier introuvable");
		return NULL;
	}

	Dataset* dataset = (Dataset*)calloc(1, sizeof(Dataset));
	if (dataset == NULL) {
		CodeError_DATA(NULL, "Dataset_dynamicAlloc - dynamic alloc dataset");
		return NULL;
	}

	if (!fscanf(pfile, "%d %d %d\n",	&dataset->instanceCount,
										&dataset->classCount,
										&dataset->featureCount)) {
		CodeError_DATA((void**)&dataset, "Dataset_dynamicAlloc - fscanf instanceCount / featureCount / classCount");

		fclose(pfile);
		pfile = NULL;

		return NULL;
	}

	return dataset;
}

Instance* Dataset_instanceAlloc(Dataset* dataset, FILE* pfile) {
	if (dataset == NULL) {
		CodeError_DATA(NULL, "Dataset_instanceAlloc - dataset = NULL");
		return NULL;
	}

	if (pfile == NULL) {
		CodeError_DATA(NULL, "Dataset_instanceAlloc - pfile = NULL");
		return NULL;
	}

	Instance* instances = (Instance*)calloc(dataset->instanceCount, sizeof(Instance));
	assert(instances);

	for (int i = 0; i < dataset->instanceCount; i++) {
		Instance* inst_tmp = &instances[i];

		if (!fscanf(pfile, "%d\t", &inst_tmp->classID)) {
			CodeError_DATA((void**)&inst_tmp, "Dataset_instanceAlloc - fscanf inst_tmp[].classID");
			CodeError_DATA((void**)&instances, "");

			fclose(pfile);
			pfile = NULL;

			return NULL;
		}

		inst_tmp->values = (int*)calloc(dataset->featureCount, sizeof(int));
		if (inst_tmp->values == NULL) {
			CodeError_DATA((void**)&inst_tmp, "Dataset_instanceAlloc - alloc inst_tmp[].values");
			return NULL;
		}

		for (int j = 0; j < dataset->featureCount; j++) {
			if (!fscanf(pfile, "%d", &inst_tmp->values[j])) {
				int k = 0;
				while (instances[k].values != NULL && k < dataset->featureCount) {
					CodeError_DATA((void**)&instances[k].values, "");
					k++;
				}
				CodeError_DATA((void**)&inst_tmp, "Dataset_instanceAlloc - fscanf inst_tmp[].values[]");
				CodeError_DATA((void**)&instances, "");

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
		CodeError_DATA(NULL, "Dataset_readFromFile - fichier inexistant");
		return NULL;
	}
		
	FILE* pfile = NULL;
	pfile = fopen(filename, "r");
	if (pfile == NULL) {
		CodeError_DATA(NULL, "Dataset_readFromFile - fichier introuvable");
		return NULL;
	}

	Dataset* dataset = Dataset_dynamicAlloc(pfile);
	if (dataset == NULL) {
		CodeError_DATA(NULL, "Dataset_readFromFile - dynamic alloc");
		return NULL;
	}
	
	dataset->instances = Dataset_instanceAlloc(dataset, pfile);
	if (dataset->instances == NULL) {
		CodeError_DATA(NULL, "Dataset_readFromFile - dynamic alloc dataset->instances");
		return NULL;
	}

	fclose(pfile);
	pfile = NULL;
	
	return dataset;
}

void Dataset_destroy(Dataset* dataset) {
	if (dataset == NULL) {
		CodeError_DATA(NULL, "Dataset_destroy - dataset = NULL");
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
		CodeError_DATA(NULL, "Dataset_getSubproblem - dataset = NULL");
		return NULL;
	}

	Subproblem* subproblem = Subproblem_create(dataset->instanceCount, dataset->featureCount, dataset->classCount);
	if (subproblem == NULL) {
		CodeError_DATA((void**)&subproblem, "Dataset_getSubproblem - allocation subproblem");
		return NULL;
	}
	
	for (int i = 0; i < dataset->instanceCount; i++) {
		if (!Subproblem_insert(subproblem, &dataset->instances[i])) {
			for (int j = 0; j < i; j++)
				CodeError_DATA((void**)&subproblem->instances[i], NULL);

			CodeError_DATA((void**)&subproblem, NULL);

			return NULL;
		}
	}

	return subproblem;
}

bool Dataset_printFeatures(Instance* instance, int featuresCount) {
	if (instance == NULL) {
		CodeError_DATA(NULL, "Dataset_printFeatures - instance = NULL");
		return false;
	}

	printf("ClassID %d ", instance->classID);

	for (int i = 0; i < featuresCount; i++)
		printf("- %d ", instance->values[i]);

	printf("\n");

	return true;
}

void Dataset_printClasses(Dataset* dataset) {
	if (dataset == NULL) {
		CodeError_DATA(NULL, "Dataset_printClasses - subproblem = NULL");
		return;
	}

	for (int i = 0; i < dataset->instanceCount; i++) {
		if (!Dataset_printFeatures(&dataset->instances[i], dataset->featureCount))
			break;
	}

	printf("\n");
}

Subproblem* Dataset_bagging(Dataset* data, float proportion)
{
	if (!data)
	{
		printf("No data\n");
		return NULL;
	}

	Subproblem* subproblem = Subproblem_create(data->instanceCount, data->featureCount, data->classCount);
	if (!subproblem)
	{
		printf("No subproble�\n");
		return NULL;
	}

	for (int i = 0; i < data->instanceCount * proportion; i++)
	{
		int r = (rand() ^ (rand() << 15)) & 0x7FFFFFFF;
		r = r % data->instanceCount;
		bool test_valid = Subproblem_insert(subproblem, &data->instances[r]);
		if (!test_valid)
		{
			printf("BIG PROBLEM\n");
			return NULL;
		}
	}

	return subproblem;
}

//----------------------------------------SUBPROBLEM--------------------------------------------------------------------

SubproblemClass* Subproblem_createClass(Subproblem* subproblem) {
	SubproblemClass* subproblem_class = (SubproblemClass*)calloc(subproblem->classCount, sizeof(SubproblemClass));
	if (subproblem_class == NULL) {
		CodeError_DATA((void**)&subproblem_class, "Subproblem_createClass - allocation subproblem_class");
		return NULL;
	}

	for (int i = 0; i < subproblem->classCount; i++) {
		subproblem_class[i].instances = (Instance**)calloc(subproblem->capacity, sizeof(Instance*));
		if (subproblem_class[i].instances == NULL) {
			for (int j = 0; j < i; j++)
				CodeError_DATA((void**)subproblem_class[j].instances, NULL);

			CodeError_DATA(NULL, "Subproblem_create - allocation subproblem->classes[].instances");

			return NULL;
		}
	}

	return subproblem_class;
}

Subproblem* Subproblem_create(	int maximumCapacity,
								int featureCount,
								int classCount) {
	if (maximumCapacity <= 0 || featureCount <= 0 || classCount <= 0) {
		CodeError_DATA(NULL, "Subproblem_create - tab range < 0");
		return NULL;
	}

	Subproblem* subproblem = (Subproblem*)calloc(1, sizeof(Subproblem));
	if (subproblem == NULL) {
		CodeError_DATA(NULL, "Subproblem_create - allocation subproblem");
		return NULL;
	}

	subproblem->instances = (Instance**)calloc(maximumCapacity, sizeof(Instance*));
	if (subproblem->instances == NULL) {
		CodeError_DATA((void**)&subproblem, "Subproblem_create - allocation subproblem->instances");
		return NULL;
	}
	
	subproblem->classCount = classCount;
	subproblem->featureCount = featureCount;
	subproblem->capacity = maximumCapacity;

	subproblem->classes = Subproblem_createClass(subproblem);
	if (subproblem->classes == NULL) {
		CodeError_DATA((void**)subproblem->instances, NULL);
		CodeError_DATA((void**)subproblem->classes, NULL);
		CodeError_DATA((void**)subproblem, "Subproblem_create - allocation subproblem->classes");

		return NULL;
	}

	return subproblem;
}

void Subproblem_destroy(Subproblem* subproblem) {
	if (subproblem == NULL) {
		CodeError_DATA(NULL, "Subproblem_destroy - subproblem = NULL");
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
		CodeError_DATA(NULL, "Subproblem_insert - subproblem = NULL");
		return false;
	}
	if (instance == NULL) {
		CodeError_DATA(NULL, "Subproblem_insert - instance = NULL");
		return false;
	}
	if (subproblem->instanceCount >= subproblem->capacity) {
		CodeError_DATA(NULL, "Subproblem_insert - capacite limite depassee");
		return false;
	}
	if (instance->classID < 0 || instance->classID >= subproblem->classCount) {
		CodeError_DATA(NULL, "Subproblem_insert - instance->classID hors limite");
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
		CodeError_DATA(NULL, "Subproblem_print - subproblem = NULL");
		return;
	}

	printf("Capacite = %d\nTaille = %d\n", subproblem->capacity, subproblem->instanceCount);
	printf("Nombre de Features par classes : %d\n", subproblem->featureCount);
	printf("Nombre de Classes : %d\n\n", subproblem->classCount);

	for (int i = 0; i < subproblem->classCount; i++)
		printf("- classe numero %d : %d instances\n", i, subproblem->classes[i].instanceCount);
}