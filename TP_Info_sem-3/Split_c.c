#include "Split_h.h"

//SPLIT -----------------------------------------

float Split_gini(Subproblem* sp, int featureID, float threshold)
{
	if (!sp) { printf("No subproblem\n"); return -1; }
	int C = sp->classCount;
	int spl = 0, spr = 0, *Il = calloc(sp->classCount, sizeof(int)), *Ir = calloc(sp->classCount, sizeof(int));
	for (int i = 0; i < sp->instanceCount; i++)
	{
		if (sp->instances[i]->values[featureID] < threshold)
		{
			spl++;
			Il[sp->instances[i]->classID]++;
		}
		else
		{
			spr++;
			Ir[sp->instances[i]->classID]++;
		}
	}

	float gspl = 1, gspr = 1.0, faspl = (float)fabs(spl), faspr = (float)fabs(spr), fasp = (float)sp->instanceCount;
	for (int c = 0; c < C; c++)
	{
		float fIl = Il[c], fIr = Ir[c];
		if (fIl != 0)
		{
			gspl -= (float)pow((fIl / faspl), 2);
		}
		if(fIr != 0)
		{
			gspr -= (float)pow((fIr / faspr), 2);
		}
	}
	free(Ir);
	free(Il);	
	return (float)(((faspl / fasp) * gspl) + ((faspr / fasp) * gspr));
}

Split Split_compute(Subproblem* subproblem)
{
	Split nulle = { 0 };
	if (!subproblem) { printf("No subproblem\n"); return nulle; }
	if (!subproblem->instances[0]) { printf("No subproblem.instances\n"); return nulle; }
	if (!subproblem->instances[0]->values) { printf("No subproblem.instances[0]->values\n"); return nulle; }

	Split best_split = { .threshold = 0, .featureID = 0 };
	float best_split_value = 1;

	for (int i = 0; i < subproblem->featureCount; i++)
	{
		float min = (float)subproblem->instances[0]->values[i], max = (float)subproblem->instances[0]->values[i];
		for (int j = 0; j < subproblem->instanceCount; j++)
		{
			if (min > subproblem->instances[j]->values[i]) min = (float)subproblem->instances[j]->values[i];
			if (max < subproblem->instances[j]->values[i]) max = (float)subproblem->instances[j]->values[i];
		}
		float threshold = (min + max) / 2;
		if (best_split_value > Split_gini(subproblem, i, threshold))
		{
			best_split_value = Split_gini(subproblem, i, threshold);
			best_split.threshold = threshold;
			best_split.featureID = i;
		}
	}
	return best_split;
}