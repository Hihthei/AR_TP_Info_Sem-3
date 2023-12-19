#ifndef DATASET_H
#define DATASET_H

#include "Settings.h"

//STRUCTURE : -----------------------------------------------------------------------------------------------------------

typedef struct sInstance {
    int* values;
    int classID;
} Instance;

typedef struct sDataset {
    Instance* instances;
    int instanceCount;
    int featureCount;
    int classCount;
} Dataset;

typedef struct sSubproblemClass {
    int instanceCount;
    Instance** instances;
} SubproblemClass;

typedef struct sSubproblem {
    Instance** instances;
    int instanceCount;
    int capacity;
    int featureCount;
    int classCount;
    SubproblemClass* classes;
} Subproblem;


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

/**
 * @brief
 *
 * Lit le fichier dont le nom est donn�, et extrait toutes les informations du dataset.
 * Ces informations seront enregistr�es dans un Dataset dont l�adresse sera renvoy�e.
 * Si la lecture du fichier �choue, la fonction renvoie NULL.
 *
 * @param filename : cha�ne de charact�re du nom du fichier
 * 
 * @return un pointeur vers une structure contenant les informations de DataSet
 */
Dataset* Dataset_readFromFile(char* filename);



/**
 * @brief
 *
 * D�truit proprement une allocation de la structure Dataset dont l�adresse est donn�e en param�tre.
 * On pensera �galement � d�sallouer le tableau d�instances pr�sent � l�int�rieur de la structure.
 * 
 * @param dataset : un pointeur vers une structure Dataset
 * 
 * @return void
 */
void Dataset_destroy(Dataset* dataset);



/**
 * @brief
 *
 * Renvoie un sous-probl�me prenant en compte toutes les instances stock�es dans le dataset dont
 * l�adresse est donn�e en param�tre. Attention : on ne demande pas de copier les instances contenues dans Dataset,
 * mais de simplement stocker leur adresse dans un tableau. On en profitera �galement pour recopier les valeurs instanceCount,
 * featureCount et classCount, qui seront identiques dans les deux structures.
 * 
 * @param dataset : un pointeur vers une structure Dataset
 *
 * @return
 */
Subproblem* Dataset_getSubproblem(Dataset* dataset);
// TODO



/**
 * @brief
 *
 * Renvoie une allocation de la structure Subproblem, en instanciant les valeurs des attributs featureCount et classCount,
 * et en allouant le tableau de pointeurs d�instance � sa capacit� donn�e en param�tre.
 * 
 * @param  : // TODO
 * 
 * @return 
 */
Subproblem* Subproblem_create(int maximumCapacity, int featureCount, int classCount);


/**
 * @brief
 *
 * D�truit proprement une allocation de Subproblem, en d�truisant les diff�rents tableaux.
 * Attention : ce n�est pas parce que l�on travaille avec des tableaux de pointeurs qu�il faut
 * d�truire ce qui se trouve dans les cases des dits-tableaux, les adresses stock�es font r�f�rences
 * aux instances pr�sentes dans la structure Dataset.
 * 
 * @param  : // TODO
 * 
 * @return 
 */
void Subproblem_destroy(Subproblem* subproblem);



/**
 * @brief
 *
 * Ins�re l�adresse d�une instance dans le sous-probl�me, � la fois dans le tableau principal
 * et le tableau d�di� � la classe de l�instance, et met � jour le nombre d�instances consid�r�es.
 * 
 * @param  : // TODO
 * 
 * @return 
 */
bool Subproblem_insert(Subproblem* subproblem, Instance* instance);
// TODO



/**
 * @brief
 *
 * Affiche le nombre de features, de classes et d�instances r�f�renc�es, ainsi que le nombre d�instances pour chacune des classes.
 *
 * @param  : // TODO
 * 
 * @return 
 */
void Subproblem_print(Subproblem* subproblem);



/**
 * @brief
 *
 *
 *
 * @param  : //TODO
 *
 * @return
 */
void Subproblem_printClasses(Subproblem* subproblem);

#endif