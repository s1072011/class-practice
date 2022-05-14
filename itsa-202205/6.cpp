#include <iostream>
#include <string>
#include <math.h>
using namespace std;

int main()
{
    int P;
    cin >> P;
    while (P--) {
        int arr[6];//H M h m E D
        for (int i = 0; i < 6; i++) {
            cin >> arr[i];
        }
        int h = arr[2] - arr[0];
        int m = arr[3] - arr[1];
        if (m < 0) {
            m += 60;
            h --;
        }
        if(m!=0) {
            h++;
        }
        cout << h * arr[4] * arr[5] << endl;
    }
}