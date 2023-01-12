#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define min
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


void bubble(FILE* file)
{
    int i,j;
    RECORD rec1 = (RECORD)malloc(sizeof(RECORD_t));
    RECORD rec2 = (RECORD)malloc(sizeof(RECORD_t));
  int records = sizeof(RECORD_t);

  for(i=0;i<MAX;i++)
  {
     for(j=0;j<MAX-i-1;j++)
     {
        fseek(file,(j)*records,SEEK_SET);
        fread(rec1,sizeof(RECORD_t),1,file);
        fread(rec2,sizeof(RECORD_t),1,file);
        if(rec1->film_id>rec2->film_id)
        {
         fseek(file,(j)*records,SEEK_SET);
         fwrite(rec2, sizeof(RECORD_t), 1, file);
         fwrite(rec1,records,1,file);
        }
     }
  }

}






RECORD binarySearch(FILE* file, int, int, int);


RECORD exponentialSearch(FILE* file, int n, int x)
{
   
    int i=0;
     RECORD rec1 = (RECORD)malloc(sizeof(RECORD_t)*MAX);
    fseek(file,(i)*sizeof(RECORD_t),SEEK_SET);
    fread(rec1,sizeof(RECORD_t),1,file);
    if(rec1->film_id == x)
    {
        return rec1;
    }

    
    int j= 1;
    fseek(file,(j)*sizeof(RECORD_t),SEEK_SET);
    fread(rec1,sizeof(RECORD_t),1,file);
    while (j < n && rec1->film_id <= x)
    {
         j = j*2;
        fseek(file,(j)*sizeof(RECORD_t),SEEK_SET);
        fread(rec1,sizeof(RECORD_t),1,file);

    }
    
    return binarySearch(file, j/2, min(j, n-1), x);
}


RECORD binarySearch(FILE* file, int l, int r, int x)
{
    RECORD rec = (RECORD)malloc(sizeof(RECORD_t));
    if (r >= l)
    {
        int mid = l + (r - l)/2;

        
        fseek(file,(mid)*sizeof(RECORD_t),SEEK_SET);
        fread(rec,sizeof(RECORD_t),1,file);
        if (rec->film_id == x)
            return rec;


        if (rec->film_id > x)
            return binarySearch(file, l, mid-1, x);

        // Else the element can only be present
        // in right subarray
        return binarySearch(file, mid+1, r, x);
    }
    return NULL;
}







int main() {
RECORD rec;
    FILE* file = fopen("data.bin","rb+");
bubble(file);
rec = exponentialSearch(file,MAX,300);
print_all_movies(rec,1);


//Read "data.bin" in binary.
return 0;
}