#include<iostream>
#include<set>
#include<vector>
#include<tuple>
#include<algorithm>
#include<queue>
#include<iterator>
#include<math.h>
#include<map>

using namespace std;

const int MAX = 250000 + 2, MAX_VALUE = 10e9;

int N, Q;
int x, y, a, b, X;
int root[MAX], visited[MAX];

vector<tuple<int, int>> point;
set<tuple<int, int, int>> x_sorted_map, y_sorted_map;
priority_queue<tuple<int, int, int>> pq;
map<tuple<int, int>, int> dist;

enum {
	FORWARD,
	REVERSE,
};

int find(int x) {
	if (root[x] == x) {
		return x;
	}
	return root[x] = find(root[x]);
}

void _union(int x, int y) {
	x = find(x);
	y = find(y);
	
	root[y] = x;
}

void add(set<tuple<int, int, int>>::iterator it, int ax, int ay, int direction) {
	int x, y, i;
	auto temp = it;

	if (direction == REVERSE) 
		temp--;
	else if(direction == FORWARD) 
		temp++;

	tie(x, y, i) = *(temp);
	_union(a, i);
	int weight = min(abs(x - ax), abs(y - ay));
	pq.push({ -weight, i , a });
}

void select(int a) {
	auto[ax, ay] = point[a];
	auto it = x_sorted_map.find({ ax, ay, a });

	if (it != --x_sorted_map.end()) {
		add(it, ax, ay, FORWARD);
	}
	if (it != x_sorted_map.begin()) {
		add(it, ax, ay, REVERSE);
	}
	it = y_sorted_map.find({ ay, ax, a });
	if (it != --y_sorted_map.end()) {
		add(it, ax, ay, FORWARD);
	}
	if (it != y_sorted_map.begin()) {
		add(it, ax, ay, REVERSE);
	}
}

int main() {
	//FAST IO
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> N >> Q;
	point.push_back({ 0, 0 });
	for (int i = 0; i < N; i++) {
		cin >> x >> y;
		point.push_back({ x, y });
		x_sorted_map.insert({ x, y, i + 1 });
		y_sorted_map.insert({ y, x, i + 1 });
	}

	//init
	for (int i = 1; i <= N; i++) {
		root[i] = i;
		visited[i] = false;
	}

	select(1);
	while (!pq.empty()) {
		auto[w, cur, bef] = pq.top(); pq.pop();
		if (visited[cur]) continue;
		visited[a] = true;

		//update dist
		dist[{root[bef], cur}] = max(-w, dist[{root[bef], cur}]);

		auto[ax, ay] = point[a];
		auto it = x_sorted_map.find({ ax, ay, a });

		if (it != --x_sorted_map.end()) {
			add(it, ax, ay, FORWARD);
		}
		if (it != x_sorted_map.begin()) {
			add(it, ax, ay, REVERSE);
		}
		it = y_sorted_map.find({ ay, ax, a });
		if (it != --y_sorted_map.end()) {
			add(it, ax, ay, FORWARD);
		}
		if (it != y_sorted_map.begin()) {
			add(it, ax, ay, REVERSE);
		}
	}

	for (int i = 0; i < Q; i++) {
		cin >> a >> b >> X;
		cout << (root[a] == root[b] && max(dist[{root[a], a}], dist[{root[b], b}]) <= X  ? "YES" : "NO") << '\n';
	}
}