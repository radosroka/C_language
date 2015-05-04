// error.c
// Řešení IJC-DU1, příklad b), 25.3.2015
// Autor: Radovan Sroka, FIT
// Přeloženo: gcc 4.9.2 20150204


#include "error.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

const int max_lenght_of_message = 500;

void FatalError(const char *fmt, ...){	

	va_list arguments;
	va_start (arguments, fmt);


	char error[500] = "CHYBA: ";

	strncat(error, fmt, max_lenght_of_message - strlen(error));

	vfprintf(stderr, error , arguments);

	va_end(arguments);
	exit(1);
}

int FatalError_i(const char *fmt, ...){
	

	va_list arguments;
	va_start (arguments, fmt);


	FatalError(fmt, arguments);

	va_end(arguments);
	return 1;
}

void Warning(const char *fmt, ...){

	va_list arguments;
	va_start (arguments, fmt);


	char error[500] = "CHYBA: ";

	strncat(error, fmt, max_lenght_of_message - strlen(error));

	vfprintf(stderr, error , arguments);

	va_end(arguments);

}