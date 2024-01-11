#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>
#include <limits.h>
#include <cstdlib>
#include <iostream>
using namespace std;
#define VISITED '!'
#define WALL '*'
#define SPACE '.'
#define DOCUMENT '$'
#define ISLOWER(c) ((c) >= 'a' && (c) <= 'z')
#define ISUPPER(c) ((c) >= 'A' && (c) <= 'Z')
#define CANMOVE(x, y) (map[(x)][(y)] != VISITED && map[(x)][(y)] != WALL)
int h, w;
char map[102][102];
bool key[26];
pair<int, int> accessible[26][10000];
int top[26];
int doc_cnt = 0;
void push(char type, pair<int, int> pos) {
	accessible[type - 'A'][top[type - 'A']++] = pos;
}
pair<int, int> pop(char type) {
	return accessible[type - 'A'][--top[type - 'A']];
}

void dfs(int x, int y) {
	char current = map[x][y];
	map[x][y] = VISITED;
	if (ISUPPER(current)) {
		if (!key[current - 'A']) {
			push(current, { x,y });
			return;
		}
	}
	else if (ISLOWER(current)) {
		key[current - 'a'] = true;
	}
	else if (current == DOCUMENT) {
		doc_cnt++;
	}

	if (CANMOVE(x - 1, y)) {
		dfs(x - 1, y);
	}
	if (CANMOVE(x + 1, y)) {
		dfs(x + 1, y);
	}
	if (CANMOVE(x, y - 1)) {
		dfs(x, y - 1);
	}
	if (CANMOVE(x, y + 1)) {
		dfs(x, y + 1);
	}
}

int main(int argc, char** argv)
{
	int TC;
	scanf("%d", &TC);
	for (int T = 0; T < TC; T++) {
		doc_cnt = 0;
		for (int i = 0; i < 26; i++) {
			key[i] = false;
			top[i] = 0;
		}

		scanf("%d %d", &h, &w);
		getchar();
		for (int i = 1; i <= h; i++) {
			for (int j = 1; j <= w; j++) {
				map[i][j] = getchar();
			}
			getchar();
		}
		char input = getchar();
		if (input != '0') {
			while (input != '\n') {
				key[input - 'a'] = true;
				input = getchar();
			}
		}
		for (int i = 0; i <= h + 1; i++) map[i][0] = map[i][w + 1] = VISITED;
		for (int i = 0; i <= w + 1; i++) map[0][i] = map[h + 1][i] = VISITED;

		for (int i = 1; i <= h; i++) {
			if (CANMOVE(i, 1)) dfs(i, 1);
			if (CANMOVE(i, w)) dfs(i, w);
		}
		for (int j = 1; j <= w; j++) {
			if (CANMOVE(1, j)) dfs(1, j);
			if (CANMOVE(h, j)) dfs(h, j);
		}
		int open = 0;
		do {
			open = 0;
			for (int i = 0; i < 26; i++) {
				if (top[i] > 0 && key[i]) {
					open++;
					while (top[i] > 0) {
						auto pos = pop(i + 'A');
						dfs(pos.first, pos.second);
					}
				}
			}
		} while (open > 0);
		printf("%d\n", doc_cnt);
	}
}
