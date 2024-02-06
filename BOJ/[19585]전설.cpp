#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <utility>
#include <cmath>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;
int c, n, q;
int color[4000001][26];

int c_top = 0;
int name[4000001][26];
int n_maxLen[4000001];
int n_minLen[4000001];
int n_top = 0;
bool c_end[4000001];
bool n_end[4000001];
string team;
string input;
bool result[20000];

void insertC() {
    int cur = 0;
    for (int i = 0; i < input.length(); i++) {
        int next = color[cur][input[i] - 'a'];
        if (next > 0) {
            cur = next;
        }
        else {
            color[cur][input[i] - 'a'] = c_top;
            cur = c_top++;
        }
    }
    c_end[cur] = true;
}

void insertN() {
    int cur = 0;
    for (int i = 0; i < input.length(); i++) {
        int len = input.length() - i;
        if (n_maxLen[cur] < len) n_maxLen[cur] = len;
        if (n_minLen[cur] > len) n_minLen[cur] = len;
        int next = name[cur][input[i] - 'a'];
        if (next > 0) {
            cur = next;
        }
        else {
            name[cur][input[i] - 'a'] = n_top;
            cur = n_top++;
            n_minLen[cur] = 1000000;
        }
    }
    n_end[cur] = true;
}

bool nameSearch(int num) {
    int cur = 0;
    for (int i = num; i < team.length(); i++) {
        if (n_maxLen[cur] < team.length() - i) return false;
        if (n_minLen[cur] > team.length() - i) return false;
        if (name[cur][team[i] - 'a'] > 0) {
            cur = name[cur][team[i] - 'a'];
        }
        else return false;
    }
    return n_end[cur];
}

bool search() {
    int cur = 0;
    for (int i = 0; i < team.length(); i++) {
        int len = team.length() - i;
        if (c_end[cur]) {
            if (nameSearch(i)) return true;
        }
        if (color[cur][team[i] - 'a'] > 0) {
            cur = color[cur][team[i] - 'a'];
        }
        else return false;
    }
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    c_end[0] = n_end[0] = false;
    c_top = n_top = 1;
    cin >> c >> n;
    for (int i = 0; i < c; i++) {
        cin >> input;
        insertC();
    }
    for (int i = 0; i < n; i++) {
        cin >> input;
        insertN();
    }
    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> team;
        result[i] = search();
    }
    for (int i = 0; i < q; i++) {
        if (result[i]) cout << "Yes\n";
        else cout << "No\n";
    }
}