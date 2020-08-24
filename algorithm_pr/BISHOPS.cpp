/*
Bishops
https://algospot.com/judge/problem/read/BISHOPS

bipartite matching.

input
�Է��� ���� ���� �׽�Ʈ ���̽��� �־�����. �Է��� ù �ٿ��� �׽�Ʈ ���̽��� ���� T�� ���´�.
������ �׽�Ʈ ���̽��� ù �ٿ��� ü������ ũ�� N (1 <= N <= 8)�� �־�����.
���� N�ٿ��� ü������ ���°� �־�����. .�� Bishop�� ���� �� �ִ� ���̸�, *�� ��ֹ��̴�.

output
������ �׽�Ʈ ���̽��鿡 ���� �ִ�� ���� �� �ִ� Bishop�� ������ ����Ѵ�.

*/


#include<iostream>
#include<vector>
#include<string>
#include<string.h>

using namespace std;

const int MAX_CHESS_BOARD_SIZE = 8, MAX = 100;

int T, N, n, m;
string chessboard[MAX_CHESS_BOARD_SIZE + 2];
int id[2][MAX_CHESS_BOARD_SIZE + 2][MAX_CHESS_BOARD_SIZE + 2], adj[MAX][MAX];
int dy[2] = { 1, 1 }, dx[2] = { 1, -1 };
vector<int> match;
vector<bool> visited;

bool dfs(int a) {
	if (visited[a]) return false;
	visited[a] = true;
	for (int b = 1; b < m; b++) {
		if (adj[a][b]) {//b�� ��Ī�Ǿ� ���� �ʰų� �̹� ��Ī�� ������ �ٸ� ������ ��Ī�� ������ ��� bMatch[b]�������� ������ ������θ� ã�´�
			if (match[b] == -1 || dfs(match[b])) {
				//���� ��θ� �߰��� ��� a�� b�� ��ġ ��Ų��
				match[b] = a;
			//	cout << a << "�� " << b << "�� ��Ī��ŵ�ϴ�." << endl;
				return true;
			}
		}
	}

	return false;
}

int bipartiteMatch() {
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


void binding() {
	//starting number for each node is 1.
	int idx[2] = { 1, 1 };
	
	for (int direction = 0; direction < 2; direction++) {
		int visited[MAX_CHESS_BOARD_SIZE + 2][MAX_CHESS_BOARD_SIZE + 2];
		memset(visited, false, sizeof(visited));
		for (int y = 1; y <= N; y++) {
			for (int x = 1; x <= N; x++) {
				int cy = y, cx = x;
				//verify that we have not visited, and can create nodes
				while (chessboard[cy][cx] != '*' && !visited[cy][cx]) {
					visited[cy][cx] = true;
					//numbering
					id[direction][cy][cx] = idx[direction];
					cy += dy[direction];
					cx += dx[direction];
				}
				idx[direction]++;
			}
		}
	}
	n = idx[0];
	m = idx[1];
}


int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> T;
	while (T-- > 0) {
		
		//input
		cin >> N;		
		for (int i = 1; i <= N; i++) {
			cin >> chessboard[i];
			chessboard[i] = "*" + chessboard[i] + "*";
		}

		//init
		chessboard[N + 1] = "**********";
		chessboard[0] = "**********";
		memset(adj, 0, sizeof(adj));
		memset(id, 0, sizeof(id));

		//creating nodes.
		binding();
		//connecting edges.
		for (int y = 1; y <= N; y++) {
			for (int x = 1; x <= N; x++) {
				if (chessboard[y][x]) {
					adj[id[0][y][x]][id[1][y][x]] = 1;
				}
			}
		}

		//bipartite matching
		int Answer = bipartiteMatch();
		
		//output
		cout << Answer << "\n";
	
	}

}
