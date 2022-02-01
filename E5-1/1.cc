#include <stdio.h>
#include <stdlib.h>
#include <vector>

#define V 100001
#define E 1000001
#define MAX_WEIGHT 1000

#ifdef DEBUG
#include <iostream>
#define DEBUGPRINT(x) std::cout << x << std::endl;
#else
#define DEBUGPRINT(x) ;
#endif

using namespace std;

typedef vector<int> Set;
vector<Set> sets;


typedef struct Edge {
    int u, v;
    int w;
}Edge;


int belong_set[V];

vector<vector<int>> w_bucket;

void initialize(int n) {
    Set zero;
    sets.push_back(zero);
    for (int i = 1; i <= n; i++) {
        belong_set[i] = i;
        Set tmp;
        tmp.push_back(i);
        sets.push_back(tmp);
    }
    for (int i = 0; i <= MAX_WEIGHT; i++) {
        w_bucket.push_back({});
    }
}

int BelongSet(int set) {
    if (belong_set[set] != set) {
        belong_set[set] = BelongSet(belong_set[set]);
    }
    return belong_set[set];
}

void UnoinSet(int i, int j) {
    belong_set[i] = BelongSet(j);
}

inline int EdgeNum(int cur_w, int cur_i) {
    return w_bucket[cur_w][cur_i];
}

int main(void)
{
    int n = 0, m = 0;
    scanf("%d%d", &n, &m);
    initialize(n);
    Edge *edges = (Edge*)malloc(sizeof(Edge)*m);
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &edges[i].u, &edges[i].v, &edges[i].w);
        w_bucket[edges[i].w].push_back(i);
    }
    int valid_edge_count = 0;
    int cur_w = 0;
    int cost = 0;
    DEBUGPRINT("output:")
    while (valid_edge_count < n-1) {
        int len = w_bucket[cur_w].size();
        for (int i = 0; i < len; i++) {
            int edge_num = EdgeNum(cur_w, i);
            int u = edges[edge_num].u;
            int v = edges[edge_num].v;
            int edge_w = edges[edge_num].w;
            int u_set = BelongSet(u);
            int v_set = BelongSet(v);
            if (u_set == v_set) {
                continue;
            } else {
                DEBUGPRINT("u, v, w: " << u << " " << v << " " << edge_w)
                valid_edge_count++;
                cost += edge_w;
                DEBUGPRINT("before union, u's belong set: " << belong_set[u] << " v's belong set: " << belong_set[v])
                UnoinSet(u_set, v_set);
                DEBUGPRINT("after union, u's belong set: " << belong_set[u] << " v's belong set: " << belong_set[v])
            }
        }
        cur_w++;
    }
    free(edges);
    printf("%d", cost);
    return 0;
}
