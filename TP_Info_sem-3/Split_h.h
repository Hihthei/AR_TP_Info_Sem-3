#ifndef SPLIT_H
#define SPLIT_H

#include "Settings.h"
#include "Dataset_h.h"

typedef struct sSplit {
	int featureID;
	float threshold;
} Split;

/**
 * @brief
 *
 *
 *
 * @param  :
 *
 * @return
 */

 //FONCTION : -----------------------------------------------------------------------------------------------------------

// R�alise le calcul d�impuret� tel qu�il est d�fini plus haut dans le texte, en tenant compte du
//sous-probl�me pass� en param�tre, mais �galement de la feature et du seuil caract�risant le split �tudi�.
// Le r�sultat sera obligatoirement entre 0 et 1 inclus.
float Split_gini(Subproblem* sp, int featureID, float threshold);

// Cette fonction va it�rer sur les features et g�n�rer � chaque fois un split comme expliqu� plus haut.
// Le split g�n�rant le moins d�impuret� sera renvoy�.
Split Split_compute(Subproblem* subproblem);

#endif