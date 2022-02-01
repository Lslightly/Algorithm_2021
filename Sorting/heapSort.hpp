#ifndef HEAPSORT_H_
#define HEAPSORT_H_
#include <stdlib.h>
#include <stdio.h>

template<typename T>
struct Heap {
	int heapsize;
	T *a;
};

template<typename T>
void initHeap(struct Heap *h, int n) {
	h->a = (T *)malloc(sizeof(T) * (n+1));
	h->heapsize = 0;
}

template<typename T>
void freeHeap(struct Heap *h) {
	free(h->a);
	h->heapsize = 0;
}

int left(int i) {
	return 2*i;
}

int right(int i) {
	return 2*i+1;
}

int parent(int i) {
	return i/2;
}

template<typename T>
int Cmp(T &a, T &b) {
    return a - b;
}

template<typename T>
void maxHeapify(struct Heap *h, int i) {
	int l = left(i), r = right(i);
	int largest = l;
	if (l <= h->heapsize && Cmp(h->a[l], h->a[i]) > 0) {
		largest = l;
	} else {
		largest = i;
	}
	if (r <= h->heapsize && Cmp(h->a[r], h->a[largest]) > 0) {
		largest = r;
	}
	if (largest != i) {
		auto temp = h->a[i];
		h->a[i] = h->a[largest];
		h->a[largest] = temp;
		maxHeapify(h, largest);
	}
}

template<typename T>
void buildMaxHeap(struct Heap *h) {
	for (int i = h->heapsize/2; i > 0; i--) {
		maxHeapify(h, i);
	}
}

template<typename T>
void heapSort(struct Heap *h) {
	buildMaxHeap(h);
	int len = h->heapsize;
	for (int i = 0; i < len; i++) {
		auto temp = h->a[1];
		h->a[1] = h->a[len-i];
		h->a[len-i] = temp;
		h->heapsize--;
		maxHeapify(h, 1);
	}
}

template<typename T>
int heapExtractMax(struct Heap *h) {
    if (h->heapsize < 1) {
        printf("heap empty, could not extract max");
        exit(0);
    }
	auto max = h->a[1];
	h->a[1] = h->a[h->heapsize];
	h->heapsize--;
	maxHeapify(h, 1);
	return max;
}

template<typename T>
int heapEmpty(struct Heap *h) {
    return h->heapsize == 0;
}

template<typename T>
int heapMaximun(struct Heap *h) {
	return h->a[1];
}

template<typename T>
void heapIncreaseKey(struct Heap *h, int i, int key) {
    if (Cmp(key, h->a[i]) < 0) {
        printf("not larger key");
        exit(0);
    }
	h->a[i] = key;
	while (i > 1 && Cmp(h->a[parent(i)], h->a[i]) < 0) {
		auto temp = h->a[parent(i)];
		h->a[parent(i)] = h->a[i];
		h->a[i] = temp;
		i = parent(i);
	}
}

template<typename T>
void maxHeapInsert(struct Heap *h, int key) {
	h->heapsize++;
	h->a[h->heapsize] = -1000;
	heapIncreaseKey(h, h->heapsize, key);
}

#endif