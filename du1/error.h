// error.h
// Řešení IJC-DU1, příklad b), 25.3.2015
// Autor: Radovan Sroka, FIT
// Přeloženo: gcc 4.9.2 20150204

#ifndef ERROR_H
#define ERROR_H


void Warning(const char *fmt, ...);

void FatalError(const char *fmt, ...);

int FatalError_i(const char *fmt, ...);






#endif