#include<stdio.h>
# include <string.h>

#define N 20


void printSolution(int sol[N][N])
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			printf(" %c ", sol[i][j]);
		printf("\n");
	}
}


int main( )
{
 
    
    FILE *filePointer ;
    FILE *fptr;
     
    char dataToBeRead[50];
    char 
    /*char maze[N][N] = { { W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W},
W,C,C,C,C,C,C,C,C,C,C,C,C,C,C,C,C,C,C,W},
W,C,W,W,W,W,W,W,C,W,C,W,W,W,W,W,C,W,C,W},
W,C,W,W,W,W,W,W,C,W,C,W,W,W,W,W,C,W,C,W},
W,C,W,W,W,W,W,W,C,C,C,C,C,C,C,C,C,C,C,W},
W,C,W,W,W,W,W,W,C,W,C,W,W,W,W,W,W,W,C,W},
W,C,W,W,W,W,W,W,C,W,C,W,W,W,W,W,W,W,C,W}
W,C,W,W,W,W,W,W,C,W,C,W,W,W,W,W,W,W,C,W}
W,C,W,W,W,W,W,W,C,C,C,C,C,C,C,C,C,C,C,W}
W,C,W,W,W,W,W,W,W,W,C,W,W,W,W,W,W,W,C,W}
W,C,W,W,W,W,W,W,W,W,C,W,W,W,W,W,W,W,C,W}
W,C,W,W,W,W,W,W,W,W,C,W,W,W,C,C,C,C,C,W}
W,C,W,W,W,W,W,W,W,W,C,W,W,W,C,W,W,W,C,W}
W,C,P,C,C,C,C,C,C,C,C,C,C,C,C,C,C,C,C,W}
WCWCWWWWWWCWWWCWWWCW}
WCWCWWWWWWCWWWCWWWCW}
WCWCWWWWWWCCCCCWWWCW}
WCWCWWWWWWWWWWCWWWCW}
WCCCCCCCCCCCCCCCCCCW}
WWWWWWWWWWWWWWWWWWWW}}; */



 
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

        

            

              
            

            
	

            printf( "%s 1" , dataToBeRead) ;
            
        
        }


        fptr = fopen("level2_1.out","w");

        if(fptr == NULL)
        {
        printf("Error!");   
                    
        }

   
   

        fclose(fptr);
        
        // Closing the file using fclose()
        fclose(filePointer) ;
         
        printf("Data successfully read from file GfgTest.c\n");
        printf("The file is now closed.") ;
    }
    return 0;       
}