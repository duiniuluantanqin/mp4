
#include "quicktime.h"


int quicktime_trpy_init(quicktime_trpy_t *trpy)
{
	trpy->numBytes = 0;
}

int quicktime_trpy_delete(quicktime_trpy_t *trpy)
{
}

int quicktime_trpy_dump(quicktime_trpy_t *trpy)
{
	printf("    total RTP bytes\n");
	printf("     numBytes "U64"\n", trpy->numBytes);
}

int quicktime_read_trpy(quicktime_t *file, quicktime_trpy_t *trpy)
{
	trpy->numBytes = quicktime_read_int64(file);
}

int quicktime_write_trpy(quicktime_t *file, quicktime_trpy_t *trpy)
{
	quicktime_atom_t atom;

	quicktime_atom_write_header(file, &atom, "trpy");

	quicktime_write_int64(file, trpy->numBytes);
	
	quicktime_atom_write_footer(file, &atom);
}

