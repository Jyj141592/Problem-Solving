#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>
#include <limits.h>
#include <cstdlib>
#include <iostream>
using namespace std;
#define PUSH(x) order[++top] = (x)
int n, m;
int pd[100][1001];
int depend[1001][1001];
bool check[1001][1001];
int depend_num[1001];
int order[1000];
int top = -1;
int current = 0;

void dependency() {
	for (int i = 0; i < m; i++) {
		for (int j = 2; j <= pd[i][0]; j++) {
			for (int k = 1; k < j; k++) {
				if (!check[pd[i][j]][pd[i][k]]) {
					check[pd[i][j]][pd[i][k]] = true;
					depend[pd[i][k]][0]++;
					depend[pd[i][k]][depend[pd[i][k]][0]] = pd[i][j];
					depend_num[pd[i][j]]++;
				}
			}
		}
	}
}

int main(int argc, char** argv)
{
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++) {
		int num;
		scanf("%d", &num);
		pd[i][0] = num;
		for (int j = 1; j <= num; j++) {
			scanf("%d", &pd[i][j]);
		}
	}

	dependency();

	for (int i = 1; i <= n; i++) {
		if (depend_num[i] == 0) PUSH(i);
	}
	while (current <= top) {
		int currentNum = order[current];
		for (int i = 1; i <= depend[currentNum][0]; i++) {
			int num = depend[currentNum][i];
			depend_num[num]--;
			if (depend_num[num] == 0) {
				PUSH(num);
			}
		}
		current++;
	}
	if (top == n - 1) {
		for (int i = 0; i < n; i++) {
			printf("%d\n", order[i]);
		}
	}
	else printf("%d\n", 0);
}
