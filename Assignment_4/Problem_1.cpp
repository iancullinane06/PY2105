#include <cmath>
#include <iostream>
#include <stdexcept>
#include <utility>
using namespace std;

const int MATRIX_SIZE = 4;
const double PIVOT_TOLERANCE = 1e-12;

class Vector {
public:
    double data[MATRIX_SIZE];

    void print() const {
        for (int i = 0; i < MATRIX_SIZE; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};

class Matrix {
public:
    double data[MATRIX_SIZE][MATRIX_SIZE];

    void print() const {
        for (int i = 0; i < MATRIX_SIZE; i++) {
            for (int j = 0; j < MATRIX_SIZE; j++) {
                cout << data[i][j] << " ";
            }
            cout << endl;
        }
    }

    int _max_row(int col) const {
        int maxRow = col;
        for (int row = col + 1; row < MATRIX_SIZE; row++) {
            if (fabs(data[row][col]) > fabs(data[maxRow][col])) {
                maxRow = row;
            }
        }
        return maxRow;
    }

    bool _partial_pivot(int col, Vector &b) {
        int maxRow = _max_row(col);
        if (fabs(data[maxRow][col]) < PIVOT_TOLERANCE) {
            throw runtime_error("Matrix is singular.");
        }
        if (maxRow == col) {
            return false;
        }
        for (int j = 0; j < MATRIX_SIZE; j++) {
            swap(data[col][j], data[maxRow][j]);
        }
        swap(b.data[col], b.data[maxRow]);
        return true;
    }

    void _eliminate(int col, Vector &b) {
        for (int row = col + 1; row < MATRIX_SIZE; row++) {
            double factor = data[row][col] / data[col][col];
            data[row][col] = 0.0;
            for (int j = col + 1; j < MATRIX_SIZE; j++) {
                data[row][j] -= factor * data[col][j];
            }
            b.data[row] -= factor * b.data[col];
        }
    }

    void _lu_decompose(Matrix &L) {
        for (int i = 0; i < MATRIX_SIZE; i++) {
            for (int j = 0; j < MATRIX_SIZE; j++) {
                L.data[i][j] = 0.0;
            }
            L.data[i][i] = 1.0;
        }

        for (int i = 0; i < MATRIX_SIZE; i++) {
            if (fabs(data[i][i]) < PIVOT_TOLERANCE) {
                throw runtime_error("LU decomposition encountered a zero pivot.");
            }
            for (int row = i + 1; row < MATRIX_SIZE; row++) {
                double factor = data[row][i] / data[i][i];
                L.data[row][i] = factor;
                data[row][i] = 0.0;
                for (int col = i + 1; col < MATRIX_SIZE; col++) {
                    data[row][col] -= factor * data[i][col];
                }
            }
        }
    }

    void _forward_substitute(const Vector &b, Vector &y) const {
        for (int i = 0; i < MATRIX_SIZE; i++) {
            y.data[i] = b.data[i];
            for (int j = 0; j < i; j++) {
                y.data[i] -= data[i][j] * y.data[j];
            }
            if (fabs(data[i][i]) < PIVOT_TOLERANCE) {
                throw runtime_error("Forward substitution encountered a zero pivot.");
            }
            y.data[i] /= data[i][i];
        }
    }

    void _back_substitute(const Vector &b, Vector &x) const {
        for (int i = MATRIX_SIZE - 1; i >= 0; i--) {
            x.data[i] = b.data[i];
            for (int j = i + 1; j < MATRIX_SIZE; j++) {
                x.data[i] -= data[i][j] * x.data[j];
            }
            if (fabs(data[i][i]) < PIVOT_TOLERANCE) {
                throw runtime_error("Back substitution encountered a zero pivot.");
            }
            x.data[i] /= data[i][i];
        }
    }
};

class Matrix_solver_Gauss {
public:
    struct Result {
        Matrix A;
        Vector b;
        Vector x;
        double determinant;
    };

    Result solve(Matrix A, Vector b) const {
        double determinant = 1.0;
        for (int i = 0; i < MATRIX_SIZE; i++) {
            if (A._partial_pivot(i, b)) {
                determinant = -determinant;
            }
            determinant *= A.data[i][i];
            A._eliminate(i, b);
        }

        Vector x;
        A._back_substitute(b, x);

        Result result;
        result.A = A;
        result.b = b;
        result.x = x;
        result.determinant = determinant;
        return result;
    }
};

class Matrix_solver_LU {
public:
    struct Result {
        Vector x;
        Matrix L;
        Matrix U;
        Matrix inverse;
    };

    Result solve(const Matrix &A, const Vector &b) const {
        Matrix L;
        Matrix U = A;
        U._lu_decompose(L);

        Vector y;
        L._forward_substitute(b, y);

        Vector x;
        U._back_substitute(y, x);

        Result result;
        result.x = x;
        result.L = L;
        result.U = U;
        result.inverse = invert(A);
        return result;
    }

    Matrix invert(const Matrix &A) const {
        Matrix L;
        Matrix U = A;
        U._lu_decompose(L);
        Matrix inverse;

        for (int col = 0; col < MATRIX_SIZE; col++) {
            Vector unit;
            for (int row = 0; row < MATRIX_SIZE; row++) {
                unit.data[row] = (row == col) ? 1.0 : 0.0;
            }

            Vector y;
            L._forward_substitute(unit, y);
            Vector solution;
            U._back_substitute(y, solution);
            for (int row = 0; row < MATRIX_SIZE; row++) {
                inverse.data[row][col] = solution.data[row];
            }
        }
        return inverse;
    }
};
