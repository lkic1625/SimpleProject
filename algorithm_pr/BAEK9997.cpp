#include<iostream>
#include<string>
#include<math.h>

#define AND &
#define OR |

using namespace std;

const int MAX = 26;
const int ALPHABET_SIZE = 26;
const int CONTAINED_ALL = (1 << ALPHABET_SIZE) - 1;

int N;
int word_to_bits[MAX];
string words[MAX];


int traversal(int i, int contained) {
    if(i > N) return 0;
    if(contained == CONTAINED_ALL){
        return pow(2, N - i);
    }

    int contained_with_i = contained OR word_to_bits[i];
    return traversal(i + 1, contained_with_i) + traversal(i + 1, contained);
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
	    cin >> words[i];
		for (char alphabet : words[i]) {
			word_to_bits[i] = word_to_bits[i] OR 1 << (alphabet - 'A');
		}
	}
	int ans = traversal(0, 0);
	cout << ans;
	//combination = (1 << N) - 1;
	//for (int subset = combination; subset; subset = ((subset - 1) AND combination)) {
        //TLE
        //6천만개
	//}
}