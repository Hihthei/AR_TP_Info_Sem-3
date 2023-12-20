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
// Permet la création d’une forêt d’arbres;

int RandomForest_predict(RandomForest* rf, Instance* instance);
// Enregistre la prédiction de chacun des arbres de la forêt sur l’instance en paramètre, et renvoie la prédiction majoritaire;

float RandomForest_evaluate(RandomForest* rf, Dataset* data);
// Renvoie la précision de la forêt sur le dataset en paramètre

int RandomForest_nodeCount(RandomForest* rf);
// Renvoie la somme des nombres de noeuds des arbres de la forêt;

void RandomForest_destroy(RandomForest* rf);
// Détruit la forêt.

#endif
