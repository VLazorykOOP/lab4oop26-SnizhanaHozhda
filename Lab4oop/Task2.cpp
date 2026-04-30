#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Tasks.h"


using namespace std;



class Person
{
public:

    string surname;
    string name;
    string patronymic;


    friend istream& operator>>(istream& in, Person& p)
    {
        in >> p.surname >> p.name >> p.patronymic;
        return in;
    }


    friend ostream& operator<<(ostream& out, const Person& p)
    {
        out << p.surname << " " << p.name << " " << p.patronymic;
        return out;
    }
};



class PhoneBook
{
private:

    string phones[100];
    Person persons[100];
    int size = 0;


public:

    int CodeError = 0;


    void add(string phone, Person p)
    {
        phones[size] = phone;
        persons[size] = p;
        size++;
    }


    Person& operator[](string phone)
    {
        for (int i = 0; i < size; i++)
        {
            if (phones[i] == phone)
            {
                CodeError = 0;
                return persons[i];
            }
        }

        CodeError = 1;

        static Person empty;
        return empty;
    }


    Person& operator()(string phone)
    {
        return (*this)[phone];
    }


    void inputKeyboard()
    {
        int n;

        cout << "Numbr of records: ";
        cin >> n;

        for (int i = 0; i < n; i++)
        {
            string phone;
            Person p;

            cout << "Phone: ";
            cin >> phone;

            cout << "Name: ";
            cin >> p;

            add(phone, p);
        }
    }


    void inputFile(string filename)
    {
        ifstream file(filename);

        int n;
        file >> n;

        for (int i = 0; i < n; i++)
        {
            string phone;
            Person p;

            file >> phone >> p;

            add(phone, p);
        }

        file.close();
    }


    void inputRandom(int n)
    {
        string surnames[] = { "Ivanenko", "Petrenko", "Shevchenko" };
        string names[] = { "Ivan", "Olena", "Yulia" };
        string patronymics[] = { "Ivanovich", "Petrivna", "Olegovna" };

        for (int i = 0; i < n; i++)
        {
            string phone = "0";

            for (int j = 0; j < 9; j++)
            {
                phone += char('0' + rand() % 10);
            }

            Person p;

            p.surname = surnames[rand() % 3];
            p.name = names[rand() % 3];
            p.patronymic = patronymics[rand() % 3];

            add(phone, p);
        }
    }


    friend ostream& operator<<(ostream& out, const PhoneBook& pb)
    {
        for (int i = 0; i < pb.size; i++)
        {
            out << pb.phones[i] << " -> " << pb.persons[i] << endl;
        }

        return out;
    }
};




void runTask2()
{
    srand(time(0));

    PhoneBook pb;

    int mode;

    cout << "Choose input method:\n";
    cout << "1 - Keyboard\n";
    cout << "2 - File\n";
    cout << "3 - Random\n";
    cout << "Your choice: ";

    cin >> mode;

\
    if (mode == 1)
    {
        pb.inputKeyboard();
    }

    else if (mode == 2)
    {
        string filename;

        cout << "Enter filename: ";
        cin >> filename;

        pb.inputFile(filename);
    }

    else if (mode == 3)
    {
        int n;

        cout << "How many records: ";
        cin >> n;

        pb.inputRandom(n);
    }


    cout << "\nPhoneBook:\n";
    cout << pb;


 
    string phone;

    cout << "\nEnter phone for search: ";
    cin >> phone;


   
    Person p1 = pb[phone];

    if (pb.CodeError == 0)
    {
        cout << "Found using []: " << p1 << endl;
    }
    else
    {
        cout << "Error: not found using []\n";
    }


    Person p2 = pb(phone);

    if (pb.CodeError == 0)
    {
        cout << "Found using (): " << p2 << endl;
    }
    else
    {
        cout << "Error: not found using ()\n";
    }
}