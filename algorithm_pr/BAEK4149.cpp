#include<iostream>
#include<vector>

#include<algorithm>


using ull = unsigned long long;

using namespace std;

vector<ull> factors;
ull n;

ull add_with_mod(ull a, ull b, ull mod) {
	a = a % mod;
	b = b % mod;
	return (a + b) % mod;
}

ull mul_with_mod(ull a, ull b, ull mod) {
	a = a % mod;
	b = b % mod;
	ull ret = 0;
	while (b > 0) {
		if (b % 2 == 1) {
			ret = add_with_mod(ret, a, mod);
		}
		a = add_with_mod(a, a, mod);
		b = b >> 1;
	}

	return ret;
}



//return a^b % mod
ull pow_with_mod(ull a, ull b, ull mod) {

	a = a % mod;
	ull ret = 1;
	while (b > 0) {
		if (b % 2 == 1) {
			ret = mul_with_mod(ret, a, mod);
		}
		a = mul_with_mod(a, a, mod);
		b = b >> 1;
	}

	return ret;
}


bool miller_rabin_primality_test(ull n, ull a) {
	
	ull d = n - 1;
	while (d % 2 == 0) {
		if (pow_with_mod(a, d, n) == n - 1) { 
			return true;
		}
		d = d >> 1;
	}

	ull pow_of_a_d = pow_with_mod(a, d, n);
	return pow_of_a_d == n - 1 || pow_of_a_d == 1;

}

bool is_prime(ull n) {
	if( n <= 1 ) return false;
	if (n <= 1000000000ULL) {
		for (ull i = 2; i * i <= n; i++) {
			if (n % i == 0) {
				return false;
			}
		}
		return true;
	}
	for (ull a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
		if (!miller_rabin_primality_test(n, a)) {
			return false;
		}
	}
	return true;
}

ull abs(ull a) {
	return a > 0 ? a : -1 * a;
}

ull gcd(ull a, ull b) {
	if (a < b) swap(a, b);
	if (b == 0) return a;
	return gcd(b, a % b);
}

void factorize(ull n) {
	if (n <= 1) return;
	
	if (is_prime(n)) {
		factors.push_back(n);
		return;
	}

	ull x = 2, q = 1, g = 1, xs, y, c = rand() % 10 + 1;

	auto f = [=](ull x) {
		return ((__int128_t)x * x + c) % n;
	};

	int m = 128;
	int l = 1;
	while (g == 1) {
		y = x;
		for (int i = 1; i < l; i++) {
			x = f(x);
		}
		int k = 0;
		while (k < l && g == 1) {
			xs = x;
			for (int i = 0; i < m && i < l - k; i++) {
				x = f(x);
				q = mul_with_mod(q, abs(y - x), n);
			}
			g = gcd(q, n);
			k += m;
		}
		l *= 2;
	}
	if (g == n) {
		do {
			xs = f(xs);
			g = gcd(abs(xs - y), n);
		} while (g == 1);
	}
	factorize(g);
	factorize(n / g);

}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> n;
	factorize(n);

	sort(factors.begin(), factors.end());
	for (auto factor : factors) {
		cout << factor << '\n';
	}
}