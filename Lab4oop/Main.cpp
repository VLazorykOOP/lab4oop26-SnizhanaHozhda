#include <iostream>
#include "Tasks.h" 

int main() {

    int choice;

    do {
        std::cout << "\n==============================\n";
        std::cout << "MENU:\n";
        std::cout << "1. Task 1\n";
        std::cout << "2. Task 2\n";
        std::cout << "3. Task 3\n";
        std::cout << "0. Exit \n";
        std::cout << "Your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1: runTask1(); break;
        case 2: runTask2(); break;
        case 3: runTask3(); break;
        case 0: std::cout << "Exit the program.\n"; break;
        default: std::cout << "Wrong choice, try again.\n";
        }
    } while (choice != 0);

    return 0;
};