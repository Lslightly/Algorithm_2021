#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int num;
	int count;
	struct Node*left;
	struct Node*right;
}Node;

typedef Node* Tree;

void insertTree(Tree root, int num);

void freeTree(Tree root);

int checkTree(Tree p, int n);

int main(void) {
	int t = 0, n = 0;
	int temp = 0;
	scanf("%d", &t);
	for (int i = 0; i < t; i++) {
		Tree root = (Tree)malloc(sizeof(Node));
		root->left = NULL;
		root->right = NULL;
		scanf("%d", &n);
		scanf("%d", &temp);
		root->count = 1;
		root->num = temp;
		for (int j = 1; j < n; j++) {
			scanf("%d", &temp);
			insertTree(root, temp);
		}
		printf("%d\n", checkTree(root, n));
		freeTree(root);
	}
	return 0;
}

void insertTree(Tree p, int num) {
	if (p == NULL) return ;
	else {
		if (p->num == num) {
			p->count++;
			return;
		} else if (p->num < num) {
			if (p->right) {
				insertTree(p->right, num);
			} else {
				p->right = (Tree)malloc(sizeof(Node));
				p->right->num = num;
				p->right->count = 1;
				p->right->left = NULL;
				p->right->right = NULL;
				return ;
			}
		} else {
			if (p->left) {
				insertTree(p->left, num);
			} else {
				p->left = (Tree)malloc(sizeof(Node));
				p->left->num = num;
				p->left->count = 1;
				p->left->left = NULL;
				p->left->right = NULL;
				return ;
			}
		}
	}
}

void freeTree(Tree p) {
	if (p) {
		if (p->left) freeTree(p->left);
		if (p->right) freeTree(p->right);
		free(p);
	}
}

int checkTree(Tree p, int n) {
	int result = 0;
	if (!p) return -1;
	else {
		if (p->count >= (n+1)/2)
			return p->num;
		else if ((result = checkTree(p->left, n)) != -1)
			return result;
		else if ((result = checkTree(p->right, n)) != -1)
			return result;
		else
			return -1;
	}
}
