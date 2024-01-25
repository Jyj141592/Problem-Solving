#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <utility>
#include <cstdlib>
using namespace std;
#define MOD 1000000007
int n, m, k;
int tree[2097153];
int entry = 1;

int partial(int left, int right) {
    if (left >= right) return 1;
    int l = 0;
    int r = entry;
    int mid;
    int idx = 1;
    while (l != left) {
        mid = (l + r) >> 1;
        if (mid > left) {
            r = mid;
            idx = idx << 1;
        }
        else {
            l = mid;
            idx = (idx << 1) + 1;
        }
    }
    while (r > right) {
        r = (l + r) >> 1;
        idx = idx << 1;
    }


    int ret = tree[idx];
    ret = ((long long)ret * partial(r, right)) % MOD;
    return ret;
}

int main()
{
    scanf("%d %d %d", &n, &m, &k);
    while (entry < n) {
        entry *= 2;
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &tree[entry + i]);
    }
    for (int i = n + entry; i < 2 * entry; i++) {
        tree[i] = 1;
    }
    for (int i = entry - 1; i > 0; i--) {
        tree[i] = ((long long)tree[i * 2] * tree[i * 2 + 1]) % MOD;
    }
    for (int i = 0; i < m + k; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        if (a == 1) {
            int idx = entry + b - 1;
            tree[idx] = c;
            idx = idx >> 1;
            while (idx > 0) {
                tree[idx] = ((long long)tree[idx * 2] * tree[idx * 2 + 1]) % MOD;
                idx = idx >> 1;
            }
        }
        else {
            printf("%d\n", partial(b - 1, c));
        }
    }
}

