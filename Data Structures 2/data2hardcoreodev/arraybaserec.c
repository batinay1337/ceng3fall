#include <stdio.h>
#include <stdlib.h>

#define SIZE 20

typedef struct NODE_s* NODE;


typedef struct NODE_s {
	NODE right;
	NODE left;
	int height;
	int parent_ptr;
	unsigned long key;
	void* data;
} NODE_t[1];

NODE node_init(void *data,int key) {
    NODE node = (NODE)malloc(sizeof(NODE_t));
    node->data = data;
    node->key = key;
    return node;
} // Initialize node init



int height(int index,NODE *nodes)
{
    if (index >= SIZE || nodes[index] == NULL)
    return -1;

    return 1 + (height(index * 2 + 1,nodes) > height(index * 2 + 2,nodes)? height(index * 2 + 1,nodes): height(index * 2 + 2,nodes));
}

int rotateRight(int index,NODE *nodes)
{
    NODE left = nodes[index * 2 + 1];
    nodes[index * 2 + 1] = nodes[index * 2 + 1 * 2 + 2];
    nodes[index] = left;
    return index * 2 + 1;
}

int rotateLeft(int index,NODE *nodes)
{
    NODE right = nodes[index * 2 + 2];
    nodes[index * 2 + 2] = nodes[index * 2 + 2 * 2 + 1];
    nodes[index] = right;
    return index * 2 + 2;
}

int rotateLeftThenRight(int index,NODE *nodes)
{
    index = rotateLeft(index * 2 + 1,nodes);
    return rotateRight(index,nodes);
}

int rotateRightThenLeft(int index,NODE *nodes)
{
    index = rotateRight(index * 2 + 2,nodes);
    return rotateLeft(index,nodes);
}


void insert(int key, NODE *nodes, int index)
{
    if (index == -1 || nodes[index] == NULL)
    {
        nodes[index] = node_init(NULL, key);
        return;
    }

    int balance = height(index * 2 + 1, nodes) - height(index * 2 + 2, nodes);

    if (balance == -2)
    {
        if (height(index * 2 + 2 * 2 + 1, nodes) > height(index * 2 + 2 * 2 + 2, nodes))
        {
            rotateLeft(index * 2 + 2, nodes);
        }

        rotateRight(index, nodes);
    }
    else if (balance == 2)
    {
        if (height(index * 2 + 1 * 2 + 2, nodes) > height(index * 2 + 1 * 2 + 1, nodes))
        {
            rotateRight(index * 2 + 1, nodes);
        }

        rotateLeft(index, nodes);
    }

    if (key < nodes[index]->key)
    {
        insert(key, nodes, index * 2 + 1);
    }

    else
    {
        insert(key, nodes, index * 2 + 2);
    }
}






int AVLsearch(int key, NODE *nodes)
{
    
    for (int i = 0; i < SIZE; i++)
    {
        
        if (nodes[i]->key == key)
        {
            return i;
        }
    }

    return -1;
}



int findMin(int index, NODE *nodes)
{
    if (index == -1)
    {
        return -1;
    }

    
    while (nodes[index * 2 + 1] != NULL)
    {
        index = index * 2 + 1;
    }


    return index;
}


void balanceTree(int index, NODE *nodes)
{
    
    if (index == -1)
    {
        return;
    }

    
    int leftHeight = height(index * 2 + 1, nodes);
    int rightHeight = height(index * 2 + 2, nodes);

    
    if (leftHeight > rightHeight + 1)
    {
        if (height((index * 2 + 1)* 2 + 2, nodes) > height((index * 2 + 1) * 2 + 1, nodes))
        {
            rotateRight(index * 2 + 1, nodes);
        }

        NODE temp = nodes[index * 2 + 1];
        nodes[index * 2 + 1] = nodes[index];
        nodes[index] = temp;

        free(temp);


        rotateRight(index, nodes);
    }
    

    else if (rightHeight > leftHeight + 1)
    {
        
        if (height((index * 2 + 2) * 2 + 1, nodes) > height((index * 2 + 2) * 2 + 2, nodes))
        {
            rotateLeft(index * 2 + 2, nodes);
        }

        
        NODE temp = nodes[index * 2 + 2];
        nodes[index * 2 + 2] = nodes[index];
        nodes[index] = temp;

        free(temp);

        
        rotateLeft(index, nodes);
    }
}



void removeNode(int key, NODE *nodes)
{
    
    int index = AVLsearch(key, nodes);

   
    if (index == -1)
    {
        printf("Düğüm bulunamadı!\n");
        return;
    }

    
    if (nodes[index * 2 + 1] == NULL && nodes[index * 2 + 2] == NULL)
    {
        nodes[index]= NULL;
        return;
    }

   
    int minIndex = findMin(index * 2 + 2,nodes); // right

    
    nodes[index] = nodes[minIndex];

    
    balanceTree(minIndex, nodes);

    nodes[minIndex] = NULL;
}


void printTree(NODE *nodes, int index, int level)
{
    
    if (index == -1 || nodes[index] == NULL)
    {
        return;
    }

    printTree(nodes, index * 2 + 2, level + 1);

    for (int i = 0; i < level; i++)
    {
        printf("          ");
    }
    printf("%lu\n", nodes[index]->key);

    printTree(nodes, index * 2 + 1, level + 1);
}

int main(){
    NODE *nodes = malloc(SIZE * sizeof(NODE));

    for (int i = 0; i < SIZE; i++)
    {
        nodes[i] = NULL;
    }

    
    insert(5, nodes, 0);
    insert(3, nodes, 0);
    insert(7, nodes, 0);
    insert(2, nodes, 0);
    insert(4, nodes, 0);
    insert(6, nodes, 0);
    insert(8, nodes, 0);

    
    printTree(nodes, 0, 0);
    
  
    removeNode(5, nodes);
    
    


    printf("\n AFTER REMOVING: \n\n\n");

    printTree(nodes, 0, 0);
   
    

    return 0;
}