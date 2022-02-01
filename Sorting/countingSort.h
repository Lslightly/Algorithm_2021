#ifndef COUNTINGSORT_H_
#define COUNTINGSORT_H_
#include <stdlib.h>

void countingSort(int a[], int b[], int k, int an) {
	int *c = (int *)malloc(sizeof(int)*k);
	int i = 0;
	for (; i < k; i++) {
		c[i] = 0;
	}
	for (i = 0; i < an; i++) {
		c[a[i]]++;
	}
	for (i = 1; i < k; i++) {
		c[i] += c[i-1];
	}
	for (i = an-1; i >= 0; i--) {
		b[c[a[i]]] = a[i];
		c[a[i]]--;
	}
	free(c);
}

#endif