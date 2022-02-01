#include <stdio.h>

#define N_MAX 2000

char matrix[N_MAX][N_MAX] = {0};

char damaged[N_MAX][N_MAX] = {0};

int main(void)
{
    int n = 0, m = 0;
    scanf("%d%d", &n, &m);
    int i = 0, j = 0;
    int squareNum = 0;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &matrix[i][j]);
            damaged[i][j] = matrix[i][j];
            if (matrix[i][j] == 0)
                squareNum++;
        }
    }
    int level = 2;
    int maxLevel = (n < m)?n:m;
    for (; level <= maxLevel; level++) {
        char newSquare = 0;
        for (i = 0; i <= n-level; i++) {
            for (j = 0; j <= m-level; j++) {
                if (damaged[i][j]) {
                    continue;
                } else {
                    int p = i;
                    int q = j+level-1;
                    char isDamage = 0;
                    for (; p < i+level-1; p++) {
                        if (matrix[p][q]) {
                            damaged[i][j] = 1;
                            j = q;
                            isDamage = 1;
                            break;
                        }
                    }
                    if (isDamage) {
                        continue;
                    }
                    q = j;
                    for (; q <= j+level-1; q++) {
                        if (matrix[p][q]) {
                            damaged[i][j] = 1;
                            isDamage = 1;
                            break;
                        }
                    }
                    if (isDamage) {
                        continue;
                    }
                    newSquare = 1;
                    squareNum++;
                }
            }
        }
        if (!newSquare) {
            break;
        }
    }
    printf("%d", squareNum);
    return 0;
}