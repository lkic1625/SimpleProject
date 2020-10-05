#include<iostream>
#include<vector>

using namespace std;

const int MAX_N = 1000, MAX_M = 1000;

//A�� B�� ������ ����
int n, m;
//��������Ʈ
bool adj[MAX_N][MAX_M];
//�� ������ ��Ī�� ��� ������ ��ȣ�� �����Ѵ�.
vector<int> aMatch, bMatch;
//dfs �湮 ����
vector<bool> visited;
//A�� ������ a���� B�� ��Ī���� ���� �������� ���� ��θ� ã�´�.
bool dfs(int a) {
	if (visited[a]) return false;
	visited[a] = true;
	for (int b = 0; b < m; b++) {
		if (adj[a][b]) {//b�� �̹� ��Ī�Ǿ� �ִٸ� bMatch[b]�������� ������ ������θ� ã�´�
			if (bMatch[b] || dfs(bMatch[b])) {
				//���� ��θ� �߰��� ��� a�� b�� ��ġ ��Ų��
				aMatch[a] = b;
				bMatch[b] = a;
				return true;
			}
		}
	}

	return false;
}

int bipartiteMatch() {
	//ó������ ������ ��� ����Ǿ� ���� ����.
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
