#include <iostream>

using namespace std;

struct Trie {
	bool word;
	Trie* nextNum[10];

	Trie() {
		this->word = false;
		for (int i = 0; i < 10; i++) {
			cout << "¤»¤»¤»" << endl;
			// this->nextNum[i] = NULL;
		}
			
	}
};

int main()
{
	int test_case;
	cin >> test_case;
	int N;
	for (int t = 0; t < test_case; t++) {
		Trie root;
		cin >> N;
		string input;
		bool Exit = false;
		for (int i = 0; i < N; i++) {
			cin >> input;
			Trie* now = &root;
			for (int j = 0; j < input.size(); j++) {
				if (now->nextNum[input[j] - '0'] == NULL) {
					Trie newTrie;
					now->nextNum[input[j] - '0'] = &newTrie;
					now = &newTrie;
				}
				else 
					now = now->nextNum[input[j] - '0'];
				
				if (now->word) {
					Exit = true;
					break;
				}
				if (j == input.size() - 1)
					now->word = true;
			}

		}
		if (Exit) 
			cout << "NO" << endl;
		else
			cout << "YES" << endl;
	}
	return 0;
}