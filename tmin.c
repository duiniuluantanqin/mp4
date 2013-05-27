
#include "funcprotos.h"
#include "quicktime.h"


int quicktime_tmin_init(quicktime_tmin_t *tmin)
{
    tmin->milliSecs = 0;

    return 0;
}

int quicktime_tmin_delete(quicktime_tmin_t *tmin)
{

    return 0;
}

int quicktime_tmin_dump(quicktime_tmin_t *tmin)
{
    printf("    min relative xmit time\n");
    printf("     milliSecs %lu\n", tmin->milliSecs);

    return 0;
}

int quicktime_read_tmin(quicktime_t *file, quicktime_tmin_t *tmin)
{
    tmin->milliSecs = quicktime_read_int32(file);

    return 0;
}

int quicktime_write_tmin(quicktime_t *file, quicktime_tmin_t *tmin)
{
    quicktime_atom_t atom;

    quicktime_atom_write_header(file, &atom, "tmin");

    quicktime_write_int32(file, tmin->milliSecs);

    quicktime_atom_write_footer(file, &atom);

    return 0;
}

