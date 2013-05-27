
#include "funcprotos.h"
#include "quicktime.h"


int quicktime_pmax_init(quicktime_pmax_t *pmax)
{
    pmax->numBytes = 0;

    return 0;
}

int quicktime_pmax_delete(quicktime_pmax_t *pmax)
{

    return 0;
}

int quicktime_pmax_dump(quicktime_pmax_t *pmax)
{
    printf("    max packet size\n");
    printf("     numBytes %lu\n", pmax->numBytes);

    return 0;
}

int quicktime_read_pmax(quicktime_t *file, quicktime_pmax_t *pmax)
{
    pmax->numBytes = quicktime_read_int32(file);

    return 0;
}

int quicktime_write_pmax(quicktime_t *file, quicktime_pmax_t *pmax)
{
    quicktime_atom_t atom;

    quicktime_atom_write_header(file, &atom, "pmax");

    quicktime_write_int32(file, pmax->numBytes);

    quicktime_atom_write_footer(file, &atom);

    return 0;
}

