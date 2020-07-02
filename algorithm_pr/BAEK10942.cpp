#include<iostream>

using namespace std;

int cache[2001][2001], N, S, E, M, num[2001];

bool dp(int S, int E) {
	if (S > E) return false;
	if (S == E) return true;
	
	int& ret = cache[S][E];
	if (ret != -1) return ret;

	return ret = (num[S] == num[E]) && dp(S + 1, E - 1);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> num[i];
	}
	
	for (int i = 0;  i < N; i++) {
		for (int j = 0; j < N; j++) {
			cache[i][j] = -1;
		}
	}
	cin >> M;
	for (int i = 0; i < M; i++) {
		cin >> S >> E;
		cout << dp(S - 1, E - 1) << endl;
	}
}