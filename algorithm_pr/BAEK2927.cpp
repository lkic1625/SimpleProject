#include<iostream>
#include<vector>
#include<math.h>
#include<queue>
#include<string>


using namespace std;

const int MAX_N = 30000 + 5, MAX_Q = 300000 + 5, LOG_MAX = 20;

enum {
	ROOT = 0,
};

struct Query {
	char command;
	int a, b;

};

struct SegmentTree {
	int size;
	vector<int> tree;

	SegmentTree(int _n) : size(_n), tree(_n * 4) {}

	void _update(int node, int start, int end, int idx, int dif) {
		if (idx < start || idx > end) return;
		tree[node] += dif;
		if (start != end) {
			int mid = (start + end) / 2;
			_update(node * 2, start, mid, idx, dif);
			_update(node * 2 + 1, mid + 1, end, idx, dif);
		}
	}

	void update(int idx, int dif) {
		_update(1, 0, size - 1, idx, dif);
	}

	int _query(int node, int start, int end, int left, int right) {
		if (right < start || end < left) return 0;
		if (left <= start && end <= right) return tree[node];
		int mid = (start + end) / 2;
		return _query(node * 2, start, mid, left, right) + _query(node * 2 + 1, mid + 1, end, left, right);
	}

	int query(int left, int right) {
		return _query(1, 0, size - 1, left, right);
	}
	
};

struct UnionFind {
	int parent[MAX_N];

	UnionFind() {
		for (int i = 0; i < MAX_N; i++) {
			parent[i] = i;
		}
	}

	int find(int a) {
		if (parent[a] == a) {
			return a;
		}
		return parent[a] = find(parent[a]);
	}
	int merge(int a, int b) {
		a = find(a);
		b = find(b);

		if (a == b) return false;

		parent[b] = a;

		return true;
	}
};

int lca[LOG_MAX][MAX_N];
int N, Q, X, A, B, penguins[MAX_N], visited[MAX_N];
Query queries[MAX_Q];
UnionFind uf;
vector<int> adj[MAX_N], children[MAX_N];
vector<int> exp_ancestor[MAX_N + 1];
string command;

int subtree_size[MAX_N]; // 해당 정점을 루트로 하는 서브트리의 크기 (= 정점의 무게)
int depth[MAX_N]; // 트리에서 해당 정점의 깊이. 루트의 깊이는 0.

// 각 무거운 경로마다, 경로에 포함된 정점의 목록. 무거운 경로 맨 위에서 그
// 선조로 가는 가벼운 간선을 포함한다.
vector<vector<int> > heavy_paths;
// 이 정점에서 부모로 가는 간선을 포함된 무거운 경로의 번호. 
// heavy_paths 내에서의 인덱스를 가리킨다.
vector<int> heavy_path_index;

vector<SegmentTree> trees;


void dfs(int u, vector<bool>& visited) {
	// calculate depth, exp_ancestor, subtree_size
	visited[u] = true;
	subtree_size[u] = 1;

	
	exp_ancestor[u] = vector<int>(1, lca[0][u]);
	for (int log_jump = 0;; ++log_jump) {
		int arrived = exp_ancestor[u][log_jump];
		if (arrived == -1 || exp_ancestor[arrived].size() <= log_jump) break;
		int next = exp_ancestor[arrived][log_jump];
		exp_ancestor[u].push_back(next);
	}

	for (int v : adj[u]) {
		if (!visited[v]) {
			lca[0][v] = u;
			children[u].push_back(v);
			depth[v] = depth[u] + 1;
			dfs(v, visited);
			subtree_size[u] += subtree_size[v];
		}
	}
}


void dfs(int before, int here, int level) {
	visited[here] = true;
	subtree_size[here] = 1;
	depth[here] = level;

	for (auto child : adj[here]) if (!visited[child]) {
		children[here].push_back(child);
		lca[0][child] = here;
		dfs(here, child, level + 1);
		subtree_size[here] += subtree_size[child];
	}

}


void dfs(int here) {
	visited[here] = true;
	for (auto child : adj[here]) if (!visited[child]) {
		children[here].push_back(child);
		dfs(child);
	}
}

void dfs1(int here, int level) {

	subtree_size[here] = 1;
	depth[here] = level;
	for (auto& child : children[here]) {
		lca[0][child] = here;
		dfs1(child, level + 1);
		subtree_size[here] += subtree_size[child];
		if (subtree_size[child] > subtree_size[children[here][0]]) {
			swap(children[here].back(), children[here][0]);
		}
	}

}

int _lca(int u, int v) {
	if (depth[u] > depth[v]) swap(u, v);

	int diff = depth[v] - depth[u];
	for (int i = 0; (1 << i) <= diff; i++) {
		if (diff & (1 << i))
			v = exp_ancestor[v][i];
	}

	if (u == v) return u;

	for (int i = exp_ancestor[u].size() - 1; i >= 0; i--) {
		if (i < exp_ancestor[v].size() && exp_ancestor[u][i] != exp_ancestor[v][i]) {
			u = exp_ancestor[u][i];
			v = exp_ancestor[v][i];
		}
	}
	return exp_ancestor[u][0];
}

void heavy_light_decomposion(int root) {
	
	heavy_path_index.assign(N + 1, -1);

	queue<int> q;
	q.push(root);

	while (!q.empty()) {
		int here = q.front(); q.pop();
		int parent = lca[0][here];

		for (int child : children[here]) {
			q.push(child);
		}

		if (here == root) continue;

		if (subtree_size[here] * 2 >= subtree_size[parent] && parent != root) {
			int parent_path_index = heavy_path_index[parent];
			heavy_paths[parent_path_index].push_back(here);
			heavy_path_index[here] = parent_path_index;
		}
		else {
			heavy_path_index[here] = heavy_paths.size();
			heavy_paths.push_back(vector<int>(2));
			heavy_paths.back()[0] = parent;
			heavy_paths.back()[1] = here;
		}

	}

}

void lca_init() {
	for (int k = 1; k < LOG_MAX; k++) {
		for (int i = 0; i <= N; i++) {
			lca[k][i] = lca[k - 1][lca[k - 1][i]];
		}
	}
}

int lowest_common_ancestor(int u, int v) {

	if (depth[u] > depth[v]) swap(u, v);

	for (int i = LOG_MAX - 1; i >= 0; i--) {
		if ((depth[v] - depth[u]) >= (1 << i)) {
			v = lca[i][v];
		}
	}

	if (u == v) {
		return v;
	}

	for (int i = LOG_MAX - 1; i >= 0; i--) {
		if (lca[i][u] != lca[i][v]) {
			u = lca[i][u];
			v = lca[i][v];
		}
	}

	return lca[0][u];
}

void init_tree() {
	
	trees.reserve(heavy_paths.size());

	for (const auto& path : heavy_paths) {
		int V = path.size();
		trees.push_back(SegmentTree(V));
		for (int vertex = 0; vertex < V; vertex++) {
			trees.back().update(vertex, penguins[path[vertex]]);
		}
	}
}

int find_edge_in_path(int path_index, int v) {
	int top_of_path = heavy_paths[path_index][0];

	return depth[v] - depth[top_of_path];
}

void update(int u, int value) {
	int path_index_u = heavy_path_index[u];
	int index_in_path = find_edge_in_path(path_index_u, u);
	
	trees[path_index_u].update(index_in_path, value - penguins[u]);

	for (int v : children[u]) {
		int path_index_v = heavy_path_index[v];
		if (path_index_u != path_index_v) {
			int vi = find_edge_in_path(path_index_v, u);
			trees[path_index_v].update(vi, value - penguins[u]);
		}
	}

	penguins[u] = value;
}




int query_topdown(int u, int v) {
	// u와 v가 같다면 경로에는 아무 간선도 포함되어 있지 않다.

	if (u == v) return penguins[u];
	
	// 만약 u와 v가 같은 무거운 경로에 속한다면 구간 트리로 해결 가능
	if (heavy_path_index[u] == heavy_path_index[v]) {
		int path_index = heavy_path_index[u];
		int	first = find_edge_in_path(path_index, u);
		int last = find_edge_in_path(path_index, v);
		int N = trees[path_index].size;

		return trees[path_index].query(first, last);
	}

	int path_index = heavy_path_index[v];
	int top_of_path = heavy_paths[path_index][0];
	int N = trees[path_index].size;


	int last = find_edge_in_path(path_index, v);
	return query_topdown(u, top_of_path) + trees[path_index].query(0, last) - penguins[top_of_path];
}

int query(int u, int v) {
	int t = _lca(u, v);

	return query_topdown(t, u) + query_topdown(t, v) - penguins[t];
}



int main() {

	//FAST IO
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> penguins[i];
	}
	cin >> Q;
	for (int i = 0; i < Q; i++) {
		cin >> command >> A >> B;
		queries[i] = { command.front() , A, B };
		if (command == "bridge") {
			uf.merge(A, B);
			adj[A].push_back(B);
			adj[B].push_back(A);
		}
	}

	for (int vertex = 1; vertex <= N; vertex++) {
		if (uf.find(vertex) == vertex) {
			uf.merge(ROOT, vertex);
			adj[ROOT].push_back(vertex);
			adj[vertex].push_back(ROOT);
		}
	}

	vector<bool> visited(N + 2, false);
	lca[0][ROOT] = -1;
	exp_ancestor[0] = vector<int>();
	dfs(ROOT, visited);
	lca_init();

	heavy_light_decomposion(ROOT);
	init_tree();

	for (int vertex = 0; vertex <= N + 1; vertex++) {
		uf.parent[vertex] = vertex;
	}

	for (int i = 0; i < Q; i++) {
		auto [operation, a, b] = queries[i];

		if (queries[i].command == 'b') {
			if (uf.merge(a, b)) {
				cout << "yes\n";
			}
			else {
				cout << "no\n";
			}
		}
		else if (operation == 'e') {
			if (uf.find(queries[i].a) == uf.find(queries[i].b)) {
				cout << query(queries[i].a, queries[i].b) << '\n';
			}
			else {
				cout << "impossible\n";
			}
		}
		else {//if operation == penguins
			update(queries[i].a, queries[i].b);
		}
	}


	

}