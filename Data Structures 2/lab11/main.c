#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000
#define NUMBER_OF_RECORDS_AT_MOVIES_1 600
#define NUMBER_OF_RECORDS_AT_MOVIES_2 600

typedef struct {
	int film_id;
	char title[255];
	char description[1023];
	unsigned int release_year;
	char rental_duration;
	float rental_rate;
	unsigned char length;
	float replacement_cost;
	char rating[10];
	char last_update[30];
} RECORD_t, *RECORD;

void print_movie(RECORD_t rec) {
	printf("ID: %d\n", rec.film_id);
	printf("TITLE: %s\n", rec.title);
	printf("DESCRIPTION: %s\n", rec.description);
	printf("RELEASE YEAR: %d\n", rec.release_year);
	printf("RENTAL DURATION: %d\n", rec.rental_duration);
	printf("RENTAL RATE: %f\n", rec.rental_rate);
	printf("REPLACEMENT COST: %f\n", rec.replacement_cost);
	printf("RATING: %s\n", rec.rating);
	printf("LAST UPDATE: %s\n", rec.last_update);
	printf("\n");
}

void print_all_movies(RECORD rec, int n) {
	int num = 0;
	int i;
	for (i = 0; i < n; i++) {
		print_movie(rec[i]);
		num++;
	}
	printf("%d", num);
}



int main() {
	FILE *fp;
    RECORD_t movies1_records;	

    if ((fp = fopen ("sorted.bin", "rb")) == NULL) {
         printf("Cannot open the sorted.bin file.\n");
         exit(1);
    }

    int ID = 700;

	
	fseek(fp, sizeof(RECORD_t)*(ID -1), SEEK_CUR);
	fread(&movies1_records,sizeof(RECORD_t),1,fp);
    print_movie(movies1_records);

    fclose(fp);
	return 0;
}
