#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Trie {
	bool lastNum;
	Trie* nextNum[10];

	Trie() {
		this->lastNum = false;
		for (int i = 0; i < 10; i++)
			this->nextNum[i] = NULL;
	}
	~Trie() {
		for (int i = 0; i < 10; i++)
			if (this->nextNum[i] != NULL)
				delete nextNum[i];
	}
};

int main()
{
	int test_case;
	cin >> test_case;
	int N;
	for (int t = 0; t < test_case; t++) {
		Trie *root = new Trie();
		vector<string>v;
		cin >> N;
		string input;
		for (int i = 0; i < N; i++) {
			cin >> input;
			v.push_back(input);
		}
		sort(v.begin(), v.end());
		bool Exit = false;
		for (int i = 0; i < N; i++) {
			Trie* now = root;
			for (int j = 0; j < v[i].size(); j++) {
				if (now->lastNum) 
					Exit = true;				
				else if(now->nextNum[v[i][j]-'0']==NULL){
					Trie* newTrie = new Trie();
					now->nextNum[v[i][j] - '0'] = newTrie;
					now = newTrie;
				}
				else 
					now = now->nextNum[v[i][j]-'0'];
			}
			now->lastNum = true;
		}
		if (Exit) 
			cout << "NO" << endl;
		else
			cout << "YES" << endl;

		delete root;
	}
	return 0;
}