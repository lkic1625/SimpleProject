#include<iostream>
#include<vector>

using namespace std;

const int MAX_N = 1000, MAX_M = 1000;

//A와 B의 정점의 개수
int n, m;
//인접리스트
bool adj[MAX_N][MAX_M];
//각 정점에 매칭된 상대 정점의 번호를 저장한다.
vector<int> aMatch, bMatch;
//dfs 방문 여부
vector<bool> visited;
//A의 정점인 a에서 B의 매칭되지 않은 정점으로 가는 경로를 찾는다.
bool dfs(int a) {
	if (visited[a]) return false;
	visited[a] = true;
	for (int b = 0; b < m; b++) {
		if (adj[a][b]) {//b가 이미 매칭되어 있다면 bMatch[b]에서부터 시작해 증가경로를 찾는다
			if (bMatch[b] || dfs(bMatch[b])) {
				//증가 경로를 발견할 경우 a와 b를 매치 시킨다
				aMatch[a] = b;
				bMatch[b] = a;
				return true;
			}
		}
	}

	return false;
}

int bipartiteMatch() {
	//처음에는 정점이 모두 연결되어 있지 않음.
	aMatch = vector<int>(n, -1);
	bMatch = vector<int>(m, -1);
	int size = 0;
	for (int start = 0; start < n; start++) {
		visited = vector<bool>(n, false);
		if (dfs(start))
			++size;
	}
	return size;
}

