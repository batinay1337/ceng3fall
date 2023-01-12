#include <stdio.h>
#include <stdlib.h>

#define ARR_SIZE 22
#define HASH_SIZE 10

typedef struct HASH_TABLE_s *HASH_TABLE;
typedef struct HASH_TABLE_s{
	int key;
	void *value;
	int flag;
} HASH_TABLE_t[1];

typedef struct AVL_TREE_NODE_s *AVL_TREE_NODE;
typedef struct AVL_TREE_NODE_s {
	AVL_TREE_NODE right;
	AVL_TREE_NODE left;
	int key;
	int height;
	void *data;
} AVL_TREE_NODE_t[1];

typedef struct AVL_TREE_s *AVL_TREE;
typedef struct AVL_TREE_s {
	AVL_TREE_NODE root;
} AVL_TREE_t[1];

AVL_TREE linked_tree_init() {
	AVL_TREE tree = (AVL_TREE)malloc(sizeof(AVL_TREE_t));
	tree->root = NULL;
	return tree;
}

AVL_TREE_NODE linked_tree_node_init(int key, void *data) {
	AVL_TREE_NODE node = (AVL_TREE_NODE)malloc(sizeof(AVL_TREE_NODE_t));
	node->right = NULL;
	node->left = NULL;
	node->key = key;
	node->height = 1;
	node->data = data;
	return node;
}

void linked_tree_horizontal_print(AVL_TREE_NODE node, int l) {
	if (node != NULL) {
		linked_tree_horizontal_print(node->right, l + 1);
		for (int i = 0; i < l; ++i) {
			printf("  ");
		}
		printf("%d (%d)\n", node->key, *(int *)node->data);
		linked_tree_horizontal_print(node->left, l + 1);
	}
}

int max(int a, int b) {
	if(a > b){
		return a;
	}else{
		return b;
	}
}

int height(AVL_TREE_NODE node) {
	if(node == NULL) {
		return 0;
	}else{
		return node->height;
	}
}

AVL_TREE_NODE linked_tree_rotate_right(AVL_TREE_NODE node) {
	AVL_TREE_NODE lchild = node->left;
	AVL_TREE_NODE r_of_lchild = lchild->right;

	// perform rotation
	lchild->right = node;
	node->left = r_of_lchild;

	// update heights
	node->height = max(height(node->left), height(node->right)) + 1;
	lchild->height = max(height(lchild->left), height(lchild->right)) + 1;

	return lchild; // left child becomes the new root
}

AVL_TREE_NODE linked_tree_rotate_left(AVL_TREE_NODE node) {
	AVL_TREE_NODE rchild = node->right;
	AVL_TREE_NODE l_of_rchild = rchild->left;

	// perform rotation
	rchild->left = node;
	node->right = l_of_rchild;

	// update heights
	node->height = max(height(node->left), height(node->right)) + 1;
	rchild->height = max(height(rchild->left), height(rchild->right)) + 1;

	return rchild; // right child becomes the new root
}

AVL_TREE_NODE linked_tree_insert(AVL_TREE_NODE node, int key, void *data) {
	if(node == NULL) {
		return(linked_tree_node_init(key, data));
	}
	if(key < node->key){
		node->left  = linked_tree_insert(node->left, key, data);
	}else if(key > node->key){
		node->right = linked_tree_insert(node->right, key, data);
	}else{
		return node;
	}

	node->height = 1 + max(height(node->left),height(node->right)); // update node height

	int balance = height(node->left) - height(node->right); // get balance factor to check if subtree is balanced

	// if subtree is unbalanced, test 4 cases:
	if(balance > 1 && key < node->left->key) { // left left
		return linked_tree_rotate_right(node);
	}

	if(balance > 1 && key > node->left->key) {	// left right
		node->left =  linked_tree_rotate_left(node->left);
		return linked_tree_rotate_right(node);
	}

	if(balance < -1 && key > node->right->key) { // right right
		return linked_tree_rotate_left(node);
	}

	if(balance < -1 && key < node->right->key) { // right left
		node->right = linked_tree_rotate_right(node->right);
		return linked_tree_rotate_left(node);
	}

	return node; // return the (unchanged) node pointer
}

HASH_TABLE init_hashtable(){
	// Fill here
}

int hash(int key){  // (n^3 + 2*n^2) mod HASH_SIZE
	// Fill here
}

void put(HASH_TABLE htable, int key, void *value){
	// Fill here
}

void print_HashTable(HASH_TABLE h1){
	// Fill here
}

int main(void) {

	HASH_TABLE h1 = init_hashtable();

	int keyArr[ARR_SIZE] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22 };
	int valArr[ARR_SIZE] = { 3, 12, 18, 22, 23, 33, 38, 45, 73, 82, 97, 98, 99, 100, 78, 11, 1, 77, 90, 25, 70, 66 };

	for (int i = 0; i < ARR_SIZE; ++i) {
		put(h1, keyArr[i], &valArr[i]);
	}
	
	print_HashTable(h1);

	return 1;
}
