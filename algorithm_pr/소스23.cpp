#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

const int MAX = 32001;
int n, m, a, b, node[MAX];
bool visited[MAX];
queue<int> v[MAX];
queue<int> q;

int main() {

	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		node[b]++;
		v[a].push(b);
	}
	for (int i = 1; i <= n; i++) {
		if (!node[i]) q.push(i);
	}
	while (!q.empty()) {
		int root = q.front();
		q.pop();
		printf("%d ", root);
		while (!v[root].empty()) {
			int child = v[root].front();
			v[root].pop();
			node[child]--;
			if (!node[child]) {
				q.push(child);		
			}
			
			
		}
	}
	
		
	


	
}