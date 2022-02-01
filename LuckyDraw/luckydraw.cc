//https://202.38.86.171:1443/problem/H2-1
#include <iostream>
#include <random>

using namespace std;

int select(int a[], int k, int n, int i);

int partition(int a[], int left, int right);

int get_middle(int a[], int left, int right);

int get_five_middle(int a[], int start);

int insert_sort(int a[], int left, int right);

void swap(int *a, int *b);

int a[10000001];

int middles[2000001];

int main(void)
{
	int n = 0, k = 0;
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}
	int result =  0;
	result = select(a, 0, n-1, k-1);
	printf("%d", a[result]);
	return 0;
}

int select(int a[], int left, int right, int i) {
	if (right - left < 10) {
		insert_sort(a, left, right);
		return i;
	}
	int k = partition(a, left, right);
	if (k == i) {
		return k;
	} else if (k < i) {
		return select(a, k+1, right, i);
	} else {
		return select(a, left, k-1, i);
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

void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

int get_middle(int a[], int left, int right) {
	int result = 0;
	int len = 0;
	len = (right-left+1)/5;
	if ((right-left+1)%5 == 0) {
		int i = 0;
		for (i = 0; i < len; i++) {
			middles[i] = get_five_middle(a, i*5+left);
		}
	} else {
		int i = 0;
		for (i = 0; i < len; i++) {
			middles[i] = get_five_middle(a, i*5+left);
		}
		len++;
		middles[i] = a[i*5+left];
	}
	result = select(middles, 0, len-1, len/2) * 5 + left;

	return result;
}

int get_five_middle(int a[], int start) {
	insert_sort(a, start, start+4);
	return a[start+2];
}

int insert_sort(int a[], int left, int right) {
	for (int i = left+1; i <= right; i++) {
		for (int j = i; j >= left+1; j--) {
			if (a[j] < a[j-1]) {
				swap(&a[j], &a[j-1]);
			} else {
				break;
			}
		}
	}
}