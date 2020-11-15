#include<iostream>
#include<algorithm>

using namespace std;

const int MAX = 10000 + 2, MAX_COORD = 30000 + 5;

enum
{
	TRUE = -1,
	FALSE = 1,
};

struct Coord {
	int x, y1, y2, isEndpoint;
};

Coord location[2 * MAX];
int X1, X2, Y1, Y2, N;
long long seg[4 * MAX_COORD], isOverlap[4 * MAX_COORD], lazy[4 * MAX_COORD];

void update_lazy(int node, int left, int right) {
	if (lazy[node] == 0) return;
	isOverlap[node] += lazy[node];
	seg[node] = isOverlap[node] ? right - left + 1 : 0;
	if (left != right) {
		lazy[node * 2] += lazy[node];
		lazy[node * 2 + 1] += lazy[node];
	}
	lazy[node] = 0;
}

long long update(int lo, int hi, int val, int node, int left, int right) {
	update_lazy(node, left, right);
	if (right < lo || hi < left) {
		return seg[node];
	}
	if (lo <= left && right <= hi) {
		lazy[node] += val;
		update_lazy(node, left, right);
		return seg[node];
	}

	int mid = (left + right) >> 1;
	seg[node] = update(lo, hi, val, node * 2, left, mid) + update(lo, hi, val, node * 2 + 1, mid + 1, right);
	return seg[node] = isOverlap[node] ? right - left + 1 : seg[node];
	
}

int main() {

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> X1 >> Y1 >> X2 >> Y2;
		location[i] = { X1 ,Y1, Y2, FALSE };
		location[i + N] = { X2, Y1, Y2, TRUE };
	}

	//init
	sort(location, location + 2 * N, [](const Coord& lv, const Coord& rv) {
		return lv.x < rv.x;
	});
	update(location[0].y1, location[0].y2 - 1, location[0].isEndpoint, 1, 0, MAX_COORD - 1);
	int prev_x = location[0].x;
	long long ans = 0;

	for (int i = 1; i < 2 * N; i++) {
		auto [x, y1, y2, isEndpoint] = location[i];
		long long width = x - prev_x;
		long long height = seg[1];
		
		ans += (width * height);
		update(y1, y2 - 1, isEndpoint, 1, 0, MAX_COORD - 1);
		prev_x = x;
	}

	cout << ans << '\n';


} 