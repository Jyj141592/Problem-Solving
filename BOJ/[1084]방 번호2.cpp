#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <cstdio>
#include <cstdlib>
using namespace std;
int n;
long long m;
long long price[10];
int fResult[50];
int sResult[50];

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &price[i]);
    }
    scanf("%lld", &m);
    int base = 0;
    long long minPrice = price[0];
    bool isZero = true;
    for (int i = 1; i < n; i++) {
        if (price[i] <= minPrice) {
            minPrice = price[i];
            base = i;
        }
        if (price[i] <= m) isZero = false;
    }
    if (m < minPrice) {
        printf("%d\n\n\n", 0);
        return 0;
    }
    if (isZero) {
        printf("%d\n%d\n%d\n", 1, 0, 0);
        return 0;
    }
    long long digit = m / minPrice;
    long long rest = m % minPrice;
    for (int i = 0; i < 50; i++) {
        fResult[i] = sResult[i] = base;
    }
    long long pos = 0;
    for (int i = n - 1; i > base && pos < digit; i--) {
        if(rest >= price[i] - minPrice){
            long long num = rest / (price[i] - minPrice);

            for (int j = 0; j < num && pos + j < 50; j++) {
                fResult[j + pos] = i;
            }
            if (digit > 50) {
                if (pos + num > digit - 50) {
                    for (int j = max((long long) 0, pos - (digit - 50)); j + digit - 50 < digit && j + digit - 50 < pos + num; j++) {
                        sResult[j] = i;
                    }
                }
            }

            rest = rest % (price[i] - minPrice);
            pos += num;
        }
    }
    if (fResult[0] == 0) {
        int minNum = 1;
        long long minLoss = price[1] / minPrice;
        if (rest < (price[1] % minPrice)) minLoss++;
        for (int i = 2; i < n; i++) {
            long long loss = price[i] / minPrice;
            if (rest < (price[i] % minPrice)) loss++;
            if (loss <= minLoss) {
                minLoss = loss;
                minNum = i;
            }
        }
        digit -= minLoss;
        fResult[0] = minNum;
        digit++;
    }

    printf("%lld\n", digit);
    if (digit <= 50) {
        for (int i = 0; i < digit; i++) {
            printf("%d", fResult[i]);
        }
        printf("\n");
        for (int i = 0; i < digit; i++) {
            printf("%d", fResult[i]);
        }
        printf("\n");
    }
    else {
        for (int i = 0; i < 50; i++) {
            printf("%d", fResult[i]);
        }
        printf("\n");
        for (int i = 0; i < 50; i++) {
            printf("%d", sResult[i]);
        }
        printf("\n");
    }
}