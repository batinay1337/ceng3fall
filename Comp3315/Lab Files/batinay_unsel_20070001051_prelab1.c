#include <stdio.h>

int main()
{
    int array[10] = {8, 1, 4, 5, 6, 3, 2, 9, 7};
    
    int i = 0;
    int sum = 0;
    
    for (int i = 0; i < 10; i++) {
        sum = sum + array[i];
    }
    
    printf("%d",sum);
    return 0;
}
