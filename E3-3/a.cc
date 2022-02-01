#include <stdio.h>

#define N_MAX 201
#define W_MAX 10001
#define WI_MAX 1001
#define VI_MAX 1001
#define NUMI_MAX 10001

int V[N_MAX][W_MAX] = {0};
int w[WI_MAX] = {0};
int v[VI_MAX] = {0};
int num[NUMI_MAX] = {0};

int main(void)
{
    int n = 0, W = 0;
    scanf("%d%d", &n, &W);
    int i =0;
    {
        scanf("%d%d%d", &w[i], &v[i], &num[i]);
        for (int jw = 0; jw <= W; jw++) {
            int maxNum = (jw/w[i] > num[i])?num[i]:jw/w[i];
            V[i][jw] = maxNum * v[i];
        }
    }

    int result = 0;
    for (i = 1; i < n; i++) {
        scanf("%d%d%d", &w[i], &v[i], &num[i]);
        for (int jw = 0; jw <= W; jw++) {
            int maxNum = (jw/w[i] > num[i])?num[i]:jw/w[i];
            int maxV = V[i-1][jw];
            for (int k = 1; k <= maxNum; k++) {
                int temp = V[i-1][jw-k*w[i]]+k*v[i];
                if (temp > maxV)
                    maxV = temp;
            }
            V[i][jw] = maxV;
            if (maxV > result)
                result = maxV;
        }
    }
    printf("%d", result);
    return 0;
}
