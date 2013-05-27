
#include "funcprotos.h"
#include "quicktime.h"


int quicktime_tmax_init(quicktime_tmax_t *tmax)
{
    tmax->milliSecs = 0;

    return 0;
}

int quicktime_tmax_delete(quicktime_tmax_t *tmax)
{

    return 0;
}

int quicktime_tmax_dump(quicktime_tmax_t *tmax)
{
    printf("    max relative xmit time\n");
    printf("     milliSecs %lu\n", tmax->milliSecs);

    return 0;
}

int quicktime_read_tmax(quicktime_t *file, quicktime_tmax_t *tmax)
{
    tmax->milliSecs = quicktime_read_int32(file);

    return 0;
}

int quicktime_write_tmax(quicktime_t *file, quicktime_tmax_t *tmax)
{
    quicktime_atom_t atom;

    quicktime_atom_write_header(file, &atom, "tmax");

    quicktime_write_int32(file, tmax->milliSecs);

    quicktime_atom_write_footer(file, &atom);

    return 0;
}

