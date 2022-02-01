#ifndef INSERTION_SORT_
#define INSERTION_SORT_

void insertionSort(int a[], int n) {
	int key, i, j;
	for (j = 2; j <= n; j++) {
		key = a[j];
		i = j-1;
		while (i > 0 && a[i] > key) {
			a[i+1] = a[i];
			i--;
		}
		a[i+1] = key;
	}
}

#endif