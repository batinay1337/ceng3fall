#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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



void bubble_in_binary(FILE* file)
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






int binarySearch(FILE* file, int, int, int);


int exponentialSearch(FILE* file, int n, int x)
{
    // If x is present at first location itself
    int i=0;
     RECORD rec1 = (RECORD)malloc(sizeof(RECORD_t)*MAX);
    fseek(file,(i)*sizeof(RECORD_t),SEEK_SET);
    fread(rec1,sizeof(RECORD_t),1,file);
    if(rec1->film_id == x)
    {
        return 0;
    }

    // Find range for binary search by
    // repeated doubling
    int j= 1;
    fseek(file,(j)*sizeof(RECORD_t),SEEK_SET);
    fread(rec1,sizeof(RECORD_t),1,file);
    while (j < n && rec1->film_id <= x)
    {
         j = j*2;
        fseek(file,(j)*sizeof(RECORD_t),SEEK_SET);
        fread(rec1,sizeof(RECORD_t),1,file);

    }
    //  Call binary search for the found range.
    return binarySearch(file, j/2, min(j, n-1), x);
}

// A recursive binary search function. It returns
// location of x in  given array arr[l..r] is
// present, otherwise -1
int binarySearch(FILE* file, int l, int r, int x)
{
    RECORD rec = (RECORD)malloc(sizeof(RECORD_t)*MAX);
    if (r >= l)
    {
        int mid = l + (r - l)/2;

        // If the element is present at the middle
        // itself
        fseek(file,(mid)*sizeof(RECORD_t),SEEK_SET);
        fread(rec,sizeof(RECORD_t),1,file);
        if (rec->film_id == x)
            return mid;


        if (rec->film_id > x)
            return binarySearch(file, l, mid-1, x);

        // Else the element can only be present
        // in right subarray
        return binarySearch(file, mid+1, r, x);
    }

    // We reach here when element is not present
    // in array
    return -1;
}







int main() {
int asd;
    FILE* file = fopen("data.bin","rb+");
bubble_in_binary(file);
asd = exponentialSearch(file,MAX,43);
printf("%d",asd+1);

//Read "data.bin" in binary.
return 0;
}