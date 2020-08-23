/*

SCPC 1�� ���� 

������ �ٱ�

Greedy

input
�Է� ���Ͽ��� ���� ���� �׽�Ʈ ���̽��� ���Ե� �� �ִ�.
������ ù° �ٿ��� �׽�Ʈ ���̽� ������ ��Ÿ���� �ڿ��� T�� �־�����,
���� ���ʷ� T���� �׽�Ʈ ���̽��� �־�����. ( 1��T��5 )
������ �׽�Ʈ ���̽� ù ��° �ٿ��� '��ǥ 0'�� ���� ���� ������ ������ ������ ���� N �� �־�����. ( 1��N��1,000,000 )
�� ��° �ٿ��� ������ ���� ��ǥ�� ��Ÿ���� N ���� ���� ai���� ��ĭ(����)�� ���̿� �ΰ� �־�����. (1��ai��10^9 )
���⼭, �־��� ��ǥ���� �����ϴ� ������ �־����� ��� �ٸ���.
�� ��° �ٿ��� �������� �� ���� ������ �̵� ������ �ִ� �Ÿ� K �� �־�����. ( 1��K��10^9 )

output
�� �׽�Ʈ ���̽��� ���� ������� ǥ��������� ����Ͽ��� �ϸ�, �� �׽�Ʈ ���̽����� ù �ٿ� ��Case #T���� ����Ͽ��� �Ѵ�.
�̶� T�� �׽�Ʈ ���̽��� ��ȣ�̴�.
�� ���� �ٿ��� �������� ������ ���� �̵��� �� �ִ� �ּ� ���� Ƚ���� ����Ѵ�.
����, �������� ������ ���� �̵��ϴ� ���� �Ұ����� ��쿡�� "-1"�� ����Ѵ�.
*/
#include <iostream>
#include<algorithm>

using namespace std;

const int MAX_STONES_COUNT = 1.0e+6, MAX_VALUE = 1.0e+9;
int Answer, N, a[MAX_STONES_COUNT + 2], K, isjumpable;

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	
	int T, test_case;
	
	cin >> T;
	for (test_case = 0; test_case < T; test_case++)
	{
		//init
		Answer = 0;

		//input
		cin >> N;
		for (int i = 1; i <= N; i++) {
			cin >> a[i];
		}
		cin >> K;

		//greedy
		for (int i = 0; i < N + 1;) {
			isjumpable = false;
			int jump = i;
			for (; a[jump + 1] - a[i] <= K && jump <= N; jump++) {
				//Go forward as much as possible if we can.
				isjumpable = true;
			}
			if (!isjumpable) {
				//If we can't move a single step, output -1.
				Answer = -1;
				break; 
			}
			i = jump;
			Answer++;
		}

		//output
		cout << "Case #" << test_case + 1 << endl;
		cout << Answer << endl;
	}

	return 0;
}