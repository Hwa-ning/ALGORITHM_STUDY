#include <iostream>
#include <string>
using namespace std;
int main()
{
	string input;
	cin >> input;
	int alphabet[26] = { 0 };   // input�� ���� �󵵸� ���� �ش� ���ڰ� ��� ���Դ��� ����
								// A��� 0��° B��� 1��°...
	
	for(int i=0;i<input.size();i++)		// input.size()��ŭ ���� input ���θ�
		input[i] = toupper(input[i]);	// ��� ���ڵ��� �빮�ڷ�

	for (int i = 0; i < input.size(); i++)
		alphabet[(input[i] - 'A')]++;	// << input[i]-'A'�ؼ� A�� 0��° B�� 1��°�� ������ �ؼ� ++�ؼ� Ƚ�� count

	int max = 0;		// max
	int max_idx = -1;	// max �� ���� index�� ����

	for (int i = 0; i < 26; i++)
		if (alphabet[i] > max) {
			max = alphabet[i];
			max_idx = i;
		}

	for (int i = 0; i < 26; i++) {
		if (alphabet[i] == max && i != max_idx) {
			cout << "?" << endl;
			return 0;
		}
	}
	cout << (char)(max_idx + 'A') << endl;
}