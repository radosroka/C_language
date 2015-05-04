// bit_array.h
// Řešení IJC-DU1, příklad a), 25.3.2015
// Autor: Radovan Sroka, FIT
// Přeloženo: gcc 4.9.2 20150204


#ifndef BIT_ARRAY_H
#define BIT_ARRAY_H


#include <stdio.h>
#include "error.h"




typedef  unsigned long int BitArray_t;
#define Longl unsigned long long int

void Eratosthenes(BitArray_t b_array[]);
void PrintPrimes(BitArray_t b_array[]);


#define DU1_GET_BIT_(p,i)(((p) >> (i)) &1)
#define DU1_SET_BIT_(p,i,b) p = ((b) ? (p)|((Longl)1 << (i)) : (p) & (~((Longl)1 << (i)) ))

#define BA_create(name, size)BitArray_t array_##name[(size/8) / sizeof(BitArray_t) + ((size/8) % sizeof(BitArray_t) > 0 ? 2 : 1)] = {0}; \
							 BitArray_t * name = array_##name; name++; name[-1] = size



#ifndef USE_INLINE

#define BA_size(name)name[-1]

#define BA_set_bit(name, index, bit) if(index < 0 || index >= BA_size(name))FatalError("I cannot set bit on index %lld in %s, doesn't exist!\n", index, #name); \
									 else DU1_SET_BIT_(name[(index/(sizeof(BitArray_t)*8))], (index%(sizeof(BitArray_t)*8)), bit)

#define BA_get_bit(name, index) ((index < 0 || index >= BA_size(name)) ? \
									 	FatalError_i("I cannot get bit from index %lld in %s, doesn't exist!\n", index, #name) : \
									  	DU1_GET_BIT_(name[(index/(sizeof(BitArray_t)*8))], (index%(sizeof(BitArray_t)*8)) ))


#else

static inline Longl BA_size(BitArray_t name[]){
	return name[-1];
}

static inline void BA_set_bit(BitArray_t name[], Longl index, int bit){
	
	if(index < 0 || index >= BA_size(name))
		FatalError("I cannot set bit on index %lld, doesn't exist!\n", index);
	else 
		DU1_SET_BIT_(name[(index/(sizeof(BitArray_t)*8))], (index%(sizeof(BitArray_t)*8)), bit);
}

static inline Longl BA_get_bit(BitArray_t name[], int index){
	
	if(index < 0 || index >= BA_size(name)){
		FatalError("I cannot get bit from index %lld, doesn't exist!\n", index);
		return -1;
	}
	else 
		return DU1_GET_BIT_(name[(index/(sizeof(BitArray_t)*8))], (index%(sizeof(BitArray_t)*8)) );
}

#endif







#endif