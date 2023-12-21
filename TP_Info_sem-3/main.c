#include "ABR_h.h"
#include "Dataset_h.h"
#include "Split_h.h"
#include "DecisionTree_h.h"
#include "RandomForest_h.h"
#include "Paint_h.h"

//*
int main(int argc, char** argv) {

    //TIME CLOCK INITIALISATION --------------------------------
    clock_t start = 0, end = 0;
    double cpu_time_used = 0;
    start = clock();
    //----------------------------------------------------------

    srand((unsigned int)time(NULL));

    char* pathR = "../Dataset/WrittingTest.bmp";
    Image *imp = readImage(pathR);
    assert(imp);
    printf("ya");
    char* pathW = "../Dataset/WrittingTest.txt";
    writeImage(imp, pathW);


    char* path = "../Dataset/PENDIGITS_train.txt";
    
    Dataset* trainData = Dataset_readFromFile(path);
    if (trainData == NULL)
        return EXIT_FAILURE;

    char* path2 = "../Dataset/PENDIGITS_test.txt";

    #ifdef DATASET_MAISON
    Dataset* testData = Dataset_readFromFile(pathW);
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


    //----------------------------------------------------------
    
    //Dataset_printClasses(trainData);

    Subproblem_print(subproblem);
    
    //en commentaire Dataset_printClasses(trainData);

    #ifdef ENSACHAGE_INITIAL
    DecisionTreeNode* tree = DecisionTree_create(subproblem, 0, 30, 1.0f);
    if (tree == NULL)
        return EXIT_FAILURE;

    printf("Generation d'un arbre de %d noeuds\n", DecisionTree_nodeCount(tree));

    float scoreTrain = DecisionTree_evaluate(tree, trainData);
    float scoreTest = DecisionTree_evaluate(tree, testData);
    printf("train = %.3f, test = %.3f\n", scoreTrain, scoreTest);

    DecisionTree_destroy(tree);
    tree = NULL;

    RandomForest* rf = RandomForest_create(100, trainData, 30, 0.5f, 1.0f);

    printf("Generation d'une foret de %d noeuds\n", RandomForest_nodeCount(rf));

    float trainScore = RandomForest_evaluate(rf, trainData);
    float testScore = RandomForest_evaluate(rf, testData);
    printf("train = %.3f, test = %.3f\n", trainScore, testScore);

    #else
    RandomForest* rf = RandomForest_create(100, trainData, 30, 1.0f, 1.0f);

    printf("Generation d'une foret de %d noeuds\n", RandomForest_nodeCount(rf));

    float trainScore = RandomForest_evaluate(rf, trainData);
    float testScore = RandomForest_evaluate(rf, testData);
    printf("train = %.3f, test = %.3f\n", trainScore, testScore);

    #endif


    //----------------------------------------------------------

    /*Split split = Split_compute(subproblem);
    printf("Split : %d _ %.2f\n", split.featureID, split.threshold);*/
    

    //----------------------------------------------------------
    
    Dataset_destroy(trainData);
    trainData = NULL;

    Subproblem_destroy(subproblem);
    subproblem = NULL;

    RandomForest_destroy(rf);
    rf = NULL;

    //DecisionTree_destroy(tree);
    //tree = NULL;

    //TIME CLOCK END --------------------------------------------
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf( "____________________________\n"
            "\nTemps d'execution : %.3fs.\n", cpu_time_used);
    //----------------------------------------------------------

    return 0;
}