
#include "funcprotos.h"
#include "quicktime.h"


int quicktime_rtp_init(quicktime_rtp_t *rtp)
{
    rtp->string = NULL;
    
    return 0;
}

int quicktime_rtp_set(quicktime_rtp_t *rtp, char *string)
{
    free(rtp->string);
    if (string != NULL) {
        rtp->string = malloc(strlen(string) + 1);
        strcpy(rtp->string, string);
    } else {
        rtp->string = NULL;
    }

    return 0;
}

int quicktime_rtp_append(quicktime_rtp_t *rtp, char *appendString)
{
    char* newString = malloc(strlen(rtp->string) + strlen(appendString) + 1);

    strcpy(newString, rtp->string);
    strcat(newString, appendString);
    free(rtp->string);
    rtp->string = newString;

    return 0;
}

int quicktime_rtp_delete(quicktime_rtp_t *rtp)
{
    free(rtp->string);

    return 0;
}

int quicktime_rtp_dump(quicktime_rtp_t *rtp)
{
    printf("    rtp\n");
    printf("     string %s\n", rtp->string);

    return 0;
}

int quicktime_read_rtp(quicktime_t *file, quicktime_rtp_t *rtp, 
                       quicktime_atom_t* rtp_atom)
{
    int rtpLen = rtp_atom->size - 12;
    free(rtp->string);
    rtp->string = malloc(rtpLen + 1);
    quicktime_read_int32(file);	// skip the 'sdp '
    quicktime_read_data(file, rtp->string, rtpLen);
    rtp->string[rtpLen] = '\0';

    return 0;
}

int quicktime_write_rtp(quicktime_t *file, quicktime_rtp_t *rtp)
{
    quicktime_atom_t atom;

    if (rtp->string == NULL) {
        return -1;
    }

    quicktime_atom_write_header(file, &atom, "rtp ");

    quicktime_write_data(file, "sdp ", 4);
    quicktime_write_data(file, rtp->string, strlen(rtp->string));

    quicktime_atom_write_footer(file, &atom);

    return 0;
}
