#include <iostream>
using namespace std;

class Matrix3D {
private:
    double matrix[3][3];
    int incrementValue;
    int count;

public:

    Matrix3D() : incrementValue(1), count(0) {
        cout << "Entrer the 9 elements of matrix 3x3 : " << endl;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cin >> matrix[i][j];
            }
        }
    }


    Matrix3D(double m[3][3]) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                matrix[i][j] = m[i][j];
            }
        }
        incrementValue = 1;
        count = 0;
    }


    void setIncrement(int val) {
        if (val < 0) {
            cout << "Value of increment is invalide. none  modification." << endl;
        } else if (count == 0) {
            incrementValue = val;
            cout << "Increment define  at  " << incrementValue << endl;
            count++;
        } else {
            cout << "Impossible to define the increment after  the first modification ." << endl;
        }
    }


    void increment() {

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                matrix[i][j] += incrementValue;
            }
        }
    }


    void displayMatrix() const {
        cout << " Actuel Matrix  : " << endl;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }


    Matrix3D operator+(const Matrix3D& other) const {
        double result[3][3];
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                result[i][j] = matrix[i][j] + other.matrix[i][j];
            }
        }
        return Matrix3D(result);
    }


    Matrix3D operator-(const Matrix3D& other) const {
        double result[3][3];
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                result[i][j] = matrix[i][j] - other.matrix[i][j];
            }
        }
        return Matrix3D(result);
    }


    Matrix3D operator*(const Matrix3D& other) const {
        double result[3][3] = {0};
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                for (int k = 0; k < 3; ++k)
                    result[i][j] += matrix[i][k] * other.matrix[k][j];
        return Matrix3D(result);
    }


     bool operator>(const Matrix3D& other) const { return this->det() > other.det(); }
    bool operator<(const Matrix3D& other) const { return this->det() < other.det(); }
    bool operator>=(const Matrix3D& other) const { return this->det() >= other.det(); }
    bool operator<=(const Matrix3D& other) const { return this->det() <= other.det(); }
    bool operator==(const Matrix3D& other) const { return this->det() == other.det(); }
    bool operator!=(const Matrix3D& other) const { return this->det() != other.det(); }


    double det() const {

        return matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1])
             - matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0])
             + matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
    }
};

int main() {
    Matrix3D mat1, mat2;

    cout << "Matrix 1 :" << endl;
    mat1.displayMatrix();

    cout << "Matrix 2 :" << endl;
    mat2.displayMatrix();

    Matrix3D mat3 = mat1 + mat2;
    cout << "Matrix  1 + Matrix 2 :" << endl;
    mat3.displayMatrix();

    Matrix3D mat4 = mat1 * mat2;
    cout << "Matrix 1 * Matrix 2 :" << endl;
    mat4.displayMatrix();

    int increment;
    cout << "Enter matrix 1 : ";
    cin >> increment;
    mat1.setIncrement(increment);
    mat1.increment();

    cout << "Matrix 1 after  incrementation : " << endl;
    mat1.displayMatrix();

    return 0;
}

