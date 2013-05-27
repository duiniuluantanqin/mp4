
#include "funcprotos.h"
#include "quicktime.h"


int quicktime_hinf_init(quicktime_hinf_t *hinf)
{
    quicktime_trpy_init(&(hinf->trpy));
    quicktime_nump_init(&(hinf->nump));
    quicktime_tpyl_init(&(hinf->tpyl));
    quicktime_maxr_init(&(hinf->maxr));
    quicktime_dmed_init(&(hinf->dmed));
    quicktime_dimm_init(&(hinf->dimm));
    quicktime_drep_init(&(hinf->drep));
    quicktime_tmin_init(&(hinf->tmin));
    quicktime_tmax_init(&(hinf->tmax));
    quicktime_pmax_init(&(hinf->pmax));
    quicktime_dmax_init(&(hinf->dmax));
    quicktime_payt_init(&(hinf->payt));

    return 0;
}

int quicktime_hinf_delete(quicktime_hinf_t *hinf)
{
    quicktime_trpy_delete(&(hinf->trpy));
    quicktime_nump_delete(&(hinf->nump));
    quicktime_tpyl_delete(&(hinf->tpyl));
    quicktime_maxr_delete(&(hinf->maxr));
    quicktime_dmed_delete(&(hinf->dmed));
    quicktime_dimm_delete(&(hinf->dimm));
    quicktime_drep_delete(&(hinf->drep));
    quicktime_tmin_delete(&(hinf->tmin));
    quicktime_tmax_delete(&(hinf->tmax));
    quicktime_pmax_delete(&(hinf->pmax));
    quicktime_dmax_delete(&(hinf->dmax));
    quicktime_payt_delete(&(hinf->payt));

    return 0;
}

int quicktime_hinf_dump(quicktime_hinf_t *hinf)
{
    printf("   hinf\n");
    quicktime_trpy_dump(&(hinf->trpy));
    quicktime_nump_dump(&(hinf->nump));
    quicktime_tpyl_dump(&(hinf->tpyl));
    quicktime_maxr_dump(&(hinf->maxr));
    quicktime_dmed_dump(&(hinf->dmed));
    quicktime_dimm_dump(&(hinf->dimm));
    quicktime_drep_dump(&(hinf->drep));
    quicktime_tmin_dump(&(hinf->tmin));
    quicktime_tmax_dump(&(hinf->tmax));
    quicktime_pmax_dump(&(hinf->pmax));
    quicktime_dmax_dump(&(hinf->dmax));
    quicktime_payt_dump(&(hinf->payt));

    return 0;
}

int quicktime_read_hinf(quicktime_t *file, quicktime_hinf_t *hinf, quicktime_atom_t *parent_atom)
{
    quicktime_atom_t leaf_atom;

    do {
        quicktime_atom_read_header(file, &leaf_atom);

        if (quicktime_atom_is(&leaf_atom, "trpy")) {
            quicktime_read_trpy(file, &(hinf->trpy));
        } else if (quicktime_atom_is(&leaf_atom, "nump")) {
            quicktime_read_nump(file, &(hinf->nump));
        } else if (quicktime_atom_is(&leaf_atom, "tpyl")) {
            quicktime_read_tpyl(file, &(hinf->tpyl));
        } else if (quicktime_atom_is(&leaf_atom, "maxr")) {
            quicktime_read_maxr(file, &(hinf->maxr));
        } else if (quicktime_atom_is(&leaf_atom, "dmed")) {
            quicktime_read_dmed(file, &(hinf->dmed));
        } else if (quicktime_atom_is(&leaf_atom, "dimm")) {
            quicktime_read_dimm(file, &(hinf->dimm));
        } else if (quicktime_atom_is(&leaf_atom, "drep")) {
            quicktime_read_drep(file, &(hinf->drep));
        } else if (quicktime_atom_is(&leaf_atom, "tmin")) {
            quicktime_read_tmin(file, &(hinf->tmin));
        } else if (quicktime_atom_is(&leaf_atom, "tmax")) {
            quicktime_read_tmax(file, &(hinf->tmax));
        } else if (quicktime_atom_is(&leaf_atom, "pmax")) {
            quicktime_read_pmax(file, &(hinf->pmax));
        } else if (quicktime_atom_is(&leaf_atom, "dmax")) {
            quicktime_read_dmax(file, &(hinf->dmax));
        } else if (quicktime_atom_is(&leaf_atom, "payt")) {
            quicktime_read_payt(file, &(hinf->payt), &leaf_atom);
        } else {
            quicktime_atom_skip(file, &leaf_atom);
        }
    } while (quicktime_position(file) < parent_atom->end);

    return 0;
}

int quicktime_write_hinf(quicktime_t *file, quicktime_hinf_t *hinf)
{
    quicktime_atom_t atom;

    quicktime_atom_write_header(file, &atom, "hinf");

    quicktime_write_trpy(file, &(hinf->trpy));
    quicktime_write_nump(file, &(hinf->nump));
    quicktime_write_tpyl(file, &(hinf->tpyl));
    quicktime_write_maxr(file, &(hinf->maxr));
    quicktime_write_dmed(file, &(hinf->dmed));
    quicktime_write_dimm(file, &(hinf->dimm));
    quicktime_write_drep(file, &(hinf->drep));
    quicktime_write_tmin(file, &(hinf->tmin));
    quicktime_write_tmax(file, &(hinf->tmax));
    quicktime_write_pmax(file, &(hinf->pmax));
    quicktime_write_dmax(file, &(hinf->dmax));
    quicktime_write_payt(file, &(hinf->payt));

    quicktime_atom_write_footer(file, &atom);

    return 0;
}

