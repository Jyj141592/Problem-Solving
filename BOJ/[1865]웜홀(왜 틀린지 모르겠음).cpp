#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>
#include <limits.h>
#include <cstdlib>
#include <iostream>
using namespace std;
#define EMPTY 100000
int minDist[500][500];
int connected[500][501];
bool visited[500];
int visitedTime[500];
bool reached[500];
bool found = false;

bool dfs(int node, int time) {
	//printf("%d %d\n", node, time);
	if (visited[node]) {
		if (time < visitedTime[node]) {
			return true;
		}
		else return false;
	}
	reached[node] = true;
	visited[node] = true;
	visitedTime[node] = time;
	int cnt = connected[node][0];
	for (int i = 1; i <= cnt; i++) {
		if (dfs(connected[node][i], time + minDist[node][connected[node][i]])) {
			return true;
		}
	}
	visited[node] = false;
	return false;
}

int main(int argc, char** argv)
{
	int TC;
	scanf("%d", &TC);
	for (int test_case = 0; test_case < TC; test_case++) {
		int n, m, w;
		scanf("%d %d %d", &n, &m, &w);
		found = false;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				minDist[i][j] = EMPTY;
			}
			connected[i][0] = 0;
			reached[i] = visited[i] = false;
		}
		for (int i = 0; i < m; i++) {
			int s, e, t;
			scanf("%d %d %d", &s, &e, &t);
			s--; e--;
			if (minDist[s][e] == EMPTY) {
				minDist[s][e] = minDist[e][s] = t;
				connected[s][++connected[s][0]] = e;
				if (s != e)
					connected[e][++connected[e][0]] = s;
			}
			else {
				if (minDist[s][e] > t) {
					minDist[s][e] = minDist[e][s] = t;
				}
			}
		}
		for (int i = 0; i < w; i++) {
			int s, e, t;
			scanf("%d %d %d", &s, &e, &t);
			s--; e--;
			if (minDist[s][e] == EMPTY) {
				minDist[s][e] = -t;
				connected[s][++connected[s][0]] = e;
			}
			else {
				if (minDist[s][e] > -t) {
					minDist[s][e] = -t;
				}
			}
		}
		for (int i = 0; i < n; i++) {
			if (!reached[i]) {
				if (dfs(i, 0)) {
					found = true;
					break;
				}
			}
		}
		if (found) printf("YES");
		else printf("NO");
	}
}
