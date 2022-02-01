#include <stdio.h>
#include <stdlib.h>

#define MAX_CLOTHES 200000

int x[MAX_CLOTHES] = {0};
int dist[MAX_CLOTHES] = {0};

int less_cmp(const void *a, const void * b) {
    return *((int*)a)-*((int*)b);
}

bool satisfy(int required_left_inters, int min_d, int inters) {
    int i = 0;
    int count = 0;
    int sum = 0;
    // printf("satisfy arg: %d %d %d\n", required_left_inters, min_d, inters);
    while (i < inters) {
        sum += dist[i];
        // printf("sum: %d\n", sum);
        if (sum >= min_d) {
            count++;
            if (count >= required_left_inters) {
                return true;
            }
            sum = 0;
        }
        i++;
    }
    return false;
}

int main(void)
{
    int n = 0, m = 0;
    int result = 0;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &x[i]);
    }
    qsort(x, n, sizeof(int), less_cmp);
    // printf("dist: ");
    for (int i = 0; i < n-1; i++) {
        dist[i] = x[i+1] - x[i];
        // printf("%d ", dist[i]);
    }
    // putchar('\n');
    int right = x[n-1]-x[0];
    int left = 1;
    while (left <= right) {
        int mid = (left + right)/2;
        if (satisfy(n-m-1, mid, n-1)) {
            // printf("%d satisfy, left %d, right %d\n", mid, left, right);
            result = mid;
            left = mid+1;
        } else {
            // printf("%d not satisfy, left %d, right %d\n", mid, left, right);
            right = mid-1;
        }
    }
    printf("%d", result);
    return 0;
}