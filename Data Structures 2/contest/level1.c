#include<stdio.h>
# include <string.h>



int func(){

    int sum = 0;




    return sum;


}



int main( )
{
 
    
    FILE *filePointer ;
    FILE *fptr;
     
    char dataToBeRead[50];
 
    filePointer = fopen("level2_1.in", "r") ;
    
    if ( filePointer == NULL )
    {
        printf( "GfgTest.c file failed to open." ) ;
    }
    else
    {
         
        printf("The file is now opened.\n") ;
         
        // Read the dataToBeRead from the file
        // using fgets() method

        int sum = 0;
        while( fgets ( dataToBeRead, 50, filePointer ) != NULL )
        {
            
            // Print the dataToBeRead
            //printf( "%s" , dataToBeRead ) ;

            for(int i = 0; i<50; i++) {
                if(dataToBeRead[i] == 'C') {
                    dataToBeRead[i] = ' ';
                    sum++;
                }
            }

            printf( "%s" , dataToBeRead ) ;
            
        
        }
printf("\n%d\n", sum);

        fptr = fopen("level2_1.out","w");

        if(fptr == NULL)
        {
        printf("Error!");   
                    
        }

   

        fprintf(fptr,"%d",sum);
        fclose(fptr);
         
        // Closing the file using fclose()
        fclose(filePointer) ;
         
        printf("Data successfully read from file GfgTest.c\n");
        printf("The file is now closed.") ;
    }
    return 0;       
}