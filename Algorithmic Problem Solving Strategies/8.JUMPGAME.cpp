#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>
#include <limits.h>
#include <cstdlib>
#include <iostream>
using namespace std;
int n;
int board[100][100];
bool check[100][100];

bool path(int x, int y) {
	if (x == n - 1 && y == n - 1) {
		return true;
	}
	check[x][y] = true;
	if (x + board[x][y] < n && !check[x + board[x][y]][y]) {
		if (path(x + board[x][y], y)) {
			return true;
		}
	}
	if (y + board[x][y] < n && !check[x][y + board[x][y]]) {
		if (path(x, y + board[x][y])) {
			return true;
		}
	}
	return false;
}

int main(int argc, char** argv)
{
	int test_case;
	scanf("%d", &test_case);
	for (int T = 0; T < test_case; T++) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				scanf("%d", &board[i][j]);
				check[i][j] = false;
			}
		}
		if (path(0, 0)) printf("YES\n");
		else printf("NO\n");
	}
}
