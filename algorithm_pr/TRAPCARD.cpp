/*

���� ��ġ
https://algospot.com/judge/problem/read/TRAPCARD

bipartite matching

input
�Է��� ù �ٿ��� �׽�Ʈ ���̽��� �� C (C <= 50) �� �־����ϴ�. 
�� �׽�Ʈ ���̽��� ù �ٿ��� ���� ������ ũ�� H, W (1 <= H,W <= 20) �� �־����ϴ�. 
�� �� H �ٿ� �� W ���ڷ� ���� ������ ������ �־����ϴ�. 
�� ���ڿ����� #�� ������ ���� ĭ, .�� �� ĭ�� ��Ÿ���ϴ�.

output
�� �׽�Ʈ ���̽����� �켱 ��ġ�� �� �ִ� ������ �ִ� ���� ����ϰ�, �� �� ������ ��ġ�� ������ ���� ������ ������ �ٽ� ����մϴ�. 
������ ��ġ�� �� ĭ�� . ��� ^ �� ǥ���ϸ�, ������ ��ġ�ϴ� ����� ���� �� �ִٸ� �� �� �ƹ� ���̳� �����ص� �˴ϴ�.

*/

#include<iostream>
#include<vector>
#include<string>

using namespace std;

const int SIZE_A = 1000 + 1, SIZE_B = 1000 + 1, HEIGHT = 20 + 2, WIDTH = 20 + 2;

int H, W, C;
int m, n;
int adj[SIZE_A][SIZE_B];
string map[HEIGHT], input, boundary = "#####################";
vector<int> match;
vector<bool> visited;


int dfs(int a) {
	if (visited[a]) return false;
	visited[a] = true;
	for (int b = 0; b < m; b++) {
		if (adj[a][b] && (match[b] == -1 || dfs(match[b]))) {
			match[b] = a;
			
			return true;
		}
	}

}
int bipartiteMatching() {
	//ó������ ������ ��� ����Ǿ� ���� ����.

	match = vector<int>(m, -1);
	int size = 0;
	for (int start = 1; start < n; start++) {
		visited = vector<bool>(n, false);
		if (dfs(start))
			++size;
	}
	return size;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	
	cin >> C;
	while (C-- > 0) {
		cin >> H >> W;
		map[0] = map[H] = boundary;
		for (int i = 1; i <= H; i++) {
			cin >> input;
			input = "#" + input + "#";
		}
	}
}