#include "quicktime.h"
#include "funcprotos.h"


int quicktime_dmed_init(quicktime_dmed_t *dmed)
{
    dmed->numBytes = 0;

    return 0;
}

int quicktime_dmed_delete(quicktime_dmed_t *dmed)
{
    return 0;
}

int quicktime_dmed_dump(quicktime_dmed_t *dmed)
{
    printf("    total media bytes\n");
    printf("     numBytes "U64"\n", dmed->numBytes);

    return 0;
}

int quicktime_read_dmed(quicktime_t *file, quicktime_dmed_t *dmed)
{
    dmed->numBytes = quicktime_read_int64(file);

    return 0;
}

int quicktime_write_dmed(quicktime_t *file, quicktime_dmed_t *dmed)
{
    quicktime_atom_t atom;

    quicktime_atom_write_header(file, &atom, "dmed");

    quicktime_write_int64(file, dmed->numBytes);

    quicktime_atom_write_footer(file, &atom);

    return 0;
}

