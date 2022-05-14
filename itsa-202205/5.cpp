#include <iostream>
#include <string>
using namespace std;

int main()
{
    int n;
    cin >> n;
    int G = 1;
    int i;
    int j;
    for (int i = 0; i < n - 1; i++) {
        G *= 10;
    }
    for (i = 1; i < G; i++) {
        string str = to_string(i);
        int plus = 0;
        int times = 1;
        for (char c : str) {
            int digit = c - '0';
            if (digit == 0) {
                times = 0;
                break;
            }
            plus += digit;
            times *= digit;
        }
        if (plus == times) {
            cout << str << endl;
        }
    }
}