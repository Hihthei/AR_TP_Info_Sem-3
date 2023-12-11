#include "ABR_h.h"

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
}
