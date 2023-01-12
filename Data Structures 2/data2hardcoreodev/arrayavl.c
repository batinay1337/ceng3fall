#include <stdio.h>
#include <stdlib.h>

#define MAX 8

typedef struct NODE_s* NODE;

typedef struct NODE_s {
	NODE right;
	NODE left;
	int height;
	int parent_ptr;
	unsigned long key;
	void* data;
} NODE_t[1];

typedef struct {
	NODE root;
} TREE_t[1], * TREE;


int max_num(int a, int b);
int height(NODE node);
NODE avl_tree_insert(NODE node, unsigned long key);

TREE tree_init() {
	TREE t = (TREE)malloc(sizeof(TREE_t));
	t->root = NULL;
	return t;
}

void tree_kill(TREE t) {
	free(t);
}

NODE tree_node_init(unsigned long key, void* data) {
	NODE n = (NODE)malloc(sizeof(NODE_t));
	n->left = NULL;
	n->right = NULL;
	n->key = key;
	n->data = data;
	return n;
}

NODE tree_insert_recursive(NODE node, unsigned long key, void* data) {
	if (node != NULL)
	{
		if (key < node->key) {
			node->left = tree_insert_recursive(node->left, key, data);
		}
		else if (key > node->key) {
			node->right = tree_insert_recursive(node->right, key, data);
		}
		else {
			printf("Error: duplicate node \n");
		}
	}
	else {
		node = tree_node_init(key, data);
	}
	return node;
}

void tree_insert(TREE tree, unsigned long key, void* data) {
	if (tree->root == NULL) {
		tree->root = tree_node_init(key, data);
	}
	else {
		avl_tree_insert(tree->root, key);
	}
}


void tree_traverse_preorder(NODE node) {

	if (node != NULL) {
		printf("%lu \n", node->key);
		fflush(stdout);
		tree_traverse_preorder(node->left);
		tree_traverse_preorder(node->right);
	}
}


void tree_print(NODE node, int k) {
	int i;
	if (node != NULL) {
		tree_print(node->right, k + 4);
		for (i = 0; i < k; i++) {
			printf(" ");
		}
		printf("%lu\n", node->key);
		tree_print(node->left, k + 4);
	}
}



NODE left_rotation(NODE node) {

	NODE node2 = node->right; //node2 node un righti
	NODE temp = node2->left; // temp node un rightinin left i

	node2->left = node; // RL yi node a atama
	node->right = temp;

	node->height = 1 + max_num(height(node->left), height(node->right)); //rotate yapildiktan sonra left ve rightini kontrol ederek yuksekligi belirleme
	node2->height = 1 + max_num(height(node2->left), height(node2->right));

	return node2;

}

NODE right_rotation(NODE node) {

	NODE node2 = node->left; //node2 ye node un lefti
	NODE temp = node2->right; // temp e left in righti

	node2->right = node; //LR ye node atama
	node->left= temp; // rotate icin bi asagi kaydirma yapma

	node->height = 1 + max_num(height(node->left), height(node->right)); //maxnuma gonderip kontrol ettiriyoz
	node2->height = 1 + max_num(height(node2->left), height(node2->right));

	return node2;
}

int max_num(int a, int b) {
	if (a > b) {
		return a; //bunu surekli geri dondurerek height kontrol ediyoruz
	}
	else {
		return b;
	}
}


int height(NODE node) {

	if (node == NULL) {
		return 0;
	}
	else {
		return node->height;
	}

}

NODE avl_tree_insert(NODE node, unsigned long key) {

	int isBalanced = 0;

	//NODE node = (NODE)tree;

	if (node == NULL) {
		return tree_node_init(key, NULL);
	}

	if (key < node->key) {
		node->left = avl_tree_insert(node->left, key);
	}
	else if (key > node->key) {
		node->right = avl_tree_insert(node->right, key);
	}
	else {
		return node;
	}

	node->height = 1 + max_num(height(node->left), height(node->right));

	isBalanced = height(node->left) - height(node->right);


	if (isBalanced > 1 && key < node->left->key) {			// ll case
		return right_rotation(node);
	}

	if (isBalanced < -1 && key < node->right->key) {		//rl case
		node->right = right_rotation(node->right);
		return left_rotation(node);
	}


	if (isBalanced < -1 && key > node->right->key) {		// rr case
		return left_rotation(node);
	}

	if (isBalanced > 1 && key > node->left->key) {			//lr case
		node->left = left_rotation(node->left);
		return right_rotation(node);
	}

	return node;
}




int main() {
	TREE t1 = tree_init();

	int key[MAX] = {1,14,15,22,46,68,90,96};

	for(int i = 0;i < MAX; i++){
			avl_tree_insert(t1->root, key[i]);
		}

	tree_print(t1->root, 0);

	tree_traverse_preorder(t1->root);
	//tree_traverse_preorder(node);

	tree_kill(t1);

	return 0;
}
