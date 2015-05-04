// steg-decode.c
// Řešení IJC-DU1, příklad b), 25.3.2015
// Autor: Radovan Sroka, FIT
// Přeloženo: gcc 4.9.2 20150204

#include <stdio.h>
#include <ctype.h>

#include "ppm.h"
#include "bit_array.h"


#define MAX_SIZE_PPM  75000000 // 5000 * 5000 * 3

int main(int argc, char const *argv[]){

	if (argc != 2){
		FatalError("Bad parameter, PPM file is missing, expected only one parameter\n");
	}

	struct ppm * image;

	if((image = ppm_read(argv[1])) == NULL)return 1;	
	
	BA_create(BitArray, MAX_SIZE_PPM);
	Eratosthenes(BitArray);

	Longl prime_counter = 0;
	
	for (Longl i = 2 ; i < image->xsize * image->ysize * 3 ; i++){
		if (!BA_get_bit(BitArray, i)){
			BA_set_bit(BitArray, prime_counter, DU1_GET_BIT_(image->data[i], 0));
			prime_counter++;
		}
	}

	char * decoded_message = (char *)BitArray;

	int zero_flag = 1;

	for (Longl i = 0; i < prime_counter / 8 ; i++){

		if (decoded_message[i] == 0){
			zero_flag = 0;
			break;
		}

		if (!isprint(decoded_message[i])){
			ppm_free(image);
			FatalError("Message is not printable\n");
		}
	}
	ppm_free(image);
	if(zero_flag)
		FatalError("Message do not end with zero");

	printf("%s\n", decoded_message);
	return 0;
}