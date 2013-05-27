
#include "funcprotos.h"

#include "quicktime.h"


int quicktime_drep_init(quicktime_drep_t *drep)
{
    drep->numBytes = 0;

    return 0;
}

int quicktime_drep_delete(quicktime_drep_t *drep)
{

    return 0;
}

int quicktime_drep_dump(quicktime_drep_t *drep)
{
    printf("    total repeated bytes\n");
    printf("     numBytes "U64"\n", drep->numBytes);

    return 0;
}

int quicktime_read_drep(quicktime_t *file, quicktime_drep_t *drep)
{
    drep->numBytes = quicktime_read_int64(file);

    return 0;
}

int quicktime_write_drep(quicktime_t *file, quicktime_drep_t *drep)
{
    quicktime_atom_t atom;

    quicktime_atom_write_header(file, &atom, "drep");

    quicktime_write_int64(file, drep->numBytes);

    quicktime_atom_write_footer(file, &atom);

    return 0;
}

