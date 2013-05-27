#include "quicktime.h"
#include "funcprotos.h"


int quicktime_dmax_init(quicktime_dmax_t *dmax)
{
    dmax->milliSecs = 0;

    return 0;
}

int quicktime_dmax_delete(quicktime_dmax_t *dmax)
{
    return 0;
}

int quicktime_dmax_dump(quicktime_dmax_t *dmax)
{
    printf("    max packet duration\n");
    printf("     milliSecs %lu\n", dmax->milliSecs);

    return 0;
}

int quicktime_read_dmax(quicktime_t *file, quicktime_dmax_t *dmax)
{
    dmax->milliSecs = quicktime_read_int32(file);

    return 0;
}

int quicktime_write_dmax(quicktime_t *file, quicktime_dmax_t *dmax)
{
    quicktime_atom_t atom;

    quicktime_atom_write_header(file, &atom, "dmax");

    quicktime_write_int32(file, dmax->milliSecs);

    quicktime_atom_write_footer(file, &atom);

    return 0;
}

