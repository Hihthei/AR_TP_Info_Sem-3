#ifndef DECISIONTREE_H
#define DECISIONTREE_H

#include "Settings.h"
#include "Split_h.h"

typedef struct sDecisionTreeNode {
	struct sDecisionTreeNode* left;
	struct sDecisionTreeNode* right;
	Split split;
	int classID;
} DecisionTreeNode;

/**
 * @brief
 *
 *
 *
 * @param  :
 *
 * @return :
 */

 //FONCTION : -----------------------------------------------------------------------------------------------------------

/**
 * @brief
 *
 * implémente l’algorithme donné plus haut, tout en ajoutant une profondeur maximum
 * qui sert de cas d’arrêt supplémentaire. On a également prunningThreshold qui représente
 * le seuil de pureté à atteindre pour qu’un noeud soit une feuille
 *
 * @param  :
 *
 * @return :
 */
DecisionTreeNode* DecisionTree_create(	Subproblem* sp,
										int currentDepth,
										int maxDepth,
										float prunningThreshold);



/**
 * @brief
 *
 * détruit récursivement les noeuds de l’arbre
 *
 * @param  :
 *
 * @return :
 */
void DecisionTree_destroy(DecisionTreeNode* decisionTree);



/**
 * @brief
 *
 * renvoie le nombre de noeuds présents dans l’arbre (y compris les feuilles),
 * qui servira à vérifier le bon fonctionnement de votre procédure de construction,
 * et également d’obtenir la taille de votre modèle.
 *
 * @param  :
 *
 * @return :
 */
int Decision_nodeCount(DecisionTreeNode* node);



/**
 * @brief
 *
 * détermine la réponse de l’arbre à l’instance. On part de la racine
 * et on descend dans l’arbre jusqu’à atteindre une feuille.
 * La classe représentée par cette feuille correspondra à la prédiction de l’arbre.
 *
 * @param  :
 *
 * @return :
 */
int DecisionTree_predict(DecisionTreeNode* tree, Instance* instance);
//TODO


/**
 * @brief
 *
 * permet de calculer la précision de l’arbre sur le dataset passé en paramètre.
 * Le score renvoyé est un réel entre 0 (l’arbre s’est tout le temps trompé)
 * et 1 (l’arbre a déterminé correctement la classe de chacune des instances du dataset).
 * On le calculera facilement comme le nombre d’instances bien classées sur le nombre total d’instances.
 *
 * @param  :
 *
 * @return :
 */
float DecisionTree_evaluate(DecisionTreeNode* tree, Dataset* dataset);
//TODO

#endif