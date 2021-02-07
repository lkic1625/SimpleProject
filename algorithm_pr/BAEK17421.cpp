#include<iostream>
#include<algorithm>
#include<stack>
#include<vector>

using namespace std;

const long long MAX_N = 100'000 + 5, MAX_HEIGHT = 1'000'000, TIME_BOUND = MAX_N * MAX_HEIGHT;

long long N, K, height[MAX_N], ans, k;

struct Segment {
    int left, right, height, pre_count;
};

int main() {
    //FAST I/O
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> N >> K;

    stack<Segment> st;
  
    for (int i = 0; i <= N; i++) {
        if (i < N) {
            cin >> height[i];
        }

        int left = i;
        int acc = 0;
        bool isFirst = true;

        while (st.empty() && st.top().height >= height[i]) {
            left = st.top().left;

            int epsilon = st.top().height - height[i];
            if (epsilon > 0) {

            }
        }
        
    }

}