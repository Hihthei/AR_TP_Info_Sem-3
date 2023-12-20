#ifndef FOREST_H
#define FOREST_H

#include "Settings.h"
#include "DecisionTree_h.h"

typedef struct sRandomForest {
	DecisionTreeNode** trees;
	int treeCount;
	int classCount;
} RandomForest;

RandomForest* RandomForest_create(int numberOfTrees, Dataset* data, int maxDepth, float baggingProportion, float prunningThreshold);
// Permet la cr�ation d�une for�t d�arbres;

int RandomForest_predict(RandomForest* rf, Instance* instance);
// Enregistre la pr�diction de chacun des arbres de la for�t sur l�instance en param�tre, et renvoie la pr�diction majoritaire;

float RandomForest_evaluate(RandomForest* rf, Dataset* data);
// Renvoie la pr�cision de la for�t sur le dataset en param�tre

int RandomForest_nodeCount(RandomForest* rf);
// Renvoie la somme des nombres de noeuds des arbres de la for�t;

void RandomForest_destroy(RandomForest* rf);
// D�truit la for�t.

#endif
