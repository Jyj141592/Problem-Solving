#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>
#include <limits.h>
#include <cstdlib>
#include <iostream>
using namespace std;
#define MOD 1000000007
long long n;
int m_pibo[2][2] = { {1,1},{1,0} };
int m[2][2] = { {1,0},{0,1} };
//mat1 = mat1 * mat2
void mMult(int mat1[2][2], int mat2[2][2]) {
	int temp[2][2];
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			temp[i][j] = mat1[i][j];
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			long long a = (long long)temp[i][0] * mat2[0][j] + (long long)temp[i][1] * mat2[1][j];
			mat1[i][j] = a % MOD;
		}
	}
}

void mPow(int mat[2][2]) {
	int temp[2][2];
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++) 
			temp[i][j] = mat[i][j];
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			long long a = (long long)temp[i][0] * temp[0][j] + (long long)temp[i][1] * temp[1][j];
			mat[i][j] = a % MOD;
		}
	}
}

int main(int argc, char** argv)
{
	scanf("%lld", &n);
	while (n > 0) {
		if ((n & 1) > 0) {
			mMult(m, m_pibo);
		}
		mPow(m_pibo);
		n = n >> 1;
	}
	printf("%d", m[1][0]);
}
