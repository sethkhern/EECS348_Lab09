#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

// Template Matrix class
template <typename T>
class Matrix {
private:
    int size;
    vector<vector<T>> data;

public:
    Matrix(int n) : size(n), data(n, vector<T>(n)) {}

    // Access element with (i, j)
    T& operator()(int i, int j) {
        if (i < 0 || i >= size || j < 0 || j >= size) {
            cout << "Index out of bounds: (" << i << ", " << j << ")" << endl;
        }
        return data[i][j];
    }

    // Output operator
    friend ostream& operator<<(ostream& os, const Matrix<T>& mat) {
        for (int i = 0; i < mat.size; ++i) {
            for (int j = 0; j < mat.size; ++j) {
                os << setw(4) << mat.data[i][j] << " ";
            }
            os << endl;
        }
        return os;
    }

    // Matrix addition
    Matrix operator+(const Matrix& other) {
        Matrix result(size);
        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                result(i, j) = data[i][j] + other.data[i][j];
        return result;
    }

    // Matrix multiplication
    Matrix operator*(const Matrix& other) {
        Matrix result(size);
        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                for (int k = 0; k < size; ++k)
                    result(i, j) += data[i][k] * other.data[k][j];
        return result;
    }

    // Element-wise sum of main diagonal with another matrix
    vector<T> sumMainDiagonalWith(const Matrix& other) const {
        vector<T> result(size);
        for (int i = 0; i < size; ++i)
            result[i] = data[i][i] + other.data[i][i];
        return result;
    }

    // Element-wise sum of secondary diagonal with another matrix
    vector<T> sumSecondaryDiagonalWith(const Matrix& other) const {
        vector<T> result(size);
        for (int i = 0; i < size; ++i)
            result[i] = data[i][size - 1 - i] + other.data[i][size - 1 - i];
        return result;
    }

    // Swap two rows
    void swapRows(int r1, int r2) {
        if (r1 < 0 || r2 < 0 || r1 >= size || r2 >= size) {
            cout << "Invalid row index for swap." << endl;
            return;
        }
        swap(data[r1], data[r2]);
    }

    // Swap two columns
    void swapColumns(int c1, int c2) {
        if (c1 < 0 || c2 < 0 || c1 >= size || c2 >= size) {
            cout << "Invalid column index for swap." << endl;
            return;
        }
        for (int i = 0; i < size; ++i)
            swap(data[i][c1], data[i][c2]);
    }

    // Load matrix data from input stream
    void loadData(istream& in) {
        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                in >> data[i][j];
    }
};

// Main program
int main() {
    ifstream file("input.txt");
    if (!file) {
        cout << "Failed to open file." << endl;
        return 1;
    }

    int size, typeFlag;
    file >> size >> typeFlag;

    if (typeFlag == 0) {
        Matrix<int> A(size), B(size);
        A.loadData(file);
        B.loadData(file);

        cout << "Matrix A:\n" << A;
        cout << "Matrix B:\n" << B;

        cout << "Result of sum:\n" << (A + B);
        cout << "Result of product:\n" << (A * B);

        // Element-wise diagonal sums
        vector<int> mainDiag = A.sumMainDiagonalWith(B);
        vector<int> secDiag = A.sumSecondaryDiagonalWith(B);

        cout << "Result of sum of main diagonals:\n";
        for (int val : mainDiag) cout << val << " ";
        cout << endl;

        cout << "Result of sum of secondary diagonals:\n";
        for (int val : secDiag) cout << val << " ";
        cout << endl;

        A.swapRows(0, 1);
        cout << "Result of the rows swapped in matrix:\n" << A;

        A.swapColumns(0, 1);
        cout << "Result of the column swapped in matrix:\n" << A;
    }
    else if (typeFlag == 1) {
        Matrix<double> A(size), B(size);
        A.loadData(file);
        B.loadData(file);

        cout << fixed << setprecision(2);
        cout << "Matrix A:\n" << A;
        cout << "Matrix B:\n" << B;

        cout << "Result of sum:\n" << (A + B);
        cout << "Result of product:\n" << (A * B);

        // Element-wise diagonal sums
        vector<double> mainDiag = A.sumMainDiagonalWith(B);
        vector<double> secDiag = A.sumSecondaryDiagonalWith(B);

        cout << "Result of sum of main diagonals: ";
        for (double val : mainDiag) cout << val << " ";
        cout << endl;

        cout << "Result of sum of secondary diagonals: ";
        for (double val : secDiag) cout << val << " ";
        cout << endl;

        A.swapRows(0, 1);
        cout << "Result of the rows swapped in matrix:\n" << A;

        A.swapColumns(0, 1);
        cout << "Result of the column swapped in matrix:\n" << A;
    }
    else {
        cout << "Unknown type flag in input file (must be 0 for int, 1 for double)." << endl;
    }

    return 0;
}
