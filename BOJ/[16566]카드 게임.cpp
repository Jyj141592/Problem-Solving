#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <utility>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
int n, m, k;
bool tree[8388608];
int result[10000];
int entry;

int main()
{
    scanf("%d %d %d", &n, &m, &k);
    entry = 1;
    while (entry < n) {
        entry *= 2;
    }
    for (int i = 0; i < m; i++) {
        int num;
        scanf("%d", &num);
        tree[entry + num - 1] = true;
    }
    for (int i = entry - 1; i > 0; i--) {
        int child = i * 2;
        tree[i] = tree[child] || tree[child + 1];
    }
    for (int i = 0; i < k; i++) {
        int num;
        scanf("%d", &num);
        num += entry;
        while (!tree[num]) {
            if (num & 1) {
                num++;
            }
            else {
                num = num >> 1;
            }
        }
        while (num < entry) {
            int child = num * 2;
            if (tree[child]) num = child;
            else num = child + 1;
        }
        //printf("%d\n", num - entry + 1);
        result[i] = num - entry + 1;
        tree[num] = false;
        num = num >> 1;
        while (num > 0) {
            int child = num * 2;
            tree[num] = tree[child] || tree[child + 1];
            if (tree[num]) break;
            else num = num >> 1;
        }
    }
    for (int i = 0; i < k; i++) {
        printf("%d\n", result[i]);
    }
}