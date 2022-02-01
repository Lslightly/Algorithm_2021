#include <iostream>


int a[100000000] = {0};

void quickSort(int a[], int left, int right);

void insertSort(int a[], int left, int right);

void swap(int *a, int *b);

int partition(int a[], int left, int right);

int main(void)
{
	int n = 0;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}
	quickSort(a, 0, n-1);
	for (int i = 0; i < n; i++) {
		printf("%d ", a[i]);
	}
	return 0;
}

void insertSort(int a[], int left, int right) {
	for (int i = left+1; i <= right; i++) {
		for (int j = right; j > left; j--) {
			if (a[j] < a[j-1]) {
				swap(&a[j], &a[j-1]);
			}
		}
	}
}

void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void quickSort(int a[], int left, int right) {
	if (right - left < 10) {
		insertSort(a, left, right);
	} else {
		int pivot = partition(a, left, right);
		quickSort(a, left, pivot-1);
		quickSort(a, pivot+1, right);
	}
}

int partition(int a[], int left, int right) {
	int pivot = rand() % (right-left+1) + left;
	swap(&a[pivot], &a[right]);
	int i = left-1, j = left;
	while (j < right) {
		if (a[j] < a[right]) {
			swap(&a[j], &a[i+1]);
			i++;
			j++;
		}
		else {
			j++;
		}
	}
	swap(&a[j], &a[i+1]);
	return i+1;
}