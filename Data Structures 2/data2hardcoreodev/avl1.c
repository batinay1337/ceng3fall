#include <stdio.h>
#include <stdlib.h>

#define SIZE 63

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


int height(NODE N)
{
    if (N == NULL)
        return 0;
    return N->height;
}


int max(int a, int b)
{
    return (a > b) ? a : b;
}

NODE minValueNode(NODE node)
{
    NODE current = node;

    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;

    return current;
}

NODE rightRotate(NODE y)
{
    NODE x = y->left;
    NODE T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;

    // Return new root
    return x;
}


NODE leftRotate(NODE x)
{
    NODE y = x->right;
    NODE T2 = y->left;

    //Perform rotation
    y->left = x;
    x->right = T2;

    //Update heights
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;

    //Return new root
    return y;
}


int getBalance(NODE N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}


NODE insert(NODE node, int key)
{
    /* 1.  Perform the normal BST insertion */
    if (node == NULL)
        return(node_init(NULL,key));

    if (key < node->key)
        node->left  = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else // Equal keys are not allowed in BST
        return node;

    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left),
                           height(node->right));

    
    int balance = getBalance(node);

 

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }

   // Right Left Case
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    
    return node;
}

NODE search(NODE root, int key)
{
    if (root == NULL || root->key == key)
       return root;

    if (root->key < key)
       return search(root->right, key);

    return search(root->left, key);
}


NODE deleteNode(NODE root, int key)
{
    

    if (root == NULL)
        return root;

    if ( key < root->key )
        root->left = deleteNode(root->left, key);


    else if( key > root->key )
        root->right = deleteNode(root->right, key);

    else
    {
      
        if( (root->left == NULL) || (root->right == NULL) )
        {
            NODE temp = root->left ? root->left :root->right;

            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // One child case
             *root = *temp; // Copy the contents of
                            // the non-empty child
            free(temp);
        }
        else
        {
            // node with two children: Get the inorder
            NODE temp = minValueNode(root->right);

            // Copy the inorder successor's data to this node
            root->key = temp->key;

            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->key);
        }
    }

    // If the tree had only one node then return
    if (root == NULL)
      return root;

    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = 1 + max(height(root->left),
                           height(root->right));

    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE
 
    int balance = getBalance(root);

   

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0)
    {  
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}




void printTree(NODE root, int level)
{
    
    if (root == NULL)
    {
        return;
    }

    printTree(root->right ,level + 1);

    
    for (int i = 0; i < level; i++)
    {
        printf("          ");
    }
    printf("%lu\n", root->key);

    
    printTree(root->left, level + 1);
}


int main(void)
{
    
    NODE root = NULL;

   
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);

    printTree(root,0);

    deleteNode(root,20);
    printf("after deletion:\n");

    printTree(root,0);

    printf("searched:\n");
     NODE searching = search(root, 30);

     printTree(searching,0);
    return 0;
}