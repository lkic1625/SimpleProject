#include<iostream>
#include<algorithm>
#include<string.h>
#include<queue>


using namespace std;

const long long MAX_LENGTH = 32767; // == 2 ^ 15 - 1
const long long MAX_M = 1000 + 1, MAX_N = 5000 + 3;
const long long MAX = MAX_N * MAX_N * MAX_LENGTH;
int K, N, length, chopsticks[MAX_N], points[MAX_N];	
long long dp[MAX_N][MAX_M];

int main() {
	
	//init
	//Memset is a char array only initialization function 
	//and sometimes does not work well in large arrays.
	for (int i = 0; i < MAX_N; i++) {
		for (int j = 0; j < MAX_N; j++) {
			dp[i][j] = MAX;
		}
	}
	

	//input
	cin >> K >> N;
	for (int i = 0; i < N; i++) {
		cin >> chopsticks[i];
	}
	
	//sorting chopsticks
	sort(chopsticks, chopsticks + N);
	
	//get points 
	for (int i = 0; i < N - 1; i++) {
		int A = chopsticks[i], B = chopsticks[i + 1];
		points[i] = (A - B) * (A - B);
	}

	//dp
	dp[N - 1][0] = dp[N - 2][0] = 0;
	for (int i = N - 3; i >= 0; i--) {
		for (int j = 0; i + j <= N - 2 && j <= K; j++) {
			if (j > 0) {
				dp[i][j] = min(dp[i + 1][j - 1], dp[i + 2][j] + points[i]);
			} 
			else {
				dp[i][j] = dp[i + 1][j];
			}
		}
	}

	cout << dp[0][K] << endl;
}