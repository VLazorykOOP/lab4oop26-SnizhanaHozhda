#include <iostream>
#include "Tasks.h"
using namespace std;


// ================= VectorShort =================
class VectorShort
{
private:
    short* data;
    int size;

public:

    VectorShort()
    {
        size = 0;
        data = nullptr;
    }

    VectorShort(int n)
    {
        size = n;
        data = new short[n] {0};
    }

    VectorShort(const VectorShort& v)
    {
        size = v.size;
        data = new short[size];

        for (int i = 0; i < size; i++)
            data[i] = v.data[i];
    }

    ~VectorShort()
    {
        delete[] data;
    }

    int getSize() const { return size; }

    short& operator[](int i)
    {
        return data[i];
    }

    friend istream& operator>>(istream& in, VectorShort& v)
    {
        for (int i = 0; i < v.size; i++)
            in >> v.data[i];
        return in;
    }

    friend ostream& operator<<(ostream& out, const VectorShort& v)
    {
        for (int i = 0; i < v.size; i++)
            out << v.data[i] << " ";
        return out;
    }
};



// ================= MatrixShort =================
class MatrixShort
{
protected:

    VectorShort* ShortArray;
    int n, size;
    int codeError;

    static int num_matrix;

public:

    // ---------- constructors ----------
    MatrixShort()
    {
        ShortArray = nullptr;
        n = size = codeError = 0;
        num_matrix++;
    }

    MatrixShort(int s)
    {
        n = size = s;
        ShortArray = new VectorShort[n];

        for (int i = 0; i < n; i++)
        {
            ShortArray[i] = VectorShort(size);
            for (int j = 0; j < size; j++)
                ShortArray[i][j] = (i == j);
        }

        num_matrix++;
    }

    MatrixShort(int n_, int s_)
    {
        n = n_;
        size = s_;
        ShortArray = new VectorShort[n];

        for (int i = 0; i < n; i++)
            ShortArray[i] = VectorShort(size);

        num_matrix++;
    }

    MatrixShort(int n_, int s_, short val)
    {
        n = n_;
        size = s_;
        ShortArray = new VectorShort[n];

        for (int i = 0; i < n; i++)
        {
            ShortArray[i] = VectorShort(size);
            for (int j = 0; j < size; j++)
                ShortArray[i][j] = val;
        }

        num_matrix++;
    }

    MatrixShort(const MatrixShort& m)
    {
        n = m.n;
        size = m.size;
        ShortArray = new VectorShort[n];

        for (int i = 0; i < n; i++)
        {
            ShortArray[i] = VectorShort(size);
            for (int j = 0; j < size; j++)
                ShortArray[i][j] = m.ShortArray[i][j];
        }

        num_matrix++;
    }

    ~MatrixShort()
    {
        delete[] ShortArray;
        num_matrix--;
    }

    // ---------- info ----------
    int getN() const { return n; }
    int getSize() const { return size; }
    int getError() const { return codeError; }

    static int getCount() { return num_matrix; }


    // ---------- indexing ----------
    VectorShort& operator[](int i)
    {
        if (i >= 0 && i < n)
            return ShortArray[i];

        codeError = 1;
        return ShortArray[n - 1];
    }


    // ---------- unary ----------
    MatrixShort& operator++()
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < size; j++)
                ShortArray[i][j]++;
        return *this;
    }

    MatrixShort operator++(int)
    {
        MatrixShort tmp = *this;
        ++(*this);
        return tmp;
    }

    MatrixShort& operator--()
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < size; j++)
                ShortArray[i][j]--;
        return *this;
    }

    bool operator!()
    {
        return (n != 0 && size != 0);
    }

    MatrixShort operator~()
    {
        MatrixShort r(n, size);

        for (int i = 0; i < n; i++)
            for (int j = 0; j < size; j++)
                r[i][j] = ~ShortArray[i][j];

        return r;
    }

    MatrixShort operator-()
    {
        MatrixShort r(n, size);

        for (int i = 0; i < n; i++)
            for (int j = 0; j < size; j++)
                r[i][j] = -ShortArray[i][j];

        return r;
    }


    // ---------- assignment ----------
    MatrixShort& operator=(const MatrixShort& m)
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < size; j++)
                ShortArray[i][j] = m.ShortArray[i][j];

        return *this;
    }


    // ---------- arithmetic ----------
    MatrixShort operator+(const MatrixShort& m)
    {
        MatrixShort r(n, size);

        for (int i = 0; i < n; i++)
            for (int j = 0; j < size; j++)
                r[i][j] = ShortArray[i][j] + m.ShortArray[i][j];

        return r;
    }

    MatrixShort operator-(const MatrixShort& m)
    {
        MatrixShort r(n, size);

        for (int i = 0; i < n; i++)
            for (int j = 0; j < size; j++)
                r[i][j] = ShortArray[i][j] - m.ShortArray[i][j];

        return r;
    }

    MatrixShort operator*(const MatrixShort& m)
    {
        MatrixShort r(n, size);

        for (int i = 0; i < n; i++)
            for (int j = 0; j < size; j++)
                r[i][j] = ShortArray[i][j] * m.ShortArray[i][j];

        return r;
    }

    MatrixShort operator*(short a)
    {
        MatrixShort r(n, size);

        for (int i = 0; i < n; i++)
            for (int j = 0; j < size; j++)
                r[i][j] = ShortArray[i][j] * a;

        return r;
    }

    MatrixShort operator/(short a)
    {
        MatrixShort r(n, size);

        for (int i = 0; i < n; i++)
            for (int j = 0; j < size; j++)
                r[i][j] = ShortArray[i][j] / a;

        return r;
    }

    MatrixShort operator%(short a)
    {
        MatrixShort r(n, size);

        for (int i = 0; i < n; i++)
            for (int j = 0; j < size; j++)
                r[i][j] = ShortArray[i][j] % a;

        return r;
    }


    // ---------- compound ----------
    MatrixShort& operator+=(const MatrixShort& m)
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < size; j++)
                ShortArray[i][j] += m.ShortArray[i][j];

        return *this;
    }

    MatrixShort& operator-=(const MatrixShort& m)
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < size; j++)
                ShortArray[i][j] -= m.ShortArray[i][j];

        return *this;
    }

    MatrixShort& operator*=(short a)
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < size; j++)
                ShortArray[i][j] *= a;

        return *this;
    }

    MatrixShort& operator/=(short a)
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < size; j++)
                ShortArray[i][j] /= a;

        return *this;
    }

    MatrixShort& operator%=(short a)
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < size; j++)
                ShortArray[i][j] %= a;

        return *this;
    }


    // ---------- bitwise ----------
    MatrixShort operator|(short a)
    {
        MatrixShort r(n, size);

        for (int i = 0; i < n; i++)
            for (int j = 0; j < size; j++)
                r[i][j] = ShortArray[i][j] | a;

        return r;
    }

    MatrixShort operator^(short a)
    {
        MatrixShort r(n, size);

        for (int i = 0; i < n; i++)
            for (int j = 0; j < size; j++)
                r[i][j] = ShortArray[i][j] ^ a;

        return r;
    }

    MatrixShort operator&(short a)
    {
        MatrixShort r(n, size);

        for (int i = 0; i < n; i++)
            for (int j = 0; j < size; j++)
                r[i][j] = ShortArray[i][j] & a;

        return r;
    }

    MatrixShort& operator<<=(short a)
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < size; j++)
                ShortArray[i][j] <<= a;

        return *this;
    }

    MatrixShort& operator>>=(short a)
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < size; j++)
                ShortArray[i][j] >>= a;

        return *this;
    }

    MatrixShort& operator|=(short a)
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < size; j++)
                ShortArray[i][j] |= a;

        return *this;
    }

    MatrixShort& operator^=(short a)
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < size; j++)
                ShortArray[i][j] ^= a;

        return *this;
    }

    MatrixShort& operator&=(short a)
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < size; j++)
                ShortArray[i][j] &= a;

        return *this;
    }


    // ---------- compare ----------
    int sum() const
    {
        int s = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < size; j++)
                s += ShortArray[i][j];
        return s;
    }

    bool operator==(const MatrixShort& m) { return sum() == m.sum(); }
    bool operator!=(const MatrixShort& m) { return sum() != m.sum(); }
    bool operator>(const MatrixShort& m) { return sum() > m.sum(); }
    bool operator<(const MatrixShort& m) { return sum() < m.sum(); }
    bool operator>=(const MatrixShort& m) { return sum() >= m.sum(); }
    bool operator<=(const MatrixShort& m) { return sum() <= m.sum(); }


    // ---------- IO ----------
    friend istream& operator>>(istream& in, MatrixShort& m)
    {
        for (int i = 0; i < m.n; i++)
            in >> m.ShortArray[i];
        return in;
    }

    friend ostream& operator<<(ostream& out, const MatrixShort& m)
    {
        for (int i = 0; i < m.n; i++)
            out << m.ShortArray[i] << endl;
        return out;
    }
};

int MatrixShort::num_matrix = 0;

void runTask3()
{
    MatrixShort A(2, 2);
    MatrixShort B(2, 2);
    MatrixShort C(2, 2);


    // ---------- INPUT ----------
    cout << "Enter matrix A:\n";
    cin >> A;

    cout << "Enter matrix B:\n";
    cin >> B;

    cout << "Enter matrix C:\n";
    cin >> C;


    // ---------- COMPLEX EXPRESSION (5+ operations) ----------
    MatrixShort R = (A + B - C) * 2 % 5 | 3;


    cout << "\nResult R = (A + B - C) * 2 % 5 | 3:\n";
    cout << R;


    // ---------- UNARY OPERATORS ----------
    ++A;
    cout << "\nAfter ++A:\n" << A;

    --B;
    cout << "\nAfter --B:\n" << B;

    MatrixShort D = -C;
    cout << "\nUnary minus C:\n" << D;

    MatrixShort E = ~C;
    cout << "\nBitwise NOT C:\n" << E;


    // ---------- INDEX ----------
    cout << "\nA[0][0] = " << A[0][0] << endl;


    // ---------- COMPARISON ----------
    if (A > B)
        cout << "A > B\n";
    else
        cout << "A <= B\n";


    // ---------- BITWISE TEST ----------
    MatrixShort F = A;
    F <<= 1;
    cout << "\nA <<= 1:\n" << F;

    F >>= 1;
    cout << "\nA >>= 1:\n" << F;


    // ---------- ASSIGNMENT OPS ----------
    A += B;
    cout << "\nA += B:\n" << A;

    A -= B;
    cout << "\nA -= B:\n" << A;

    A *= 2;
    cout << "\nA *= 2:\n" << A;

    A /= 2;
    cout << "\nA /= 2:\n" << A;

    A %= 3;
    cout << "\nA %= 3:\n" << A;


    // ---------- OBJECT COUNT ----------
    cout << "\nMatrix objects count: " << MatrixShort::getCount() << endl;
}#include "Tasks.h"
#include <iostream>
using namespace std;

// ===================== VECTORSHORT =====================
class VectorShort {
protected:
    short* data;
    int size;
    int codeError;
public:
    VectorShort(int s = 0, short init = 0) : size(s), codeError(0) {
        if (s > 0) {
            data = new (nothrow) short[s];
            if (!data) { codeError = 1; size = 0; return; }
            for (int i = 0; i < s; i++) data[i] = init;
        }
        else data = nullptr;
    }

    VectorShort(const VectorShort& v) {
        size = v.size;
        codeError = v.codeError;
        if (size > 0) {
            data = new short[size];
            for (int i = 0; i < size; i++) data[i] = v.data[i];
        }
        else data = nullptr;
    }

    ~VectorShort() { delete[] data; }

    int getSize() const { return size; }
    int getCodeError() const { return codeError; }

    short& operator[](int i) {
        if (i < 0 || i >= size) { codeError = 2; return data[size - 1]; }
        return data[i];
    }
};

// ===================== MATRIXSHORT =====================
class MatrixShort {
protected:
    VectorShort* ShortArray;
    int n, size;
    int codeError;
    static int num_matrix;

    bool sameSize(const MatrixShort& m) const {
        return n == m.n && size == m.size;
    }

    void setError(int c) const { const_cast<MatrixShort*>(this)->codeError = c; }

public:
    MatrixShort() : ShortArray(nullptr), n(0), size(0), codeError(0) { num_matrix++; }

    MatrixShort(int r, int c) : n(r), size(c), codeError(0) {
        ShortArray = new VectorShort[n];
        for (int i = 0; i < n; i++) ShortArray[i] = VectorShort(size, 0);
        num_matrix++;
    }

    MatrixShort(int r, int c, short v) : n(r), size(c), codeError(0) {
        ShortArray = new VectorShort[n];
        for (int i = 0; i < n; i++) ShortArray[i] = VectorShort(size, v);
        num_matrix++;
    }

    MatrixShort(const MatrixShort& m) : n(m.n), size(m.size), codeError(m.codeError) {
        ShortArray = new VectorShort[n];
        for (int i = 0; i < n; i++) ShortArray[i] = m.ShortArray[i];
        num_matrix++;
    }

    ~MatrixShort() { delete[] ShortArray; num_matrix--; }

    // ================= ERROR =================
    void printError() const {
        if (codeError == 0) cout << "No error\n";
        else cout << "Error code: " << codeError << endl;
    }

    // ================= INPUT FRIENDLY =================
    friend istream& operator>>(istream& is, MatrixShort& m) {
        cout << "Enter elements (row by row):\n";
        for (int i = 0; i < m.n; i++) {
            for (int j = 0; j < m.size; j++) {
                cout << "A[" << i << "][" << j << "] = ";
                is >> m.ShortArray[i][j];
            }
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

    static int getCount() { return num_matrix; }

    // ================= ADD/SUB =================
    MatrixShort operator+(const MatrixShort& m) {
        if (!sameSize(m)) { setError(11); return MatrixShort(); }
        MatrixShort r(n, size);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < size; j++)
                r.ShortArray[i][j] = ShortArray[i][j] + m.ShortArray[i][j];
        return r;
    }

    MatrixShort operator-(const MatrixShort& m) {
        if (!sameSize(m)) { setError(12); return MatrixShort(); }
        MatrixShort r(n, size);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < size; j++)
                r.ShortArray[i][j] = ShortArray[i][j] - m.ShortArray[i][j];
        return r;
    }

    // ================= MATRIX MULTIPLICATION =================
    MatrixShort operator*(const MatrixShort& m) {
        if (size != m.n) { setError(10); return MatrixShort(); }
        MatrixShort r(n, m.size, 0);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m.size; j++)
                for (int k = 0; k < size; k++)
                    r.ShortArray[i][j] += ShortArray[i][k] * m.ShortArray[k][j];
        return r;
    }
};

int MatrixShort::num_matrix = 0;

// ================= RUN MENU =================
void runTask3() {
    int n, m;
    cout << "Enter rows and cols: "; cin >> n >> m;

    MatrixShort A(n, m), B(n, m);

    cin >> A;
    cin >> B;

    int ch;
    do {
        cout << "\n===== MENU =====\n";
        cout << "1 A+B\n2 A-B\n3 A*B\n4 Show errors\n5 Count objects\n0 Exit\nChoice: ";
        cin >> ch;

        MatrixShort R;

        switch (ch) {
        case 1: R = A + B; cout << R; break;
        case 2: R = A - B; cout << R; break;
        case 3: R = A * B; cout << R; break;
        case 4:
            cout << "A: "; A.printError();
            cout << "B: "; B.printError();
            break;
        case 5:
            cout << MatrixShort::getCount() << endl;
            break;
        }

    } while (ch != 0);
}

// NOTE: STL version (vector<vector<short>>) can be provided if needed.
