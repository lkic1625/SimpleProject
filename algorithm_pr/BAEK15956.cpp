#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#include <set>
#include <map>
#include <cmath>
#include <utility>
#include <list>
#include <unordered_set>
#include <assert.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

struct bus {
	int s, e, i;
	bool operator< (bus& a) {
		if (a.s == s) return e > a.e;
		return s < a.s;
	}
};

int cmp(const bus& a, const bus& b) {
	return a.i < b.i;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int N, M;
	cin >> N >> M;
	vector<bus> v(M);
	int back = 0;
	for (int i = 0; i < M; i++) {
		cin >> v[i].s >> v[i].e;
		v[i].i = i + 1;
		if (v[i].s > v[i].e) {
			back = max(back, v[i].e);
			v[i].e += N;
		}
	}
	sort(v.begin(), v.end());
	deque<bus> dq;
	for (int i = 0; i < M; i++)
		if (dq.empty() || dq.back().e < v[i].e)
			dq.push_back(v[i]);
	while (!dq.empty() && dq.front().e <= back) dq.pop_front();
	sort(dq.begin(), dq.end(), cmp);
	for (bus b : dq) cout << b.i << ' ';
	return 0;
}