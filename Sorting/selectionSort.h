#ifndef SELECTIONSORT_H_
#define SELECTIONSORT_H_

void selectionSort(int a[], int length) {
	for (int i = 0; i < length-1; i++) {
		k = i;
		for (int j = i+1; j < length; j++) {
			if (a[j] < a[k]) {
				k = j;
			}
		}
		if (k != i) {
			int temp = a[k];
			a[k] = a[i];
			a[i] = temp;
		}
	}
}

#endif