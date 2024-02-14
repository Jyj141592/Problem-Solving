#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <utility>
#include <cmath>
#include <vector>
#include <algorithm>
typedef long long ll;
using namespace std;
pair<int, int> lu;
pair<int, int> rd;
pair<int, int> i_lu;
pair<int, int> i_rd;
int require[5];
int two_cnt = 0, one_cnt = 0;
ll sum = 0;

void inside(pair<int, int>& o, pair<int, int>& i, bool isUp) {
	int mod;
	mod = o.first % 5;
	i.first = o.first - mod;
	if (isUp && mod != 0) i.first += 5;
	mod = o.second % 5;
	i.second = o.second - mod;
	if (isUp && mod != 0) i.second += 5;
}

void small() {
	int q1, q2;
	int h, v;
	if (i_rd.first < i_lu.first && i_rd.second < i_lu.second) {
		q1 = lu.first / 5;
		q2 = lu.second / 5;
		if (((q1 + q2) & 1) == 0) {
			require[rd.first - lu.first] += rd.second - lu.second;
		}
		else {
			require[rd.second - lu.second] += rd.first - lu.first;
		}
	}
	else if (i_rd.first < i_lu.first) {
		int n = (i_rd.second - i_lu.second) / 5;
		h = v = n / 2;
		if (n & 1) h++;
		q1 = lu.first / 5;
		q2 = i_lu.second / 5;
		bool hor = ((q1 + q2) & 1) == 0;
		if (hor) {
			require[rd.first - lu.first] += 5 * h;
			sum += v * (rd.first - lu.first);
			require[i_lu.second - lu.second] += rd.first - lu.first;
			if (h == v) {
				require[rd.first - lu.first] += rd.second - i_rd.second;
			}
			else {
				require[rd.second - i_rd.second] += rd.first - lu.first;
			}
		}
		else {
			require[rd.first - lu.first] += 5 * v;
			sum += h * (rd.first - lu.first);
			require[rd.first - lu.first] += i_lu.second - lu.second;
			if (h == v) {
				require[rd.second - i_rd.second] += rd.first - lu.first;
			}
			else {
				require[rd.first - lu.first] += rd.second - i_rd.second;
			}
		}
	}
	else {
		int n = (i_rd.first - i_lu.first) / 5;
		h = v = n / 2;
		if (n & 1) h++;
		q1 = i_lu.first / 5;
		q2 = lu.second / 5;
		bool hor = ((q1 + q2) & 1) == 0;
		if (hor) {
			require[rd.second - lu.second] += 5 * v;
			sum += h * (rd.second - lu.second);
			require[rd.second - lu.second] += i_lu.first - lu.first;
			if (h == v) {
				require[rd.first - i_rd.first] += rd.second - lu.second;
			}
			else {
				require[rd.second - lu.second] += rd.first - i_rd.first;
			}
		}
		else {
			require[rd.second - lu.second] += 5 * h;
			sum += v * (rd.second - lu.second);
			require[i_lu.first - lu.first] += rd.second - lu.second;
			if (h == v) {
				require[rd.second - lu.second] += rd.first - i_rd.first;
			}
			else {
				require[rd.first - i_rd.first] += rd.second - lu.second;
			}
		}
	}
}

void side() {
	if (i_rd.first < i_lu.first || i_rd.second < i_lu.second) {
		small();
		return;
	}
	bool hor;
	int v = 0, h = 0;
	int q1;
	int q2;
	int n = (i_rd.second - i_lu.second) / 5;
	h = v = n / 2;
	if (n & 1) {
		h++;
	}

	if (lu.first != i_lu.first) {
		q1 = i_lu.first / 5;
		q2 = i_lu.second / 5;
		hor = ((q1 + q2) & 1) != 0;
		if (hor) {
			require[i_lu.first - lu.first] += h * 5;
			sum += v * (i_lu.first - lu.first);
			require[i_lu.second - lu.second] += i_lu.first - lu.first;
			if (h == v) {
				require[i_lu.first - lu.first] += rd.second - i_rd.second;
			}
			else {
				require[rd.second - i_rd.second] += i_lu.first - lu.first;
			}
		}
		else {
			require[i_lu.first - lu.first] += v * 5;
			sum += h * (i_lu.first - lu.first);
			require[i_lu.first - lu.first] += i_lu.second - lu.second;
			if (h == v) {
				require[rd.second - i_rd.second] += i_lu.first - lu.first;
			}
			else {
				require[i_lu.first - lu.first] += rd.second - i_rd.second;
			}
		}
	}
	if (rd.first != i_rd.first) {
		q1 = i_rd.first / 5;
		q2 = i_lu.second / 5;
		hor = ((q1 + q2) & 1) == 0;
		if (hor) {
			require[rd.first - i_rd.first] += h * 5;
			sum += v * (rd.first - i_rd.first);
			require[i_lu.second - lu.second] += rd.first - i_rd.first;
			if (h == v) {
				require[rd.first - i_rd.first] += rd.second - i_rd.second;
			}
			else {
				require[rd.second - i_rd.second] += rd.first - i_rd.first;
			}
		}
		else {
			require[rd.first - i_rd.first] += v * 5;
			sum += h * (rd.first - i_rd.first);
			require[rd.first - i_rd.first] += i_lu.second - lu.second;
			if (h == v) {
				require[rd.second - i_rd.second] += rd.first - i_rd.first;
			}
			else {
				require[rd.first - i_rd.first] += rd.second - i_rd.second;
			}
		}
	}
	n = (i_rd.first - i_lu.first) / 5;
	h = v = n / 2;
	if (n & 1) h++;
	if (i_lu.second != lu.second) {
		q1 = i_lu.first / 5;
		q2 = i_lu.second / 5;
		hor = ((q1 + q2) & 1) != 0;
		if (hor) {
			require[i_lu.second - lu.second] += 5 * v;
			sum += h * (i_lu.second - lu.second);
		}
		else {
			require[i_lu.second - lu.second] += 5 * h;
			sum += v * (i_lu.second - lu.second);
		}
	}
	if (i_rd.second != rd.second) {
		q1 = i_lu.first / 5;
		q2 = i_rd.second / 5;
		hor = ((q1 + q2) & 1) == 0;
		if (hor) {
			require[rd.second - i_rd.second] += 5 * v;
			sum += h * (rd.second - i_rd.second);
		}
		else {
			require[rd.second - i_rd.second] += 5 * h;
			sum += v * (rd.second - i_rd.second);
		}
	}
}

int main()
{
	scanf("%d %d %d %d", &lu.first, &lu.second, &rd.first, &rd.second);
	inside(lu, i_lu, true);
	inside(rd, i_rd, false);
	if (i_rd.first - i_lu.first > 0 && i_rd.second - i_lu.second > 0)
		sum = ((ll)(i_rd.first - i_lu.first)) * (i_rd.second - i_lu.second) / 5;
	side();
	sum += require[4] + require[3];
	one_cnt = require[4];
	two_cnt = require[3];
	if (two_cnt >= require[2]) {
		two_cnt -= require[2];
		one_cnt += two_cnt * 2;
	}
	else {
		require[2] -= two_cnt;
		int addi = require[2] / 2;
		sum += addi;
		one_cnt += addi;
		if (require[2] & 1) {
			sum++;
			one_cnt += 3;
		}
	}
	if (one_cnt < require[1]) {
		require[1] -= one_cnt;
		sum += require[1] / 5;
		if (require[1] % 5 > 0) sum++;
	}
	printf("%lld", sum);
}