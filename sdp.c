
#include "funcprotos.h"
#include "quicktime.h"


int quicktime_sdp_init(quicktime_sdp_t *sdp)
{
    sdp->string = NULL;

    return 0;
}

int quicktime_sdp_set(quicktime_sdp_t *sdp, char *string)
{
    free(sdp->string);
    if (string != NULL) {
        sdp->string = malloc(strlen(string) + 1);
        strcpy(sdp->string, string);
    } else {
        sdp->string = NULL;
    }

    return 0;
}

int quicktime_sdp_append(quicktime_sdp_t *sdp, char *appendString)
{
    char* newString = malloc(strlen(sdp->string) + strlen(appendString) + 1);

    strcpy(newString, sdp->string);
    strcat(newString, appendString);
    free(sdp->string);
    sdp->string = newString;

    return 0;
}

int quicktime_sdp_delete(quicktime_sdp_t *sdp)
{
    free(sdp->string);

    return 0;
}

int quicktime_sdp_dump(quicktime_sdp_t *sdp)
{
    printf("    sdp\n");
    printf("     string %s\n", sdp->string);

    return 0;
}

int quicktime_read_sdp(quicktime_t *file, quicktime_sdp_t *sdp, 
                       quicktime_atom_t* sdp_atom)
{
    int sdpLen = sdp_atom->size - 8;
    free(sdp->string);
    sdp->string = malloc(sdpLen + 1);
    quicktime_read_data(file, sdp->string, sdpLen);
    sdp->string[sdpLen] = '\0';

    return 0;
}

int quicktime_write_sdp(quicktime_t *file, quicktime_sdp_t *sdp)
{
    quicktime_atom_t atom;

    if (sdp->string == NULL) {
        return -1;
    }

    quicktime_atom_write_header(file, &atom, "sdp ");

    quicktime_write_data(file, sdp->string, strlen(sdp->string));

    quicktime_atom_write_footer(file, &atom);

    return 0;
}
