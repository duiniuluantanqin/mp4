
#include "funcprotos.h"
#include "quicktime.h"


int quicktime_tpyl_init(quicktime_tpyl_t *tpyl)
{
    tpyl->numBytes = 0;

    return 0;
}

int quicktime_tpyl_delete(quicktime_tpyl_t *tpyl)
{

    return 0;
}

int quicktime_tpyl_dump(quicktime_tpyl_t *tpyl)
{
    printf("    total RTP payload bytes\n");
    printf("     numBytes "U64"\n", tpyl->numBytes);

    return 0;
}

int quicktime_read_tpyl(quicktime_t *file, quicktime_tpyl_t *tpyl)
{
    tpyl->numBytes = quicktime_read_int64(file);

    return 0;
}

int quicktime_write_tpyl(quicktime_t *file, quicktime_tpyl_t *tpyl)
{
    quicktime_atom_t atom;

    quicktime_atom_write_header(file, &atom, "tpyl");

    quicktime_write_int64(file, tpyl->numBytes);

    quicktime_atom_write_footer(file, &atom);

    return 0;
}

