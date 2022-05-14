#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;
    while (n--) {
        int m;
        cin >> m;
        int one = 1;
        int result = 1;
        while (one %= m) {
            one = one * 10 + 1;
            result++;
        }
        cout << result << endl;
    }
}