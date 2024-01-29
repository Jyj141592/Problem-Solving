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
int height[500000];

long long sight(int left, int right) {
    if (right - left < 3) {
        return right - left - 1;
    }
    int middle = (left + right) >> 1;
    long long ret = sight(left, middle);
    ret += sight(middle + 1, right);
    int maximum = -1;
    int lMax = -1;
    int cnt = 0;
    int rep = 0;
    int j = middle - 1;
    int i = middle + 1;
    for (; j >= left; j--) {
        if (height[j] >= lMax) {
            if (lMax <= height[middle]) {
                ret++;
            }
            lMax = height[j];
            if (height[j] > height[middle]) break;
            else if (height[j] == height[middle]) {
                int tM = lMax;
                for (int k = j - 1; k >= left; k--) {
                    if (height[k] >= tM) {
                        if (tM <= height[middle]) ret++;
                        tM = height[k];
                        if (height[k] > height[middle]) break;
                    }
                }
                break;
            }
        }
    }

    for (; i < right; i++) {
        if (height[i] >= maximum) {
            if (maximum <= height[middle]) {
                ret++;
            }
            if (height[i] >= height[middle]) {
                ret += rep;
                if (height[i] != maximum) {
                    rep = 0;
                }
                cnt = 0;
                for (; j >= left; j--) {
                    if (height[j] >= lMax) {
                        cnt++;
                        if (height[j] == height[i]) {
                            rep++;
                        }
                        else if (height[j] > height[i]) {
                            break;
                        }
                        lMax = height[j];
                    }
                } 
                ret += cnt;
            }
            maximum = height[i];
        }
    }
    return ret;
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &height[i]);
    }
    printf("%lld", sight(0, n));
}