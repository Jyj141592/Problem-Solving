#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>
#include <limits.h>
#include <cstdlib>
#include <iostream>
using namespace std;
#define QUEUESIZE 1000000
#define ISEMPTY (top == tail)
#define CANMOVE_S(x,y) (map[(x)][(y)] == 0 && distS[(x)][(y)] == 0)
#define CANMOVE_E(x,y) (map[(x)][(y)] == 0 && distE[(x)][(y)] == 0)

struct P_D{
	int x;
	int y;
	int dist;
};
int n, m;
int map[1002][1002];
int distS[1002][1002];
int distE[1002][1002];
P_D q[QUEUESIZE];
int top = 0;
int tail = 0;

void push(int x, int y, int d, bool start) {
	q[tail] = { x,y,d };
	tail = (tail + 1) % QUEUESIZE;
	if (start)
		distS[x][y] = d;
	else
		distE[x][y] = d;
}

P_D pop() {
	int temp = top;
	top = (top + 1) % QUEUESIZE;
	return q[temp];
}

int concate(int x1, int y1, int x2, int y2) {
	int minDist = INT32_MAX;
	if (distS[x1][y1] > 0 && distE[x2][y2] > 0) {
		minDist = distS[x1][y1] + distE[x2][y2] + 1;
	}
	if (distE[x1][y1] > 0 && distS[x2][y2] > 0) {
		minDist = min(minDist, distE[x1][y1] + distS[x2][y2] + 1);
	}
	return minDist;
}

int main(int argc, char** argv)
{
	scanf("%d %d", &n, &m);
	for (int i = 0; i <= n + 1; i++) {
		map[i][0] = map[i][m + 1] = -1;
	}
	for (int i = 0; i <= m + 1; i++) {
		map[0][i] = map[n + 1][i] = -1;
	}
	getchar();
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			char c = getchar();
			map[i][j] = c - '0';
		}
		getchar();
	}
	// bfs로 처음부터 각 칸의 최단 거리 구하기
	push(1, 1, 1, true);
	while (!ISEMPTY) {
		P_D p = pop();
		if (CANMOVE_S(p.x + 1, p.y)) push(p.x + 1, p.y, p.dist + 1, true);
		if (CANMOVE_S(p.x - 1, p.y)) push(p.x - 1, p.y, p.dist + 1, true);
		if (CANMOVE_S(p.x, p.y + 1)) push(p.x, p.y + 1, p.dist + 1, true);
		if (CANMOVE_S(p.x, p.y - 1)) push(p.x, p.y - 1, p.dist + 1, true);
	}
	// bfs로 마지막부터 각 칸의 최단 거리 구하기
	push(n, m, 1, false);
	while (!ISEMPTY) {
		P_D p = pop();
		if (CANMOVE_E(p.x + 1, p.y)) push(p.x + 1, p.y, p.dist + 1, false);
		if (CANMOVE_E(p.x - 1, p.y)) push(p.x - 1, p.y, p.dist + 1, false);
		if (CANMOVE_E(p.x, p.y + 1)) push(p.x, p.y + 1, p.dist + 1, false);
		if (CANMOVE_E(p.x, p.y - 1)) push(p.x, p.y - 1, p.dist + 1, false);
	}
	int minDist = distS[n][m] > 0 ? distS[n][m] : INT32_MAX;


	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (map[i][j] == 1) {
				// 가로방향으로 뚫기
				if (map[i][j - 1] == 0 && map[i][j + 1] == 0) {
					minDist = min(minDist, concate(i, j - 1, i, j + 1));
				}
				// 세로방향으로 뚫기
				if (map[i - 1][j] == 0 && map[i + 1][j] == 0) {
					minDist = min(minDist, concate(i - 1, j, i + 1, j));
				}
				// 왼쪽 위로 뚫기
				if (map[i - 1][j - 1] == 1 && map[i - 1][j] == 0 && map[i][j - 1] == 0) {
					minDist = min(minDist, concate(i - 1, j, i, j - 1));
				}
				// 왼쪽 아래로 뚫기
				if (map[i + 1][j - 1] == 1 && map[i + 1][j] == 0 && map[i][j - 1] == 0) {
					minDist = min(minDist, concate(i + 1, j, i, j - 1));
				}
				// 오른쪽 위로 뚫기
				if (map[i - 1][j + 1] == 1 && map[i - 1][j] == 0 && map[i][j + 1] == 0) {
					minDist = min(minDist, concate(i - 1, j, i, j + 1));
				}
				// 오른쪽 아래로 뚫기
				if (map[i + 1][j + 1] == 1 && map[i + 1][j] == 0 && map[i][j + 1] == 0) {
					minDist = min(minDist, concate(i + 1, j, i, j + 1));
				}
			}
		}
	}
	if (minDist == INT32_MAX) {
		printf("%d", -1);
	}
	else {
		printf("%d", minDist);
	}
}
