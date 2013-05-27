#include "quicktime.h"
#include "funcprotos.h"


int quicktime_matrix_init(quicktime_matrix_t *matrix)
{
    int i;
    for(i = 0; i < 9; i++) matrix->values[i] = 0;
    matrix->values[0] = matrix->values[4] = 1;
    matrix->values[8] = 16384;

    return 0;
}

int quicktime_matrix_delete(quicktime_matrix_t *matrix)
{

    return 0;
}

int quicktime_read_matrix(quicktime_t *file, quicktime_matrix_t *matrix)
{
    int i = 0;
    for(i = 0; i < 9; i++)
    {
        matrix->values[i] = quicktime_read_fixed32(file);
    }

    return 0;
}

int quicktime_matrix_dump(quicktime_matrix_t *matrix)
{
    int i;
    printf("   matrix");
    for(i = 0; i < 9; i++) printf(" %f", matrix->values[i]);
    printf("\n");

    return 0;
}

int quicktime_write_matrix(quicktime_t *file, quicktime_matrix_t *matrix)
{
    int i;
    for(i = 0; i < 9; i++)
    {
        quicktime_write_fixed32(file, matrix->values[i]);
    }

    return 0;
}
