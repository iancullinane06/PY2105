#include <iostream>
#include <cmath>
using namespace std;

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
};

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
            // Partial pivoting
            int maxRow = i;
            for (int k = i + 1; k < n; k++) {
                if (abs(A.data[k][i]) > abs(A.data[maxRow][i])) {
                    maxRow = k;
                }
            }
            for (int k = i; k < n; k++) {
                swap(A.data[i][k], A.data[maxRow][k]);
            }
            swap(b.data[i], b.data[maxRow]);

            // Elimination
            for (int k = i + 1; k < n; k++) {
                double factor = (double)A.data[k][i] / A.data[i][i];
                for (int j = i; j < n; j++) {
                    A.data[k][j] -= factor * A.data[i][j];
                }
                b.data[k] -= factor * b.data[i];
            }
        }

        // Back substitution
        double x[4];
        for (int i = n - 1; i >= 0; i--) {
            x[i] = b.data[i];
            for (int j = i + 1; j < n; j++) {
                x[i] -= A.data[i][j] * x[j];
            }
            x[i] /= A.data[i][i];
        }

        // Print solution
        for (int i = 0; i < n; i++) {
            cout << "x[" << i << "] = " << x[i] << endl;
        }

        Result result;
        result.A = A;
        result.b = b;
        for (int i = 0; i < n; i++) {
            result.x.data[i] = x[i];
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
        int n = 4;
        Matrix L = {{{0}}};
        Matrix U = A;
        for (int i = 0; i < n; i++) {
            L.data[i][i] = 1;
        }
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                double factor = (double)U.data[j][i] / U.data[i][i];
                L.data[j][i] = factor;
                for (int k = i; k < n; k++) {
                    U.data[j][k] -= factor * U.data[i][k];
                }
            }
        }

        // Forward substitution to solve Ly = b
        double y[4];
        for (int i = 0; i < n; i++) {
            y[i] = b.data[i];
            for (int j = 0; j < i; j++) {
                y[i] -= L.data[i][j] * y[j];
            }
        }

        // Back substitution to solve Ux = y
        double x[4];
        for (int i = n - 1; i >= 0; i--) {
            x[i] = y[i];
            for (int j = i + 1; j < n; j++) {
                x[i] -= U.data[i][j] * x[j];
            }
            x[i] /= U.data[i][i];
        }

        Matrix_solver_LU::Result result;
        result.A = A;
        result.b = b;
        for (int i = 0; i < n; i++) {
            result.x.data[i] = x[i];
        }
        result.L = L;
        result.U = U;
        return result;
    }
};