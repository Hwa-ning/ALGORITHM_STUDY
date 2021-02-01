#include <iostream>
#include <map>
using namespace std;

int N, M;
map<string,string>site_password;

int main()
{
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> N >> M;
	for (int i = 0; i < N; ++i) {
		string site, pw;
		cin >> site >> pw;
		site_password.insert({ site, pw });
	}

	for (int i = 0; i < M; ++i) {
		string input;
		cin >> input;
		cout << site_password.find(input)->second << "\n";
	}
}