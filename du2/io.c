// io.c
// Řešení IJC-DU2, příklad b), 26.4.2015
// Autor: Radovan Sroka, FIT
// Přeloženo: gcc 4.8.2

#include "io.h"

#define MAX_LENGTH 128

int warning_flag = 0;

int fgetw(char *s, int max, FILE *f){

	if (s == NULL){
		fprintf(stderr, "%s\n", "fgetw: string parameter is NULL");
		return -2;
	}
	if (f == NULL){
		fprintf(stderr, "%s\n", "fgetw: file parameter is NULL");
		return -3;
	}
	if (max < 1 || max > MAX_LENGTH){
		fprintf(stderr, "%s\n", "fgetw: max parameter is out of range 1-127");
		return -4;
	}

	int c;
	while( (c = fgetc(f)) != EOF && isspace(c)){}

	if (c == EOF)return EOF;
	else s[0] = c;
	
	int len;
	for (len = 1; (c = fgetc(f)) != EOF && !isspace(c) ; len++){
		if (len == max - 1){
			if (!warning_flag){
				fprintf(stderr, "%s\n", "Warning: Too long word");
				warning_flag = 1;
			}
			break;
		}
		s[len] = c;
	}

	s[len] = '\0';

	if (!isspace(c))
		while( (c = fgetc(f)) != EOF && !isspace(c)){}

	return len;
}