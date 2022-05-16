#include <iostream>
#include <exception>
#include <iomanip>

using namespace std;

class dimension_exception :public exception {
public:
    dimension_exception()
        :exception("dimension exception") {}
    explicit dimension_exception(const char* _Msg)
        :exception(_Msg) {}
};

class singular_exception : public exception {
public:
    singular_exception()
        :exception("singular exception") {}
    explicit singular_exception(const char* _Msg)
        :exception(_Msg) {}
};

class MATRIX {
private:
    size_t     _Row;
    size_t     _Column;
    MATRIX* _Inversed_mat{ 0 };
    double** _Matrix;
    void check(double& num) {
        if (num < DBL_EPSILON && num > -DBL_EPSILON) {
            num = 0.0;
        }
    }
    void free() {
        if (_Matrix != 0) {
            for (size_t i = 0; i < _Row; i++)
                delete[] _Matrix[i];
            delete[] _Matrix;
        }
        delete _Inversed_mat;
    }
    //交換row
    void swap(double*& row_1, double*& row_2) {
        double* temp = row_1;
        row_1 = row_2;
        row_2 = temp;
    }
    //計算行列式值
    double get_determinant(const MATRIX& matrix) {
        if (matrix._Row != matrix._Column)
            throw dimension_exception("not a square matrix");
        size_t size = matrix._Row;
        if (size == 1)
            return matrix[0][0];
        else if (size == 2)
            return matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
        double determinant_value = 0;
        MATRIX temp(size - 1);
        for (size_t k = 0; k < size; k++) {
            //降階
            for (size_t i = 1, new_i = 0; i < size; i++, new_i++) {
                for (size_t j = 0, new_j = 0; j < size; j++) {
                    if (j == k) continue;
                    temp[new_i][new_j] = matrix[i][j];
                    new_j++;
                }
            }
            determinant_value += pow(-1, k) * matrix[0][k] * get_determinant(temp);
        }
        return determinant_value;
    }
public:
    MATRIX() :_Row(0), _Column(0), _Matrix(0) {}

    MATRIX(initializer_list<initializer_list<double>> matrix) {
        _Row = matrix.size();
        _Column = 0;
        size_t i;
        size_t j;
        for (i = 0; i < _Row; i++) {
            size_t size = matrix.begin()[i].size();
            if (size > _Column) _Column = size;
        }
        init();
        for (i = 0; i < _Row; i++)
            for (j = 0; j < matrix.begin()[i].size(); j++)
                _Matrix[i][j] = matrix.begin()[i].begin()[j];
    }

    explicit MATRIX(size_t size) :_Row(size), _Column(size) {
        init();
    }

    explicit MATRIX(size_t row, size_t column) :_Row(row), _Column(column) {
        init();
    }

    MATRIX(const MATRIX& matrix) {
        *this = matrix;
    }

    ~MATRIX() {
        free();
    }
    //初始化_Matrix, 把每個元素設成0
    void init() {
        try {
            _Matrix = new double* [_Row];
            for (size_t i = 0; i < _Row; i++) {
                _Matrix[i] = new double[_Column];
                for (size_t j = 0; j < _Column; j++)
                    _Matrix[i][j] = 0.0;
            }
        }
        catch (const bad_alloc& e) {
            cerr << e.what() << endl;
            free();
            exit(-1);
        }
    }
    //設成單位矩陣
    void set_identity() {
        for (size_t i = 0; i < _Row; i++) {
            for (size_t j = 0; j < _Column; j++) {
                _Matrix[i][j] = (i == j) ? 1 : 0;
            }
        }
    }
    //沒參數，給外部用起來比較直觀，不須傳入參數，回傳行列式值
    double get_determinant() {
        return get_determinant(*this);
    }
    //計算反矩陣, 回傳MATRIX物件
    const MATRIX& inverse() {
        if (_Row != _Column)
            throw dimension_exception("not a square matrix");
        if (!get_determinant(*this))
            throw singular_exception();
        MATRIX temp = *this;
        MATRIX temp_inversed(_Row, _Column);
        temp_inversed.set_identity();
        size_t r = 0;
        size_t c = 0;
        size_t i;
        size_t j;
        while (r < _Row && c < _Column) {
            size_t row_max = r;
            for (i = r; i < _Row; i++) {
                if (fabs(temp[i][c]) > fabs(temp[row_max][c]))
                    row_max = i;
            }
            swap(temp[r], temp[row_max]);
            swap(temp_inversed[r], temp_inversed[row_max]);
            double f;
            for (i = 0; i < _Row; i++) {
                if (i != r) {
                    f = temp[i][c] / temp[r][c];
                    for (j = 0; j < _Column; j++) {
                        temp[i][j] -= temp[r][j] * f;
                        temp_inversed[i][j] -= temp_inversed[r][j] * f;
                        check(temp[i][j]);
                        check(temp_inversed[i][j]);
                    }
                }
                else {
                    f = temp[r][c];
                    if (f == 1) continue;
                    for (j = 0; j < _Column; j++) {
                        temp[i][j] /= f;
                        temp_inversed[i][j] /= f;
                        check(temp[i][j]);
                        check(temp_inversed[i][j]);
                    }
                }
            }
            r++;
            c++;
        }
        _Inversed_mat = new MATRIX(temp_inversed);
        return *_Inversed_mat;
    }
    //重載operator[], 回傳_Matrix[m]
    double*& operator[](size_t index) {
        return _Matrix[index];
    }

    double*& operator[](size_t index) const {
        return _Matrix[index];
    }
    //MATRIX物件可以用等號賦值
    MATRIX& operator=(const MATRIX& other) {
        free();
        _Row = other._Row;
        _Column = other._Column;
        init();
        for (size_t i = 0; i < _Row; i++)
            for (size_t j = 0; j < _Column; j++)
                _Matrix[i][j] = other[i][j];
        return *this;
    }

    friend istream& operator>>(istream& is, const MATRIX& matrix) {
        for (size_t i = 0; i < matrix._Row; i++)
            for (size_t j = 0; j < matrix._Column; j++)
                is >> matrix[i][j];
        return is;
    }

    friend ostream& operator<<(ostream& os, const MATRIX& matrix) {
        for (size_t i = 0; i < matrix._Row; i++) {
            for (size_t j = 0; j < matrix._Column; j++)
                os << setw(12) << matrix[i][j];
            os << endl;
        }
        return os;
    }
};

int main() {
    int row, column;
    cin >> row >> column;
    MATRIX m(row, column);
    cin >> m;
    cout << m << endl;
    try
    {
        cout << m.inverse() << endl;
    }
    catch (const dimension_exception& e)
    {
        cerr << e.what() << endl;
    }
    catch (const singular_exception& e)
    {
        cerr << e.what() << endl;
    }
}
