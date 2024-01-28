// 실수: 오타를 조심하자
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
#define DIST(x, y) (abs(x.first - y.first) + abs(x.second - y.second))
int n, w;
pair<int, int> accident[1000];
int sequential[1000];
int minimum[1000][1000];
int memo[1000];
int stack[1000];
int top = 0;
pair<int, int> s1 = { 1,1 };
pair<int, int> s2;

int main()
{
    scanf("%d %d", &n, &w);
    for (int i = 0; i < w; i++) {
        scanf("%d %d", &accident[i].first, &accident[i].second);
    }
    s2 = { n,n };
    sequential[0] = 0;
    for (int i = 1; i < w; i++) {
        sequential[i] = sequential[i - 1] + DIST(accident[i], accident[i - 1]);
    }

    int minVal, minIdx;
    if (DIST(s1, accident[0]) > DIST(s2, accident[0])) {
        minVal = DIST(s1, accident[0]) + sequential[w - 1];
        minIdx = -1;
    }
    else {
        minVal = DIST(s2, accident[0]) + sequential[w - 1];
        minIdx = -2;
    }

    if (w > 1) {
        int t1 = DIST(s1, accident[0]) + DIST(s2, accident[1]);
        int t2 = DIST(s1, accident[1]) + DIST(s2, accident[0]);
        if (t1 < t2) {
            minimum[1][0] = t1;
            memo[1] = -2;
        }
        else {
            minimum[1][0] = t2;
            memo[1] = -1;
        }

        for (int i = 2; i < w; i++) {
            for (int j = 0; j < i; j++) {
                if (j == i - 1) {
                    int num = j - 1;
                    int val = minimum[i - 1][j - 1] + DIST(accident[i], accident[j - 1]);
                    int temp;
                    for (int k = j - 2; k >= 0; k--) {
                        temp = minimum[i - 1][k] + DIST(accident[i], accident[k]);
                        if (temp < val) {
                            num = k;
                            val = temp;
                        }
                    }
                    temp = sequential[i - 1] + DIST(s1, accident[0]) + DIST(s2, accident[i]);
                    if (temp < val) {
                        num = -2;
                        val = temp;
                    }
                    temp = sequential[i - 1] + DIST(s2, accident[0]) + DIST(s1, accident[i]);
                    if (temp < val) {
                        num = -1;
                        val = temp;
                    }
                    memo[i] = num;
                    minimum[i][j] = val;
                }
                else {
                    minimum[i][j] = minimum[i - 1][j] + DIST(accident[i], accident[i - 1]);
                }
            }
        }
    }
    for (int i = 0; i < w - 1; i++) {
        if (minimum[w - 1][i] < minVal) {
            minVal = minimum[w - 1][i];
            minIdx = i;
        }
    }

    printf("%d\n", minVal);
    if (minIdx < 0) {
        for (int i = 0; i < w; i++) {
            printf("%d\n", -minIdx);
        }
    }
    else {
        int rear = minIdx;
        int num = 1;
        for (int i = w - 1; i >= 0; i--) {
            stack[top++] = num;
            if (rear >= 0) {
                if (i - 1 == rear) {
                    rear = memo[i];
                    num = (num % 2) + 1;
                }
            }
        }
        if (num == -rear) {
            for (int i = w - 1; i >= 0; i--) {
                printf("%d\n", (stack[i] % 2) + 1);
            }
        }
        else {
            for (int i = w - 1; i >= 0; i--) {
                printf("%d\n", stack[i]);
            }
        }
    }
}