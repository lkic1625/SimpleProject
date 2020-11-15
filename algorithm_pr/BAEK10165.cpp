#include<iostream>
#include<set>
#include<tuple>
#include<queue>

using namespace std;

struct Route {
	int start, end, index;
};

auto compare_length = [](const Route& lv, const Route& rv) {
	if (lv.end - lv.start == rv.end - rv.start)
		return lv.start < rv.start;
	return lv.end - lv.start > rv.end - rv.start;
};

auto compare_x = [](const Route& lv, const Route& rv) {
	return lv.start < rv.start;
};

const int MAX_M = 500000 + 5, MAX_N = 1e9;
int N, M, a, b, isCanceled[MAX_M];
Route sorted_by_length[MAX_M];
set<Route, decltype(compare_x)> sorted_by_x(compare_x);

int main() {
	//FAST IO
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	
	cin >> N >> M;
	for (int i = 1; i <= M; i++) {
		cin >> a >> b;
		//bus route is a circle
		if (a > b) {
			sorted_by_length[i] = { a, b + N, i };
			sorted_by_x.insert({ a, b + N, i });
		}
		else {
			sorted_by_length[i] = { a, b, i };
			sorted_by_x.insert({ a, b, i });
			sorted_by_x.insert({ a + N, b + N, i });
		}
		
	}

	sort(sorted_by_length, sorted_by_length + M + 1, compare_length);

	for (auto route : sorted_by_length) {
		auto [start, end, index] = route;

		if (isCanceled[index]) continue;

		for (auto iter = sorted_by_x.find(route); iter != sorted_by_x.end();) {
			auto [nextStart, nextEnd, nextIndex] = *iter;

			if (nextStart >= end) {
				break;
			}
			if (nextEnd <= end && index != nextIndex) { 
				iter = sorted_by_x.erase(iter);
				isCanceled[nextIndex] = true; 
			}
			else {
				iter++;
			}
		}
	}

	for (int i = 1; i <= M; i++) {
		if (isCanceled[i]) continue;
		cout << i << " ";
	}
}

