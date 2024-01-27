// 실수: 처음에는 각 정점에 방문한 시간의 최댓값을 저장해서 구현하려 했음
// DP로 구현할 때는 모든 정점을 방문하지 않기 때문에 최댓값이 정상적으로 저장되지 않음
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <utility>
#include <cstdlib>
#include <vector>
using namespace std;
struct Path {
    int dest;
    int time;
};
struct Node {
    vector<Path> path;
    vector<int> maxPath;
    int time = -1;
};
int n, m;
int st;
int ed;
Node nodes[10001];
bool visited[10001];

int cnt = 0;

int longPath(int node) {
    if (node == ed) {
        return 0;
    }
    if (nodes[node].time >= 0) {
        return nodes[node].time;
    }
    for (Path& next : nodes[node].path) {
        int result = longPath(next.dest) + next.time;
        if (result > nodes[node].time) {
            nodes[node].time = result;
            nodes[node].maxPath.clear();
            nodes[node].maxPath.push_back(next.dest);
        }
        else if (result == nodes[node].time) {
            nodes[node].maxPath.push_back(next.dest);
        }
    }
    return nodes[node].time;
}

int pathCnt(int node) {
    if (visited[node]) return 0;
    visited[node] = true;
    int cnt = nodes[node].maxPath.size();
    for (int next : nodes[node].maxPath) {
        cnt += pathCnt(next);
    }
    return cnt;
}

int main()
{
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        int s, e, t;
        scanf("%d %d %d", &s, &e, &t);
        nodes[s].path.push_back({ e,t });
    }
    scanf("%d %d", &st, &ed);
    int result = longPath(st);
    int maxPath = pathCnt(st);
    
    printf("%d\n%d", result, maxPath);
}

