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
int diam = 0;
vector<pair<int, int>> edges[100001];


int diameter(int node, int prev) {
	int edge = edges[node].size();
	if (edge == 1) return 0;
	else if (edge == 2) {
		if (edges[node][0].first == prev) {
			return edges[node][1].second + diameter(edges[node][1].first, node);
		}
		else {
			return edges[node][0].second + diameter(edges[node][0].first, node);
		}
	}
	else {
		int fir = 0, sec = 0;
		for (auto edge : edges[node]) {
			if (edge.first == prev) {
				continue;
			}
			int temp = edge.second + diameter(edge.first, node);
			if (temp > fir) {
				sec = fir;
				fir = temp;
			}
			else if (temp > sec) {
				sec = temp;
			}
		}
		diam = max(diam, fir + sec);
		return fir;
	}
}

void diameter() {
	if (edges[1].size() == 1) {
		int temp = edges[1][0].second + diameter(edges[1][0].first, 1);
		diam = max(diam, temp);
	}
	else {
		int fir = 0, sec = 0;
		for (auto node : edges[1]) {
			int temp = node.second + diameter(node.first, 1);
			if (temp > fir) {
				sec = fir;
				fir = temp;
			}
			else if (temp > sec) {
				sec = temp;
			}
		}
		diam = max(diam, fir + sec);
	}
}

int main(int argc, char** argv)
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		int num, next, dist;
		scanf("%d", &num);
		while (true) {
			scanf("%d", &next);
			if (next == -1) break;
			scanf("%d", &dist);
			edges[num].push_back({ next,dist });
		}
	}
	diameter();
	printf("%d", diam);
}
