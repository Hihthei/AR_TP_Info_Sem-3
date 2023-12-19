#include "ABR_h.h"
#include "Dataset_h.h"
#include "Split_h.h"

/*
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
}//*/

//*
int main(int argc, char** argv)
{
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

    /*
    printf("%d %d %d\n", trainData->instanceCount, trainData->featureCount, trainData->classCount);

    Subproblem* subproblem = Subproblem_create(10, 10, 10);
    if (subproblem == NULL)
        return EXIT_FAILURE;
    //*/
    
    //*
    Subproblem* subproblem = Dataset_getSubproblem(trainData);
    if (subproblem == NULL)
		return EXIT_FAILURE;
    //*/


    //----------------------------------------------------------

    //en commentaire Dataset_printClasses(trainData);

    Subproblem_print(subproblem);

    //----------------------------------------------------------

    Split split = Split_compute(subproblem);
    printf("ICI : %f %f %f\n", split.threshold, Split_gini(subproblem, 5, 1), Split_gini(subproblem, 1, 0.6));

    //----------------------------------------------------------
    
    Dataset_destroy(trainData);
    trainData = NULL;

    Subproblem_destroy(subproblem);
    subproblem = NULL;

    //TIME CLOCK END --------------------------------------------
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf( "____________________________\n"
            "\nTemps d'execution : %f.\n", cpu_time_used);
    //----------------------------------------------------------

    return 0;
}//*/
