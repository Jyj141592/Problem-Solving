#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;
int n, m;
int entry;
int tree[524289];
int dvd[100001];

int pSum(int s) {
    if (s >= entry) return 0;
    int idx = 1;
    int left = 0, right = entry;
    while (s != left) {
        int mid = (left + right) >> 1;
        if (s >= mid) {
            left = mid;
            idx = (idx << 1) + 1;
        }
        else {
            right = mid;
            idx = idx << 1;
        }

    }
    return tree[idx] + pSum(right);
}

void update(int num, int value) {
    int idx = entry + num;
    while(idx > 0) {
        tree[idx] += value;
        idx = idx >> 1;
    }
}

int main()
{
    int tc;
    scanf("%d", &tc);
    for (int T = 0; T < tc; T++) {
        scanf("%d %d", &n, &m);
        entry = 1;
        while (entry < m + n) {
            entry = entry << 1;
        }
        for (int i = 1; i <= n; i++) {
            dvd[i] = n - i;
        }
        for (int i = 0; i < entry; i++) {
            if (i < n) {
                tree[entry + i] = 1;
            }
            else tree[entry + i] = 0;
        }
        for (int i = entry - 1; i > 0; i--) {
            int child = i << 1;
            tree[i] = tree[child] + tree[child + 1];
        }
        for (int i = 0; i < m; i++) {
            int num;
            scanf("%d", &num);
            printf("%d ", pSum(dvd[num] + 1));
            update(dvd[num], -1);
            dvd[num] = n + i;
            update(n + i, 1);
        }
        printf("\n");
    }
}