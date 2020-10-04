#include<iostream>
#include<string>
#include<stack>
#include<queue>

using namespace std;

string str = "";
string parseStr;
stack<int> s;
queue<int> q;

int cur = 0;

enum 
{
	SQUARE_BRACKETS = '[',
	BRACKETS = '('
};

int Length;
bool isBalance(int bracket) {
	if (cur == parseStr.size() - 1) return false;
	bool ret = true;
	if (parseStr[cur] == SQUARE_BRACKETS || parseStr[cur] == BRACKETS) {
		ret = ret && isBalance(parseStr[cur++]);
	}
	else if (parseStr[cur] - bracket == 2 || parseStr[cur] - bracket == 1) {
		return ret && true;
	}
	else {
		return false;
	}
}

int main() {

	//FAST IO
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	string input;
	while (true) {
		cur = 0;
		getline(cin, str, '.');
		if (str == ".") break;
		for (auto iter : str) {
			if (iter == BRACKETS
				|| iter == BRACKETS + 1
				|| iter == SQUARE_BRACKETS
				|| iter == SQUARE_BRACKETS + 2)
			{
				parseStr += iter;
			}
		}
		
	
		parseStr += ']';

		cout << (isBalance('[') ? "yes" : "no") << '\n';
	}
	
}