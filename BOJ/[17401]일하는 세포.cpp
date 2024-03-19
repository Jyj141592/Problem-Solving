#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdio>
// 1036
using namespace std;
#define MOD 1000000007
int t, n, d;
int map[100][20][20];
int mul[20][20];
int rest[20][20];
int result[20][20];

void matrix_mul(int dest[20][20], int src[20][20]) {
    int temp[20][20];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            temp[i][j] = dest[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            long long val = 0;
            for (int k = 0; k < n; k++) {
                val += (long long)temp[i][k] * src[k][j];
                val = val % MOD;
            }
            dest[i][j] = val;
        }
    }
}


int main()
{
    scanf("%d %d %d", &t, &n, &d);
    for (int i = 0; i < n; i++) {
        result[i][i] = 1;
        mul[i][i] = 1;
    }

    for (int i = 0; i < t; i++) {
        int e, a, b, c;
        scanf("%d", &e);
        for (int j = 0; j < e; j++) {
            scanf("%d %d %d", &a, &b, &c);
            map[i][a - 1][b - 1] = c;
        }
    }
    if (t > d) {
        for (int i = 0; i < d; i++) {
            matrix_mul(result, map[i]);
        }
    }
    else {
        int r = d % t;
        for (int i = 0; i < t; i++) {
            if (r == i) {
                for (int j = 0; j < n; j++) {
                    for (int k = 0; k < n; k++) {
                        rest[j][k] = mul[j][k];
                    }
                }
            }
            matrix_mul(mul, map[i]);
        }
        int q = d / t;
        while (q > 0) {
            if (q & 1) {
                matrix_mul(result, mul);
            }
            int temp[20][20];
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    temp[i][j] = mul[i][j];
                }
            }
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    long long val = 0;
                    for (int k = 0; k < n; k++) {
                        val += (long long)temp[i][k] * temp[k][j];
                        val = val % MOD;
                    }
                    mul[i][j] = val;
                }
            }
            q = q >> 1;
        }
        if (r > 0) {
            matrix_mul(result, rest);
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
}