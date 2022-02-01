#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

#define NUMBER 100005
#define EDGE_NUMBER 1000005

using namespace std;

typedef vector<int> Set;

typedef vector<Set> Sets;

Sets sets;

typedef struct Node {
	bool isFree;
	bool isA;
	int belongSet;
}Node;

typedef struct Edge {
	int danger;
	int i;
	int j;
}Edge;

Node nodes[NUMBER];

vector<Edge> edges;

void initNode(int n);

void input(int m);

void ReverseIsA(int setNumer);

bool isConnected(int i, int j);

int minDanger(int m);

bool Cmp(const Edge &a, const Edge &b) {
	return a.danger > b.danger;
}


int main(void) {
	int n = 0, m = 0;
	scanf("%d%d", &n, &m);
	initNode(n);
	input(m);
	sort(edges.begin(), edges.end(), Cmp);
	printf("%d", minDanger(m));
	return 0;
}

void initNode(int n) {
	for (int i = 0; i <= n; i++) {
		nodes[i].isFree = true;
		nodes[i].belongSet = 0;
	}
}

void input(int m) {
	Edge temp;
	for (int i = 0; i < m; i++) {
		scanf("%d%d%d", &temp.i, &temp.j, &temp.danger);
		edges.push_back(temp);
	}
}

int minDanger(int m) {
	for (int k = 0; k < m; k++) {
		auto edge = edges[k];
		auto i = edge.i;
		auto j = edge.j;
		auto danger = edge.danger;
		if (i == j) return danger;
		else if (nodes[i].isFree && nodes[j].isFree) {
			auto len = sets.size();
			Set set;
			set.push_back(i);
			set.push_back(j);
			sets.push_back(set);
			nodes[i].belongSet = nodes[j].belongSet = len;
			nodes[i].isFree = nodes[j].isFree = false;
			nodes[i].isA = true;
			nodes[j].isA = false;
		} else if (nodes[i].isFree || nodes[j].isFree) {
			if (nodes[i].isFree) {
				auto belongSet = nodes[j].belongSet;
				nodes[i].isFree = false;
				nodes[i].isA = !nodes[j].isA;
				nodes[i].belongSet = belongSet;
				sets[belongSet].push_back(i);
			} else {
				auto belongSet = nodes[i].belongSet;
				nodes[j].isFree = false;
				nodes[j].isA = !nodes[i].isA;
				nodes[j].belongSet = belongSet;
				sets[belongSet].push_back(j);
			}
		} else {
			if (nodes[i].isA ^ nodes[j].isA) {
				auto jBelongSet = nodes[j].belongSet;
				for (auto v: sets[nodes[i].belongSet]) {
					nodes[v].belongSet = jBelongSet;
					sets[jBelongSet].push_back(v);
				}
			} else {
				if (nodes[i].belongSet == nodes[j].belongSet) {
					return danger;
				} else {
					auto jBelongSet = nodes[j].belongSet;
					ReverseIsA(nodes[i].belongSet);
					for (auto v: sets[nodes[i].belongSet]) {
						nodes[v].belongSet = jBelongSet;
						sets[jBelongSet].push_back(v);
					}
				}
			}
		}
	}
	return 0;
}

void ReverseIsA(int setNumer) {
	for (auto i: sets[setNumer]) {
		nodes[i].isA = !nodes[i].isA;
	}
}