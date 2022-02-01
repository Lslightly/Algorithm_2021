#include <stdio.h>
#include <stdlib.h>
#include <queue>

using namespace std;

#define V 100001
#define E 1000001

#ifdef DEBUG
#include <iostream>
#define DEBUGCOUT(x) std::cout << x << std::endl;fflush(stdout);
#define DEBUGPRINTF(x) printf(x);fflush(stdout);
#else
#define DEBUGCOUT(x) ;
#define DEBUGPRINTF(x) ;
#endif

typedef struct Dist {
    int dist;
    //  inf + x = inf
    Dist operator+(const struct Dist &b) {
        if (this->dist == -1 || b.dist == -1) {
            return {-1};
        } else {
            return {this->dist + b.dist};
        }
    }
    void operator=(const struct Dist &b) {
        this->dist = b.dist;
    }
    bool operator==(const struct Dist &b) {
        return this->dist == b.dist;
    }

    //  a < b return true 
    //  a >= b return false
    //  a is inf, then a < b is always false
    //  a is not inf, b is inf, then a < b is always true
    bool operator<(const struct Dist &b) {
        if (this->dist == -1) {
            return false;
        } else if (b.dist == -1) {
            return true;
        } else {
            return this->dist < b.dist;
        }
    }
}Dist;

typedef struct AdjNode {
    int adj;
    Dist w;
    struct AdjNode *next;
}AdjNode, *AdjList;

struct Vertex;


typedef struct Vertex {
    int heap_index;
    Dist dist;
    AdjList head, tail;
    void init() {
        this->head = (AdjList)malloc(sizeof(AdjNode));
        this->head->next = nullptr;
        this->tail = this->head;
        this->dist.dist = -1;
    }
    AdjList find(int adj) {
        auto p = this->head->next;
        while (p) {
            if (p->adj == adj) {
                return p;
            }
            p = p->next;
        }
        return nullptr;
    }
    void insert(int adj, int w) {
        auto find_result = this->find(adj);
        Dist tmp = {w};
        if (find_result &&  tmp < find_result->w) {
            find_result->w = tmp;
        } else if (find_result) {
            return;
        } else {
            auto adjp = (AdjList)malloc(sizeof(AdjNode));
            adjp->next = nullptr;
            adjp->adj = adj;
            adjp->w = tmp;
            this->tail->next = adjp;
            this->tail = adjp;
        }
    }
    Dist getAdjW(int adj) {
        AdjList p = this->head->next;
        while (p) {
            if (p->adj == adj) {
                return p->w;
            }
            p = p->next;
        }
        return {-1};
    }
    bool relax(int adj, struct Vertex &v);
    void all_relax();
    bool operator<(const struct Vertex &v) {
        return this->dist < v.dist;
    }
}Vertex;

Vertex vtxs[V];

bool Vertex::relax(int adj, struct Vertex &v) {
    if (this->dist + getAdjW(adj) < v.dist) {
        DEBUGCOUT("u.d: " << this->dist.dist << " + w(u,v): "<<getAdjW(adj).dist << " < " << adj << ".d: " << v.dist.dist)
        v.dist.dist = this->dist.dist + getAdjW(adj).dist;
        return true;
    } else {
        return false;
    }
}

void Vertex::all_relax() {
    AdjList p = this->head->next;
    while (p) {
        this->relax(p->adj, vtxs[V]);
        p = p->next;
    }
}

typedef struct Heap {
	int heapsize;
	int *a;
}Heap;

void Swap(struct Heap *h, int i, int j) {
    auto temp = h->a[i];
    h->a[i] = h->a[j];
    h->a[j] = temp;
    vtxs[h->a[i]].heap_index = i;
    vtxs[h->a[j]].heap_index = j;
}

void initHeap(struct Heap *h, int n) {
	h->a = (int *)malloc(sizeof(int) * (n+1));
	h->heapsize = 0;
}

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

int Cmp(int &a, int &b) {
    if (vtxs[a].dist < vtxs[b].dist) {
        return 1;
    } else if (vtxs[a].dist == vtxs[b].dist) {
        return 0;
    } else {
        return -1;
    }
}

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
        Swap(h, largest, i);
		maxHeapify(h, largest);
	}
}

void buildMaxHeap(struct Heap *h) {
	for (int i = h->heapsize/2; i > 0; i--) {
		maxHeapify(h, i);
	}
}

void heapSort(struct Heap *h) {
	buildMaxHeap(h);
	int len = h->heapsize;
	for (int i = 0; i < len; i++) {
        Swap(h, 1, len-i);
		h->heapsize--;
		maxHeapify(h, 1);
	}
}

int heapExtractMax(struct Heap *h) {
    if (h->heapsize < 1) {
        printf("heap empty, could not extract max");
        exit(0);
    }
	auto max = h->a[1];
	Swap(h, 1, h->heapsize);
	h->heapsize--;
	maxHeapify(h, 1);
	return max;
}

int heapEmpty(struct Heap *h) {
    return h->heapsize == 0;
}

int heapMaximun(struct Heap *h) {
	return h->a[1];
}

void heapIncreaseKey(struct Heap *h, int i, int key) {
    if (Cmp(h->a[i], h->a[i]) < 0) {
        printf("not larger key");
        exit(0);
    }
	h->a[i] = key;
	while (i > 1 && Cmp(h->a[parent(i)], h->a[i]) < 0) {
        DEBUGCOUT("Swap heap: " << parent(i) << " " << i)
        Swap(h, parent(i), i);
		i = parent(i);
	}
}

void maxHeapInsert(struct Heap *h, int key) {
	h->heapsize++;
	h->a[h->heapsize] = key;
	heapIncreaseKey(h, h->heapsize, key);
}

int main(void)
{
    Heap h;
    int n = 0, m = 0, s = 0, t = 0;
    scanf("%d%d%d%d", &n,&m,&s,&t);
    initHeap(&h, n);
    for (int i = 1; i <= n; i++) {
        vtxs[i].init();
        vtxs[i].heap_index = i;
        h.a[i] = i;
    }
    int u, v, w;
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &u, &v, &w);
        vtxs[u].insert(v, w);
    }
    vtxs[s].dist.dist = 0;
    h.heapsize = n;
    buildMaxHeap(&h);
    for (int i = 1; i <= h.heapsize; i++) {
        DEBUGCOUT("vtxs: " << h.a[i] << " dist: " << vtxs[h.a[i]].dist.dist)
    }
    while (!heapEmpty(&h)) {
        auto minVertex_index = heapExtractMax(&h);
        auto p = vtxs[minVertex_index].head->next;
        DEBUGCOUT("u: " << minVertex_index)
        while (p) {
            if (vtxs[minVertex_index].relax(p->adj, vtxs[p->adj])) {
                DEBUGCOUT("after relax " << minVertex_index << " to " << p->adj << " dist : " << vtxs[p->adj].dist.dist)
                DEBUGCOUT("before decrease key heap_index: " << vtxs[p->adj].heap_index)
                for (int i = 1; i <= h.heapsize; i++) {
                    DEBUGCOUT("vtxs: " << h.a[i] << " dist: " << vtxs[h.a[i]].dist.dist)
                    DEBUGCOUT("vtxs[" << h.a[i] << "]'s heap index" << vtxs[h.a[i]].heap_index)
                }
                heapIncreaseKey(&h, vtxs[p->adj].heap_index, p->adj);
                DEBUGCOUT("after decrease key heap_index: " << vtxs[p->adj].heap_index)
                for (int i = 1; i <= h.heapsize; i++) {
                    DEBUGCOUT("vtxs: " << h.a[i] << " dist: " << vtxs[h.a[i]].dist.dist)
                }
            }
            p = p->next;
        }
        DEBUGCOUT("adj visit complete")
    }
    printf("%d", vtxs[t].dist.dist);
    freeHeap(&h);
    for (int i = 0; i < n; i++) {
        auto p = vtxs[i].head;
        AdjList p_next;
        while (p) {
            p_next = p->next;
            free(p);
            p = p_next;
        }
    }
    return 0;
}

