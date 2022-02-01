#include <stdio.h>
#include <stdlib.h>

int select(int a[], int k, int n, int i);

int partition(int a[], int left, int right);

void swap(int *a, int *b);

int insert_sort(int a[], int left, int right);

int a[10000001];

int main(void)
{
	int t = 0;
	scanf("%d", &t);
	for (int j = 0; j < t; j++)
	{
		int n = 0, k = 0;
		scanf("%d%d", &n, &k);
		for (int i = 0; i < n; i++)
		{
			scanf("%d", &a[i]);
		}
		int result = 0;
		result = select(a, 0, n - 1, k - 1);
		printf("%d\n", a[result]);
	}
	return 0;
}

int select(int a[], int left, int right, int i)
{
	if (right - left < 10)
	{
		insert_sort(a, left, right);
		return i;
	}
	int k = partition(a, left, right);
	if (k == i)
	{
		return k;
	}
	else if (k < i)
	{
		return select(a, k + 1, right, i);
	}
	else
	{
		return select(a, left, k - 1, i);
	}
}

int partition(int a[], int left, int right)
{
	int pivot = rand() % (right - left + 1) + left;
	swap(&a[pivot], &a[right]);
	int i = left - 1, j = left;
	while (j < right)
	{
		if (a[j] < a[right])
		{
			swap(&a[j], &a[i + 1]);
			i++;
			j++;
		}
		else
		{
			j++;
		}
	}
	swap(&a[j], &a[i + 1]);
	return i + 1;
}

void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

int insert_sort(int a[], int left, int right)
{
	for (int i = left + 1; i <= right; i++)
	{
		for (int j = i; j >= left + 1; j--)
		{
			if (a[j] < a[j - 1])
			{
				swap(&a[j], &a[j - 1]);
			}
			else
			{
				break;
			}
		}
	}
}