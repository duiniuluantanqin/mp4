
#include "funcprotos.h"
#include "quicktime.h"


int quicktime_hint_udta_init(quicktime_hint_udta_t *hint_udta)
{
    quicktime_hinf_init(&(hint_udta->hinf));
    quicktime_hint_hnti_init(&(hint_udta->hnti));

    return 0;
}

int quicktime_hint_udta_delete(quicktime_hint_udta_t *hint_udta)
{
    quicktime_hinf_delete(&(hint_udta->hinf));
    quicktime_hint_hnti_delete(&(hint_udta->hnti));

    return 0;
}

int quicktime_hint_udta_dump(quicktime_hint_udta_t *hint_udta)
{
    printf("  udta\n");
    quicktime_hinf_dump(&hint_udta->hinf);
    quicktime_hint_hnti_dump(&hint_udta->hnti);

    return 0;
}

int quicktime_read_hint_udta(quicktime_t *file, quicktime_hint_udta_t *hint_udta, quicktime_atom_t *parent_atom)
{
    quicktime_atom_t leaf_atom;

    do {
        /* udta atoms can be terminated by a 4 byte zero */
        if (parent_atom->end - quicktime_position(file) < HEADER_LENGTH) {
            u_char trash[HEADER_LENGTH];
            int remainder = parent_atom->end - quicktime_position(file);
            quicktime_read_data(file, trash, remainder);
            break;
        }

        quicktime_atom_read_header(file, &leaf_atom);

        if (quicktime_atom_is(&leaf_atom, "hinf")) {
            quicktime_read_hinf(file, &(hint_udta->hinf), &leaf_atom);
        } else if (quicktime_atom_is(&leaf_atom, "hnti")) {
            quicktime_read_hint_hnti(file, &(hint_udta->hnti), &leaf_atom);
        } else {
            quicktime_atom_skip(file, &leaf_atom);
        }
    } while (quicktime_position(file) < parent_atom->end);

    return 0;
}

int quicktime_write_hint_udta(quicktime_t *file, quicktime_hint_udta_t *hint_udta)
{
    quicktime_atom_t atom;

    if (hint_udta->hnti.sdp.string == NULL) {
        return -1;
    }

    quicktime_atom_write_header(file, &atom, "udta");

    quicktime_write_hinf(file, &(hint_udta->hinf));
    quicktime_write_hint_hnti(file, &(hint_udta->hnti));

    quicktime_atom_write_footer(file, &atom);

    return 0;
}

