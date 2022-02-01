#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 10

enum Color
{
	RED,
	BLACK
};

typedef struct Node
{
	char color;
	char name[LEN];
	int count;
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

int cmp(char a[], char b[])
{
	return strcmp(a, b);
}

//	T中已包含节点
//	找得到与name匹配的节点就返回指针，p是父亲
//	否则返回T.nil
Tree rbtreeFindInsertPlace(RBTree T, char name[LEN], Tree *p)
{
	Tree x = T.root;
	while (x != T.nil)
	{
		int pname_name = cmp(x->name, name);
		if (pname_name == 0)
			return x;
		else if (pname_name < 0)
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

Tree rbtreeInsert(RBTree *T, char name[LEN])
{
	Tree y = T->nil;
	Tree x = T->root;
	if (T->size == 0)
	{ //	没有节点
		Tree z = (Tree)malloc(sizeof(Node));
		z->color = BLACK;
		z->count = 1;
		z->left = T->nil;
		z->right = T->nil;
		z->p = T->nil;
		strcpy(z->name, name);
		T->root = z;
		T->size = 1;
		return z;
	}
	Tree temp = rbtreeFindInsertPlace(*T, name, &y);
	if (temp == T->nil)
	{ //	没找到，找到了插入位置
		Tree z = (Tree)malloc(sizeof(Node));
		z->color = RED;
		z->count = 1;
		strcpy(z->name, name);
		z->left = T->nil;
		z->right = T->nil;
		z->p = y;
		if (cmp(z->name, y->name) < 0)
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
		temp->count++;
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

void deleteName(RBTree *T, char name[LEN])
{
	Tree tempp;
	Tree p = rbtreeFindInsertPlace(*T, name, &tempp);
	if (p == T->nil)
	{
		exit(1);
	}
	else
	{
		p->count--;
		if (p->count == 0)
		{
			T->size--;
			rbtreeDelete(T, p);
		}
		else
		{
			return;
		}
	}
}

void rbtreeInit(RBTree *T)
{
	T->nil = (Tree)malloc(sizeof(Node));
	T->nil->color = BLACK;
	T->nil->count = 0;
	strcpy(T->nil->name, "");
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

void nodePrint(RBTree T, Tree p) {
	if (p == T.nil) return ;
	printf("%s %d\n", p->name, p->count);
	nodePrint(T, p->left);
	nodePrint(T, p->right);
}

void printRange(char **name, int left, int right) {
	printf("range:\n");
	for (int i = left; i < right; i++) {
		printf("%s ", name[i]);
	}
	putchar('\n');
}

char names[10000000][6];

int leK(RBTree *T, int k, int n) {
	rbtreeInit(T);
	int i = 0, j = 0;
	int count = 0;
	while (j < n) {
		rbtreeInsert(T, names[j]);
		while (rbtreeSize(T) > k) {
			deleteName(T, names[i++]);
		}
		count+=j-i;
		j++;
	}
	freeRBTree(T);
	return count;
}

int main()
{
	// char name[40] = "test/testdata/test_0";
	// for (int l = 0; l < 50; l++)
	// {
		// // int l = 3;
		// int len = strlen(name);
		// name[len-1] = l+'0';
		// freopen(name, "r", stdin);
		int n, k;
		scanf("%d%d", &n, &k);
		RBTree TK, TK1;
		rbtreeInit(&TK);
		rbtreeInit(&TK1);
		int count_k = 0;
		int count_k1 = 0;
		int ik = 0, ik1 = 0;
		for (int j = 0; j < n; j++)
		{
			scanf("%s", names[j]);
			rbtreeInsert(&TK, names[j]);
			rbtreeInsert(&TK1, names[j]);
			while (rbtreeSize(&TK) > k) {
				deleteName(&TK, names[ik++]);
			}
			count_k += j-ik;
			while (rbtreeSize(&TK1) > k-1)
			{
				deleteName(&TK1, names[ik1++]);
			}
			count_k1 += j-ik1;
		}
		freeRBTree(&TK);
		freeRBTree(&TK1);
		printf("%d", count_k - count_k1);
		// printf("%d: %d\n", l,  count);
	// }
	return 0;
}
