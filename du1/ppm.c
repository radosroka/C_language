// ppm.c
// Řešení IJC-DU1, příklad b), 25.3.2015
// Autor: Radovan Sroka, FIT
// Přeloženo: gcc 4.9.2 20150204

#include <stdio.h>
#include <stdlib.h>

#include "error.h"
#include "ppm.h"


struct ppm * ppm_alocate(int width, int height){

	struct ppm * image;
	
	if ((image = (struct ppm *)malloc(sizeof(struct ppm) + (3 * width * height))) == NULL)return NULL;	

	image->xsize = width;
	image->ysize = height;
	return image;
}


void ppm_free(struct ppm * image){
	free(image);
}




struct ppm * ppm_read(const char * filename){

	struct ppm * image = NULL;
	FILE * file = NULL;

	int width = 0, height = 0;
	int ppm_max = 0;


	if ((file = fopen(filename, "r")) == NULL)
		FatalError("Cannot open file %s\n", filename);

	char type[2] = {'P', '6'};
	char buffer[10];

	for(int i = 0 ; i < 3 ; i++ ){
		if (fgets(buffer, 10, file) == NULL){
			fclose(file);
			Warning("Unexpected EOF, bad file format\n");
			return NULL;
		}

		else {
			switch (i){
				case 0:
					if(type[0] != buffer[0] || type[1] != buffer[1]){
						fclose(file);
						Warning("Bad file format on line %d\n", i);
						return NULL;
					}
					break;

				case 1:
					if (sscanf(buffer, "%d %d", &width, &height) != 2){
						fclose(file);
						Warning("Bad file format on line %d\n", i);
						return NULL;
					}
					break;

				case 2:
					if (sscanf(buffer, "%d", &ppm_max) != 1){
						fclose(file);
						Warning("Bad file format on line %d\n", i);
						return NULL;
					}
					break;
			}
		}
	}

	if (width > 5000 || height > 5000){
		fclose(file);
		FatalError("PPM file is too large, xsize = %d, ysize = %d", width, height);
	}

	if ((image = ppm_alocate(width, height)) == NULL){
		fclose(file);
		FatalError("Cannot alocate memory for ppm");
	}

	int c = 0;
	int counter = 0;
	while((c = fgetc(file)) != EOF){
		if (counter >= (3 * image->xsize * image->ysize)){
			ppm_free(image);
			fclose(file);
			Warning("Mismatch expected data and real data\n");
			return NULL;
		}

		image->data[counter] = (char)c;
		counter++;
	}

	fclose(file);

	return image;
}


int ppm_write(struct ppm *p, const char * filename){

	if (p == NULL || filename == NULL){
		Warning("Bad ppm_write parameter NULL\n");
		return -1;
	}

	FILE * file = NULL;
	if ((file = fopen(filename, "w")) == NULL){
		Warning("Cannot open file %s for write\n", filename);
		return -1;
	}


	fprintf(file, "P6\n%d %d\n255\n", p->xsize, p->ysize);



	for(unsigned i = 0 ; i < p->xsize * p->ysize * 3 ; i++){
		if (fputc(p->data[i], file) == EOF){
			fclose(file);
			Warning("Write error, file %s, char %c, index, %d", filename, p->data[i], i);
			return -1;
		}
	}


	fclose(file);
	return 0;
}