#include<iostream>
#include<vector>
#include<queue>
#include<string.h>
#include<algorithm>

using namespace std;

const int MAX = 300 + 5, MAX_M = 1e6, MAX_X = 1e4 + 1, BOUNDARY = MAX_X * MAX_M;

enum {
	LEFT,
	RIGHT,
	DIRECTION = 2,
};

int n, m, x;
int cache[DIRECTION][MAX][MAX];
vector<int> coord;

int dp(int selected, int l, int r, int time) {

	if (l < 1 || r > n + 1) return 0;
	if (time > m) return 0;

	int& ret = cache[selected][l][r];
	if (ret != -1) return ret;

	ret = BOUNDARY;
	int length = n - (r - l);

	if (selected == RIGHT) {
		ret = min(ret, abs(coord[r] - coord[r + 1]) * length + dp(RIGHT, l, r + 1, abs(coord[r] - coord[r + 1])));
		ret = min(ret, abs(coord[r] - coord[l - 1]) * length + dp(LEFT, l - 1, r, abs(coord[r] - coord[l - 1])));
	}
	if (selected == LEFT) {
		ret = min(ret, abs(coord[l] - coord[r + 1]) * length + dp(RIGHT, l, r + 1, abs(coord[l] - coord[r + 1])));
		ret = min(ret, abs(coord[l] - coord[l - 1]) * length + dp(LEFT, l - 1, r, abs(coord[l] - coord[l - 1])));
	}

	return ret;

}


int main() {
	memset(cache, -1, sizeof cache);
	cin >> n >> m;

	coord.push_back(MAX_X * 2);
	coord.push_back(-MAX_X * 2);
	coord.push_back(0);
	for (int i = 1; i <= n; i++) {
		cin >> x;
		coord.push_back(x);
	}

	sort(coord.begin(), coord.end());
	int start = lower_bound(coord.begin(), coord.end(), 0) - coord.begin();

	int ans = n * m - dp(RIGHT, start, start, 0);
	cout << max(ans, 0);

}