#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
	string input;
	cin >> input;
	string temp1, temp2;
	int num1, num2;
	int i = 0;
	for (; i < input.length(); i++) {
		if (input.at(i) == ':')
		{
			i++;
			break;
		}
		else
			temp1 += (input.at(i));
	}

	for (; i < input.length(); i++)
		temp2 += (input.at(i));

	num1 = stoi(temp1);
	num2 = stoi(temp2);

	int j = min(num1, num2);
	for (int i = 2; i <= j; i++) {
		if (num1 % i == 0 && num2 % i == 0)
		{
			num1 /= i;
			num2 /= i;
			i--;
		}
	}
	cout << num1 << ":" << num2 << endl;
}