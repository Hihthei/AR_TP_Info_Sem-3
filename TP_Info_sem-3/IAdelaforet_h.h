#ifndef IADELAFORET_H
#define IADELAFORET_H

#include "Settings.h"
#include "DecisionTree_h.h"

int DecisionTree_predict(DecisionTreeNode* tree, Instance* instance);
// Détermine la réponse de l’arbre à l’instance.On part de la racine et on descend dans
// l’arbre jusqu’à atteindre une feuille.La classe représentée par cette feuille correspondra
// à la prédiction de l’arbre

float DecisionTree_evaluate(DecisionTreeNode* tree, Dataset* dataset);
// Permet de calculer la précision de l’arbre sur le dataset passé en paramètre.Le score
// renvoyé est un réel entre 0 (l’arbre s’est tout le temps trompé) et 1 (l’arbre a déterminé
// correctement la classe de chacune des instances du dataset).On le calculera facilement
// comme le nombre d’instances bien classées sur le nombre total d’instances.

#endif
