
#include "funcprotos.h"

#include "quicktime.h"


int quicktime_hmhd_init(quicktime_hmhd_t *hmhd)
{
    hmhd->version = 0;
    hmhd->flags = 0;
    hmhd->maxPDUsize = 0;
    hmhd->avgPDUsize = 0;
    hmhd->maxbitrate = 0;
    hmhd->avgbitrate = 0;
    hmhd->slidingavgbitrate = 0;

    return 0;
}

int quicktime_hmhd_delete(quicktime_hmhd_t *hmhd)
{

    return 0;
}

int quicktime_hmhd_dump(quicktime_hmhd_t *hmhd)
{
    printf("    hint media header\n");
    printf("     version %d\n", hmhd->version);
    printf("     flags %d\n", hmhd->flags);
    printf("     maxPDUsize %d\n", hmhd->maxPDUsize);
    printf("     avgPDUsize %d\n", hmhd->avgPDUsize);
    printf("     maxbitrate %d\n", hmhd->maxbitrate);
    printf("     avgbitrate %d\n", hmhd->avgbitrate);
    printf("     slidingavgbitrate %d\n", hmhd->slidingavgbitrate);

    return 0;
}

int quicktime_read_hmhd(quicktime_t *file, quicktime_hmhd_t *hmhd)
{
    hmhd->version = quicktime_read_char(file);
    hmhd->flags = quicktime_read_int24(file);
    hmhd->maxPDUsize = quicktime_read_int16(file);
    hmhd->avgPDUsize = quicktime_read_int16(file);
    hmhd->maxbitrate = quicktime_read_int32(file);
    hmhd->avgbitrate = quicktime_read_int32(file);
    hmhd->slidingavgbitrate = quicktime_read_int32(file);

    return 0;
}

int quicktime_write_hmhd(quicktime_t *file, quicktime_hmhd_t *hmhd)
{
    quicktime_atom_t atom;

    quicktime_atom_write_header(file, &atom, "hmhd");

    quicktime_write_char(file, hmhd->version);
    quicktime_write_int24(file, hmhd->flags);

    quicktime_write_int16(file, hmhd->maxPDUsize);
    quicktime_write_int16(file, hmhd->avgPDUsize);
    quicktime_write_int32(file, hmhd->maxbitrate);
    quicktime_write_int32(file, hmhd->avgbitrate);
    quicktime_write_int32(file, hmhd->slidingavgbitrate);

    quicktime_atom_write_footer(file, &atom);

    return 0;
}

