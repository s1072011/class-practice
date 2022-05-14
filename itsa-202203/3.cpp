#include <iostream>
#include <string>

using namespace std;

int main()
{
	int n;
	cin >> n;
	cin.ignore();
	while (n--) {
		string s;
		string check[100];
		getline(cin, s);
		for (int i = 0; i < s.length(); i++) {
			for (int j = 0; j < s.length(); j++) {
				if (check[j] == "") {
					check[j] += s[i];
					break;
				}
				else {
					if (check[j][0] == s[i]) {
						check[j] += s[i];
						break;
					}
				}
			}
		}
		int max = 0;
		char ans;
		for (int i = 0; i < 100; i++) {
			if (check[i].length() > max) {
				max = check[i].length();
				ans = check[i][0];
			}
		}
		cout << ans << endl;
	}
}