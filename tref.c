
#include "funcprotos.h"
#include "quicktime.h"


int quicktime_tref_init(quicktime_tref_t *tref)
{
    quicktime_hint_init(&(tref->hint));

    return 0;
}

int quicktime_tref_init_hint(quicktime_tref_t *tref, quicktime_trak_t *refTrak)
{
    quicktime_hint_set(&(tref->hint), refTrak);

    return 0;
}

int quicktime_tref_delete(quicktime_tref_t *tref)
{
    quicktime_hint_delete(&(tref->hint));

    return 0;
}

int quicktime_tref_dump(quicktime_tref_t *tref)
{
    printf("  tref\n");
    quicktime_hint_dump(&tref->hint);

    return 0;
}

int quicktime_read_tref(quicktime_t *file, quicktime_tref_t *tref, quicktime_atom_t *parent_atom)
{
    quicktime_atom_t leaf_atom;

    do {
        quicktime_atom_read_header(file, &leaf_atom);

        if (quicktime_atom_is(&leaf_atom, "hint")) {
            quicktime_read_hint(file, &(tref->hint), &leaf_atom);
        } else {
            quicktime_atom_skip(file, &leaf_atom);
        }
    } while (quicktime_position(file) < parent_atom->end);

    return 0;
}

int quicktime_write_tref(quicktime_t *file, quicktime_tref_t *tref)
{
    quicktime_atom_t atom;

    if (tref->hint.numTracks == 0) {
        return -1;
    }

    quicktime_atom_write_header(file, &atom, "tref");

    quicktime_write_hint(file, &(tref->hint));

    quicktime_atom_write_footer(file, &atom);

    return 0;
}

