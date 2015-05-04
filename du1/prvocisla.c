// prvocisla.c
// Řešení IJC-DU1, příklad b), 25.3.2015
// Autor: Radovan Sroka, FIT
// Přeloženo: gcc 4.9.2 20150204

#include <stdio.h>

#include "bit_array.h"

#define N 201000000 //hladam prvocisla do N


int main(){
	BA_create(x, N);
	Eratosthenes(x);
	PrintPrimes(x);

	return 0;
}
