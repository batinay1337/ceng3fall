#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct NODE_s *NODE;
typedef struct NODE_s{
    NODE right;
	NODE left;
	int key;
	void *data;
	int height;
} NODE_t[1];


void inorder(NODE node){
	if(node != NULL){
		inorder(node->left);
		printf("%d ", node->key);
		inorder(node->right);
	}
}

void bst_print(NODE node, int l){
	int i;
	if(node != NULL){
		bst_print(node->right, l+1);
		for (i = 0; i < l; ++i) {
			printf("     ");
		}
		printf("%d\n", node->key);
		bst_print(node->left, l+1);
	}
}

BST bst_init(){
	BST t = (BST)malloc(sizeof(BST_t));
	t->root = NULL;
	return t;
}

void bst_free(BST t){
	//Think about what happens to the nodes!?
	free(t);
}

NODE bst_init_node(int key, void *data){
	NODE node = (NODE)malloc(sizeof(NODE_t));
	node->left = NULL;
	node->right = NULL;
	node->key = key;
	node->data = data;
	ndoe->height = 0;
	return node;
}

void bst_free_node(NODE n){
	free(n);
}

/*
void bst_insert(BST t, int key, void *data){
	if(t == NULL){
		printf("ERROR. Uninitialized tree\n");
	}
	else{
		if(t->root == NULL){
			t->root = bst_init_node(key, data);
		}
		else{
			NODE node = t->root;
			while(node != NULL){
				if(key < node->key){
					if(node->left == NULL){
						node->left = bst_init_node(key, data);
						node = NULL;
					}
					else{
						node = node->left;
					}
				}
				else if(key > node->key){
					if(node->right == NULL){
						node->right = bst_init_node(key, data);
						node = NULL;
					}
					else{
						node = node->right;
					}
				}
				else{
					printf("Duplicate key: %d. Ignoring...\n\n\n", key);
					node = NULL;
				}
			}
		}
	}
}
*/

NODE bst_insert_rec_avl(NODE node, int key, void *data){ /////////////////////////// AVL
	if(node == NULL){
		node = bst_init_node(key, data);
	}
	else{
		if(key < node->key){
			node->left = bst_insert_rec_avl(node->left, key, data);
		}
		else if(key > node->key){
			node->right = bst_insert_rec_avl(node->right, key, data);
		}
		else{
			printf("Duplicate key: %d. Ignoring...\n\n\n", key);
		}
	}
	//MARK: Update the height of the current node.
	node->height = max(node->left->height, node->right->height) + 1; 

	//Compute balance factor;
	int balance_factor = node->left->height - node->right->height;
	// CAOTION  node->left or node -> right might be NULL.

	if(balance_factor == 2) {
		
		if(node->left->left->height > node->left->right->height) {
			//LL
			RightRotate(node);

		}
		else {
			//LR
				leftRotate(node->left);
				RightRotate(node);
		}
	}

	else if(balance_factor = -2) {
		
		if(node->right->right->height > node->right->left->height){
			//RR
			leftRotate(node);
		}
		else{
			//RL

			RightRotate(node->right);
			leftRotate(node);
		}
	}



	




	return node;
}

void bst_insert(BST t, int key, void *data){
	if(t == NULL){
		printf("ERROR. Uninitialized tree\n");
	}
	else{
		if(t->root == NULL){
			t->root = bst_init_node(key, data);
		}
		else{
			t->root = bst_insert_rec(t->root, key, data);
		}
	}
}

void bst_delete_unbalanced_iterative(BST t, int key, void *data){
	if(t == NULL){
		printf("ERROR. Uninitialized tree\n");
	}
	else{

		NODE parent = (NODE)t;
		NODE curr = t->root;
		while((curr != NULL) && (key != curr->key)){
			if(key < curr->key){
				parent = curr;
				curr = curr->left;
			}
			else if(key > curr->key){
				parent = curr;
				curr = curr->right;
			}
		}

		if(curr == NULL){
			printf("The key is not found.\n");
		}
		else{
			/* NO CHILD */
			if( (curr->left == NULL) && (curr->right == NULL) ){
				if(curr == parent->left){
					parent->left = NULL;
				}
				else{
					parent->right = NULL;
				}
				//bst_free_node(curr);
				free(curr->data); /* !? */
				free(curr);

			}
			/* SINGLE CHILD ON THE RIGHT */
			else if( (curr->left == NULL) && (curr->right != NULL) ){
				if(curr == parent->left){
					parent->left = curr->right;
				}
				else{
					parent->right = curr->right;
				}
			}
			/* SINGLE CHILD ON THE LEFT */
			else if( (curr->left != NULL) && (curr->right == NULL) ){
				if(curr == parent->left){
					parent->left = curr->left;
				}
				else{
					parent->right = curr->left;
				}
			}
			/* TWO CHILDREN */
			else{
				NODE max = curr->left;
				while(max->right != NULL){
					max = max->right;
				}
				max->right = curr->right;

				if(curr == parent->left){
					parent->left = curr->left;
				}
				else{
					parent->right = curr->left;
				}
			}
		}
	}
}


/*void inorder(NODE node, NODE *array, int i) {
	
	
	if(node!= NULL) {
		inorder(node->left, array, i);
		array[i] = node; 
		i++;
		inorder(node->right, array, i);
	}
	
}

NODE balance(NODE array, int start, int end){
	if(start != end) {
		//find the middle node

		NODE_t node = array[(start+end)/2];
		
		node->left = balance(array, start, ((start+end)/2));
		node->right = balance(array, ((start+end)/2)+1, end);
		
		return node;
	}
	return NULL;
	
}


*/
void BSTToSkewed(BST t)
{
    NODE gp = (NODE)t;

    NODE p = t-> root;
    
    
    while(p!= NULL){
		NODE child = p->left;
        if(p->left != NULL) {
            //RR
           p->left = child ->right;
           child->right = p;
           gp->right = child;
		   p = child;
        }
        else{
            gp = p; 
            p = p->right;
        }
    }
}

void leftRotate(NODE gp, NODE p, NODE child) {
	p->right = child ->left;
    child->left = p;
    gp->left = child;
	p = child;
}
void makeLeftRotations(BST t, int i){
	NODE gp = NULL; //first left
    NODE p = (NODE)t-> root;
	NODE child = p->left;

	while(i>0 && child != NULL){
		leftRotate(gp, p, child);
		gp = child;
		p = gp->right;
		child = p->right;
		i = i-1;

	}

}

void createPerfectTree(BST t, int n){ //fex. n = 12, we have 12 node

	// m = 2^[log2(n+1)] - 1
	//int n = 23; // m = 15
    int m = 1;
    int i = 0;
    
    while(n >1)  {
    	n = n>>1;
       	i++;
    	m = m*2;
    }
   
  	m -= 1;
	makeLeftRotations(t, n-m);
	while(m>1) {
		m = m/2;
		makeLeftRotations(t, m);
	}

	
}

int findHeight(NODE node){
	int left_height = 0;
	int right_height = 0;

	if(node == NULL){
		return 0;
	}

	left_height = findHeight(node->left);
	right_height = findHeight(node->right);

	node->height = max(left_height, right_height);

	if(left_height > right_height){
		return left_height + 1;
	}
	else {
		return right_height + 1;
	}


}

void avlTree(BST t){
	//phase 1 = check all balance in the sub trees
	//+ olarak bir de balancefactor hesaplamak lazım
	NODE gp = (NODE)t;
	
    NODE p = t-> root;

	findHeight(p->left);






    
}


// Entry point
int main()
{

   // Creating a binary search tree
   BST t1 = bst_init();
    

	bst_insert(t1, 44, NULL);
	bst_insert(t1, 11, NULL);
	bst_insert(t1, 34, NULL);
	bst_insert(t1, 52, NULL);
	bst_insert(t1, 89, NULL);
	bst_insert(t1, 62, NULL);
	bst_insert(t1, 23, NULL);
	bst_insert(t1, 72, NULL);
	bst_insert(t1, 93, NULL);
	bst_print(t1->root, 0);
	printf("\n\n\n");
   /*
   Toggle between the lines 106 and 107
   by commenting/uncommenting to test both
   cases i.e. k = 0 or k = 1
   int k = 0;
   */
   

   /*
   Converting the binary search tree into a
   increasing / decreasing skewed tree
   */
   BSTToSkewed(t1);

   bst_print(t1->root, 0);

   // Traversing the skewed tree
   int n = 12;
   createPerfectTree(t1, n);
	printf("\n\n\n");
   bst_print(t1->root, 0);
   

   return 0;
}