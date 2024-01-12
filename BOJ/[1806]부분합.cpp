#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>
#include <limits.h>
#include <cstdlib>
#include <iostream>
using namespace std;
int n, s;
int arr[100000];
long long sum = 0;
int minLength;


int main(int argc, char** argv)
{
	scanf("%d %d", &n, &s);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	int left = 0, right = 0;
	for (int i = 0; i < n; i++) {
		sum += arr[i];
		if (sum >= s) {
			right = i + 1;
			break;
		}
	}
	if (sum < s) {
		minLength = 0;
	}
	else {
		minLength = right;
		int curLength = minLength;
		while (right < n || sum >= s) {
			sum -= arr[left++];
			curLength--;
			if (sum < s) {
				while (right < n && sum < s) {
					sum += arr[right++];
					curLength++;
				}
			}
			if (sum >= s) minLength = min(curLength, minLength);
		}
	}
	printf("%d", minLength);
}
