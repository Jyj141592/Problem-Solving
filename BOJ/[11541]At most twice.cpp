#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <cstdio>
#include <cstdlib>
using namespace std;
long long u;
int n[19];
int digit = 0;
int result[19];
int usage[10];


int main()
{
    scanf("%lld", &u);
    while (u > 0) {
         n[digit++] = u % 10;
         u = u / 10;
    }
    bool small = false;
    for (int i = digit - 1; i >= 0; i--) {
        if (small) {
            for (int j = 9; j >= 0; j--) {
                if (usage[j] < 2) {
                    result[i] = j;
                    usage[j]++;
                    break;
                }
            }
        }
        else {
            int num = n[i];
            if (usage[num] < 2) {
                result[i] = num;
                usage[num]++;
            }
            else {
                result[i] = num;
                usage[num]++;
                bool exit = false;
                for (; i < digit; i++) {
                    int t = result[i];
                    usage[t]--;
                    if (t > 0) {
                        for (int j = t - 1; j >= 0; j--) {
                            if (usage[j] < 2) {
                                result[i] = j;
                                usage[j]++;
                                exit = true;
                                break;
                            }
                        }
                    }
                    if (exit) break;
                }
                small = true;
            }
        }
    }
    long long answer = 0;
    for (int i = digit - 1; i >= 0; i--) {
        answer *= 10;
        answer += result[i];
    }
    printf("%lld", answer);
}