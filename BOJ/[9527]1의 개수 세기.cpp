#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>

using namespace std;
long long a, b;
int aBin[65];
int aDigit = 0;
int bBin[65];
int bDigit = 0;
unsigned long long cnt[65];
unsigned long long aCnt = 0;
unsigned long long bCnt = 0;

void toBinary(unsigned long long n, int bin[], int& digit) {
    digit = 0;
    while (n > 0) {
        bin[digit++] = n & 1;
        n = n >> 1;
    }
}

unsigned long long one_cnt(unsigned long long n, int bin[], int digit) {
    if (digit == 0) return 0;
    unsigned long long next = n - (((unsigned long long)1) << (digit - 1));
    unsigned long long ret = cnt[digit - 1] + 1 + next;
    int nextDgt = 0;
    for (int i = digit - 2; i >= 0; i--) {
        if (bin[i] == 1) {
            nextDgt = i + 1;
            break;
        }
    }
    ret += one_cnt(next, bin, nextDgt);
    return ret;
}

int main()
{
    cin >> b >> a;
    unsigned long long temp = 2;
    cnt[0] = 0;
    cnt[1] = 1;
    for (int i = 2; i <= 64; i++) {
        cnt[i] = cnt[i - 1] * 2 + temp;
        temp = temp << 1;
    }
    toBinary(a, aBin, aDigit);
    toBinary(b - 1, bBin, bDigit);
    aCnt = one_cnt(a, aBin, aDigit);
    bCnt = one_cnt(b - 1, bBin, bDigit);
    printf("%llu", aCnt - bCnt);
}

