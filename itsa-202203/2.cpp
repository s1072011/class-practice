#include <iostream>
#include <string>

using namespace std;

int main()
{
	string account[6] = { "123","456","789","336","775","566" };
	string pass[6] = { "456","789","888","558","666","221" };
	int last[6] = { 9000,5000,6000,10000,12000,7000 };
	int User = -1;
LOGIN:
	string user;
	string pw;
	cin >> user >> pw;
	int count = 0;
	for (int i = 0; i < 6; i++) {
		if (account[i] == user) {
			if (pass[i] != pw) {
				cout << "ERROR" << endl;
				goto LOGIN;
			}
			else {
				User = i;
				count = 0;
				cout << "OK" << endl;
				break;
			}
		}
		count++;
	}
	if (count == 6) {
		cout << "ERROR" << endl;
		goto LOGIN;
	}
	string s;
	while (cin >> s) {
		if (s == "L") {
			string input;
			cin.ignore(1, ' ');
			getline(cin, input);
			int money = 0, digit = 1;
			for (int i = input.length() - 1; i >= 0; i--) {
				if (input[i] >= 48 && input[i] <= 57) {
					money += (input[i] - '0') * digit;
					digit *= 10;
				}
				else {
					money = 0;
					cout << "ERROR" << endl;
					break;
				}
			}
			if (money > last[User]) {
				cout << "ERROR" << endl;
			}
			else if (money != 0) {
				last[User] = last[User] - money;
				cout << "OK" << endl;
			}
		}
		else if (s == "S") {
			cout << last[User] << endl;
		}
		else if (s == "E") {
			cout << "BYE" << endl;
			break;
		}
		else {
			string trash;
			getline(cin, trash);
			cout << "ERROR" << endl;
		}
	}
}