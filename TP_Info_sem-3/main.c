#include "ABR_h.h"
#include "Dataset_h.h"
#include "Split_h.h"
#include "DecisionTree_h.h"
#include "RandomForest_h.h"
#include "Paint_h.h"
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

    #ifdef DATASET_MAISON
    char* pathR = "../Dataset/WrittingTest4.bmp";
    Image* img = readImage(pathR);
    assert(img);
    char cookie = 0;
    printf("Voulez-vous participer à l'experience DATASETMAISON ? (y/n) : ");
    int poubelle = scanf("%c", &cookie);
    Dataset* testData;
    while ((cookie != 'y') && (cookie != 'n'))
    {
        printf("Voulez-vous participer à l'experience DATASETMAISON ? (y/n) : ");
        int poubelle = scanf("%c", &cookie);
    }
    char* pathW = "../Dataset/WrittingTest.txt";
    if (cookie == 'n')
    {
        writeImage(img, pathW);
        testData = Dataset_readFromFile(pathW);
    }
    else
    {
        char* pathD = "../Dataset/WrittingDataset.txt";
        char* pathC = "../Dataset/WrittingCopy.txt";
        modifyDataset(img, pathW, pathD, pathC);
        copyDataset(pathD, pathC);
        testData = Dataset_readFromFile(pathC);
    }
    #else
    Dataset* testData = Dataset_readFromFile(path2);
    #endif
  
    if (trainData == NULL)
        return EXIT_FAILURE;

    printf("%d %d %d\n", trainData->instanceCount, trainData->featureCount, trainData->classCount);

    /*Subproblem* subproblem = Subproblem_create(10, 10, 10);
    if (subproblem == NULL)
        return EXIT_FAILURE;*/
    
    Subproblem* subproblem = Dataset_getSubproblem(trainData);
    if (subproblem == NULL)
		    return EXIT_FAILURE;

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

    #ifdef ENSACHAGE_INITIAL
    DecisionTreeNode* tree = DecisionTree_create(subproblem, 0, 25, 1.0f);

    if (tree == NULL)
        return EXIT_FAILURE;

    int nodeCount = DecisionTree_nodeCount(tree);
    printf("Generation d'un arbre de %d noeuds\n", nodeCount);

    float scoreTrain = DecisionTree_evaluate(tree, trainData);
    float scoreTest = DecisionTree_evaluate(tree, testData);
    printf("train = %.3f, test = %.3f\n", scoreTrain, scoreTest);

    DecisionTree_destroy(tree);
    tree = NULL;

    RandomForest* rf = RandomForest_create(5, trainData, 25, 0.5f, 1.0f);

    printf("Generation d'une foret de %d noeuds\n", RandomForest_nodeCount(rf));

    float trainScore = RandomForest_evaluate(rf, trainData);
    float testScore = RandomForest_evaluate(rf, testData);
    printf("train = %.3f, test = %.3f\n", trainScore, testScore);

    #else
    RandomForest* rf = RandomForest_create(3, trainData, 30, 1.0f, 1.0f);

    printf("Generation d'une foret de %d noeuds\n", RandomForest_nodeCount(rf));

    float trainScore = RandomForest_evaluate(rf, trainData);
    float testScore = RandomForest_evaluate(rf, testData);

    printf("train = %.3f, test = %.3f\n", trainScore, testScore);

    #endif

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

    RandomForest_destroy(rf);
    rf = NULL;

    //----------------------------------------------------------

    //TIME CLOCK END --------------------------------------------
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf( "____________________________\n"
            "\nTemps d'execution : %.3fs.\n", cpu_time_used);
    //----------------------------------------------------------

    return 0;
}