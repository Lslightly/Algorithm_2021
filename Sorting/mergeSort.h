#ifndef MERGESORT_H_
#define MERGESORT_H_
#include <stdlib.h>

void merge(int a[], int p, int q, int r) {
	int n1 = q-p+1, n2 = r-q;
	int *L = (int *)malloc(sizeof(int)*n1);
	int *R = (int *)malloc(sizeof(int)*n2);
	int i, j;
	for (i = 0; i < n1; i++) {
		L[i] = a[p+i];
	}
	for (i = 0; i < n2; i++) {
		R[i] = a[q+1+i];
	}
	i = 0;
	j = 0;
	int k = p;
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			a[k++] = L[i];
			i++;
		} else {
			a[k++] = R[j];
			j++;
		}
	}
	while (i < n1) {
		a[k++] = L[i];
	}
	while (j < n2) {
		a[k++] = R[j];
	}
	free(L);
	free(R);
}

void mergeSort(int a[], int p, int r) {
	if (p < r) {
		mergeSort(a, p, (p+r)/2);
		mergeSort(a, (p+r)/2+1, r);
		merge(a, p, (p+r)/2, r);
	}
}

#endif