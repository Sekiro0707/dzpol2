#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <Windows.h>

using namespace std;

template <class T>
class Matrix {
private:
    T** data;
    int rows, cols;


    void clear() {
        for (int i = 0; i < rows; i++) {
            delete[] data[i];
        }
        delete[] data;
    }

public:
    Matrix(int rows, int cols) : rows(rows), cols(cols) {
        data = new T * [rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new T[cols];
        }
    }

    Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
        data = new T * [rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new T[cols];
            for (int j = 0; j < cols; j++) {
                data[i][j] = other.data[i][j];
            }
        }
    }

    ~Matrix() {
        clear();
    }

    void filrnbetman() {
        cout << "Введіть елементи матриці:\n";
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cin >> data[i][j];
            }
        }
    }

    void filr(T minValue, T maxValue) {
        srand(time(0));
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                data[i][j] = minValue + rand() % (maxValue - minValue + 1);
            }
        }
    }

    void display() const {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << setw(5) << data[i][j] << " ";
            }
            cout << endl;
        }
    }

    Matrix operator+(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw invalid_argument("Розміри матриць не співпадають!");
        }
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    Matrix operator-(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw invalid_argument("Розміри матриць не співпадають!");
        }
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }

    Matrix operator*(const Matrix& other) const {
        if (cols != other.rows) {
            throw invalid_argument("Кількість стовпців першої матриці не дорівнює кількості рядків другої матриці!");
        }
        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < other.cols; j++) {
                result.data[i][j] = 0;
                for (int k = 0; k < cols; k++) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    Matrix operator/(T scalar) const {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] / scalar;
            }
        }
        return result;
    }

    T maxent() const {
        T maxVal = data[0][0];
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (data[i][j] > maxVal) {
                    maxVal = data[i][j];
                }
            }
        }
        return maxVal;
    }

    T mixelment() const {
        T minVal = data[0][0];
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (data[i][j] < minVal) {
                    minVal = data[i][j];
                }
            }
        }
        return minVal;
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);


    int rows, cols;

    cout << "Введіть кількість рядків і стовпців для матриці: ";
    cin >> rows >> cols;

    Matrix<int> mat1(rows, cols);
    mat1.filr(1, 10);

    cout << "Матриця 1 (випадкові значення):\n";
    mat1.display();

    Matrix<int> mat2(rows, cols);
    mat2.filrnbetman();

    cout << "\nМатриця 2 (введена з клавіатури):\n";
    mat2.display();

    cout << "\nСума матриць:\n";
    Matrix<int> sumatr1 = mat1 + mat2;
    sumatr1.display();

    cout << "\nРізниця матриць:\n";
    Matrix<int> difmatrix = mat1 - mat2;
    difmatrix.display();

    cout << "\nМаксимальний елемент в матриці 1: " << mat1.maxent() << endl;
    cout << "Мінімальний елемент в матриці 2: " << mat2.mixelment() << endl;

    return 0;
}
