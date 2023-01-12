#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int value;
  struct Node *left;
  struct Node *right;
} Node;

void heapify(Node *node, int n, int i) {
  int largest = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;

  if (left < n && node[left].value > node[largest].value) {
    largest = left;
  }

  if (right < n && node[right].value > node[largest].value) {
    largest = right;
  }

  if (largest != i) {
    int temp = node[i].value;
    node[i].value = node[largest].value;
    node[largest].value = temp;
    heapify(node, n, largest);
  }
}

void heap_sort(Node *node, int n) {
  for (int i = n / 2 - 1; i >= 0; i--) {
    heapify(node, n, i);
  }

  for (int i = n - 1; i >= 0; i--) {
    int temp = node[0].value;
    node[0].value = node[i].value;
    node[i].value = temp;
    heapify(node, i, 0);
  }
}

int main() {
  Node node[] = {
    {3, NULL, NULL},
    {5, NULL, NULL},
    {1, NULL, NULL},
    {4, NULL, NULL},
    {2, NULL, NULL}
  };
  
  int n = sizeof(node) / sizeof(node[0]);
  heap_sort(node, n);
    
  
  printf("Sorted array: \n");
  for (int i = 0; i < n; i++) {
    printf("%d ", node[i].value);
  }
  printf("\n");

  return 0;
}
