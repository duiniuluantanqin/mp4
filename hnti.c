
#include "funcprotos.h"

#include "quicktime.h"


int quicktime_hnti_init(quicktime_hnti_t *hnti)
{
    return quicktime_rtp_init(&(hnti->rtp));
}

int quicktime_hnti_delete(quicktime_hnti_t *hnti)
{
    return quicktime_rtp_delete(&(hnti->rtp));
}

int quicktime_hnti_dump(quicktime_hnti_t *hnti)
{
    printf("   hnti\n");
    return quicktime_rtp_dump(&hnti->rtp);
}

int quicktime_read_hnti(quicktime_t *file, quicktime_hnti_t *hnti, quicktime_atom_t *parent_atom)
{
    quicktime_atom_t leaf_atom;

    do {
        quicktime_atom_read_header(file, &leaf_atom);

        if (quicktime_atom_is(&leaf_atom, "rtp ")) {
            quicktime_read_rtp(file, &(hnti->rtp), &leaf_atom);
        } else {
            quicktime_atom_skip(file, &leaf_atom);
        }
    } while (quicktime_position(file) < parent_atom->end);

    return 0;
}

int quicktime_write_hnti(quicktime_t *file, quicktime_hnti_t *hnti)
{
    quicktime_atom_t atom;

    if (hnti->rtp.string == NULL) {
        return -1;
    }

    quicktime_atom_write_header(file, &atom, "hnti");

    quicktime_write_rtp(file, &(hnti->rtp));

    quicktime_atom_write_footer(file, &atom);

    return 0;
}

