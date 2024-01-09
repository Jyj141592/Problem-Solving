#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>
#include <limits.h>
#include <cstdlib>
#include <iostream>
using namespace std;
int n, k, w;
int delay[1001];
int prereq[1001][1001];
int req_time[1001];

int dfs(int n, int time) {
	if(req_time[n]>=0) return time + req_time[n];
	if (prereq[n][0] == 0) {
		req_time[n] = delay[n];
		return time + req_time[n];
	}
	int cnt = prereq[n][0];
	int maxTime = 0;
	for (int i = 1; i <= cnt; i++) {
		maxTime = max(maxTime, dfs(prereq[n][i], time + delay[n]));
	}
	req_time[n] = maxTime - time;
	return maxTime;
}

int main(int argc, char** argv)
{
	int TC;
	scanf("%d", &TC);
	for (int T = 0; T < TC; T++) {
		scanf("%d %d", &n, &k);
		for (int i = 1; i <= n; i++) {
			scanf("%d", &delay[i]);
			prereq[i][0] = 0;
			
			req_time[i] = -1;
		}
		for (int i = 0; i < k; i++) {
			int x, y;
			scanf("%d %d", &x, &y);
			int cnt = ++prereq[y][0];
			prereq[y][cnt] = x;
		}
		scanf("%d", &w);
		printf("%d\n", dfs(w, 0));
	}
}
