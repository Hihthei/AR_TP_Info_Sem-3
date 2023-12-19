#include "ABR_h.h"
#include "Dataset_h.h"

////*
//int main(int argc, char** argv)
//{
//    //TIME CLOCK INITIALISATION --------------------------------
//    clock_t start = 0, end = 0;
//    double cpu_time_used = 0;
//    start = clock();
//    //----------------------------------------------------------
//
//    srand((unsigned int)time(NULL));
//
//    char* path = "../Dataset/PENDIGITS_test.txt";
//    
//    Dataset* trainData = Dataset_readFromFile(path);
//    if (trainData == NULL)
//        return EXIT_FAILURE;
//
//    /*
//    printf("%d %d %d\n", trainData->instanceCount, trainData->featureCount, trainData->classCount);
//
//    Subproblem* subproblem = Subproblem_create(10, 10, 10);
//    if (subproblem == NULL)
//        return EXIT_FAILURE;
//    //*/
//    
//    //*
//    Subproblem* subproblem = Dataset_getSubproblem(trainData);
//    if (subproblem == NULL)
//		return EXIT_FAILURE;
//    //*/
//
//
//    //----------------------------------------------------------
//
//    //Dataset_printClasses(trainData);
//
//    Subproblem_print(subproblem);
//
//    //----------------------------------------------------------
//    
//    Dataset_destroy(trainData);
//    trainData = NULL;
//
//    Subproblem_destroy(subproblem);
//    subproblem = NULL;
//
//    //TIME CLOCK END --------------------------------------------
//    end = clock();
//    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
//    printf( "____________________________\n"
//            "\nTemps d'execution : %.3fs.\n", cpu_time_used);
//    //----------------------------------------------------------
//
//    return 0;
//}//*/

int main(int argc, char** argv)
{
    //TIME CLOCK INITIALISATION --------------------------------
    clock_t start = 0, end = 0;
    double cpu_time_used = 0;
    start = clock();
    //----------------------------------------------------------

    srand((unsigned int)time(NULL));

	BSTree* tree = BSTree_Create();

	for (int i = 0; i < 1500; i++)
	{
        BSTree_Insert(tree, rand() % 3000);
	}
    printf("%d - %d\n", tree->size, BSTree_nodeCount(tree));

    BSTree_Delete(tree);

    //TIME CLOCK END --------------------------------------------
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf( "____________________________\n"
            "\nTemps d'execution : %.3fs.\n", cpu_time_used);
    //----------------------------------------------------------

    return 0;
}