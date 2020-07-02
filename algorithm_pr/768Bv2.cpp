#include<iostream>
typedef long long ll;
using namespace std;

const int ELEMENT_MAXIMUM = 50;
ll n, l, r, cache[ELEMENT_MAXIMUM + 1] = { 1 , };

int search(ll n, ll l, ll r, int height) {
	

}

int main() {
	
	int ans = 0;
	
	for (int i = 1; i < ELEMENT_MAXIMUM; i++) {
		cache[i - 1] = cache[i] * 2;
	}
	
	cin >> n >> l >> r;	
	
	
	




}


