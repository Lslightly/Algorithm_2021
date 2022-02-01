#include <stdio.h>
#include <stdlib.h>

//	以Count信息作为有序队列的排队依据
//	以num信息进行输入数据的树构建
typedef struct OrderedListNode
{
	int num;
	int count;
	int left;
	int right;
	int parent;
} OrderedListNode;

typedef struct OrderedList
{
	int tail;
	OrderedListNode *elem; //	第0个元素存储树的根信息
} OrderedList;
OrderedList count_list = {0, NULL};

int checkExceedHalf(OrderedList *list, int n);

//	以优先队列方式存储信息
void insertList(OrderedList *list, int num);

void swapBefore(OrderedList *list, int i);

//	树根节点初始化
void initList(OrderedList *list);

//	返回插入位置的父亲或者就是相等的那个节点索引
int insertTree(OrderedList *list, int num, int cur_i);

int main(void)
{
	int t = 0;
	int n = 0;
	int temp = 0;
	int result = 0;
	scanf("%d", &t);
	for (int k = 0; k < t; k++)
	{
		scanf("%d", &n);
		count_list.elem = (OrderedListNode *)malloc(sizeof(OrderedListNode) * (n+1));
		initList(&count_list);
		int i = 1;
		for (i = 1; i < (n + 1) / 2; i++)
		{
			scanf("%d", &temp);
			insertList(&count_list, temp);
		}
		for (; i < (2*n)/3+1; i++)
		{
			scanf("%d", &temp);
			insertList(&count_list, temp);
			result = checkExceedHalf(&count_list, n);
			if (result != -1)
			{
				printf("%d\n", result);
				break;
			}
			else
			{
				continue;
			}
		}
		if (count_list.elem[1].count < n/6) {
			result = -1;
			for (; i < n; i++) {
				scanf("%d", &temp);
			}
		} else {
			for (; i < n; i++) {
				scanf("%d", &temp);
				insertList(&count_list, temp);
				result = checkExceedHalf(&count_list, n);
				if (result != -1)
				{
					printf("%d\n", result);
					break;
				}
				else
				{
					continue;
				}
			}
		}
		if (result == -1)
		{
			printf("%d\n", result);
		}
		free(count_list.elem);
	}
}

void insertList(OrderedList *list, int num)
{
	int insert_i = insertTree(list, num, list->elem[0].left);
	int sort_i = 0;
	if (list->elem[insert_i].num == num)
	{
		list->elem[insert_i].count++;
		sort_i = insert_i;
	}
	else
	{
		list->tail++;
		list->elem[list->tail].num = num;
		list->elem[list->tail].count = 1;
		list->elem[list->tail].parent = insert_i;
		list->elem[list->tail].left = 0;
		list->elem[list->tail].right = 0;
		if (list->elem[insert_i].num > num)
		{
			list->elem[insert_i].left = list->tail;
		}
		else
		{
			list->elem[insert_i].right = list->tail;
		}
		sort_i = list->tail;
	}
	for (; sort_i > 1; sort_i--)
	{
		if (list->elem[sort_i].count > list->elem[sort_i - 1].count)
		{
			swapBefore(list, sort_i);
		} else {
			break;
		}
	}
}

void initList(OrderedList *list)
{
	int temp = 0;
	scanf("%d", &temp);
	list->tail = 1;
	list->elem[0].num = 100000001;
	list->elem[0].count = 0;
	list->elem[0].left = 1;
	list->elem[0].right = 0;
	list->elem[1].num = temp;
	list->elem[1].count = 1;
	list->elem[1].left = 0;
	list->elem[1].right = 0;
	list->elem[1].parent = 0;
}

int checkExceedHalf(OrderedList *list, int n)
{
	if (list->elem[1].count >= (n + 1) / 2)
	{
		return list->elem[1].num;
	}
	else
	{
		return -1;
	}
}

int insertTree(OrderedList *list, int num, int cur_i) {
	if (list->elem[cur_i].num == num) {
		return cur_i;
	} else if (list->elem[cur_i].num > num) {
		if (list->elem[cur_i].left == 0) {
			return cur_i;
		} else {
			return insertTree(list, num, list->elem[cur_i].left);
		}
	} else {
		if (list->elem[cur_i].right == 0) {
			return cur_i;
		} else {
			return insertTree(list, num, list->elem[cur_i].right);
		}
	}
}

void swapBefore(OrderedList *list, int i) {
	OrderedListNode temp_i = list->elem[i], temp_i1 = list->elem[i-1];
	list->elem[i] = temp_i1;
	list->elem[i-1] = temp_i;

	OrderedListNode * I = &temp_i, *I1 = &temp_i1;
	OrderedListNode * real_i = &list->elem[i], *real_i1 = &list->elem[i-1];
	OrderedListNode * P;
	if (I->left == i || I->right == i) {
		P = &list->elem[I->parent];
		real_i1->parent = i;
		if (I->left == i) {
			I->left = i-1;
			list->elem[real_i->right].parent = i;
		} else {
			I->right = i-1;
			list->elem[real_i->left].parent = i;
		}
		if (P->num < I->num) {
			P->right = i;
		} else {
			P->left = i;
		}
		list->elem[real_i1->left].parent = i-1;
		list->elem[real_i1->right].parent = i-1;
	} else if (I->parent == i) {
		I->parent = i-1;
		if (I1->num < I->num) {
			I1->right = i;
			list->elem[I1->left].parent = i-1;
		} else {
			I1->left = i;
			list->elem[I1->right].parent = i-1;
		}
		list->elem[I->left].parent = i;
		list->elem[I->right].parent = i;
		P = &list->elem[I1->parent];
		if (P->num < I1->num) {
			P->right = i-1;
		} else {
			P->left = i-1;
		}
	} else {
		P = &list->elem[I->parent];
		if (P->num < I->num) {
			P->right = i;
		} else {
			P->left = i;
		}
		list->elem[I->left].parent = i;
		list->elem[I->right].parent = i;
		P = &list->elem[I1->parent];
		if (P->num < I->num) {
			P->right = i-1;
		} else {
			P->left = i-1;
		}
		list->elem[I1->left].parent = i-1;
		list->elem[I1->right].parent = i-1;
	}

}