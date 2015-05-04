// wordcount.c
// Řešení IJC-DU2, příklad b), 26.4.2015
// Autor: Radovan Sroka, FIT
// Přeloženo: gcc 4.8.2


#include "htable.h"
#include "io.h"

/*
*	velkost hash tabulky je nastavena na 100000 zaznamov co pre 64bit pointre zaberie iba 800kB
*	pri 32b pontroch iba 400kB co vobec nieje vela a je to velmi rychle aj do 1000000 zaznamov 
*	odskusane experimentom
*/

#define HTABLE_SIZE 100000
#define MAX_LENGTH 128

void print(htab_listitem * item){
	printf("%s\t%lld\n", item->key, item->data);
}

int main()
{
	setbuf(stdin, NULL);
	htab_t * tab = NULL;
	htab_listitem * item = NULL;
	char buffer[MAX_LENGTH];


	if ((tab = htab_init(HTABLE_SIZE)) == NULL)return 1;

	int a = 0;
	while((a = fgetw(buffer, MAX_LENGTH, stdin)) > 0){
		if ((item = htab_lookup(tab, buffer)) == NULL){
			goto error;	
		}
		else 
			item->data++;
	}


	htab_foreach(tab, print);

	//htab_statistics(tab);

	htab_free(tab);
	return 0;

	error:	htab_free(tab);
	return 1;
}