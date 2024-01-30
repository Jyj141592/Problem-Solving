#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <utility>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits.h>
using namespace std;
int n;
int tree[2097152];
#define INDEX(n) (1048575 + n)
#define ENTRY(i) (i - 1048575)
void add(int n, int value) {
    int idx = INDEX(n);
    while (idx > 0) {
        tree[idx] += value;
        idx = idx >> 1;
    }
}

int search(int node, int rank) {
    if (node > INDEX(0)) {
        int ret = ENTRY(node);
        add(ret, -1);
        return ret;
    }
    int child = node << 1;
    if (tree[child] >= rank) {
        return search(child, rank);
    }
    else {
        return search(child + 1, rank - tree[child]);
    }
}

int main()
{
    scanf("%d", &n);
    for (int T = 0; T < n; T++) {
        int a, b, c;
        scanf("%d", &a);
        if (a == 1) {
            scanf("%d", &b);
            printf("%d\n", search(1, b));
        }
        else {
            scanf("%d %d", &b, &c);
            add(b, c);
        }
    }
}