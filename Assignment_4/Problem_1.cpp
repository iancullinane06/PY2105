#include <iostream>
#include <cmath>
using namespace std;

class Vector {
public:
    double data[4];

    void print() {
        for (int i = 0; i < 4; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};

class Matrix {
public:
    double data[4][4];

    void print() {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                cout << data[i][j] << " ";
            }
            cout << endl;
        }
    }

    int _max_row(int col) const {
        int maxRow = col;
        for (int k = col + 1; k < 4; k++) {
            if (abs(data[k][col]) > abs(data[maxRow][col])) {
                maxRow = k;
            }
        }
        return maxRow;
    }

    void _partial_pivot(int col, Vector &b) {
        int maxRow = _max_row(col);
        for (int k = 0; k < 4; k++) {
            swap(data[col][k], data[maxRow][k]);
        }
        swap(b.data[col], b.data[maxRow]);
    }

    void _eliminate(int col, Vector &b) {
        for (int k = col + 1; k < 4; k++) {
            double factor = (double)data[k][col] / data[col][col];
            for (int j = col; j < 4; j++) {
                data[k][j] -= factor * data[col][j];
            }
            b.data[k] -= factor * b.data[col];
        }
    }

    void _lu_decompose(Matrix &L) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                L.data[i][j] = 0;
            }
            L.data[i][i] = 1;
        }

        for (int i = 0; i < 4; i++) {
            for (int j = i + 1; j < 4; j++) {
                double factor = data[j][i] / data[i][i];
                L.data[j][i] = factor;
                for (int k = i; k < 4; k++) {
                    data[j][k] -= factor * data[i][k];
                }
            }
        }
    }

    void _forward_substitute(const Vector &b, Vector &y) const {
        for (int i = 0; i < 4; i++) {
            y.data[i] = b.data[i];
            for (int j = 0; j < i; j++) {
                y.data[i] -= data[i][j] * y.data[j];
            }
            y.data[i] /= data[i][i];
        }
    }

    void _back_substitute(const Vector &b, Vector &x) const {
        for (int i = 3; i >= 0; i--) {
            x.data[i] = b.data[i];
            for (int j = i + 1; j < 4; j++) {
                x.data[i] -= data[i][j] * x.data[j];
            }
            x.data[i] /= data[i][i];
        }
    }
};

// Matrix solver using Naive Gaussian Elimination with Partial Pivoting
class Matrix_solver_Gauss {
public:
    // Add member functions and variables here
    struct Result {
        Matrix A;
        Vector b;
        Vector x;
    };

    Result solve(Matrix A, Vector b) {

        int n = 4;
        for (int i = 0; i < n; i++) {
            A._partial_pivot(i, b);
            A._eliminate(i, b);
        }

        // Back substitution
        Vector x;
        A._back_substitute(b, x);

        // Print solution
        for (int i = 0; i < n; i++) {
            cout << "x[" << i << "] = " << x.data[i] << endl;
        }

        Result result;
        result.A = A;
        result.b = b;
        for (int i = 0; i < n; i++) {
            result.x.data[i] = x.data[i];
        }
        return result;
    }
};

class Matrix_solver_LU {
public:
    struct Result {
        Matrix A;
        Vector b;
        Vector x;
        Matrix L;
        Matrix U;
    };

    Matrix_solver_LU::Result solve(Matrix A, Vector b) {
        Matrix L;
        Matrix U = A;
        U._lu_decompose(L);

        // Forward substitution to solve Ly = b
        Vector y;
        L._forward_substitute(b, y);

        // Back substitution to solve Ux = y
        Vector x;
        U._back_substitute(y, x);

        Matrix_solver_LU::Result result;
        result.A = A;
        result.b = b;
        for (int i = 0; i < 4; i++) {
            result.x.data[i] = x.data[i];
        }
        result.L = L;
        result.U = U;
        return result;
    }
};