// tail.c
// Řešení IJC-DU2, příklad a), 26.4.2015
// Autor: Radovan Sroka, FIT
// Přeloženo: gcc 4.8.2


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
	N, PLUS_N
};

typedef struct{
	FILE * input;
	long long n;
	int mode;
}Params;

Params params;
FILE * file = NULL;

void init(int argc, char const *argv[]){
		
	char * endptr = NULL;

	if (argc == 1){
		params.input = stdin;
		params.n = 10;
		params.mode = N;
	}
		
	else if (argc == 2){
		
		params.n = 10;
		params.mode = N;

		if ((params.input = fopen(argv[1], "r")) == NULL){
			perror(argv[1]);
			exit(1);
		}
		else
			file = params.input;
	}

	else if (argc == 3){
		
		if (strcmp(argv[1], "-n") != 0){
			fprintf(stderr, "%s\n", "Bad first parameter, must be -n");		
			exit(1);	
		}
		else {
			params.input = stdin;

			if (argv[2][0] == '+')
				params.mode = PLUS_N;
			else
				params.mode = N;
			
			params.n = strtoll(argv[2], &endptr, 10);
			if (*endptr != '\0'){
				fprintf(stderr, "%s\n", "Parameter parse failed - conversion");
				exit(1);
			}
		}
	}

	else if (argc == 4){

		if ((params.input = fopen(argv[3], "r")) == NULL){
			perror(argv[3]);
			exit(1);
		}
		else
			file = params.input;

		if (strcmp(argv[1], "-n") != 0){
			fprintf(stderr, "%s\n", "Bad first parameter, must be -n");	
			fclose(params.input);	
			exit(1);	
		}

		if (argv[2][0] == '+')
			params.mode = PLUS_N;
		else
			params.mode = N;
			
		params.n = strtoll(argv[2], &endptr, 10);
		if (*endptr != '\0'){
			fprintf(stderr, "%s\n", "Parameter parse failed - conversion");
			fclose(params.input);	
			exit(1);
		}
	}
	else {
		fprintf(stderr, "%s\n", "Bad parameters");
		exit(1);
	}
}

void deinit(){
	if (file != NULL)fclose(file);
}

#define BUFFER_MAX 510

int plus_mode(){
	char * buffer;
	char flag = 0;

	if ((buffer = (char *)malloc(BUFFER_MAX + 1)) == NULL){
		fprintf(stderr, "%s\n", "Alloc of buffer failed");
		return 1;
	}

	for (long long line = 1; fgets(buffer, BUFFER_MAX + 1, params.input) != NULL ; line++){

		if (line >= params.n)
			printf("%s", buffer);

		for (int i = 0; strlen(buffer) == BUFFER_MAX && buffer[BUFFER_MAX] != '\n' ; i++){
			if (i == 0){
				if (line >= params.n){
					printf("\n");
					if (flag == 0)flag = 1;
				}
			}
			if (fgets(buffer, BUFFER_MAX + 1, params.input) == NULL)
				break;
		}
	}

	if (flag)fprintf(stderr, "%s\n", "Warning: Too long line");

	free(buffer);
	return 0;
}


int normal_mode(){
	char **buffer;
	int * flags;
	long long line;

	if ((buffer = (char **)malloc(sizeof(char *) * params.n)) == NULL){
		fprintf(stderr, "%s\n", "Alloc of buffer failed");
		return 1;
	}

	if ((flags = (int *)calloc(sizeof(int), params.n)) == NULL){
		fprintf(stderr, "%s\n", "Alloc of buffer failed");
		free(buffer);
		return 1;
	}

	for (long long i = 0; i < params.n; i++){
		if ((buffer[i] = (char *)malloc(BUFFER_MAX)) == NULL){
		
		for (long long j = 0; j < i; j++){
			free(buffer[j]);
		}
		free(buffer);
		free(flags);
		fprintf(stderr, "%s\n", "Alloc of buffer failed");
		return 1;
		}
	}


	for (line = 0; fgets(buffer[line % params.n], BUFFER_MAX, params.input) != NULL ; line++){

		if ( strlen(buffer[line % params.n]) == BUFFER_MAX-1 && buffer[line % params.n][BUFFER_MAX-1] != '\n'){
			buffer[line % params.n][BUFFER_MAX-1] = '\n';
			flags[line % params.n] = 1;
			int c;
			while( (c = fgetc(params.input)) != '\n' && c != EOF){}		
		}
		else
			flags[line % params.n] = 0;
	}

	long long index = line % params.n;
	do {
		printf("%s", buffer[index]);
		if (index == params.n - 1)index = -1;
		index++;
	}while(index != line % params.n);

	int flag = 0;

	for (long long i = 0 ; i < params.n ; i++)
		if (flags[i]){
			flag = 1;
			break;
		}

	if (flag)fprintf(stderr, "%s\n", "Warning: Too long line");


	for (long long j = 0; j < params.n; j++){
		free(buffer[j]);
	}
	free(buffer);
	free(flags);

	return 0;
}


int main(int argc, char const *argv[])
{
	init(argc, argv);

	if (params.n < 0){
		fprintf(stderr, "%s\n", "Number must be positive or zero");
		exit(1);
	}

	if (params.n > 10000000){
		fprintf(stderr, "%s\n", "Too many lines");
		exit(1);
	}

	if (params.n == 0){
		deinit();
		return 0;
	}

	if (params.mode == 1){
		if (plus_mode()){
			deinit();
			exit(1);
		}
	}
	else if (params.mode == 0){ 
		if (normal_mode()){
			deinit();
			exit(1);
		}
	}

	deinit();
	return 0;
}