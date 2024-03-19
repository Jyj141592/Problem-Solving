#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdio>
// 1036
using namespace std;
#define MOD 1000000007
int n;
int m[8][8] = { {1,0,0,0,0,0,0,0},
    {0,1,0,0,0,0,0,0},
    {0,0,1,0,0,0,0,0},
    {0,0,0,1,0,0,0,0},
    {0,0,0,0,1,0,0,0},
    {0,0,0,0,0,1,0,0},
    {0,0,0,0,0,0,1,0},
    {0,0,0,0,0,0,0,1} };
int mul[8][8] = {
    {0,1,1,0,0,0,0,0},
    {1,0,1,1,0,0,0,0},
    {1,1,0,1,1,0,0,0},
    {0,1,1,0,1,1,0,0},
    {0,0,1,1,0,1,0,1},
    {0,0,0,1,1,0,1,0},
    {0,0,0,0,0,1,0,1},
    {0,0,0,0,1,0,1,0}
};

int main()
{
    scanf("%d", &n);
    int temp[8][8];
    while (n > 0) {
        if (n & 1) {
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    temp[i][j] = m[i][j];
                }
            }
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    long long val = 0;
                    for (int k = 0; k < 8; k++) {
                        val += (long long)temp[i][k] * mul[k][j];
                        val = val % MOD;
                    }
                    m[i][j] = val;
                }
            }
        }
        n = n >> 1;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                temp[i][j] = mul[i][j];
            }
        }
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                long long val = 0;
                for (int k = 0; k < 8; k++) {
                    val += (long long)temp[i][k] * temp[k][j];
                    val = val % MOD;
                }
                mul[i][j] = val;
            }
        }
    }
    printf("%d", m[0][0]);
}