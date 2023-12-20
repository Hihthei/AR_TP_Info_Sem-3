#include "Split_h.h"

//SPLIT -----------------------------------------

float Split_gini(Subproblem* sp, int featureID, float threshold)
{
	if (!sp) { printf("No subproblem\n"); return; }
	int C = sp->classCount;
	int spl = 0, spr = 0, *Il = (int*)calloc(sp->capacity, sizeof(int)), *Ir = (int*)calloc(sp->capacity, sizeof(int));
	for (int i = 0; i < sp->instanceCount; i++)
	{
		if (sp->instances[i]->values[featureID] <= threshold)
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

	float gspl = 1, gspr = 1, faspl = fabs(spl), faspr = fabs(spr), fasp = sp->instanceCount;
	for (int c = 0; c < C - 1; c++)
	{
		float fIl = (float)fabs(Il[c]), fIr = (float)fabs(Ir[c]);
		gspl -= pow((fIl / faspl), 2);
		gspr -= pow((fIr / faspr), 2);
	}

	return (float)(((faspl / fasp) * gspl) + ((faspr / fasp) * gspr));
}

Split Split_compute(Subproblem* subproblem)
{
	if (!subproblem) { printf("No subproblem\n"); return; }

	Split best_split;
	float best_split_value = 1;
	best_split.threshold = 0;
	best_split.featureID = 0;

	for (int i = 0; i < subproblem->featureCount; i++)
	{
		float min = subproblem->instances[0]->values[i], max = subproblem->instances[0]->values[i];
		for (int j = 0; j < subproblem->instanceCount; j++)
		{
			if(min > subproblem->instances[j]->values[i]) min = subproblem->instances[j]->values[i];
			if(max < subproblem->instances[j]->values[i]) max = subproblem->instances[j]->values[i];
		}
		float threshold  = (min + max) / 2;
		if (best_split_value > Split_gini(subproblem, i, threshold))
		{
			best_split_value = Split_gini(subproblem, i, threshold);
			best_split.threshold = threshold;
			best_split.featureID = i;
		}
	}
	return best_split;
}