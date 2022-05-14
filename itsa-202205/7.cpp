#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct Account {
    int _Money = 0;
    void add(int money) {
        _Money += money;
    }
    void remove(int money) {
        if (money > _Money) {
            cout << "Insufficient Balance" << endl;
            return;
        }
        _Money -= money;
    }
};

namespace itsa7 {
    void round(double& num, int n) {
        int t = pow(10, n);
        int temp = int(num * t);
        num = temp / (double)t;
    }
    int pow(int n, int t) {
        while (t--) {
            n *= n;
        }
        return n;
    }
}

int main()
{
    string input;
    Account A, B;
    while (getline(cin, input)) {
        string command[3]{};
        int index = 0;
        for (char c : input) {
            if (c == ' ') {
                index++;
                continue;
            }
            command[index] += c;
        }
        if (command[0] == "v") {
            cout << "A : " << A._Money << " , B : " << B._Money << endl;
        }
        else if (command[0] == "p") {
            double all = A._Money + B._Money;
            if (all == 0.0) {
                cout << setprecision(1) << fixed << "A : " << 0.0 << "% , B : " << 0.0 << "%" << endl;
                continue;
            }
            double a = (A._Money / all) * 100;
            double b = 100.0 - a;
            itsa7::round(a, 1);
            itsa7::round(b, 1);
            cout << setprecision(1) << fixed << "A : " << a << "% , B : " << b << "%" << endl;
        }
        else if (command[0] == "s") {
            if (command[1] == "a") {
                A.add(stoi(command[2]));
            }
            else if (command[1] == "b") {
                B.add(stoi(command[2]));
            }
        }
        else if (command[0] == "w") {
            if (command[1] == "a") {
                A.remove(stoi(command[2]));
            }
            else if (command[1] == "b") {
                B.remove(stoi(command[2]));
            }
        }
        else if (command[0] == "-1") {
            break;
        }
    }
}