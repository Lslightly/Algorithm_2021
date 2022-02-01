#include <stdio.h>
#include <stdlib.h>

#define MAX_VILLAGES 100000

int villages[MAX_VILLAGES];

int cmp(const void *a, const void *b) {
    return *((int*)a) - *((int *)b);
}

int main(void)
{
    int r = 0, n = 0;
    scanf("%d%d", &n, &r);
    for (int i = 0; i < n; i++) {
        scanf("%d", &villages[i]);
    }
    qsort(villages, n, sizeof(int), cmp);
    int count = 0;
    int curVillageIndex = 0;
    while (curVillageIndex < n) {
        int farthest = villages[curVillageIndex]+r;
        while (curVillageIndex < n && villages[curVillageIndex] <= farthest) {
            curVillageIndex++;
        }
        count++;
        if (curVillageIndex >= n) {
            break;
        } else {
            farthest = villages[curVillageIndex-1]+r;
            while (curVillageIndex < n && villages[curVillageIndex] <= farthest) {
                curVillageIndex++;
            }
            if (curVillageIndex >= n) {
                break;
            }
        }
    }
    printf("%d", count);
    return 0;
}