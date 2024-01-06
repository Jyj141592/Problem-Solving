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
vector<pair<int, int>> tasks;

int main(int argc, char** argv)
{
	scanf("%d", &n);
	tasks.resize(n);
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &tasks[i].second, &tasks[i].first);
	}
	sort(tasks.begin(), tasks.end(), greater<pair<int, int>>());
	int time = INT32_MAX;
	for (int i = 0; i < n; i++) {
		time = min(tasks[i].first - tasks[i].second, time - tasks[i].second);
	}
	if (time < 0) {
		printf("%d", -1);
	}
	else {
		printf("%d", time);
	}
}
