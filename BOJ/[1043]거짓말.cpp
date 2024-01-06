#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>
#include <limits.h>
#include <cstdlib>
#include <iostream>
using namespace std;
int n, m;
long long avoid = 0;
long long truth = 0;
long long party[50];

int main(int argc, char** argv)
{
	scanf("%d %d", &n, &m);
	int t;
	scanf("%d", &t);
	for (int i = 0; i < t; i++) {
		int num;
		scanf("%d", &num);
		truth = truth | ((long long)1 << (num - 1));
	}
	avoid = truth;
	for (int i = 0; i < m; i++) {
		party[i] = 0;
		scanf("%d", &t);
		for (int j = 0; j < t; j++) {
			int num;
			scanf("%d", &num);
			party[i] = party[i] | ((long long)1 << (num - 1));
		}
		//if ((party[i] & truth) > 0) {
		//	avoid = avoid | party[i];
		//}
	}
	int count = m;
	int dec = 0;
	do {
		dec = 0;
		for (int i = 0; i < count; i++) {
			if ((party[i - dec] & avoid) > 0) {
				long long temp = party[i - dec];
				avoid = avoid | temp;
				party[i - dec] = party[count - 1 - dec];
				party[count - 1 - dec] = party[i - dec];
				dec++;
			}
		}
		count -= dec;
	} while (dec > 0);


	printf("%d", count);

	//for (int i = 0; i < 64; i++) {
	//	int a = truth & 1;
	//	printf("%d", a);
	//	truth = truth >> 1;
	//}
	//printf("\n");
	//for (int i = 0; i < 64; i++) {
	//	int b = avoid & 1;
	//	printf("%d", b);
	//	avoid = avoid >> 1;
	//}
}
