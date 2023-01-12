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
}

int cmp_id_des(void *a, void *b) {
	//TODO
	return 0;
}

int cmp_length_asc(void *a, void *b) {
	//TODO
	return 0;
}

int cmp_description_dec(void *a, void *b) {
	//TODO
	return 0;
}

void xsort(void **array, int size, int (*compare)(void *a, void *b)) {
	//TODO
	//Write the result in "sorted.bin" in binary.
}

void printAll(void **array, int size) {
	//TODO
}

int main() {
	//TODO
	//Read "data.bin" in binary.
	return 0;
}
