#ifndef QUICKSORT_H_
#define QUICKSORT_H_
#include <random>

void swap(int &a, int &b) {
	int temp = a;
	a = b;
	b = temp;
}

int random(int p, int r) {
	return p + rand() % (r-p+1);
}

int randomized_partition(int a[], int p, int r) {
	int i = random(p, r);
	swap(a[i], a[r]);
	return partition(a, p, r);
}

int partition(int a[], int p, int r) {
	int i = p-1, j = p;
	for (; j < r-1; j++) {
		if (a[j] < a[r]) {
			i = i+1;
			swap(a[i], a[j]);
		}
	}
	swap(a[i+1], a[r]);
	return i+1;
}

void quickSort(int a[], int p, int r) {
	if (p < r) {
		int q = partition(a, p, r);
		quickSort(a, p, q-1);
		quickSort(a, q, r);
	}
}

void randomized_quickSort(int a[], int p, int r) {
	if (p < r) {
		int q = randomized_partition(a, p, r);
		randomized_quickSort(a, p, q-1);
		randomized_quickSort(a, q, r);
	}
}

#endif