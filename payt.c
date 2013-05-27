
#include "funcprotos.h"
#include "quicktime.h"


int quicktime_payt_init(quicktime_payt_t *payt)
{
    payt->payloadNumber = 0;
    payt->rtpMapString[0] = '\0';

    return 0;
}

int quicktime_payt_delete(quicktime_payt_t *payt)
{

    return 0;
}

int quicktime_payt_dump(quicktime_payt_t *payt)
{
    printf("    payload type\n");
    printf("     payload number %lu\n", payt->payloadNumber);
    printf("     rtp map string %s\n", payt->rtpMapString);

    return 0;
}

int quicktime_read_payt(quicktime_t *file, quicktime_payt_t *payt)
{
    payt->payloadNumber = quicktime_read_int32(file);
    quicktime_read_pascal(file, payt->rtpMapString);

    return 0;
}

int quicktime_write_payt(quicktime_t *file, quicktime_payt_t *payt)
{
    quicktime_atom_t atom;

    quicktime_atom_write_header(file, &atom, "payt");

    quicktime_write_int32(file, payt->payloadNumber);
    quicktime_write_pascal(file, payt->rtpMapString);

    quicktime_atom_write_footer(file, &atom);

    return 0;
}

