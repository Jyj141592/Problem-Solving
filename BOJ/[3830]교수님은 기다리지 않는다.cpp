#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <utility>
using namespace std;
#define FINAL -2
#define NONE -1
int n, m;
int group[100001];
pair<int, int> gParent[100001];
int g = 0;
int offset[100001];

pair<int, int> findRoot(int gNum) {
    if (gParent[gNum].first == FINAL) return { gNum, 0 };
    pair<int, int> root = findRoot(gParent[gNum].first);
    gParent[gNum].first = root.first;
    gParent[gNum].second = root.second + gParent[gNum].second;
    return gParent[gNum];
}

void update(int num) {
    if (group[num] == NONE) return;
    if (gParent[group[num]].first != FINAL) {
        pair<int, int> root = findRoot(group[num]);
        offset[num] += root.second;
        group[num] = root.first;
    }
}

int main()
{
    scanf("%d %d", &n, &m);
    while (n != 0 && m != 0) {
        for (int i = 1; i <= n; i++) {
            group[i] = NONE;
        }
        g = 0;
        for (int i = 0; i < m; i++) {
            char c = getchar();
            while (c != '!' && c != '?') {
                c = getchar();
            }
            if (c == '!') {
                int a, b, w;
                scanf("%d %d %d", &a, &b, &w);
                if (group[a] != NONE) {
                    if (group[b] != NONE) {
                        update(a);
                        update(b);
                        if (group[a] != group[b]) {
                            int temp = offset[b] - w;
                            gParent[group[a]].first = group[b];
                            gParent[group[a]].second = temp - offset[a];
                            group[a] = group[b];
                            offset[a] = temp;
                        }
                    }
                    else {
                        update(a);
                        group[b] = group[a];
                        offset[b] = offset[a] + w;
                    }
                }
                else {
                    if (group[b] != NONE) {
                        update(b);
                        group[a] = group[b];
                        offset[a] = offset[b] - w;
                    }
                    else {
                        gParent[g] = { FINAL, FINAL };
                        group[a] = group[b] = g;
                        g++;
                        offset[a] = 0;
                        offset[b] = w;
                    }
                }
            }
            else {
                int a, b;
                scanf("%d %d", &a, &b);
                update(a);
                update(b);
                if (group[a] == NONE || group[b] == NONE) {
                    printf("UNKNOWN\n");
                }
                else if (group[a] != group[b]) {
                    printf("UNKNOWN\n");
                }
                else {
                    printf("%d\n", offset[b] - offset[a]);
                }
            }
        }
        scanf("%d %d", &n, &m);
    }
}