#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <cstdio>
#include <cstdlib>
using namespace std;
#define MOD 1234567891
int n, l;
int num[50];
// 0 -> 7...7, 1 -> 7...4, 2 -> 4...7, 3 -> 4...4
int type[4];
int mul[2][2];
int result[2][2];

int main()
{
    scanf("%d%d", &n, &l);
    for (int i = 0; i < n; i++) {
        scanf("%d", &num[i]);
    }
    for (int i = 0; i < n; i++) {
        bool pass = false;
        for (int j = i + 1; j < n; j++) {
            if (num[j] == num[i]) {
                pass = true;
                break;
            }
        }
        if (pass) continue;
        int t = num[i];
        int r = t % 10;
        t = t / 10;
        int idx = 0;
        if (r != 4 && r != 7) continue;
        if (r == 4) idx += 1;
        while (t > 0) {
            r = t % 10;
            if (r != 4 && r != 7) {
                pass = true;
                break;
            }
            t = t / 10;
        }
        if (pass) continue;
        if (r == 4) idx += 2;
        type[idx]++;
    }

    result[0][0] = result[1][1] = 1;
    mul[0][0] = type[0];
    mul[0][1] = type[2];
    mul[1][0] = type[1];
    mul[1][1] = type[3];

    int temp[2][2];
    while (l > 0) {
        if (l & 1) {
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 2; j++) {
                    temp[i][j] = result[i][j];
                }
            }
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 2; j++) {
                    long long t = 0;
                    for (int k = 0; k < 2; k++) {
                        t += ((long long)temp[i][k] * mul[k][j]) % MOD;
                        t = t % MOD;
                    }
                    result[i][j] = t;
                }
            }
        }
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                temp[i][j] = mul[i][j];
            }
        }
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                long long t = 0;
                for (int k = 0; k < 2; k++) {
                    t += ((long long)temp[i][k] * temp[k][j]) % MOD;
                    t = t % MOD;
                }
                mul[i][j] = t;
            }
        }
        l = l >> 1;
    }
    long long t = result[0][0] + result[0][1] + result[1][0] + result[1][1];
    printf("%d", t % MOD);
}