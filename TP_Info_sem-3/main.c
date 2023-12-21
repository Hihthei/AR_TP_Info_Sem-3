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

    char* path = "../Dataset/PENDIGITS_train.txt";
    
    Dataset* trainData = Dataset_readFromFile(path);
    if (trainData == NULL)
        return EXIT_FAILURE;

    char* path2 = "../Dataset/PENDIGITS_test.txt";

    #ifdef DATASET_MAISON
    char* pathR = "../Dataset/etsr.bmp";
    Image* img = readImage(pathR);
    assert(img);
    char* pathW = "../Dataset/WrittingTest.txt";
    writeImage(img, pathW);
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

    #ifndef ENSACHAGE_INITIAL
    DecisionTreeNode* tree = DecisionTree_create(subproblem, 0, 25, 1.0f);
    if (tree == NULL)
        return EXIT_FAILURE;

    printf("Generation d'un arbre de %d noeuds\n", DecisionTree_nodeCount(tree));

    float scoreTrain = DecisionTree_evaluate(tree, trainData);
    float scoreTest = DecisionTree_evaluate(tree, testData);
    printf("train = %.3f, test = %.3f\n", scoreTrain, scoreTest);

    DecisionTree_destroy(tree);
    tree = NULL;

    RandomForest* rf = RandomForest_create(17, trainData, 25, 0.5f, 1.0f);

    printf("Generation d'une foret de %d noeuds\n", RandomForest_nodeCount(rf));

    float trainScore = RandomForest_evaluate(rf, trainData);
    float testScore = RandomForest_evaluate(rf, testData);
    printf("train = %.3f, test = %.3f\n", trainScore, testScore);

    RandomForest* rf2 = RandomForest_create(17, trainData, 25, 0.5f, 1.0f);

    printf("Generation d'une foret de %d noeuds\n", RandomForest_nodeCount(rf2));

    float trainScore2 = RandomForest_evaluate(rf2, trainData);
    float testScore2 = RandomForest_evaluate(rf2, testData);
    printf("train = %.3f, test = %.3f\n", trainScore2, testScore2);

    RandomForest* rf3 = RandomForest_create(20, trainData, 25, 0.5f, 1.0f);

    printf("Generation d'une foret de %d noeuds\n", RandomForest_nodeCount(rf3));

    float trainScore3 = RandomForest_evaluate(rf3, trainData);
    float testScore3 = RandomForest_evaluate(rf3, testData);
    printf("train = %.3f, test = %.3f\n", trainScore3, testScore3);

    #else
    RandomForest* rf = RandomForest_create(20, trainData, 30, 1.0f, 1.0f);

    printf("Generation d'une foret de %d noeuds\n", RandomForest_nodeCount(rf));

    float trainScore = RandomForest_evaluate(rf, trainData);
    float testScore = RandomForest_evaluate(rf, testData);
    printf("train = %.3f, test = %.3f\n", trainScore, testScore);

    RandomForest* rf2 = RandomForest_create(20, trainData, 30, 1.0f, 1.0f);

    printf("Generation d'une foret de %d noeuds\n", RandomForest_nodeCount(rf2));

    float trainScore2 = RandomForest_evaluate(rf2, trainData);
    float testScore2 = RandomForest_evaluate(rf2, testData);
    printf("train = %.3f, test = %.3f\n", trainScore2, testScore2);

    RandomForest* rf3 = RandomForest_create(20, trainData, 30, 1.0f, 1.0f);

    printf("Generation d'une foret de %d noeuds\n", RandomForest_nodeCount(rf3));

    float trainScore3 = RandomForest_evaluate(rf3, trainData);
    float testScore3 = RandomForest_evaluate(rf3, testData);
    printf("train = %.3f, test = %.3f\n", trainScore3, testScore3);

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