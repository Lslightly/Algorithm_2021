#include <stdio.h>
#include <stdlib.h>
#include <vector>
using namespace std;

#define V 5001

#ifdef DEBUG
#include <iostream>
#define DEBUGCOUT(x) cout << x << endl;
#define DEBUGUSE(x) x
#else
#define DEBUGCOUT(x) ;
#define DEBUGUSE(x) ;
#endif

enum {
    White,
    Grey,
    Black
};

typedef struct AdjNode {
    int adj;
    struct AdjNode *next;
}AdjNode, *AdjList;

typedef struct Vertex {
    int id;
    int color;
    int f;
    int parent;
    int belong_scc;
    AdjList head;
    AdjList tail;
}Vertex;

typedef struct SCCAdjNode {
    int adj;
    struct SCCAdjNode *next;
}SCCAdjNode, *SCCAdjList;

typedef struct SCCVertex {
    vector<int> vertexs;
    int dom;
    SCCAdjList head;
    SCCAdjList tail;
}SCCVertex;

Vertex G[V];
Vertex GT[V];
int num_scc = 0;
SCCVertex SCCG[V];
int time = 0;

void insertEdge(Vertex vtxs[], int u, int v) {
    AdjList tmp = (AdjList)malloc(sizeof(AdjNode));
    tmp->next = nullptr;
    tmp->adj = v;
    vtxs[u].tail->next = tmp;
    vtxs[u].tail = tmp;
}

void insertSCCEdge(int u, int v) {
    SCCAdjList p = SCCG[u].head;
    while (p && p->next) {
        if (p->adj == v) {
            return;
        } else {
            p = p->next;
        }
    }
    if (p->adj == v) {
        return;
    }
    SCCAdjList tmp = (SCCAdjList)malloc(sizeof(SCCAdjNode));
    tmp->adj = v;
    tmp->next = nullptr;
    p->next = tmp;
    SCCG[u].tail = tmp;
}

void init_vtxs(Vertex vtxs[], int n, int m) {
    for (int i = 1; i <= n; i++) {
        vtxs[i].color = White;
        vtxs[i].head = (AdjList)malloc(sizeof(AdjNode));
        vtxs[i].head->next = nullptr;
        vtxs[i].head->adj = -1;
        vtxs[i].tail = vtxs[i].head;
        vtxs[i].f = 0;
        vtxs[i].id = i;
    }
}

void freeVertex(Vertex vtxs[], int u) {
    AdjList p_next;
    AdjList p = vtxs[u].head;
    while (p) {
        p_next = p->next;
        free(p);
        p = p_next;
    }
}

void free_vtxs(Vertex vtxs[], int n) {
    for (int i = 1; i <= n; i++) {
        freeVertex(vtxs, i);
    }
}

void DFS(Vertex vtxs[], int u) {
    time++;
    vtxs[u].color = Grey;
    AdjList p = vtxs[u].head->next;
    while (p) {
        int adj = p->adj;
        if (vtxs[adj].color == White) {
            vtxs[adj].parent = u;
            DFS(vtxs, adj);
        }
        p = p->next;
    }
    vtxs[u].color = Black;
    time++;
    vtxs[u].f = time;
}

void DFS_get_SCC(vector<int> &scc, Vertex vtxs[], int u) {
    vtxs[u].color = Grey;
    scc.push_back(vtxs[u].id);
    AdjList p = vtxs[u].head->next;
    while (p) {
        int adj = p->adj;
        if (vtxs[adj].color == White) {
            vtxs[adj].parent = u;
            DFS_get_SCC(scc, vtxs, adj);
        }
        p = p->next;
    }
    vtxs[u].color = Black;
}

int finish_time_cmp(const void *a, const void *b) {
    return ((Vertex*)b)->f - ((Vertex*)a)->f;
}

void SCC(int n) {
    for (int i = 1; i <= n; i++) {
        if (G[i].color == White) {
            DFS(G, i);
        }
    }
    for (int i = 1; i <= n; i++) {
        DEBUGCOUT(G[i].id << "'s finish time: " << G[i].f)
        DEBUGCOUT((GT[i].color == White))
        GT[i].f = G[i].f;
    }
    qsort(GT+1, n, sizeof(Vertex), finish_time_cmp);
    DEBUGUSE(
        printf("after sort finish time\n");
        for (int i = 1; i <= n; i++) {
            DEBUGCOUT(GT[i].id << "'s finish time: " << GT[i].f)
        }
    )
    vector<int> scc;
    for (int i = 1; i <= n; i++) {
        scc.clear();
        DEBUGCOUT(GT[i].id << " " << (GT[i].color == White))
        if (GT[i].color == White) {
            DFS_get_SCC(scc, GT, i);
            SCCG[num_scc].vertexs = scc;
            SCCG[num_scc].head = (SCCAdjList)malloc(sizeof(SCCAdjNode));
            SCCG[num_scc].head->next = nullptr;
            SCCG[num_scc].head->adj = -1;
            SCCG[num_scc].tail = SCCG[num_scc].head;
            SCCG[num_scc].dom = -1;
            num_scc++;
        }
    }
    DEBUGCOUT("SCC:")
    for (int i = 0; i < num_scc; i++) {
        DEBUGCOUT("scc " << i)
        for (int j = 0; j < SCCG[i].vertexs.size(); j++) {
            DEBUGUSE(
                cout << SCCG[i].vertexs[j] << " ";
            )
            G[SCCG[i].vertexs[j]].belong_scc = i;
        }
        DEBUGCOUT("")
    }
}

void buildSCCG(int n) {
    for (int i = 1; i <= n; i++) {
        AdjList p = G[i].head->next;
        int iscc = G[i].belong_scc;
        DEBUGCOUT(i << "'s belong_scc: " << iscc)
        while (p) {
            int adj = p->adj;
            int adjscc = G[adj].belong_scc;
            DEBUGCOUT("adj:" << adj << "'s belong_scc: " << adjscc)
            if (iscc != adjscc) {
                insertSCCEdge(iscc, adjscc);
            }
            p = p->next;
        }
    }
}

void DFSSCCG(int i) {
    SCCAdjList p = SCCG[i].head->next;
    DEBUGCOUT("SCC " << i << "'s adj:")
    SCCG[i].dom = 0;
    while (p) {
        int adj = p->adj;
        DEBUGUSE(cout << adj << " ";)
        DEBUGCOUT("")
        if (SCCG[adj].dom == -1) {
            DFSSCCG(adj);
        }
        SCCG[i].dom += SCCG[adj].dom;
        p = p->next;
    }
    SCCG[i].dom += SCCG[i].vertexs.size();
}

int main(void)
{
    int n, m;
    scanf("%d%d", &n, &m);
    init_vtxs(G, n, m);
    init_vtxs(GT, n, m);
    int u, v;
    for (int i; i < m; i++) {
        scanf("%d%d", &u, &v);
        insertEdge(G, u, v);
        DEBUGCOUT("insert G com " << u << " " << v)
        insertEdge(GT, v, u);
        DEBUGCOUT("insert GT com " << u << " " << v)
    }
    SCC(n);
    DEBUGCOUT("build SCCG")
    buildSCCG(n);
    DEBUGCOUT("build SCCG com")
    for (int i = 0; i < num_scc; i++) {
        if (SCCG[i].dom == -1) {
            DFSSCCG(i);
        }
    }
    int result = 0;
    for (int i = 0; i < num_scc; i++) {
        if (SCCG[i].dom > result) {
            result = SCCG[i].dom;
        }
    }
    printf("%d", result);
    free_vtxs(G, n);
    free_vtxs(GT, n);
    return 0;
}