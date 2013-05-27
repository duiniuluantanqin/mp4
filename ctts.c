#include "quicktime.h"
#include "funcprotos.h"


int quicktime_ctts_init(quicktime_ctts_t *ctts)
{
    ctts->version = 0;
    ctts->flags = 0;
    ctts->total_entries = 0;
    ctts->entries_allocated = 0;

    return 0;
}

int quicktime_ctts_init_table(quicktime_ctts_t *ctts)
{
    if (!ctts->entries_allocated) {
        ctts->entries_allocated = 1;
        ctts->table = (quicktime_ctts_table_t*)
            malloc(sizeof(quicktime_ctts_table_t) * ctts->entries_allocated);
        ctts->total_entries = 1;
    }

    return 0;
}

int quicktime_ctts_init_common(quicktime_t *file, quicktime_ctts_t *ctts)
{
    quicktime_ctts_table_t *table;
    quicktime_ctts_init_table(ctts);
    table = &(ctts->table[0]);

    table->sample_count = 0;      /* need to set this when closing */
    table->sample_offset = 0;

    return 0;
}

int quicktime_ctts_delete(quicktime_ctts_t *ctts)
{
    if (ctts->total_entries) {
        free(ctts->table);
    }
    ctts->total_entries = 0;

    return 0;
}

int quicktime_ctts_dump(quicktime_ctts_t *ctts)
{
    int i;
    printf("     composition time to sample\n");
    printf("      version %d\n", ctts->version);
    printf("      flags %d\n", ctts->flags);
    printf("      total_entries %d\n", ctts->total_entries);
    for(i = 0; i < ctts->total_entries; i++) {
        printf("       count %ld offset %ld\n", 
            ctts->table[i].sample_count,
            ctts->table[i].sample_offset);
    }

    return 0;
}

int quicktime_read_ctts(quicktime_t *file, quicktime_ctts_t *ctts)
{
    int i;
    ctts->version = quicktime_read_char(file);
    ctts->flags = quicktime_read_int24(file);
    ctts->total_entries = quicktime_read_int32(file);

    ctts->table = (quicktime_ctts_table_t*)
        malloc(sizeof(quicktime_ctts_table_t) * ctts->total_entries);

    for (i = 0; i < ctts->total_entries; i++) {
        ctts->table[i].sample_count = quicktime_read_int32(file);
        ctts->table[i].sample_offset = quicktime_read_int32(file);
    }

    return 0;
}

int quicktime_write_ctts(quicktime_t *file, quicktime_ctts_t *ctts)
{
    int i;
    quicktime_atom_t atom;

    if (ctts->total_entries == 1 && ctts->table[0].sample_offset == 0) {
        return -1;
    }

    quicktime_atom_write_header(file, &atom, "ctts");

    quicktime_write_char(file, ctts->version);
    quicktime_write_int24(file, ctts->flags);
    quicktime_write_int32(file, ctts->total_entries);
    for(i = 0; i < ctts->total_entries; i++) {
        quicktime_write_int32(file, ctts->table[i].sample_count);
        quicktime_write_int32(file, ctts->table[i].sample_offset);
    }
    quicktime_atom_write_footer(file, &atom);

    return 0;
}

int quicktime_update_ctts(quicktime_ctts_t *ctts, long sample_offset)
{
    if (sample_offset == ctts->table[ctts->total_entries-1].sample_offset) {
        ctts->table[ctts->total_entries-1].sample_count++;
    } else {
        /* need a new entry in the table */

        /* allocate more entries if necessary */
        if (ctts->total_entries >= ctts->entries_allocated) {
            ctts->entries_allocated *= 2;
            ctts->table = (quicktime_ctts_table_t*)realloc(ctts->table,
                sizeof(quicktime_ctts_table_t) * ctts->entries_allocated);
        }

        ctts->table[ctts->total_entries].sample_count = 1;
        ctts->table[ctts->total_entries].sample_offset = sample_offset;
        ctts->total_entries++;
    }

    return 0;
}
