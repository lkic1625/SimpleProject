/*
https://codeforces.com/problemset/problem/1336/A
A. Linova and Kingdom

Input
The first line contains two integers n and k (2≤n≤2⋅10^5, 1≤k<n)  — the number of cities and industry cities respectively.

Each of the next n−1 lines contains two integers u and v (1≤u,v≤n), denoting there is a road connecting city u and city v.

It is guaranteed that from any city, you can reach any other city by the roads.

Output
Print the only line containing a single integer 
— the maximum possible sum of happinesses of all envoys.

*/

#include<iostream>
#include<vector>

using namespace std;

const int MAX_ELEMENT = 2.0e5;
int n, k, u, v;
vector<int> adj[MAX_ELEMENT], dfsSequence;
int cache[MAX_ELEMENT][2];

void dfs(int bef, int cur) {
	for (int i = 0; i < adj[cur].size(); i++) {
		if(adj[cur][i] = bef)
	}
}

int dp(int befElement, int isIndustry) {

}

int main() {

	//fast I/O
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//input
	cin >> n >> k;
	for (int i = 0; i < n - 1; i++) {
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}


}
