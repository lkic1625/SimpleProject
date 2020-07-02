#include<algorithm>
#include<map>
#include<queue>
#include<cstdio>
#include<cstring>
#include<cassert>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

int C, N, M;
const int ALPHABETS = 26;
int toNumber(char ch) { return ch - 'A'; }

// Ʈ������ �� ��带 ��Ÿ���� ��ü
struct TrieNode {
	TrieNode* children[ALPHABETS];
	// �� ��ġ���� ������ ���ڿ��� ��ȣ
	int terminal;

	// �� ��忡�� ��Ī�� �������� �� �� ������ ���� ����Ѵ�.
	// �� ��忡 �����Ǵ� ���ڿ��� ���̻��̸鼭 Ʈ���̿� ���Ե� �ִ� ���ڿ�.
	TrieNode* fail;
	// �� ��尡 �湮�Ǿ��� �� �����ϴ� ���ڿ����� ��ȣ
	vector<int> output;

	TrieNode() : terminal(-1) {
		memset(children, 0, sizeof(children));
	}

	~TrieNode() {
		for (int i = 0; i < ALPHABETS; i++)
			if (children[i])
				delete children[i];
	}

	// �� ��带 ��Ʈ�� �ϴ� Ʈ���̿� ��ȣ�� id �� ���ڿ� key �� �߰��Ѵ�
	void insert(const char* key, int id) {
		// ���ڿ��� ������ terminal �� ������ �ٲٰ� ����
		if (*key == 0)
			terminal = id;
		else {
			int next = toNumber(*key);
			// �ش� �ڽ� ��尡 ���ٸ� �����Ѵ�
			if (children[next] == NULL)
				children[next] = new TrieNode();
			// �ش� �ڽ� ���� ���ȣ��
			children[next]->insert(key + 1, id);
		}
	}

	TrieNode* find(const char* key) {
		if (*key == 0) return this;
		int next = toNumber(*key);
		if (children[next] == NULL) return NULL;
		return children[next]->find(key + 1);
	}
};

void computeFailFunc(TrieNode* root) {
	queue<TrieNode*> q;
	root->fail = root;
	q.push(root);
	while(!q.empty()) {
		TrieNode* here = q.front();
		q.pop();
		for (int edge = 0; edge < ALPHABETS; edge++) {
			TrieNode* child = here->children[edge];
			if (!child) continue;
			if (here == root) child->fail = root;
			else {
				TrieNode* t = here->fail;
				while (t != root && t->children[edge] == NULL) {
					t = t->fail;
				}
				if (t->children[edge]) t = t->children[edge];
				child->fail = t;
				child->output = child->fail->output;
				if (child->terminal != -1) child->output.push_back(child->terminal);
				q.push(child);
			}
		}
	}
}

int main() {
	
}