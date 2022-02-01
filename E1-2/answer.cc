#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Number {
	int digits;
	char *str;
}Number;


char s[1000005] = "";
Number heap_number[500001];
int len = 0;

//	>0 a > b
//	==0 a==b
//	<0 a < b
int Compare(Number a, Number b) {
	if (a.digits > b.digits)
		return a.digits-b.digits;
	else if (a.digits < b.digits)
		return a.digits-b.digits;
	else {
		int i = 0;
		for (i = 0; i < a.digits; i++) {
			if (a.str[i] > b.str[i])
				return 1;
			else if (a.str[i] < b.str[i])
				return -1;
		}
		return 0;
	}
}

void Swap(Number *a, Number *b) {
	Number temp = *a;
	*a = *b;
	*b = temp;
}

int FindT(char *s, int start, int N, char T) {
	for (int i = start; i < N; i++) {
		if (s[i] == T)
			return i;
	}
	return N;
}

int FirstNot(char *s, char c, int start, int end) {
	int i = start;
	for (; i < end; i++) {
		if (s[i] != c)
			return i;
	}
	return end;
}

void buildHeap(Number a) {
	len++;
	heap_number[len] = a;
	int i = len;
	while (i != 1) {
		if (Compare(heap_number[i/2], a) > 0) {
			heap_number[i] = heap_number[i/2];
			i /= 2;
		} else {
			break;
		}
	}
	heap_number[i] = a;
}

void printHeap() {
	while (len >= 1) {
		printf("%s ", heap_number[1].str);
		heap_number[1] = heap_number[len];
		len--;
		int i = 1;
		while (2*i <= len) {
			if (2*i+1 <= len) {
				if (Compare(heap_number[i], heap_number[2*i]) > 0) {
					if (Compare(heap_number[2*i] , heap_number[2*i+1]) < 0) {
						Swap(&heap_number[i], &heap_number[2*i]);
						i = 2*i;
					} else {
						Swap(&heap_number[i], &heap_number[2*i+1]);
						i = 2*i+1;
					}
				} else {
					if (Compare(heap_number[i], heap_number[2*i+1]) < 0) {
						break;
					} else {
						Swap(&heap_number[i], &heap_number[2*i+1]);
						i = 2*i+1;
					}
				}
			} else {
				if (Compare(heap_number[i], heap_number[2*i]) > 0) {
					Swap(&heap_number[i], &heap_number[2*i]);
					i = 2*i;
				} else {
					break;
				}
			}
		}
	}
}

int main(void) {
	int N, t;
	scanf("%d%d", &N, &t);
	char T = t+'0';
	scanf("%s", s);
	char c = 0;
	int i = 0;
	char in_str = 0;
	int start = 0;
	Number a;
	while (i<N) {
		c = s[i];
		if (c == T) {
			if (in_str) {
				buildHeap(a);
				in_str = 0;
			} else {
			}
		} else {
			int end = FindT(s, i, N, T);
			int first_not_zero = FirstNot(s, '0', i, end);
			if (first_not_zero == end) {
				a.str = (char *)malloc(sizeof(char) * 2);
				strcpy(a.str, "0");
				a.str[1] = '\0';
				a.digits = 1;
			} else {
				a.str = (char *)malloc(sizeof(char) * (end-first_not_zero+1));
				strncpy(a.str, s+first_not_zero, end-first_not_zero);
				a.str[end-first_not_zero] = '\0';
				a.digits = end-first_not_zero;
			}
			in_str = 1;
			i = end-1;
		}
		++i;
	}
	if (c != T) {
		buildHeap(a);
	}
	printHeap();
	return 0;
}