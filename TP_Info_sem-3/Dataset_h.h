#ifndef DATASET_H
#define DATASET_H

#include "Settings.h"

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

//Lit le fichier dont le nom est donné, et extrait toutes les informations du dataset. Ces informations seront enregistrées dans un Dataset dont l’adresse sera renvoyée. Si la lecture du fichier échoue, la fonction renvoie NULL.
Dataset* Dataset_readFromFile(char* filename);

//Détruit proprement une allocation de la structure Dataset dont l’adresse est donnée en paramètre. On pensera également à désallouer le tableau d’instances présent à l’intérieur de la structure.
void Dataset_destroy(Dataset* data);

//Renvoie un sous-problème prenant en compte toutes les instances stockées dans le dataset dont l’adresse est donnée en paramètre. Attention : on ne demande pas de copier les instances contenues dans Dataset, mais de simplement stocker leur adresse dans un tableau. On en profitera également pour recopier les valeurs instanceCount, featureCount et classCount, qui seront identiques dans les deux structures.
Subproblem* Dataset_getSubproblem(Dataset* data);

//Renvoie une allocation de la structure Subproblem, en instanciant les valeurs des attributs featureCount et classCount, et en allouant le tableau de pointeurs d’instance à sa capacité donnée en paramètre.
Subproblem* Subproblem_create(int maximumCapacity, int featureCount, int classCount);

//Détruit proprement une allocation de Subproblem, en détruisant les différents tableaux. Attention : ce n’est pas parce que l’on travaille avec des tableaux de pointeurs qu’il faut détruire ce qui se trouve dans les cases des dits-tableaux, les adresses stockées font références aux instances présentes dans la structure Dataset.
void Subproblem_destroy(Subproblem* subproblem);

//Insère l’adresse d’une instance dans le sous-problème, à la fois dans le tableau principal et le tableau dédié à la classe de l’instance, et met à jour le nombre d’instances considérées.
void Subproblem_insert(Subproblem* subproblem, Instance* instance);

//Affiche le nombre de features, de classes et d’instances référencées, ainsi que le nombre d’instances pour chacune des classes.
void Subproblem_print(Subproblem* subproblem);

#endif