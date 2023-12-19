#include "ABR_h.h"
#include "Dataset_h.h"

int main(int argc, char** argv)
{
    char path[128] = "C:/Users/alyog/Documents/Datasets/PENDIGITS_train.txt";
    Dataset* trainData = Dataset_readFromFile(path);
    if (!trainData) printf("NO FILE !\n");
    else printf("%d %d %d\n", trainData->instanceCount, trainData->featureCount, trainData->classCount);

    Subproblem* subproblem = Dataset_getSubproblem(trainData);
    //Subproblem_print(subproblem);

    // Subproblem_destroy(subproblem);
    // Dataset_destroy(trainData);

    return 0;
}

/*
int main(int argc, char** argv)
{
    //TIME CLOCK INITIALISATION --------------------------------
    clock_t start = 0, end = 0;
    double cpu_time_used = 0;
    start = clock();
    //----------------------------------------------------------

    srand((unsigned int)time(NULL));

    BSTree* tree = BSTree_Create();

    //----------------------------------------------------------

    for (int i = 0; i < 15; i++) {
        int tmp = (int)rand()%10;
        BSTree_Insert(tree, tmp);
    }

    printf("tree size = %d\n", tree->size);

    BSTree_Print_UI(tree);

    //----------------------------------------------------------

    BSTree_Delete(tree);
    tree = NULL;

    //TIME CLOCK END --------------------------------------------
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf( "____________________________\n"
                    "\nTemps d'execution : %f.\n", cpu_time_used);
    //----------------------------------------------------------
    return 0;
}*/
