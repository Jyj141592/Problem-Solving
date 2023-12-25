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
int maxSum[100][100];

int main(int argc, char** argv)
{
	int test_case;
	scanf("%d", &test_case);
	for (int T = 0; T < test_case; T++) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j <= i; j++) {
				scanf("%d", &board[i][j]);
			}
		}
		for (int i = 0; i < n; i++) {
			maxSum[n - 1][i] = board[n - 1][i];
		}
		for (int i = n - 2; i >= 0; i--) {
			for (int j = 0; j <= i; j++) {
				maxSum[i][j] = max(maxSum[i + 1][j], maxSum[i + 1][j + 1]) + board[i][j];
			}
		}
		printf("%d\n", maxSum[0][0]);
	}
}
