
#include "quicktime.h"
#include "funcprotos.h"


int quicktime_avcc_init(quicktime_avcc_t *avcc)
{
    avcc->data_size = 0;
    memset(avcc->data, '0', 2048);
    return 0;
}

void quicktime_get_avcc_header(quicktime_avcc_t *avcc,
                               unsigned char *data, 
                               int *size)
{
    if (avcc->data_size == 0) {
        data = NULL;
        *size = 0;
    } else {
        memcpy(data, avcc->data, avcc->data_size);
        *size = avcc->data_size;
    }
}
// Set esds header to a copy of the argument
void quicktime_set_avcc_header(quicktime_avcc_t *avcc,
                               unsigned char *data, 
                               int size)
{
    memset(avcc->data, '0', 2048);
    memcpy(avcc->data, data, size);
    avcc->data_size = size;
}

void quicktime_write_avcc(quicktime_t *file, 
                          quicktime_avcc_t *avcc)
{
    quicktime_atom_t atom;
    quicktime_atom_write_header(file, &atom, "avcC");
    quicktime_write_data(file, avcc->data, avcc->data_size);
    quicktime_atom_write_footer(file, &atom);
}



int quicktime_read_avcc(quicktime_t *file, 
                        quicktime_atom_t *parent_atom,
                        quicktime_avcc_t *avcc)
{
    avcc->data_size = parent_atom->size - 8;
    quicktime_read_data(file, 
        avcc->data, 
        avcc->data_size);
    quicktime_atom_skip(file, parent_atom);
    return 0;
}

void quicktime_avcc_dump(quicktime_avcc_t *avcc)
{
    int i;
    printf("       h264 description\n");
    printf("        data_size=0x%x\n", avcc->data_size);
    printf("        data=");
    for(i = 0; i < avcc->data_size; i++)
    {
        printf("0x%02x ", (unsigned char)avcc->data[i]);
    }
    printf("\n");
}