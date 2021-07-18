#include <iostream>
#include <string>
#include <map>

using namespace std;

map<string, int>m;
int main()
{
	string input;
	int tree_count = 0;
	while(getline(cin, input)) {
		if (m.find(input) == m.end()) 
			m.insert({ input,1 });
		else
			m[input]++;
		tree_count++;
	}
	map<string, int>::iterator it;

	cout << fixed;
	cout.precision(4);
	for (it = m.begin(); it != m.end(); it++)
		cout << it->first << " "<<(double) it->second / tree_count * 100 << endl;
}