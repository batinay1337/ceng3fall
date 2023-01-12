#include <stdio.h>

void left_rotate(int arr[], int n, int d)
{
// store first d elements in a temp array
int temp[d];
for (int i = 0; i < d; i++)
temp[i] = arr[i];

// shift rest of the elements to the left
for (int i = d; i < n; i++)
arr[i - d] = arr[i];

// copy the stored elements from temp to the end of the array
for (int i = 0; i < d; i++)
arr[n - d + i] = temp[i];
}

void right_rotate(int arr[], int n, int d)
{
// store last d elements in a temp array
int temp[d];
for (int i = n - 1; i > n - d - 1; i--)
temp[i - (n - d)] = arr[i];

// shift rest of the elements to the right
for (int i = n - 1; i >= d; i--)
arr[i] = arr[i - d];

// copy the stored elements from temp to the beginning of the array
for (int i = 0; i < d; i++)
arr[i] = temp[i];
}

int main()
{
int arr[] = {1, 2, 3, 4, 5, 6, 7};
int n = sizeof(arr) / sizeof(arr[0]);
int d = 2;

// print array before rotation
printf("Original array: ");
for (int i = 0; i < n; i++)
printf("%d ", arr[i]);

// rotate array by d elements
left_rotate(arr, n, d);

// print array after rotation
printf("\nRotated array: ");
for (int i = 0; i < n; i++)
printf("%d ", arr[i]);

right_rotate(arr, n, d);

// print array after rotation
printf("\nRotated array: ");
for (int i = 0; i < n; i++)
printf("%d ", arr[i]);

return 0;
}