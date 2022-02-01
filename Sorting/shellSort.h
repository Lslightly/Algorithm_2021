#ifndef SHELLSORT_H_
#define SHELLSORT_H_

void shellPass(int a[], int d, int n) {
	int i, j;
	int key;
	for (i = d; i < n; i++) {
		if (a[i] < a[i-d]) {
			key = a[i];
			j = i-d;
			while (j > 0 && key < a[j]) {
				a[j+d] = a[j];
				j -= d;
			}
			a[j+d] = key;
		}
	}
}

void shellSort(int a[], int d[], int an, int dn) {
	for (int i = 0; i < dn; i++) {
		shellPass(a, d[i], an);
	}
}

#endif