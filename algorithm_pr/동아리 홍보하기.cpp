#include<iostream>
#include<algorithm>
#include<set>
#include<vector>
using namespace std;

const int MAX = 200001;
vector<int> adj[MAX];
int N, M, A, B;
int cache[MAX][4];

int parent[200001];
 
int find(int x) {

	if (x == parent[x]) return x;
	return parent[x] = find(parent[x]);
}

void uni(int x, int y) {
	x = find(x);
	y = find(y);
	parent[x] = y;
}

int dp(int prv, int cur, int dis) {

	if (dis > 3) return MAX + MAX;
	if (adj[cur].size() == 0 && prv == 0) return 1;
	if (adj[cur].size() == 1 && adj[cur][0] == prv) return dis > 2 ? 1 : 0;
	//leaf node

	if (dis > 3) return MAX + MAX;

	int& ret = cache[cur][dis];
	if (ret != -1) return ret;
	
	int trav[2] = { 0, 0 };
	for (auto iter : adj[cur]) {
		if (iter != prv) {
			trav[0] += 1 + dp(cur, iter, 1);
		}
	}
	if (dis < 3) {
		for (auto iter : adj[cur]) {
			if (iter != prv) {
				trav[1] += 0 + dp(cur, iter, dis + 1);
			}
		}
		return ret = min(trav[0], trav[1]);
	}
	
	return ret = trav[0];
	

}

int main() {
	cin >> N >> M;
	for (int i = 0; i < MAX; i++) {
		parent[i] = i;
		for(int j = 0; j < 4; j++)
			cache[i][j] = -1;
	}
	for (int i = 0; i < M; i++) {
		scanf("%d %d", &A, &B);
		if (A == B) continue;
		adj[A].push_back(B);
		adj[B].push_back(A);
		if (find(A) != find(B))
			uni(A, B);
	}
	for (int i = 1; i <= N; i++) {
		if (parent[i] == i) adj[0].push_back(i);
	}
	int ans = 0;
	for (auto p : adj[0]) {
		ans += dp(0, p, 1);
		}
	cout << ans << endl;

}
