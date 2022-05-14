#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;
    while (n--) {
        int N[4]{};
        cin >> N[0];
        cin >> N[1];
        cin >> N[2];
        cin >> N[3];
        int ans = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = i + 1; j < 4; j++) {
                if (N[i] > N[j]) {
                    ans++;
                }
            }
        }
        cout << ((ans & 1) ? 'B' : 'A') << endl;
    }
}