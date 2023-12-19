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

// Réalise le calcul d’impureté tel qu’il est défini plus haut dans le texte, en tenant compte du
//sous-problème passé en paramètre, mais également de la feature et du seuil caractérisant le split étudié.
// Le résultat sera obligatoirement entre 0 et 1 inclus.
float Split_gini(Subproblem* sp, int featureID, float threshold);

// Cette fonction va itérer sur les features et générer à chaque fois un split comme expliqué plus haut.
// Le split générant le moins d’impureté sera renvoyé.
Split Split_compute(Subproblem* subproblem);

#endif