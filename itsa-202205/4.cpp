#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;
    int size = n + 1;
    int i, j;
    int** path;
    path = new int* [size];
    for (i = 0; i < size; i++) {
        path[i] = new int[size];
        for (j = 0; j < size; j++) {
            if (i == j)
                path[i][j] = 0;
            else
                path[i][j] = 50;
        }
    }
    int e;
    cin >> e;
    while (e--) {
        int days;
        cin >> i >> j >> days;
        path[i][j] = days;
    }

    int* result = new int[size];
    for (i = 0; i < size; i++) {
        result[i] = *(*(path + 1) + i);
    }

    int temp;
    for (i = 2; i < size; i++) {
        for (j = i + 1; j < size; j++) {
            temp = result[i] + path[i][j];
            if (temp < result[j]) {
                result[j] = temp;
            }
        }
    }
    for (i = size - 1; i > 2; i--) {
        for (j = i - 1; j > 1; j--) {
            temp = result[i] + path[i][j];
            if (temp < result[j]) {
                result[j] = temp;
            }
        }
    }
    for (i = 2; i < size; i++) {
        for (j = i + 1; j < size; j++) {
            temp = result[i] + path[i][j];
            if (temp < result[j]) {
                result[j] = temp;
            }
        }
    }

    cout << result[size - 1] << endl;

    for (i = 0; i < size; i++) {
        delete[] path[i];
    }
    delete[] path;
    delete[] result;
}