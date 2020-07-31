/*
https://www.algospot.com/judge/problem/read/MATCHFIX\

networkFlow, bellmanFord Algorithm

input
�Է��� ù �ٿ��� �׽�Ʈ ���̽��� �� C (C <= 50) �� �־����ϴ�.
�� �׽�Ʈ ���̽��� ù �ٿ��� ��� ���׿� �����ϴ� ������ �� N (2 <= N <= 12) �� ���� �ִ� ����� �� M (0 <= M <= 100) �� �־����ϴ�. 
�� �� �� �������Դ� 0���� N-1 ������ ��ȣ�� �־����ϴ�. 
�� ���� �ٿ��� N ���� ������ 0������ N-1 ������ ������� �� ������ ���� �¼��� �־����ϴ�. 
�� �� M �ٿ��� �� ��⸦ ġ���� �� ������ ��ȣ�� �־����ϴ�. ��� ������ ���� �¼��� 1000 �����Դϴ�.

output
�� �׽�Ʈ ���̽����� �� �ٿ� X�� ���׸� �ܵ� ����ϱ� ���� �ʿ��� �ּ� �¼��� ����մϴ�. ���� �̰��� �Ұ����ϴٸ� -1 �� ����մϴ�.

*/
#include<iostream>
#include<tuple>
#include<algorithm>
#include<string.h>
#include<queue>

using namespace std;

const int MAX_N = 12, MAX_M = 100, PLAYER_X = 0, SIZE = MAX_N + MAX_M, SOURCE = SIZE,  SINK = SIZE + 1;

int C, N, M, input, u, v;
int wins[MAX_N + 2], capacity[SIZE + 2][SIZE + 2], flow[SIZE + 2][SIZE + 2];
pair<int, int> match[MAX_M];

int bellmanFord(int source, int sink) {
	//init flow edge
	memset(flow, 0, sizeof(flow));
	int totalFlow = 0;
	while (true) {
		vector<int> parent(SIZE + 2, -1);
		queue<int> q;
		parent[source] = source;
		q.push(source);
		while (!q.empty()) {
			int here = q.front(); q.pop();
			for (int there = 0; there < SIZE + 2; there++) {
				if (capacity[here][there] - flow[here][there] > 0
					&& parent[there] == -1) {//If there is a node that has not been visited and can flow, push to the queue.
					q.push(there);
					parent[there] = here;
				}
			}

		}
		if (parent[sink] == -1) break;
		int amount = MAX_N + 1;
		//finding the minimum amount of flow.
		for (int p = sink; p != source; p = parent[p]) {
			amount = min(amount, capacity[parent[p]][p] - flow[parent[p]][p]);
		}
		//flowing..
		for (int p = sink; p != source; p = parent[p]) {
			flow[parent[p]][p] += amount;
			flow[p][parent[p]] -= amount;
		}
		totalFlow += amount;
	}
	return totalFlow;

}


int isChampionshipable(int totalWins) {

	//If there is a Wins greater than totalWins, then return false;
	if (*max_element(wins  + 1, wins + N) >= totalWins) return false;
	//init capacity edge
	memset(capacity, 0, sizeof(capacity));
	//boundary of Indexing 
	int boundary = MAX_N;

	for (int i = 0; i < M; i++) {
		int u = match[i].first;
		int v = match[i].second;
		capacity[SOURCE][boundary + i] = 1;
		capacity[boundary + i][u] = 1;
		capacity[boundary + i][v] = 1;
	}
	
	//If X is to win alone with a w win, the win or loss of the remaining games will be properly determined 
	//and all other players must finish the league with less than w - 1 win.
	for (int node = 0; node < N; node++) {
		capacity[node][SINK] = max(totalWins - wins[node] - 1, 0);
	}
	capacity[PLAYER_X][SINK] = totalWins - wins[PLAYER_X];

	return bellmanFord(SOURCE, SINK) == M && flow[PLAYER_X][SINK] == capacity[PLAYER_X][SINK];

}


int main() {
	//fast I/O
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//input
	cin >> C;
	while (C-- > 0) {
		int totalMatchCountOfX = 0;
		cin >> N >> M;
		for (int player = 0; player < N; player++) {
			cin >> input;
			wins[player] = input;
		}
		for (int game = 0; game < M; game++) {
			cin >> u >> v;
			match[game] = { u ,v };
			if (u == 0 || v == 0) {
				totalMatchCountOfX++;
			}
		}
		int flag = false, i = 0;
		for (; i <= totalMatchCountOfX; i++) {
			if (isChampionshipable(wins[PLAYER_X] + i)) {
				flag = true;
				break;
			}
		}
		if(flag)
			cout << i + wins[PLAYER_X] << "\n";
		else
			cout << -1 << "\n";

	}
	return 0;


}
