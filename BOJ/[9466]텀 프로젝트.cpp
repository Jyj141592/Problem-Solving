#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <utility>
#include <cmath>
using namespace std;
int n;
int choose[100001];
int rest;
int turns[100001];

int circular(int s, int t) {
    int turn = t;
    while (true) {
        if (turns[s] == 0) {
            turns[s] = turn++;
            s = choose[s];
        }
        else {
            if (turns[s] >= t) {
                rest -= turn - turns[s];
            }
            break;
        }
    }
    return turn;
}

int main()
{
    int tc;
    scanf("%d", &tc);
    for (int T = 0; T < tc; T++) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &choose[i]);
            turns[i] = 0;
        }
        rest = n;
        int turn = 1;
        for (int i = 1; i <= n; i++) {
            if (turns[i] == 0) {
                turn = circular(i, turn);
            }
        }
        printf("%d\n", rest);
    }
}