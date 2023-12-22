#include "ABR_h.h"
#include "Dataset_h.h"
#include "Split_h.h"
#include "DecisionTree_h.h"
#include "RandomForest_h.h"
#include "Paint_h.h"
#include "FileSave.h"

int main(int argc, char** argv) {

    //TIME CLOCK INITIALISATION --------------------------------
    clock_t start = 0, middle = 0, end = 0;
    double cpu_time_used = 0;
    start = clock();
    //  //----------------------------------------------------------

    #ifdef FOR_MOODLE

        Dataset* trainData = Dataset_readFromFile(argv[1]);
        Subproblem* sp = Dataset_getSubproblem(trainData);
        RandomForest* rf = RandomForest_create(NOMBRE_ARBRES, trainData, MAX_DEPTH, BAGGING_PROPORTION, PRUNNING_THRESHOLD);
        Dataset* testData = Dataset_readFromFile(argv[2]);
        float scoreTest = RandomForest_evaluate(rf, testData);
        RandomForest_destroy(rf);
        Subproblem_destroy(sp);
        Dataset_destroy(trainData);
        Dataset_destroy(testData);
        return 0;

    #else

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
         
        //path_train = "../Dataset/FASHION_train.txt";
        //path_test = "../Dataset/FASHION_test.txt";

        //path_train = "../Dataset/MNIST_train.txt";
        //path_test = "../Dataset/MNIST_test.txt";
    }

        #ifdef DATASET_MAISON
        char* pathR = CHEMIN_IMAGE_BMP;
        Image* img = readImage(pathR);
        assert(img);
        char cookie = 0;
        printf("Voulez-vous participer a l'experience DATASETMAISON ? (y/n) : ");
        int poubelle = scanf("%c", &cookie);
        Dataset* testData;
        while ((cookie != 'y') && (cookie != 'n'))
        {
            printf("Voulez-vous participer a l'experience DATASETMAISON ? (y/n) : ");
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

        Dataset* testData = Dataset_readFromFile(path_test);
        if (testData == NULL)
            return EXIT_FAILURE;
        
        #endif    

        Dataset* trainData = Dataset_readFromFile(path_train);
        if (trainData == NULL)
            return EXIT_FAILURE; 

        Subproblem* subproblem = Dataset_getSubproblem(trainData);
        if (subproblem == NULL)
		    return EXIT_FAILURE;

        //----------------------------------------------------------

        //CALCUL PAR L'ARBRE ---------------------------------------

        Subproblem_print(subproblem);

        #ifdef ENSACHAGE_INITIAL
        DecisionTreeNode* tree = DecisionTree_create(subproblem, 0, MAX_DEPTH, PRUNNING_THRESHOLD);

        if (tree == NULL)
            return EXIT_FAILURE;

        int nodeCount = DecisionTree_nodeCount(tree);
        printf("Generation d'un arbre de %d noeuds\n", nodeCount);

        float scoreTrain = DecisionTree_evaluate(tree, trainData);
        float scoreTest = DecisionTree_evaluate(tree, testData);
        printf("train = %.3f, test = %.3f\n", scoreTrain, scoreTest);

        RandomForest* rf = RandomForest_create(NOMBRE_ARBRES, trainData, MAX_DEPTH, BAGGING_PROPORTION, PRUNNING_THRESHOLD);

        int rf_nodeCount = RandomForest_nodeCount(rf);

        printf("Generation d'une foret de %d noeuds\n", rf_nodeCount);

        float trainScore = RandomForest_evaluate(rf, trainData);
        float testScore = RandomForest_evaluate(rf, testData);
        printf("train = %.3f, test = %.3f\n", trainScore, testScore);

        #else
        DecisionTreeNode* tree = DecisionTree_create(subproblem, 0, MAX_DEPTH, PRUNNING_THRESHOLD);

        if (tree == NULL)
            return EXIT_FAILURE;

        int nodeCount = DecisionTree_nodeCount(tree);
        printf("Generation d'un arbre de %d noeuds (perte de precision due au bagging)\n", nodeCount);

        float scoreTrain = DecisionTree_evaluate(tree, trainData);
        float scoreTest = DecisionTree_evaluate(tree, testData);
        printf("train = %.3f, test = %.3f\n", scoreTrain, scoreTest);

        RandomForest* rf = NULL;

            #ifdef SAVE_LOAD
                char* fileName = FileLoad_UserInterface();
                rf = SaveTree_loadForest(fileName);
            #else
                rf = RandomForest_create(NOMBRE_ARBRES, trainData, MAX_DEPTH, BAGGING_PROPORTION, PRUNNING_THRESHOLD);
            #endif

        int rf_nodeCount = RandomForest_nodeCount(rf);

        printf("Generation d'une foret de %d noeuds\n", rf_nodeCount);

        float trainScore = RandomForest_evaluate(rf, trainData);
        float testScore = RandomForest_evaluate(rf, testData);

        printf("train = %.3f, test = %.3f\n", trainScore, testScore);

        //TIME CLOCK MIDDLE ----------------------------------------
        middle = clock();
        cpu_time_used = ((double)(middle - start)) / CLOCKS_PER_SEC;
        printf("\nTemps d'execution : %.3fs.\n"
            "____________________________\n", cpu_time_used);
        //----------------------------------------------------------

            #ifdef SAVE_LOAD
                    if (FileSave_UserInterface(rf_nodeCount, trainScore, testScore, rf) == -1)
                        return EXIT_FAILURE;
            #endif

        #endif

        //DESTROY --------------------------------------------------
    
    
        Dataset_destroy(trainData);
        trainData = NULL;

        Subproblem_destroy(subproblem);
        subproblem = NULL;

        DecisionTree_destroy(tree);
        tree = NULL;
  
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

    #endif  
}