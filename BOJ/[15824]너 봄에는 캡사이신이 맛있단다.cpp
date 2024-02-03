#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;
#define MOD 1000000007
int n;
int arr[300000];

int compare(const void* a, const void* b) {
    int* f = (int*)a;
    int* s = (int*)b;
    if (*f > *s) return 1;
    else if (*f < *s) return -1;
    else return 0;
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    qsort(arr, n, sizeof(int), compare);
    long long sum = 0;
    long long cnt = 1;
    long long prev = 0;
    for (int i = 1; i < n; i++) {
        long long diff = arr[i] - arr[i - 1];
        long long cur = (diff * (cnt - 1)) % MOD;
        cur = (cur + prev) % MOD;
        cur = (cur << 1) % MOD;
        cur = (cur + diff) % MOD;
        sum = (sum + cur) % MOD;
        prev = cur;
        cnt = (cnt << 1) % MOD;
    }
    printf("%lld", sum);
}