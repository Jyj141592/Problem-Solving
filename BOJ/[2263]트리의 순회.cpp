#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>
#include <limits.h>
#include <cstdlib>
#include <iostream>
using namespace std;
#define PUSH(x) pre[cnt++] = (x)
int n;
int post[100000];
int in[100000];
int pre[100000];
int inPos[100001];
int cnt = 0;

void toPreOrder(int iLeft, int pLeft, int count) {
	if (count <= 1) {
		if (count == 1) {
			PUSH(in[iLeft]);
		}
		return;
	}
	int root = post[pLeft + count - 1];
	PUSH(root);
	int left, right;
	left = inPos[root] - iLeft;
	right = count - left - 1;
	toPreOrder(iLeft, pLeft, left);
	toPreOrder(iLeft + left + 1, pLeft + left, right);
}

int main(int argc, char** argv)
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &in[i]);
		inPos[in[i]] = i;
	}
	for (int i = 0; i < n; i++) {
		scanf("%d", &post[i]);
	}
	toPreOrder(0, 0, n);
	for (int i = 0; i < n; i++) {
		printf("%d ", pre[i]);
	}
}
