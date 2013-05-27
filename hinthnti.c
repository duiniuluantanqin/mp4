
#include "quicktime.h"


int quicktime_hint_hnti_init(quicktime_hint_hnti_t *hnti)
{
    return quicktime_sdp_init(&(hnti->sdp));
}

int quicktime_hint_hnti_delete(quicktime_hint_hnti_t *hnti)
{
    return quicktime_sdp_delete(&(hnti->sdp));
}

int quicktime_hint_hnti_dump(quicktime_hint_hnti_t *hnti)
{
    printf("   hnti\n");
    return quicktime_sdp_dump(&hnti->sdp);
}

int quicktime_read_hint_hnti(quicktime_t *file, quicktime_hint_hnti_t *hnti, quicktime_atom_t *parent_atom)
{
    quicktime_atom_t leaf_atom;

    do 
    {
        quicktime_atom_read_header(file, &leaf_atom);

        if (quicktime_atom_is(&leaf_atom, "sdp ")) 
        {
            quicktime_read_sdp(file, &(hnti->sdp), &leaf_atom);
        } 
        else 
        {
            quicktime_atom_skip(file, &leaf_atom);
        }
    } while (quicktime_position(file) < parent_atom->end);

    return 0;
}

int quicktime_write_hint_hnti(quicktime_t *file, quicktime_hint_hnti_t *hnti)
{
    quicktime_atom_t atom;

    if (hnti->sdp.string == NULL) 
    {
        return -1;
    }

    quicktime_atom_write_header(file, &atom, "hnti");

    quicktime_write_sdp(file, &(hnti->sdp));

    quicktime_atom_write_footer(file, &atom);

    return 0;
}

