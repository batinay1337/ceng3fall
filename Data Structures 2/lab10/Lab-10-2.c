#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 1000

typedef struct {
	int film_id;
	char title[255];
	char description[1023];
	unsigned int release_year;
	int rental_duration;
	float rental_rate;
	unsigned char length;
	float replacement_cost;
	char rating[10];
	char last_update[30];
} RECORD_t, *RECORD;

void swap(void *a, void *b) {
	//TODO

	RECORD_t temp = *((RECORD)a);
	//temp = a;
	*((RECORD)a) = *((RECORD)b);
	*((RECORD)b) = temp;
}

int cmp_id_des(void *a, void *b) { // a b den küçükse 1
	//TODO

	if (((RECORD)a)->film_id > (((RECORD)b)->film_id))
	{
		return 1;
	}
	else {
		return 0;
	}
	
	
}

int cmp_length_asc(void *a, void *b) { //a b den büyükse 1
	//TODO
	if (((RECORD)a)->length > (((RECORD)b)->length))
	{
		return 1;
	}
	else {
		return 0;
	}
}

int cmp_description_dec(void *a, void *b) {//a den b den küçükse 1, değilse 0
	//TODO
	if (strcmp(((RECORD)a)->description, ((RECORD)b)->description) > 0)
	{
		return 1;
	}
	else {
		return 0;
	}
}
void printAll(RECORD array, int size) {
	//TODO

	int i;
	for (i = 0; i < size; i++)
	{
		printf("id: %d\n", array[i].film_id);
		printf("title: %s\n", array[i].title);
		printf("description: %s\n", array[i].description);
		printf("release_year: %d\n", array[i].release_year);
		printf("rental_duration: %d\n", array[i].rental_duration);
		printf("rental_rate: %f\n", array[i].rental_rate);
		printf("length: %d\n", array[i].length);
		printf("replacement_cost: %f\n", array[i].replacement_cost);
		printf("rating: %s\n", array[i].rating);
		printf("last_update: %s\n", array[i].last_update);
		
	}
	
}

void xsort(RECORD array, int size, int (*compare)(void *a, void *b)) {
	//TODO
	//Write the result in "sorted.bin" in binary.

	int i, j;
	for (i = 0; i < size-1; i++) {
		for (j = 0; j < size-i-1; j++)
		{
			if (compare(&array[j], &array[j+1]) == 1 )
			{
				swap(&array[j], &array[j+1]);
			
			}
			
		}
		
	}
	
	

	
	FILE *movies_test = fopen("sorted.bin", "wb"); //// yazmak için
	fwrite(array,sizeof(RECORD_t)*MAX, 1, movies_test);

	

	fclose(movies_test);
	
	

}



int main() {
	//TODO
	//Read "data.bin" in binary.
	FILE *movies_file = fopen("data.bin", "rb");
	if (movies_file == NULL) {
		printf("Cannot open the data.bin file.\n");
		exit(2);
	}


	RECORD movies_records = (RECORD)malloc(sizeof(RECORD_t) * MAX);
	fread(movies_records, sizeof(RECORD_t) * MAX, 1, movies_file);
	fclose(movies_file);



	xsort(movies_records, MAX, cmp_description_dec);
	xsort(movies_records, MAX, cmp_length_asc); 
	xsort(movies_records, MAX, cmp_id_des);

	FILE *moviesread_file = fopen("sorted.bin", "rb");
	if (moviesread_file == NULL) {
		printf("Cannot open the sorted.bin file.\n");
		exit(2);
	}

	RECORD moviesread_records = (RECORD)malloc(sizeof(RECORD_t) * MAX);
	fread(moviesread_records, sizeof(RECORD_t) * MAX, 1, moviesread_file);
	fclose(moviesread_file);

	printAll(moviesread_records, MAX);
	printf("DONE!");
	
	free(movies_records);
	return 0;

	
}
