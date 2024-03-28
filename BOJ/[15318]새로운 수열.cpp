#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <cstdio>
#include <cstdlib>
using namespace std;
int n;
int a[300000];
long long b[300000];

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    long long add = 0;
    int sign = 1;
    for (int i = 0; i < n; i++) {
        long long temp = sign * a[i];
        add += temp;
        b[0] += temp * (i + 1);
        sign = -sign;
    }
    int prev = (n & 1) ? 1 : -1;
    for (int i = 1; i < n; i++) {
        b[i] = -b[i - 1] + add;

        b[i] += a[i - 1] * n * prev;
        add = -add;
        if (prev == 1) {
            add += 2 * a[i - 1];
        }
    }
    
    for (int i = 0; i < n; i++) {
        printf("%lld ", b[i]);
    }
}