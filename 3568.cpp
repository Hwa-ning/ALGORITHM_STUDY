#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<string>v;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	string input;
	getline(cin,input);
	string word="";
	string type="";
	for (int i = 0; i < input.length(); i++) {
		if (input[i] == ' ') {
			type = word;
			word.clear();
		}
		else if (input[i] == ',') {
			v.push_back(word);
			i++;
			word.clear();
		}
		else if (input[i] == ';')
			v.push_back(word);
		else
			word += input[i];
	}

	for (int i = 0; i < v.size(); i++) {
		cout << type;
		bool is_first = true;
		for (int j = v[i].size() - 1; j >= 0; j--)
		{
			if (v[i][j] == ']') {
				cout << "[]";
				j--;
				continue;
			}
			else if ('a' <= v[i][j] && v[i][j] <= 'z' || 'A' <= v[i][j] && v[i][j] <= 'Z') {
				string temp = "";
				while (true)
				{
					if (j < 0)
						break;
					if (!((v[i][j] >= 'a' && v[i][j] <= 'z') || (v[i][j] >= 'A' && v[i][j] <= 'Z')))
						break;
					else {
						temp += v[i][j];
						j--;
					}
				}
				reverse(temp.begin(), temp.end());
				cout << " " << temp;
			}
			else
				cout << v[i][j];
		}
		cout << ";" << "\n";
	}
}