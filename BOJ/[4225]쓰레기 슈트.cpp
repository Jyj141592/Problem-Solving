#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <utility>
#include <cmath>
#include <fstream>
using namespace std;
#define PUSH(x) stack[top++] = (x)
#define POP top--
int n;
pair<int, int> points[101];
pair<int, int> stack[101];
int top = 0;
pair<int, int> minY;


int compare(const void* a, const void* b) {
    pair<int, int>* f = (pair<int, int>*) a;
    pair<int, int>* s = (pair<int, int>*) b;
    pair<int, int> fir = { f->first - minY.first, f->second - minY.second };
    pair<int, int> sec = { s->first - minY.first, s->second - minY.second };
    if (fir.second * sec.first > sec.second * fir.first) return 1;
    else if (fir.second * sec.first < sec.second * fir.first) return -1;
    else {
        if (fir.second > sec.second) return 1;
        else if (fir.second < sec.second) return -1;
        else {
            if (fir.first > sec.first) return 1;
            else if (fir.first < sec.first) return -1;
            else return 0;
        }
    }
}

bool ccw(pair<int, int> point) {
    if (top < 2) return true;
    int det = (stack[top - 1].first - stack[top - 2].first) * (point.second - stack[top - 1].second) -
        (stack[top - 1].second - stack[top - 2].second) * (point.first - stack[top - 1].first);
    return det >= 0;
}

void convex() {
    qsort(points, n, sizeof(pair<int, int>), compare);
    top = 0;
    points[n] = points[0];
    PUSH(points[0]);
    PUSH(points[1]);
    for (int i = 2; i <= n; i++) {
        while (!ccw(points[i])) {
            POP;
        }
        PUSH(points[i]);
    }
}

double minWidth() {
    double m = 100000;
    for (int i = 1; i < top; i++) {
        int x = stack[i].first - stack[i - 1].first;
        int y = stack[i].second - stack[i - 1].second;
        double len = sqrt(x * x + y * y);
        double maxWidth = -1;
        for (int j = 1; j < top; j++) {
            if (j == i || j == i - 1) continue;
            int t = abs(y * (stack[j].first - stack[i].first) - x * (stack[j].second - stack[i].second));
            maxWidth = max(maxWidth, t / len);
        }
        m = min(m, maxWidth);
    }
    return m;
}

int main()
{
    scanf("%d", &n);
    int T = 0;
    while (n > 0) {
        T++;
        minY = { 100000, 100000 };
        for (int i = 0; i < n; i++) {
            scanf("%d %d", &points[i].first, &points[i].second);
            if (points[i].second < minY.second || (points[i].second == minY.second && points[i].first < minY.first)) {
                minY = points[i];
            }
        }
        convex();
        printf("Case %d: %0.2lf\n", T, ceil(minWidth() * 100) / 100);
        scanf("%d", &n);
    }
}