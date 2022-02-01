#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAP_SIZE 500

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

typedef struct BiForest
{
	BiTree trees[MAP_SIZE];
	int num_nodes;
} BiForest;

int strSum(char name[LEN])
{
	int len = strlen(name);
	int sum = 0;
	for (int k = 1; k < len; k++)
	{
		sum += name[k];
		sum *= name[k - 1];
		sum %= MAP_SIZE;
	}
	return sum;
}

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

Tree getRightMinimum(Tree T, Tree *parent)
{
	if (!T)
		return NULL;
	*parent = T;
	Tree p = T->right;
	while (p->left)
	{
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
	if (k->count == 0)
	{
		if (k->left == NULL || k->right == NULL)
		{
			if (parent == NULL)
			{
				if (k->left)
					T->root = k->left;
				else
					T->root = k->right;
			}
			else
			{
				if (parent->left == k)
				{
					parent->left = (k->left) ? k->left : k->right;
				}
				else
				{
					parent->right = (k->left) ? k->left : k->right;
				}
			}
		}
		else
		{
			Tree sub, sub_p = k;
			sub = getRightMinimum(k, &sub_p);
			sub->left = k->left;
			if (sub_p == k)
			{
				if (parent == NULL)
				{
					T->root = sub;
				}
				else
				{
					if (parent->left == k)
					{
						parent->left = sub;
					}
					else
					{
						parent->right = sub;
					}
				}
			}
			else
			{
				sub_p->left = sub->right;
				sub->right = k->right;
				if (parent == NULL)
				{
					T->root = sub;
				}
				else
				{
					if (parent->left == k)
					{
						parent->left = sub;
					}
					else
					{
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
	if (!k)
	{
		Tree z = (Tree)malloc(sizeof(Node));
		z->count = 1;
		z->left = NULL;
		z->right = NULL;
		strcpy(z->name, name);
		if (parent == NULL)
		{
			T->root = z;
		}
		else if (strcmp(parent->name, name) < 0)
		{
			parent->right = z;
		}
		else
		{
			parent->left = z;
		}
		return 1;
	}
	else
	{
		k->count++;
		return 0;
	}
}

void freeTree(Tree T)
{
	if (!T)
		return;
	freeTree(T->left);
	freeTree(T->right);
	free(T);
}

void freeBiTree(BiTree *T)
{
	freeTree(T->root);
}

void freeMap(BiForest *BF)
{
	for (int i = 0; i < MAP_SIZE; i++)
	{
		freeBiTree(&BF->trees[i]);
	}
}

void initMap(BiForest *BF)
{
	for (int i = 0; i < MAP_SIZE; i++)
	{
		BF->trees[i].root = NULL;
	}
	BF->num_nodes = 0;
}

void mapInsertName(BiForest *BF, char name[LEN])
{
	BF->num_nodes += insertName(&BF->trees[strSum(name)], name);
}

void mapDeleteName(BiForest *BF, char name[LEN])
{
	BF->num_nodes -= deleteName(&BF->trees[strSum(name)], name);
}

char names[10000000][6] = {""};

int main(void)
{
	int n, k = 0;
	scanf("%d%d", &n, &k);
	int ik = 0, ik1 = 0;
	int countk = 0, countk1 = 0;
	BiForest name_mapk, name_mapk1;
	initMap(&name_mapk);
	initMap(&name_mapk1);
	for (int i = 0; i < n; i++)
	{
		scanf("%s", names[i]);
		mapInsertName(&name_mapk, names[i]);
		mapInsertName(&name_mapk1, names[i]);
		while (name_mapk.num_nodes > k)
		{
			mapDeleteName(&name_mapk, names[ik]);
			ik++;
		}
		while (name_mapk1.num_nodes > k - 1)
		{
			mapDeleteName(&name_mapk1, names[ik1]);
			ik1++;
		}
		countk += i - ik;
		countk1 += i - ik1;
	}
	freeMap(&name_mapk);
	freeMap(&name_mapk1);
	printf("%d", countk - countk1);
	return 0;
}