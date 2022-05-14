#include <iostream>

using namespace std;

int main()
{
    int n = 0;
    cin >> n;
    int** map;
    map = new int* [n];
    int i = 0, j = 0;
    for (i = 0; i < n; i++) {
        map[i] = new int[n];
        for (j = 0; j < n; j++)
            cin >> map[i][j];
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            int count = 0;
            if (map[i][j] == 1) {
                if (j != n - 1) {
                    cout << 0 << " ";
                }
                else {
                    cout << 0;
                }
            }
            else {
                if (i - 1 >= 0 && j - 1 >= 0 && map[i - 1][j - 1] == 1) {
                    count++;
                }
                if (j - 1 >= 0 && map[i][j - 1] == 1) {
                    count++;
                }
                if (j - 1 >= 0 && i + 1 < n && map[i + 1][j - 1] == 1) {
                    count++;
                }
                if (i - 1 >= 0 && map[i - 1][j] == 1) {
                    count++;
                }
                if (i + 1 < n && map[i + 1][j] == 1) {
                    count++;
                }
                if (j + 1 < n && i - 1 >= 0 && map[i - 1][j + 1] == 1) {
                    count++;
                }
                if (j + 1 < n && map[i][j + 1] == 1) {
                    count++;
                }
                if (i + 1 < n && j + 1 < n && map[i + 1][j + 1] == 1) {
                    count++;
                }
                if (j != n - 1) {
                    cout << count << " ";
                }
                else {
                    cout << count;
                }
            }
        }
        cout << endl;
    }
    for (i = 0; i < n; i++) 
        delete map[i];
    delete[] map;
}