#include <iostream>
#include <string.h>

#define LEN 10

typedef struct Node
{
	char name[LEN];
	int count; //	times of name[LEN]
	struct Node *left;
	struct Node *right;
} Node;

typedef Node *Tree;

typedef struct BiTree
{
	Tree root;
} BiTree;


Tree searchBiTree(Tree T, char name[LEN], Tree *parent)
{
	while (T != NULL)
	{
		int cmp_result = strcmp(T->name, name);
		if (cmp_result == 0)
			return T;
		else if (cmp_result < 0)
		{
			*parent = T;
			T = T->right;
		}
		else
		{
			*parent = T;
			T = T->left;
		}
	}
	return T;
}

Tree getRightMinimum(Tree T, Tree *parent) {
	if (!T) return NULL;
	*parent = T;
	Tree p = T->right;
	while (p->left) {
		*parent = p;
		p = p->left;
	}
	return p;
}

int deleteName(BiTree *T, char name[LEN])
{
	Tree parent = NULL;
	Tree k = searchBiTree(T->root, name, &parent);
	k->count--;
	if (k->count == 0) {
		if (k->left == NULL || k->right == NULL) {
			if (parent == NULL) {
				if (k->left)
					T->root = k->left;
				else
					T->root = k->right;
			} else {
				if (parent->left == k) {
					parent->left = (k->left)?k->left:k->right;
				} else {
					parent->right = (k->left)?k->left:k->right;
				}
			}
		} else {
			Tree sub, sub_p = k;
			sub = getRightMinimum(k, &sub_p);
			sub->left = k->left;
			if (sub_p == k) {
				if (parent == NULL) {
					T->root = sub;
				} else {
					if (parent->left == k) {
						parent->left = sub;
					} else {
						parent->right = sub;
					}
				}
			} else {
				sub_p->left = sub->right;
				sub->right = k->right;
				if (parent == NULL) {
					T->root = sub;
				} else {
					if (parent->left == k) {
						parent->left = sub;
					} else {
						parent->right = sub;
					} 
				}
			}
		}
		free(k);
		return 1;
	}
	return 0;
}

int insertName(BiTree *T, char name[LEN])
{
	Tree parent = NULL;
	Tree k = searchBiTree(T->root, name, &parent);
	if (!k) {
		Tree z = (Tree)malloc(sizeof(Node));
		z->count = 1;
		z->left = NULL;
		z->right = NULL;
		strcpy(z->name, name);
		if (parent == NULL) {
			T->root = z;
		} else if (strcmp(parent->name, name) < 0) {
			parent->right = z;
		} else {
			parent->left = z;
		}
		return 1;
	} else {
		k->count++;
		return 0;
	}
}

int main(void) {
	char name[LEN];
	int mode = 0;
	BiTree T;
	T.root = NULL;
	while (1) {
		scanf("%d", &mode);
		if (mode == -1) {
			break;
		}
		switch (mode)
		{
		case 1:
			printf("insert:");
			scanf("%s", name);
			insertName(&T, name);
			break;
		case 2:
			printf("delete:");
			scanf("%s", name);
			deleteName(&T, name);
			break;
		case 3:
			break;
		default:
			break;
		}
	}
}