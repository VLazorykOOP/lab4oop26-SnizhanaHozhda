
#include "Tasks.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;


class Vector3F
{
private:

    float* data;

public:

    int State;
    static int count;


    Vector3F()
    {
        data = new float[3] {0, 0, 0};
        State = 0;
        count++;
    }


    Vector3F(float a)
    {
        data = new float[3] {a, a, a};
        State = 0;
        count++;
    }


    Vector3F(float* arr)
    {
        data = new float[3];

        if (arr == nullptr)
        {
            data[0] = data[1] = data[2] = 0;
            State = 1;
        }
        else
        {
            for (int i = 0; i < 3; i++)
                data[i] = arr[i];

            State = 0;
        }

        count++;

    }

    Vector3F(const Vector3F& other) {
        data = new float[3];
        for (int i = 0; i < 3; i++) data[i] = other.data[i];
        State = other.State;
        count++;
    }

    // 2. Оператор присвоювання (Copy Assignment Operator)
    Vector3F& operator=(const Vector3F& v) {
        if (this != &v) {
            for (int i = 0; i < 3; i++)
                data[i] = v.data[i];
            State = v.State;
        }
        return *this;
    }


    ~Vector3F() {
        if (data != nullptr) {
            delete[] data;
            data = nullptr;
        }
        count--;
    }


    Vector3F& operator++()
    {
        for (int i = 0; i < 3; i++)
            data[i] += 1.0;

        return *this;
    }


    Vector3F operator++(int)
    {
        Vector3F temp = *this;

        for (int i = 0; i < 3; i++)
            data[i] += 1.0;

        return temp;
    }


    Vector3F& operator--()
    {
        for (int i = 0; i < 3; i++)
            data[i] -= 1.0;

        return *this;
    }


    bool operator!()
    {
        return (data[0] != 0 && data[1] != 0 && data[2] != 0);
    }


    Vector3F operator~()
    {
        Vector3F r;

        r.data[0] = -data[1];
        r.data[1] = data[0];
        r.data[2] = 0;

        return r;
    }


    Vector3F operator-()
    {
        Vector3F r;

        for (int i = 0; i < 3; i++)
            r.data[i] = -data[i];

        return r;
    }


    Vector3F& operator+=(const Vector3F& v)
    {
        for (int i = 0; i < 3; i++)
            data[i] += v.data[i];

        return *this;
    }


    Vector3F& operator-=(const Vector3F& v)
    {
        for (int i = 0; i < 3; i++)
            data[i] -= v.data[i];

        return *this;
    }


    Vector3F& operator*=(float a)
    {
        for (int i = 0; i < 3; i++)
            data[i] *= a;

        return *this;
    }


    Vector3F& operator/=(float a)
    {
        if (a == 0)
        {
            State = 2;
            return *this;
        }

        for (int i = 0; i < 3; i++)
            data[i] /= a;

        return *this;
    }


    Vector3F& operator&=(const Vector3F& v)
    {
        float x = data[1] * v.data[2] - data[2] * v.data[1];
        float y = data[2] * v.data[0] - data[0] * v.data[2];
        float z = data[0] * v.data[1] - data[1] * v.data[0];

        data[0] = x;
        data[1] = y;
        data[2] = z;

        return *this;
    }


    Vector3F operator%(int a)
    {
        Vector3F r;

        for (int i = 0; i < 3; i++)
            r.data[i] = int(data[i]) % a;

        return r;
    }


    float& operator[](int i)
    {
        if (i >= 0 && i < 3)
            return data[i];

        State = 3;
        return data[2];
    }

    float operator()() const
    {
        return data[0] + data[1] + data[2];
    }


    bool operator==(const Vector3F& v)
    {
        for (int i = 0; i < 3; i++)
            if (data[i] != v.data[i])
                return false;

        return true;
    }


    bool operator!=(const Vector3F& v)
    {
        return !(*this == v);
    }


    bool operator>(const Vector3F& v)
    {
        return (*this)() > v();
    }


    bool operator<(const Vector3F& v)
    {
        return (*this)() < v();
    }


    bool operator>=(const Vector3F& v)
    {
        return (*this)() >= v();
    }


    bool operator<=(const Vector3F& v)
    {
        return (*this)() <= v();
    }


    friend Vector3F operator+(Vector3F a, const Vector3F& b)
    {
        a += b;
        return a;
    }


    friend Vector3F operator-(Vector3F a, const Vector3F& b)
    {
        a -= b;
        return a;
    }


    friend Vector3F operator*(Vector3F a, float b)
    {
        a *= b;
        return a;
    }


    friend Vector3F operator/(Vector3F a, float b)
    {
        a /= b;
        return a;
    }


    friend istream& operator>>(istream& in, Vector3F& v)
    {
        in >> v.data[0] >> v.data[1] >> v.data[2];
        return in;
    }


    friend ostream& operator<<(ostream& out, const Vector3F& v)
    {
        out << "(" << v.data[0] << ", " << v.data[1] << ", " << v.data[2] << ")";
        return out;
    }
};


int Vector3F::count = 0;



void runTask1()
{
    srand(time(0));


    Vector3F a;
    Vector3F b;


    cout << "Enter vector a (x y z): ";
    cin >> a;

    cout << "Enter vector b (x y z): ";
    cin >> b;


    // випадковий вектор
    float arr[3];

    for (int i = 0; i < 3; i++)
        arr[i] = rand() % 10;

    Vector3F r(arr);

    cout << "Random vector r: " << r << endl;


    // складний вираз (5+ операцій)
    Vector3F c = a + b - r * 2 + (b % 2);


    cout << "Result c = a + b - r*2 + (b%2): ";
    cout << c << endl;


    // перевірка операторів
    cout << "a[1] = " << a[1] << endl;

    cout << "Sum a() = " << a() << endl;


    if (!a)
        cout << "Vector a has no zero elements\n";
    else
        cout << "Vector a contains zero elements\n";


    if (a > b)
        cout << "a > b\n";
    else
        cout << "a <= b\n";


    // інкременти
    ++a;
    cout << "After ++a: " << a << endl;

    b++;
    cout << "After b++: " << b << endl;


    // векторний добуток
    Vector3F t = a;
    t &= b;

    cout << "a cross b: " << t << endl;


    cout << "Number of objects: " << Vector3F::count << endl;
}