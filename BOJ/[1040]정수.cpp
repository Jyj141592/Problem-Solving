#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <utility>
#include <cmath>
#include <vector>
#include <algorithm>
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
int num[19];
int ans[20];
int length = 0;
int d = 0;
int k;
int used = 0;
bool digit[10];

bool search(int dgt, bool done) {
	if (dgt >= d && used == k) return true;
	if (d - dgt < k - used) return false;
	if (done) {
		if (k == used) {
			for (int i = 0; i < 10; i++) {
				if (digit[i]) {
					ans[dgt] = i;
					return search(dgt + 1, true);
				}
			}
		}
		else if (d - dgt == k - used) {
			for (int i = 0; i < 10; i++) {
				if (!digit[i]) {
					digit[i] = true;
					used++;
					ans[dgt] = i;
					return search(dgt + 1, true);
				}
			}
		}
		else {
			if (!digit[0]) {
				digit[0] = true;
				used++;
			}
			ans[dgt] = 0;
			return search(dgt + 1, true);
		}
	}
	else {
		if (k == used) {
			if (digit[num[dgt]]) {
				ans[dgt] = num[dgt];
				if (search(dgt + 1, false)) return true;
			}
			for (int i = num[dgt] + 1; i < 10; i++) {
				if (digit[i]) {
					ans[dgt] = i;
					return search(dgt + 1, true);
				}
			}
			return false;
		}
		bool find = false;
		ans[dgt] = num[dgt];
		if (!digit[num[dgt]]) {
			digit[num[dgt]] = true;
			used++;
			find = true;
		}
		else if (d - dgt == k - used) {
			for (int i = num[dgt] + 1; i < 10; i++) {
				if (!digit[i]) {
					ans[dgt] = i;
					digit[i] = true;
					used++;
					return search(dgt + 1, true);
				}
			}
			return false;
		}
		if (search(dgt + 1, false)) {
			return true;
		}
		else {
			if (find) {
				used--;
				digit[num[dgt]] = false;
			}
			if (d - dgt == k - used) {
				for (int i = num[dgt] + 1; i < 10; i++) {
					if (!digit[i]) {
						ans[dgt] = i;
						digit[i] = true;
						used++;
						return search(dgt + 1, true);
					}
				}
				return false;
			}
			else {
				if (num[dgt] == 9) return false;
				ans[dgt] = num[dgt] + 1;
				if (!digit[num[dgt] + 1]) {
					digit[num[dgt] + 1] = true;
					used++;
				}
				return search(dgt + 1, true);
			}
		}
	}
}

void lessVal(int dgt, int cnt) {
	ans[0] = 1;
	ans[1] = 0;
	cnt -= 2;
	int n = 2;
	for (int i = 2; i < dgt; i++) {
		if (dgt - i > cnt) {
			ans[i] = 0;
		}
		else {
			ans[i] = n++;
		}
	}
}

int main()
{
	ull n;
	scanf("%llu", &n);
	d = 0;
	while (n > 0) {
		num[d++] = n % 10;
		n /= 10;
	}
	for (int i = 0; i < d / 2; i++) {
		int temp = num[i];
		num[i] = num[d - i - 1];
		num[d - i - 1] = temp;
	}
	scanf("%d", &k);
	if (d < k) {
		length = k;
		lessVal(length, k);
	}
	else {
		length = d;
		if (!search(0, false)) {
			length = d + 1;
			lessVal(length, k);
		}
	}
	n = ans[0];
	for (int i = 1; i < length; i++) {
		n *= 10;
		n += ans[i];
	}
	printf("%llu", n);
}