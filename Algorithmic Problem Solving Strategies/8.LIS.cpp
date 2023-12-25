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
int series[500];
int cnt[500];

int main(int argc, char** argv)
{
	int test_case;
	scanf("%d", &test_case);
	for (int T = 0; T < test_case; T++) {
		scanf("%d", &n);
		int maximum = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d", &series[i]);
		}
		for (int i = n - 1; i >= 0; i--) {
			int maxCnt = 0;
			for (int j = i + 1; j < n; j++) {
				if (series[i] < series[j]) {
					maxCnt = max(maxCnt, cnt[j]);
				}
			}
			cnt[i] = maxCnt + 1;
			maximum = max(maximum, cnt[i]);
		}
		printf("%d\n", maximum);
	}
}
