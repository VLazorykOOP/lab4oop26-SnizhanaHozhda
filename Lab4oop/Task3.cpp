#include "Tasks.h"
#include <iostream>
#include <new> 

using namespace std;

class VectorShort {
    short* data;
    int size;
    int codeError;
public:

    friend class MatrixShort;

    VectorShort(int s = 0, short init = 0) : size(s), codeError(0) {
        data = (s > 0) ? new (nothrow) short[s] : nullptr;
        if (s > 0 && !data) { codeError = 1; size = 0; }
        else if (data) { for (int i = 0; i < s; i++) data[i] = init; }
    }

    VectorShort(const VectorShort& v) : size(v.size), codeError(v.codeError) {
        data = (size > 0) ? new (nothrow) short[size] : nullptr;
        if (data) for (int i = 0; i < size; i++) data[i] = v.data[i];
    }

    VectorShort& operator=(const VectorShort& v) {
        if (this != &v) {
            delete[] data;
            size = v.size;
            codeError = v.codeError;
            data = (size > 0) ? new (nothrow) short[size] : nullptr;
            if (data) for (int i = 0; i < size; i++) data[i] = v.data[i];
        }
        return *this;
    }

    ~VectorShort() { delete[] data; }
    short& operator[](int i) { return data[i]; }
};

class MatrixShort {
    VectorShort* ShortArray;
    int n, size;
    int codeError;
    static int num_matrix;
public:
    MatrixShort() : ShortArray(nullptr), n(0), size(0), codeError(0) {
        num_matrix++; }

    MatrixShort(int r, int c) : n(r), size(c), codeError(0) {
        ShortArray = (n > 0) ? new VectorShort[n] : nullptr;
        for (int i = 0; i < n; i++) ShortArray[i] = VectorShort(size, 0);
        num_matrix++;
    }

    MatrixShort(const MatrixShort& m) : n(m.n), size(m.size), codeError(m.codeError) {
        ShortArray = (n > 0) ? new VectorShort[n] : nullptr;
        for (int i = 0; i < n; i++) ShortArray[i] = m.ShortArray[i];
        num_matrix++;
    }

   

    MatrixShort& operator=(const MatrixShort& m) {
        if (this != &m) {
            delete[] ShortArray;
            n = m.n; size = m.size;
            ShortArray = (n > 0) ? new VectorShort[n] : nullptr;
            for (int i = 0; i < n; i++) ShortArray[i] = m.ShortArray[i];
        }
        return *this;
    }

    void printError() const {
        if (codeError == 0) {
            cout << "No error" << endl;
        }
        else {
            cout << "Error code: " << codeError << endl;
        }
    }

    int getN() const { return n; }
    int getSize() const { return size; }
    int getCodeError() const { return codeError; }

    ~MatrixShort() { delete[] ShortArray; num_matrix--; }

    friend istream& operator>>(istream& is, MatrixShort& m) {
        cout << "Input elements of matrix\n";
        for (int i = 0; i < m.n; i++)
            for (int j = 0; j < m.size; j++) {
                cout << "A[" << i << "][" << j << "] = ";
                is >> m.ShortArray[i][j];
            }
        return is;
    }

    friend ostream& operator<<(ostream& os, const MatrixShort& m) {
        for (int i = 0; i < m.n; i++) {
            for (int j = 0; j < m.size; j++) os << m.ShortArray[i][j] << " ";
            os << endl;
        }
        return os;
    }

    MatrixShort operator+(const MatrixShort& m) {
        MatrixShort res(n, size);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < size; j++) res.ShortArray[i][j] = ShortArray[i][j] + m.ShortArray[i][j];
        return res;
    }

   
    MatrixShort operator-(const MatrixShort& m) {
        MatrixShort res(n, size);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < size; j++)
                res.ShortArray[i][j] = ShortArray[i][j] - m.ShortArray[i][j];
        return res;
    }

   
    MatrixShort operator*(const MatrixShort& m) {
        MatrixShort res(n, m.size);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m.size; j++) {
                res.ShortArray[i][j] = 0;
                for (int k = 0; k < size; k++)
                    res.ShortArray[i][j] += ShortArray[i][k] * m.ShortArray[k][j];
            }
        return res;
    }

   
    MatrixShort& operator++() {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < size; j++)
                ShortArray[i][j]++;
        return *this;
    }

    MatrixShort operator++(int) {
        MatrixShort temp(*this); 
        operator++();            
        return temp;             
    }

    MatrixShort& operator--() {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < size; j++)
                ShortArray[i][j]--;
        return *this;
    }


    MatrixShort operator--(int) {
        MatrixShort temp(*this);
        operator--();
        return temp;
    }


    bool operator!() const {
        return (n != 0 && size != 0);
    }


    MatrixShort operator-() const {
        MatrixShort res(n, size);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < size; j++)
                res.ShortArray[i].data[j] = -this->ShortArray[i].data[j];
        return res;
    }


    MatrixShort operator~() const {
        MatrixShort res(n, size);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < size; j++)
                res.ShortArray[i].data[j] = ~this->ShortArray[i].data[j];
        return res;
    }

    static int getCount() { return num_matrix; }
};

int MatrixShort::num_matrix = 0;

void runTask3() {
    int n, m;
    cout << "Enter the number of rows and columns for the matrices: ";
    cin >> n >> m;

    MatrixShort A(n, m), B(n, m);
    cout << "Enter matrix A:" << endl; cin >> A;
    cout << "Enter matrix B:" << endl; cin >> B;

    int ch;
    do {
        cout << "\n===== MENU =====\n"
            << "1. A + B\n2. A - B\n3. A * B\n4. Show errors\n"
            << "5. Object count\n6. Increment ++A\n7. Decrement --A\n"
            << "8. Check if not empty\n";
        cout << "9. Unary minus (-A)\n10. Bitwise NOT (~A)\n";

        cin >> ch;

        MatrixShort R; 
        switch (ch) {
        case 1:
            R = A + B;
            cout << "Result:\n" << R << endl;
            break;
        case 2:
            R = A - B;
            cout << "Result:\n" << R << endl;
            break;
        case 3:
            if (n == m) { 
                R = A * B;
                cout << "Result:\n" << R << endl;
            }
            else {
                cout << "Dimension error for multiplication!" << endl;
            }
            break;
        case 4:
            cout << "Errors in A: "; A.printError();
            cout << "Errors in B: "; B.printError();
            break;
        case 5:
            cout << "Count: " << MatrixShort::getCount() << endl;
            break;
        case 6:
            ++A;
            cout << "Matrix A incremented (prefix):\n" << A << endl;
            break;
        case 7:
            A--;
            cout << "Matrix A decremented (postfix):\n" << A << endl;
            break;
        case 8:
            if (!A) {
                cout << "Matrix A is not empty." << endl;
            }
            else {
                cout << "Matrix A is empty (zero dimensions)." << endl;
            }
            break;
        case 9:
            cout << "Result (-A):\n" << -A << endl;
            break;
        case 10:
            cout << "Result (~A):\n" << ~A << endl;
            break;
        case 0:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice, please try again." << endl;
            break;
        }


    } while (ch != 0);
}