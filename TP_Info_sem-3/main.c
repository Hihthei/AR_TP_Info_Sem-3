#include "ABR_h.h"
#include "Dataset_h.h"
#include "Split_h.h"
#include "DecisionTree_h.h"
#include "RandomForest_h.h"
#include "FileSave.h"

//*
int main(int argc, char** argv) {

    //TIME CLOCK INITIALISATION --------------------------------
    clock_t start = 0, middle = 0, end = 0;
    double cpu_time_used = 0;
    start = clock();

    //----------------------------------------------------------

    //RECUPERATION DU PROBLEME ---------------------------------

    char* path_train = NULL;
    char* path_test = NULL;

    if (argv[1] != NULL && argv[2] != NULL) {
        path_train = argv[1];
        path_test = argv[2];
    }
    else {
        path_train = "../Dataset/PENDIGITS_train.txt";
        path_test = "../Dataset/PENDIGITS_test.txt";
    }

    Dataset* trainData = Dataset_readFromFile(path_train);
    if (trainData == NULL)
        return EXIT_FAILURE;

    Dataset* testData = Dataset_readFromFile(path_test);
    if (trainData == NULL)
        return EXIT_FAILURE;

    Subproblem* subproblem = Dataset_getSubproblem(trainData);
    if (subproblem == NULL)
		return EXIT_FAILURE;

    //----------------------------------------------------------

    //CALCUL PAR L'ARBRE ---------------------------------------

    Subproblem_print(subproblem);
    
    DecisionTreeNode* tree = DecisionTree_create(subproblem, 0, 30, 1.0f);
    if (tree == NULL)
        return EXIT_FAILURE;

    int nodeCount = DecisionTree_nodeCount(tree);
    printf("Generation d'un arbre de %d noeuds\n", nodeCount);

    float scoreTrain = DecisionTree_evaluate(tree, trainData);
    float scoreTest = DecisionTree_evaluate(tree, testData);
    printf("train = %.3f, test = %.3f\n", scoreTrain, scoreTest);
    
    //en commentaire Dataset_printClasses(trainData);

    RandomForest* rf = RandomForest_create(20, trainData, 30, 0.5f, 1.0f);

    printf("Generation d'une foret de %d noeuds\n", RandomForest_nodeCount(rf));

    float trainScore = RandomForest_evaluate(rf, trainData);
    float testScore = RandomForest_evaluate(rf, testData);
    printf("train = %.3f, test = %.3f\n\n", trainScore, testScore);

        //TIME CLOCK END --------------------------------------------
    middle = clock();
    cpu_time_used = ((double)(middle - start)) / CLOCKS_PER_SEC;
    printf( "\nTemps d'execution : %.3fs.\n"
            "____________________________\n", cpu_time_used);
        //----------------------------------------------------------

    //----------------------------------------------------------

    //SAUVEGARDE DE L'ARBRE / LA FORET -------------------------

    int tmp = FileSave_UserInterface(nodeCount, trainScore, testScore);

    //----------------------------------------------------------

    //DESTROY --------------------------------------------------
    
    Dataset_destroy(trainData);
    trainData = NULL;

    Subproblem_destroy(subproblem);
    subproblem = NULL;

    DecisionTree_destroy(tree);
    tree = NULL;

    RandomForest_destroy(rf);
    tree = NULL;

    //----------------------------------------------------------

    //TIME CLOCK END --------------------------------------------
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf( "____________________________\n"
            "\nTemps d'execution : %.3fs.\n", cpu_time_used);
    //----------------------------------------------------------

    return 0;
}