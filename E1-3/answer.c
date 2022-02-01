#include <stdio.h>
#include <stdlib.h>

#define MODULO 10000007

typedef struct Node {
	int num;
	int treesize;
	struct Node *left;
	struct Node *right;
}Node;

typedef Node* Tree;

int getTreeSize(Tree root) {
	if (root) return root->treesize;
	else return 0;
}

//	在root树下插入num，同时返回逆序数
int insertTree(Tree root, int num) {
	root->treesize += 1;
	if (num >= root->num) {
		if (root->right) {
			return insertTree(root->right, num);
		} else {
			root->right = (Tree)malloc(sizeof(Node));
			root->right->num = num;
			root->right->left = NULL;
			root->right->right = NULL;
			root->right->treesize = 1;
			return 0;
		}
	} else {
		if (root->left) {
			return insertTree(root->left, num) + 1 + getTreeSize(root->right);
		} else {
			root->left = (Tree)malloc(sizeof(Node));
			root->left->num = num;
			root->left->left = NULL;
			root->left->right = NULL;
			root->left->treesize = 1;
			return 1+getTreeSize(root->right);
		}
	}
}

void freeTree(Tree root) {
	if (!root) return ;
	else {
		Tree left = root->left, right = root->right;
		free(root);
		freeTree(left);
		freeTree(right);
	}
}

int main(void) {
	int N;
	scanf("%d", &N);
	int temp = 0;
	int answer = 0;
	Tree root = (Tree)malloc(sizeof(Node));
	scanf("%d", &temp);
	root->num = temp;
	root->left = NULL;
	root->right = NULL;
	root->treesize = 1;
	for (int i = 1; i < N; i++) {
		scanf("%d", &temp);
		answer += insertTree(root, temp);
		answer %= MODULO;
	}
	printf("%d", answer);

	return 0;
}
