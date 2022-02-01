#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CACHE_SIZE 20

enum Color
{
	RED,
	BLACK
};

typedef struct Node
{
	char color;
	int key;
	struct Node *left;
	struct Node *right;
	struct Node *p;
} Node;
typedef Node *Tree;

typedef struct RBTree
{
	Tree nil;
	Tree root;
	int size;
} RBTree;

void left_rotate(RBTree *T, Tree x)
{
	Tree y = x->right;
	x->right = y->left;
	if (y->left != T->nil)
	{
		y->left->p = x;
	}
	y->p = x->p;
	if (x->p == T->nil)
	{
		T->root = y;
	}
	else if (x == x->p->left)
	{
		x->p->left = y;
	}
	else
	{
		x->p->right = y;
	}
	y->left = x;
	x->p = y;
}

void right_rotate(RBTree *T, Tree y)
{
	Tree x = y->left;
	y->left = x->right;
	if (x->right != T->nil)
	{
		x->right->p = y;
	}
	x->p = y->p;
	if (y->p == T->nil)
	{
		T->root = x;
	}
	else if (y->p->left == y)
	{
		y->p->left = x;
	}
	else
	{
		y->p->right = x;
	}
	x->right = y;
	y->p = x;
}

//	T中已包含节点
//	找得到与key匹配的节点就返回指针，p是父亲
//	否则返回T.nil
Tree rbtreeFindInsertPlace(RBTree T, int key, Tree *p)
{
	Tree x = T.root;
	while (x != T.nil)
	{
		if (key == x->key)
			return x;
		else if (key > x->key)
		{
			*p = x;
			x = x->right;
		}
		else
		{
			*p = x;
			x = x->left;
		}
	}
	return x;
}

void rbtreeInsertFixUp(RBTree *T, Tree z)
{
	Tree y;
	while (z->p->color == RED)
	{
		if (z->p == z->p->p->left)
		{
			y = z->p->p->right;
			if (y->color == RED)
			{
				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			}
			else if (z == z->p->right)
			{
				z = z->p;
				left_rotate(T, z);
				z->p->color = BLACK;
				z->p->p->color = RED;
				right_rotate(T, z->p->p);
			}
			else
			{
				z->p->color = BLACK;
				z->p->p->color = RED;
				right_rotate(T, z->p->p);
			}
		}
		else
		{
			y = z->p->p->left;
			if (y->color == RED)
			{
				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			}
			else if (z == z->p->left)
			{
				z = z->p;
				right_rotate(T, z);
				z->p->color = BLACK;
				z->p->p->color = RED;
				left_rotate(T, z->p->p);
			}
			else
			{
				z->p->color = BLACK;
				z->p->p->color = RED;
				left_rotate(T, z->p->p);
			}
		}
	}
	T->root->color = BLACK;
}

int rbtreeCheck(RBTree *T, Tree p) {
	if (p == T->nil) return 1;
	int left_result = rbtreeCheck(T, p->left), right_result = rbtreeCheck(T, p->right);
	if (left_result == -1 || right_result == -1) {
		return -1;
	}
	else if (left_result != right_result)
		return -1;
	else {
		if (p->color == BLACK) {
			return left_result+1;
		} else {
			return left_result;
		}
	}
}

Tree rbtreeInsert(RBTree *T, int key)
{
	Tree y = T->nil;
	Tree x = T->root;
	if (T->size == 0)
	{ //	没有节点
		Tree z = (Tree)malloc(sizeof(Node));
		z->color = BLACK;
		z->key = key;
		z->left = T->nil;
		z->right = T->nil;
		z->p = T->nil;
		T->root = z;
		T->size = 1;
		return z;
	}
	Tree temp = rbtreeFindInsertPlace(*T, key, &y);
	if (temp == T->nil)
	{ //	没找到，找到了插入位置
		Tree z = (Tree)malloc(sizeof(Node));
		z->color = RED;
		z->key = key;
		z->left = T->nil;
		z->right = T->nil;
		z->p = y;
		if (z->key < y->key)
		{
			y->left = z;
		}
		else
		{
			y->right = z;
		}
		rbtreeInsertFixUp(T, z);
		T->size++;
		// if (rbtreeCheck(T, T->root) == -1) {
		// 	exit(1);
		// }
		return z;
	}
	else
	{ //	在树上已经存在，只需count++
		return temp;
	}
}

//	让u的parent指向v，且v的parent指向u的parent
void rbtreeTransplant(RBTree *T, Tree u, Tree v)
{
	if (u->p == T->nil)
	{
		T->root = v;
	}
	else if (u == u->p->left)
	{
		u->p->left = v;
	}
	else
	{
		u->p->right = v;
	}
	v->p = u->p;
}

//	z不为T.nil
Tree rbTreeMinimum(RBTree *T, Tree z)
{
	while (z->left != T->nil)
	{
		z = z->left;
	}
	return z;
}

//	z不为T.nil
Tree rbTreeMaximum(RBTree *T, Tree z) {
	while (z->right != T->nil) {
		z = z->right;
	}
	return z;
}

Tree rbTreePredecessor(RBTree *T, Tree z) {
	if (z->left != T->nil) {
		return rbTreeMaximum(T, z->left);
	}
	Tree y = z->p;
	while (y != T->nil && z == y->left) {
		y = y->p;
		z = z->p;
	}
	return y;
}

Tree rbTreeSuccessor(RBTree *T, Tree z) {
	if (z->right != T->nil) {
		return rbTreeMinimum(T, z->right);
	}
	Tree y = z->p;
	while (y != T->nil && z == y->right) {
		y = y->p;
		z = z->p;
	}
	return y;
}

void rbtreeDeleteFixUp(RBTree *T, Tree x)
{
	Tree w;
	while (x != T->root && x->color == BLACK)
	{
		if (x == x->p->left)
		{
			w = x->p->right;
			if (w->color == RED)
			{
				w->color = BLACK;
				x->p->color = RED;
				left_rotate(T, x->p);
				w = x->p->right;
			}
			if (w->left->color == BLACK && w->right->color == BLACK)
			{
				w->color = RED;
				x = x->p;
			}
			else if (w->right->color == BLACK)
			{
				w->left->color = BLACK;
				w->color = RED;
				right_rotate(T, w);
				w = x->p->right;
				w->color = x->p->color;
				x->p->color = BLACK;
				w->right->color = BLACK;
				left_rotate(T, x->p);
				x = T->root;
			}
			else
			{
				w->color = x->p->color;
				x->p->color = BLACK;
				w->right->color = BLACK;
				left_rotate(T, x->p);
				x = T->root;
			}
		}
		else
		{
			w = x->p->left;
			if (w->color == RED)
			{
				w->color = BLACK;
				x->p->color = RED;
				right_rotate(T, x->p);
				w = x->p->left;
			}
			if (w->right->color == BLACK && w->left->color == BLACK)
			{
				w->color = RED;
				x = x->p;
			}
			else if (w->left->color == BLACK)
			{
				w->right->color = BLACK;
				w->color = RED;
				left_rotate(T, w);
				w = x->p->left;
				w->color = x->p->color;
				x->p->color = BLACK;
				w->left->color = BLACK;
				right_rotate(T, x->p);
				x = T->root;
			}
			else
			{
				w->color = x->p->color;
				x->p->color = BLACK;
				w->left->color = BLACK;
				right_rotate(T, x->p);
				x = T->root;
			}
		}
	}
	x->color = BLACK;
}

void rbtreeDelete(RBTree *T, Tree z)
{
	Tree y = z;
	Tree x;
	char y_original_color = y->color;
	if (z->left == T->nil)
	{
		x = z->right;
		rbtreeTransplant(T, z, z->right);
	}
	else if (z->right == T->nil)
	{
		x = z->left;
		rbtreeTransplant(T, z, z->left);
	}
	else
	{
		y = rbTreeMinimum(T, z->right);
		y_original_color = y->color;
		x = y->right;
		if (y->p == z)
		{
			x->p = y;
		}
		else
		{
			rbtreeTransplant(T, y, y->right);
			y->right = z->right;
			y->right->p = y;
		}
		rbtreeTransplant(T, z, y);
		y->left = z->left;
		y->left->p = y;
		y->color = z->color;
	}
	if (y_original_color == BLACK)
	{
		rbtreeDeleteFixUp(T, x);
	}
		// if (rbtreeCheck(T, T->root) == -1) {
		// 	exit(1);
		// }
	free(z);
}

void rbtreeInit(RBTree *T)
{
	T->nil = (Tree)malloc(sizeof(Node));
	T->nil->color = BLACK;
	T->nil->key = 0;
	T->nil->p = T->nil;
	T->nil->left = T->nil;
	T->nil->right = T->nil;
	T->root = T->nil;
	T->size = 0;
}

int rbtreeSize(RBTree *T)
{
	return T->size;
}


void freeNode(RBTree *T, Tree p)
{
	if (p != T->nil)
	{
		freeNode(T, p->left);
		freeNode(T, p->right);
		free(p);
	}
}

void freeRBTree(RBTree *T)
{
	freeNode(T, T->root);
	free(T->nil);
}

int findKeyInCache(int key_cache[CACHE_SIZE], int cache_full, int replace_i, int key) {
	int bound = (cache_full)?CACHE_SIZE:replace_i;
	for (int i = 0; i < bound; i++) {
		if (key_cache[i] == key) {
			return key_cache[i];
		}
	}
	return -1;
}

int main(void) {
	RBTree T;
	rbtreeInit(&T);
	int key = 0;
	char op[10] = "";
	int key_cache[CACHE_SIZE] = {0};
	int replace_i = 0;
	int cache_full = 0;
	while (1) {
		scanf("%s", op);
		if (op[0] == 'I') {
			scanf("%d", &key);
			rbtreeInsert(&T, key);
			if (cache_full) {
				key_cache[replace_i] = key;
				replace_i = (replace_i+1)%CACHE_SIZE;
			} else {
				key_cache[replace_i] = key;
				replace_i++;
				if (replace_i == CACHE_SIZE) {
					cache_full = 1;
					replace_i = 0;
				}
			}
		} else if (op[0] == 'F') {
			scanf("%d", &key);
			int result = findKeyInCache(key_cache, cache_full, replace_i, key);
			if (result == -1) {
				Tree p, x;
				x = rbtreeFindInsertPlace(T, key, &p);
				if (x == T.nil) {
					if (p->key < key) {
						printf("%d\n", p->key);
					} else {
						Tree pred = rbTreePredecessor(&T, p);
						printf("%d\n", pred->key);
					}
				} else {
					printf("%d\n", x->key);
				}
			} else {
				printf("%d\n", result);
			}
		} else {
			break;
		}
	}
	freeRBTree(&T);
	return 0;
}

