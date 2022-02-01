#include <iostream>

#define BLOCK_SIZE 10000

using namespace std;

typedef struct bucket {
	int n;
	int *array;
	int digits;
	int *index;
} bucket;



void bucket_init(bucket &bkt, int digits);
int get_digits(int n);
void bucket_insert(bucket &bkt, int number);
int * radixSort(int * a, int n, int digits);
void bucket_free(bucket &bkt);
void bucket_print(bucket &bkt);
void insertSort(int *a, int *index, int n);

int get_digits(int n) {
	int digit = 0;
	if (n == 0) return 0;
	while (n != 0) {
		digit++;
		n /= 10;
	}
	return digit-1;
}

int main(void)
{
	int n = 0;
	bucket bkt[10];
	scanf("%d", &n);
	int temp = 0;
	for (int i = 0; i < 10; i++) {
		bucket_init(bkt[i], i+1);
	}
	for (int i = 0; i < n; i++) {
		scanf("%d", &temp);
		bucket_insert(bkt[get_digits(temp)], temp);
	}
	for (int i = 0; i < 10; i++) {
		bkt[i].index = radixSort(bkt[i].array, bkt[i].n, bkt[i].digits);
		bucket_print(bkt[i]);
		bucket_free(bkt[i]);
	}
	return 0;
}

void bucket_init(bucket &bkt, int digits) {
	bkt.n = 0;
	bkt.array = (int *)malloc(sizeof(int)*BLOCK_SIZE);
	bkt.digits = digits;
}

void bucket_insert(bucket &bkt, int number) {
	bkt.array[bkt.n] = number;
	bkt.n++;
	if (bkt.n % BLOCK_SIZE == 0) {
		bkt.array = (int*)realloc(bkt.array, sizeof(int)*(bkt.n+BLOCK_SIZE));
	}
}

void bucket_print(bucket &bkt) {
	for (int i = 0; i < bkt.n; i++) {
		printf("%d ", bkt.array[bkt.index[i]]);
	}
}

void bucket_free(bucket &bkt) {
	free(bkt.array);
	free(bkt.index);
}

int * radixSort(int * a, int n, int digits) {
	int *temp = (int *)malloc(sizeof(int)*n);
	int *index = (int *)malloc(sizeof(int)*n);
	for (int i = 0; i < n; i++) {
		temp[i] = a[i];
		index[i] = i;
	}
	for (int i = 0; i < digits; i++) {
		insertSort(temp, index, n);
		for (int j = 0; j < n; j++) {
			temp[j] /= 10;
		}
	}
	free(temp);
	return index;
}

void insertSort(int *a, int *index, int n) {
	for (int i = 0; i < n-1; i++) {
		for (int j = i; j >=0; j--) {
			if (a[index[j]] % 10 > a[index[j+1]] % 10) {
				int temp = index[j];
				index[j] = index[j+1];
				index[j+1] = temp;
			}
		}
	}
}