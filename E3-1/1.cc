#include <stdio.h>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

#define LIMIT 10002

typedef struct Point {
    int y;
    int maxS;
}Point;


map<int, vector<Point>> columns;

int SColumn[LIMIT] = {0};

void insert(int x, int y);

bool Cmp(const Point &a, const Point &b) {
    return a.y < b.y;
}

int main(void)
{
    int n = 0;
    scanf("%d", &n);
    int x, y;
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &x, &y);
        columns[x].push_back({y, 0});
    }
    int maxS = 0;
    for (auto iter = columns.begin(); iter != columns.end(); iter++) {
        for (auto v: iter->second) {
            v.maxS = 0;
            for (auto y = 0; y <= v.y; y++) {
                if (SColumn[y] > v.maxS) {
                    v.maxS = SColumn[y];
                }
            }
            v.maxS++;
            if (v.maxS > maxS)
                maxS = v.maxS;
            if (v.maxS > SColumn[v.y]) {
                SColumn[v.y] = v.maxS;
            }
        }
    }
    printf("%d", maxS);
    return 0;
}
