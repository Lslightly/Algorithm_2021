#include <stdio.h>

#define NUMBER 201

int Sum[NUMBER][NUMBER] = {0};
int Time[NUMBER][NUMBER] = {0};

int main(void)
{
    int n = 0;
    scanf("%d", &n);
    int a[NUMBER] = {0};
    for (int i = 0; i < n; i++) {
        scanf("%d", &Sum[i][i]);
    }
    for (int inter = 1; inter <= n-1; inter++) {
        for (int left = 0; left < n-inter; left++) {
            int right = left+inter;
            int pivot = left+1;
            Sum[left][right] = Sum[left][pivot-1]+Sum[pivot][right];
            int minTime = Time[left][pivot-1]+Time[pivot][right];
            for (pivot+=1; pivot <= right; pivot++) {
                int temp = Time[left][pivot-1]+Time[pivot][right];
                if (temp < minTime) {
                    minTime = temp;
                }
            }
            Time[left][right] = minTime+Sum[left][right];
        }
    }
    printf("%d", Time[0][n-1]);
    return 0;
}