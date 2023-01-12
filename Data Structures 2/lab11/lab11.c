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




void xsort(FILE *fp, int size) {
	//TODO
	//Write the result in "sorted.bin" in binary.
    FILE *movies_test = fopen("sorted2.bin", "rb+"); //// yazmak için
    RECORD movies1_records = (RECORD)malloc(sizeof(RECORD_t) * MAX);
    RECORD movies2_records = (RECORD)malloc(sizeof(RECORD_t) * MAX);
	int i, j;
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++)
		{   
            fseek(fp, sizeof(RECORD_t)*(j), SEEK_SET); //array[j]
	        fread(movies1_records,sizeof(RECORD_t),1,fp);
	        fseek(fp, sizeof(RECORD_t)*(j+1), SEEK_SET); //array[j]
	        fread(movies1_records,sizeof(RECORD_t),1,fp);

			if (movies1_records->film_id < movies2_records->film_id)
			{   
                fseek(fp, (j)*sizeof(RECORD_t), SEEK_SET);
                fwrite(movies2_records,sizeof(RECORD_t), 1, movies_test);
                fseek(fp, (j+1)*sizeof(RECORD_t), SEEK_SET);
                fwrite(movies1_records,sizeof(RECORD_t), 1, movies_test);
	        
				
			
			}
		}
	}
    fclose(movies_test);
    free(movies1_records);
    free(movies2_records);
}

int binarySearch(FILE *file, int l, int r, int x){
    RECORD rec = (RECORD)malloc(sizeof(RECORD_t) * MAX);

    if(r>= l) {
        int mid = l+(r-l)/2;
        
        fseek(file,(mid)*sizeof(RECORD_t), SEEK_SET);
        fread(rec,sizeof(RECORD_t),1,file);
        if(rec ->film_id == x){
            return mid;
        }
        if(rec->film_id > x){
            return binarySearch(file,l,mid-1,x);

        }

        return binarySearch(file, mid+1,r,x);
    }

    return -1;
}



int main() {
	FILE *fp;
    RECORD_t movies1_records;	

    /*if ((fp = fopen ("sorted.bin", "rb+")) == NULL) {
         printf("Cannot open the sorted.bin file.\n");
         exit(1);
    }
*/
    int ID = 100;
    xsort(fp, MAX);

    binarySearch(fp, 0,MAX-1, ID);

    FILE *moviesread_file = fopen("data.bin", "rb");
	if (moviesread_file == NULL) {
		printf("Cannot open the sorted.bin file.\n");
		exit(2);
	}

    RECORD moviesread_records = (RECORD)malloc(sizeof(RECORD_t) * MAX);
	fread(moviesread_records, sizeof(RECORD_t) * MAX, 1, moviesread_file);
	fclose(moviesread_file);

	//print_all_movies(moviesread_records, MAX);
	
	//fseek(fp, sizeof(RECORD_t)*ID, SEEK_CUR); //go to id record + next record
	//fseek(fp, -(long)sizeof(RECORD_t), SEEK_CUR); // go to id record

	//fread(&movies1_records,sizeof(RECORD_t),1,fp);
    //print_movie(movies1_records);
    free(moviesread_records);
    fclose(fp);
	return 0;
}
