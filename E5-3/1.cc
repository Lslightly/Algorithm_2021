#include <stdio.h>
#include <stdlib.h>
#include <queue>
using namespace std;

#define V 501
#define E 20001

#ifdef DEBUG
#include <iostream>
#define DEBUGCOUT(x) cout << x << std::endl;
#define DEBUGUSE(x) x;
#else
#define DEBUGCOUT(x) ;
#define DEBUGUSE(x) ;
#endif

int f[V][V] = {0};
int c[V][V] = {0};
int cf[V][V] = {0};
bool visited[V] = {false};
int parent[V] = {0};

void update_flow(int u, int v, int new_flow) {
    DEBUGCOUT("u: " << u << " v: " << v << " old flow: " << f[u][v] << " new flow: " << new_flow)
    int tmp = new_flow - f[u][v];
    cf[u][v] -= tmp;
    cf[v][u] += tmp;
    f[u][v] += tmp;
}

//  m edges
void init(int m) {
    int u, v, l;
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &u, &v, &l);
        c[u][v] += l;
        cf[u][v] += l;
    }
}

int findCFPath(int s, int t, int n) {
    queue<int> path_queue;
    for (int i = 1; i <= n; i++) {
        visited[i] = false;
    }
    visited[s] = true;
    path_queue.push(s);
    while (!path_queue.empty()) {
        int tmp = path_queue.front();
        path_queue.pop();
        for (int i = 1; i <= n; i++) {
            if (visited[i] || cf[tmp][i] == 0) {
                continue;
            } else {
                parent[i] = tmp;
                if (i == t) {
                    int len = 1;
                    while (parent[i] != s) {
                        len++;
                        i = parent[i];
                    }
                    return len;
                } else {
                    visited[i] = true;
                    path_queue.push(i);
                }
            }
        }
    }
    return -1;
}

int minCFinPath(int len, int t) {
    int min = cf[parent[t]][t];
    t = parent[t];
    for (int i = 1; i < len; i++) {
        if (cf[parent[t]][t] < min) {
            min = cf[parent[t]][t];
        }
        t = parent[t];
    }
    return min;
}

void FF(int s, int t, int n) {
    int len = findCFPath(s, t, n);
    while (len != -1) {
        int min_cf = minCFinPath(len, t);
        DEBUGUSE(
            printf("path from %d to %d\n", s, t);
            auto tmp = t;
            for (int i = 0; i < len; i++) {
                printf("%d ", t);
            }
            tmp = parent[tmp];
            putchar('\n');
        )
        int tmp = t;
        for (int i = 0; i < len; i++) {
            if (c[parent[tmp]][tmp] > 0) {
                update_flow(parent[tmp], tmp, f[parent[tmp]][tmp]+min_cf);
            } else {
                update_flow(parent[tmp], tmp, f[parent[tmp]][tmp]-min_cf);
            }
            tmp = parent[tmp];
        }
        len = findCFPath(s, t, n);
    }
}

int main(void)
{
    int n, m, s, t;
    scanf("%d%d%d%d", &n, &m, &s, &t);
    init(m);
    FF(s, t, n);
    int result = 0;
    for (int i = 1; i <= n; i++) {
        result += f[i][t];
    }
    printf("%d", result);
    return 0;
}