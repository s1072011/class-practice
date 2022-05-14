#include <iostream>

using namespace std;

class Building {
    int L, R, H;
public:
    friend istream& operator>>(istream& is, Building& res) {
        is >> res.L >> res.R >> res.H;
        return is;
    }
    friend class Result;
};

class Result {
    int _Max = 0;
    int* _Ans = 0;
public:
    ~Result() {
        delete[] _Ans;
    }
    void set_max(const Building& b) {
        if (b.R > _Max) {
            _Max = b.R;
        }
    }
    void check(const Building& b) {
        for (int i = b.L; i <= b.R; i++) {
            if (b.H > _Ans[i]) {
                _Ans[i] = b.H;
            }
        }
    }
    void init() {
        _Max++;
        _Ans = new int[_Max];
        memset(_Ans, 0, sizeof(int) * _Max);
    }
    friend ostream& operator<<(ostream& os, Result& res) {
        for (int i = 0; i < res._Max; i++) {
            os << res._Ans[i];
            if (i < res._Max - 1) {
                os << " ";
            }
        }
        return os;
    }
};

int main()
{
    int n;
    cin >> n;
    while (n--) {
        int m;
        cin >> m;
        Building* b = new Building[m];
        Result res;
        int i;
        for (i = 0; i < m; i++) {
            cin >> b[i];
            res.set_max(b[i]);
        }
        res.init();
        for (i = 0; i < m; i++) {
            res.check(b[i]);
        }
        cout << res << endl;
        delete[] b;
    }
}