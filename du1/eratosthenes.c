// erastothenes.c
// Řešení IJC-DU1, příklad a), 25.3.2015
// Autor: Radovan Sroka, FIT
// Přeloženo: gcc 4.9.2 20150204

#include "bit_array.h"
#include <math.h>


void Eratosthenes(BitArray_t b_array[]){

	

	BA_set_bit(b_array, 0, 1);
	BA_set_bit(b_array, 1, 1);
	
	for(Longl i = 2 ; i <= (Longl)sqrt(BA_size(b_array)) ; i++){
		
		if(BA_get_bit(b_array, i)) continue;

		else 
			for (Longl k = 2*i; k < BA_size(b_array) ; k += i){
				BA_set_bit(b_array, k, 1);			
			}
	}
}

void PrintPrimes(BitArray_t b_array[]){

	int counter = 0;

	for(Longl i = BA_size(b_array) - 1 ; (i >= 2) && (counter < 9) ; i--){

		if(!BA_get_bit(b_array, i)){
			printf("%lld\n", i);
			counter++;
		}

	}
}

