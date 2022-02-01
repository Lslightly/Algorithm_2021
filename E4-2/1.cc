#include <stdio.h>
#include <stdlib.h>

#define MAX_TASK_NUM 100000

typedef struct Task {
    int rt;
    int leftt;
} Task;


typedef struct Heap {
	int heapsize;
	Task *a;
}Heap;

void initHeap(Heap *h, int n) {
	h->a = (Task *)malloc(sizeof(int) * (n+1));
	h->heapsize = 0;
}

void freeHeap(Heap *h) {
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

int Cmp(Task &a, Task &b) {
    return b.leftt - a.leftt;
}

void maxHeapify(Heap *h, int i) {
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

Task heapExtractMax(Heap *h) {
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


int heapEmpty(Heap *h) {
    return h->heapsize == 0;
}

Task heapMaximun(Heap *h) {
	return h->a[1];
}

void heapIncreaseKey(Heap *h, int i, Task key) {
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

void maxHeapInsert(Heap *h, Task key) {
	h->heapsize++;
	h->a[h->heapsize] = key;
    h->a[h->heapsize].leftt++;
	heapIncreaseKey(h, h->heapsize, key);
}

int cmp(const void *a, const void *b) {
    return ((Task*)a)->rt - ((Task*)b)->rt;
}

int main(void)
{
    int n;
    scanf("%d", &n);
    Task * tasks = (Task*)malloc(sizeof(Task)*n);
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &tasks[i].rt, &tasks[i].leftt);
    }
    Heap prioQ;
    initHeap(&prioQ, n);
    qsort(tasks, n, sizeof(Task), cmp);
    int curT = tasks[0].rt;
    int totalTime = 0;
    for (int i = 0; i < n; ) {
        while (i < n && tasks[i].rt == curT) {
            maxHeapInsert(&prioQ, tasks[i]);
            i++;
        }
        Task minLeftTask = heapExtractMax(&prioQ);
        if (i == n) {
            while (!heapEmpty(&prioQ)) {
                totalTime += minLeftTask.leftt * (prioQ.heapsize+1);
                minLeftTask = heapExtractMax(&prioQ);
            }
            totalTime += minLeftTask.leftt;
        } else {
            int nextrt = tasks[i].rt;
            int flag = 0;
            while (minLeftTask.leftt + curT <= nextrt) {
                totalTime += minLeftTask.leftt * (prioQ.heapsize+1);
                curT += minLeftTask.leftt;
                if (heapEmpty(&prioQ)) {
                    flag = 1;
                    curT = nextrt;
                    break;
                } else {
                    minLeftTask = heapExtractMax(&prioQ);
                }
            }
            if (flag) {
                continue;
            }
            totalTime += (nextrt - curT)*(prioQ.heapsize + 1);
            minLeftTask.leftt -= (nextrt-curT);
            maxHeapInsert(&prioQ, minLeftTask);
            curT = nextrt;
        }
    }
    printf("%d", totalTime);
    freeHeap(&prioQ);
    free(tasks);
    return 0;
}