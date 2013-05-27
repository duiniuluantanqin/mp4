
#include "funcprotos.h"

#include "quicktime.h"


int quicktime_nump_init(quicktime_nump_t *nump)
{
    nump->numPackets = 0;

    return 0;
}

int quicktime_nump_delete(quicktime_nump_t *nump)
{

    return 0;
}

int quicktime_nump_dump(quicktime_nump_t *nump)
{
    printf("    total RTP packets\n");
    printf("     numBytes "U64"\n", nump->numPackets);

    return 0;
}

int quicktime_read_nump(quicktime_t *file, quicktime_nump_t *nump)
{
    nump->numPackets = quicktime_read_int64(file);

    return 0;
}

int quicktime_write_nump(quicktime_t *file, quicktime_nump_t *nump)
{
    quicktime_atom_t atom;

    quicktime_atom_write_header(file, &atom, "nump");

    quicktime_write_int64(file, nump->numPackets);

    quicktime_atom_write_footer(file, &atom);

    return 0;
}

