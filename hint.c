
#include "funcprotos.h"
#include "quicktime.h"


int quicktime_hint_init(quicktime_hint_t *hint)
{
    hint->numTracks = 0;
    hint->trackIds[0] = -1;
    hint->traks[0] = NULL;

    return 0;
}

int quicktime_hint_set(quicktime_hint_t *hint, quicktime_trak_t *refTrak)
{
    hint->traks[hint->numTracks] = refTrak;
    hint->trackIds[hint->numTracks] = refTrak->tkhd.track_id;
    hint->numTracks++;

    return 0;
}

int quicktime_hint_delete(quicktime_hint_t *hint)
{
    return 0;
}

int quicktime_read_hint(quicktime_t *file, quicktime_hint_t *hint, quicktime_atom_t *parent_atom)
{
    quicktime_trak_t* refTrak = NULL;

    while (quicktime_position(file) < parent_atom->end) {
        hint->trackIds[hint->numTracks] = quicktime_read_int32(file);
        hint->traks[hint->numTracks] = NULL; 
        hint->numTracks++;
    }

    return 0;
}

int quicktime_write_hint(quicktime_t *file, quicktime_hint_t *hint)
{
    quicktime_atom_t atom;
    int i = 0;

    quicktime_atom_write_header(file, &atom, "hint");

    for (i = 0; i < hint->numTracks; i++) {
        quicktime_write_int32(file, hint->trackIds[i]);
    }

    quicktime_atom_write_footer(file, &atom);

    return 0;
}

int quicktime_hint_dump(quicktime_hint_t *hint)
{
    int i;

    printf("   hint\n");
    for (i = 0; i < hint->numTracks; i++) {
        printf("    track %d\n", hint->trackIds[i]);
    }

    return 0;
}

