#include <iostream>

using namespace std;

int main()
{
	int n;
	cin >> n;
	while (n--) {
		char num[10];
		int N = 0, S = 0, G = 0, bad = 0;
		int i;
		cin >> num;
		for (i = 0; i < 8; i++) {
			N += num[i] - '0';
		}
		bad = num[8] - '0';
		for (i = 1; i < N; i++) {
			if (N % i == 0) {
				S += i;
			}
		}
		G = S + bad;
		if (N == G) {
			cout << 0 << endl;
		}
		else if (N < G) {
			cout << G - N << endl;
		}
		else if (N > G) {
			cout << -1 << endl;
		}
	}
}