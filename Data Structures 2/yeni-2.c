#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_NODES 1000

typedef struct node
{
int data;
int height;
int left;
int right;
} Node;

Node avl[MAX_NODES];
int size = 0;

// Returns the height of the given node
int get_height(int index)
	{
		if (index == -1)
	{
		return 0;
	}
		return avl[index].height;
	}

// Returns the balance factor of the given node
int get_balance(int index)
	{
		return get_height(avl[index].left) - get_height(avl[index].right);
	}


// Performs a right rotation on the given node and returns the new root
	int rotate_right(int index)
	{
		int new_root = avl[index].left;
		avl[index].left = avl[new_root].right;
		avl[new_root].right = index;
		// Update the heights of the rotated nodes
		avl[index].height = fmax(get_height(avl[index].left), get_height(avl[index].right)) + 1;
		avl[new_root].height = fmax(get_height(avl[new_root].left), get_height(avl[new_root].right)) + 1;

	return new_root;

}

// Performs a left rotation on the given node and returns the new root
	int rotate_left(int index)
		{
			int new_root = avl[index].right;
			avl[index].right = avl[new_root].left;
			avl[new_root].left = index;
			// Update the heights of the rotated nodes
			avl[index].height = fmax(get_height(avl[index].left), get_height(avl[index].right)) + 1;
			avl[new_root].height = fmax(get_height(avl[new_root].left), get_height(avl[new_root].right)) + 1;

			return new_root;

}

// Returns the index of the newly inserted node
int insert(int data)
{
// Check if there is space in the array for a new node
	if (size >= MAX_NODES)
		{
			printf("Error: Array is full, cannot insert new node\n");
			return -1;
		}

	int index = 0;
	while (1)
	{
		if (data < avl[index].data)
		{
			// Move to the left child if it exists, otherwise insert the new node as the left child
			if (avl[index].left != -1)
			{
				index = avl[index].left;
			}
			else
			{
				avl[index].left = size;
				avl[size].data = data;
				avl[size].height = 1;
				avl[size].left = -1;
				avl[size].right = -1;
				size++;
				return size - 1;
			}
		}
		else
		{
			// Move to the right child if it exists, otherwise insert the new node as the right child
			if (avl[index].right != -1)
			{
				index = avl[index].right;
			}
			else
			{
				avl[index].right = size;
				avl[size].data = data;
				avl[size].height = 1;
				avl[size].left = -1;
				avl[size].right = -1;
				size++;
				return size - 1;
			}
		}

		// Update the height of the current node
		avl[index].height = fmax(get_height(avl[index].left), get_height(avl[index].right)) + 1;

		// Get the balance factor of the current node
		int balance = get_balance(index);

		// Left Left case
		if (balance > 1 && data < avl[avl[index].left].data)
		{
			index = rotate_right(index);
		}
		// Right Right case
		else if (balance < -1 && data > avl[avl[index].right].data)
		{
			index = rotate_left(index);
		}
		// Left Right case
		else if (balance > 1 && data > avl[avl[index].left].data)
		{
			avl[index].left = rotate_left(avl[index].left);
			index = rotate_right(index);
		}
		// Right Left case
		else if (balance < -1 && data < avl[avl[index].right].data)
		{
			avl[index].right = rotate_right(avl[index].right);
			index = rotate_left(index);
		}
	
}

}		

void print(int index)
{
	if (index == -1)
	{
		return;
	}

		printf("%d ", avl[index].data);
		print(avl[index].left);
		print(avl[index].right);
}
		
int main()
{
	// Initialize the root node
	avl[0].data = 5;
	avl[0].height = 1;
	avl[0].left = -1;
	avl[0].right = -1;
	size++;

	// Insert some nodes into the tree
	insert(3);
	insert(7);
	insert(1);
	insert(6);
	insert(8);
	insert(2);

	// Print the height and balance factor of each node
		for (int i = 0; i < size; i++)
		{
			//printf("Node %d: height = %d, balance = %d\n", avl[i].data, avl[i].height, get_balance(i));
					print(i);
		}

		
		


	}