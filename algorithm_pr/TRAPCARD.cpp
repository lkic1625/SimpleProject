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
#include<string.h>
#include<queue>

using namespace std;

const int SIZE_A = 10000 + 1, SIZE_B = 10000 + 1, HEIGHT = 20 + 2, WIDTH = 20 + 2;
const int SIZE = HEIGHT * WIDTH, SOURCE = SIZE, SINK = SIZE + 1;

int u, v;
int capacity[SIZE + 2][SIZE + 2], flow[SIZE + 2][SIZE + 2];

struct Node {
	int x;
	int y;
	int index;
	
};

int H, W, C;
int m, n;
int dx[4] = { 0 , 1, 0, -1 }, dy[4] = { -1, 0, 1, 0 };
int adj[SIZE_A][SIZE_B];
string map[HEIGHT], input, boundary = "#####################";
Node node[SIZE_A][SIZE_B];
vector<int> match;
vector<bool> visited;


int dfs(int a) {
	if (visited[a]) return false;
	visited[a] = true;
	for (int b = 0; b < m; b++) {
		if (adj[a][b] && (match[b] == -1 || dfs(match[b]))) {
			match[b] = a;
		//	cout << a << " �� " << b << "��Ī" << endl;
			return true;
		}
	}

}
int bipartiteMatching() {
	//ó������ ������ ��� ����Ǿ� ���� ����.

	match = vector<int>(m, -1);
	int size = 0;
	for (int start = 0; start < n; start++) {
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
		memset(adj, -1, sizeof(adj));
		memset(capacity, 0, sizeof(capacity));

		cin >> H >> W;
		map[0] = map[H + 1] = boundary;
		for (int i = 1; i <= H; i++) {
			cin >> input;
			input = "#" + input + "#";
			map[i] = input;
		}

		n = m = 0;
		for (int i = 1; i <= H; i++) {
			for (int j = 1; j <= W; j++) {
				if(map[i][j] == '.'){
					if ((i + j) % 2)
						node[i][j] = { j, i, m++ };
					else
						node[i][j] = { j, i, n++ };
				}
			}
		}

		for (int y = 1; y <= H; y++) {
			for (int x = 1; x <= W; x++) {
				if ((y + x) % 2 || map[y][x] != '.') continue;
				for (int i = 0; i < 4; i++) {
					int cy = y + dy[i], cx = x + dx[i];
					int A = node[y][x].index, B = node[cy][cx].index;
					if (map[cy][cx] == '.') {
						adj[A][B] = 1;
						capacity[SOURCE][A]++;
						capacity[A][B]++;
						capacity[B][SINK]++;
					}
				}
				
			}
		}

		int Answer = bipartiteMatching();
		cout << Answer << "\n";

	}
}