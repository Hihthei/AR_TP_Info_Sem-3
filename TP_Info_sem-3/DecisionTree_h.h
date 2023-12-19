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
 * impl�mente l�algorithme donn� plus haut, tout en ajoutant une profondeur maximum
 * qui sert de cas d�arr�t suppl�mentaire. On a �galement prunningThreshold qui repr�sente
 * le seuil de puret� � atteindre pour qu�un noeud soit une feuille
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
 * d�truit r�cursivement les noeuds de l�arbre
 *
 * @param  :
 *
 * @return :
 */
void DecisionTree_destroy(DecisionTreeNode* decisionTree);



/**
 * @brief
 *
 * renvoie le nombre de noeuds pr�sents dans l�arbre (y compris les feuilles),
 * qui servira � v�rifier le bon fonctionnement de votre proc�dure de construction,
 * et �galement d�obtenir la taille de votre mod�le.
 *
 * @param  :
 *
 * @return :
 */
int Decision_nodeCount(DecisionTreeNode* node);



/**
 * @brief
 *
 * d�termine la r�ponse de l�arbre � l�instance. On part de la racine
 * et on descend dans l�arbre jusqu�� atteindre une feuille.
 * La classe repr�sent�e par cette feuille correspondra � la pr�diction de l�arbre.
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
 * permet de calculer la pr�cision de l�arbre sur le dataset pass� en param�tre.
 * Le score renvoy� est un r�el entre 0 (l�arbre s�est tout le temps tromp�)
 * et 1 (l�arbre a d�termin� correctement la classe de chacune des instances du dataset).
 * On le calculera facilement comme le nombre d�instances bien class�es sur le nombre total d�instances.
 *
 * @param  :
 *
 * @return :
 */
float DecisionTree_evaluate(DecisionTreeNode* tree, Dataset* dataset);
//TODO

#endif