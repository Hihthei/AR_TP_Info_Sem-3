#include "Dataset_h.h"

Dataset* Dataset_readFromFile(char* filename) {
	if (filename == NULL)
		return NULL;
		
	FILE* pfile = NULL;
	pfile = fopen(filename, "r");

	if (pfile == NULL)
		return NULL;

	Dataset* dataset = calloc(1, sizeof(Dataset));

	int tmp = fscanf(pfile, "%d %d %d\n", &(dataset->instanceCount),
								&(dataset->featureCount),
								&(dataset->classCount));
	return dataset;
}

void Dataset_destroy(Dataset* data) {
	// TODO
	return;
}

Subproblem* Dataset_getSubproblem(Dataset* data) {
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
	return;
}

void Subproblem_insert(	Subproblem* subproblem,
						Instance* instance) {
	// TODO
	return;
}

void Subproblem_print(Subproblem* subproblem) {
	// TODO
	return;
}