#ifndef IADELAFORET_H
#define IADELAFORET_H

#include "Settings.h"
#include "DecisionTree_h.h"

int DecisionTree_predict(DecisionTreeNode* tree, Instance* instance);
// D�termine la r�ponse de l�arbre � l�instance.On part de la racine et on descend dans
// l�arbre jusqu�� atteindre une feuille.La classe repr�sent�e par cette feuille correspondra
// � la pr�diction de l�arbre

float DecisionTree_evaluate(DecisionTreeNode* tree, Dataset* dataset);
// Permet de calculer la pr�cision de l�arbre sur le dataset pass� en param�tre.Le score
// renvoy� est un r�el entre 0 (l�arbre s�est tout le temps tromp�) et 1 (l�arbre a d�termin�
// correctement la classe de chacune des instances du dataset).On le calculera facilement
// comme le nombre d�instances bien class�es sur le nombre total d�instances.

#endif
