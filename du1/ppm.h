// ppm.h
// Řešení IJC-DU1, příklad b), 25.3.2015
// Autor: Radovan Sroka, FIT
// Přeloženo: gcc 4.9.2 20150204

#ifndef PPM_H
#define PPM_H


struct ppm {
    unsigned xsize;
    unsigned ysize;
    char data[5000 * 5000 * 3];
 };

struct ppm * ppm_read(const char * filename);

int ppm_write(struct ppm *p, const char * filename);

void ppm_free(struct ppm * image);

#endif