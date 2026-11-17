#include <iostream>
#include <string>
#include <cstdlib>
#include <windows.h>
#include <fstream>
#include <list>
#include <set>
#include <vector>
#include <algorithm>
#include <ctime>
#include <sstream>
#include "Header1.h"

using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Settings settings;
    set<string> specialties;
    list<string> studentNames;
    loadSettings(settings);
    loadSpecialties(specialties);
    loadStudentNames(studentNames);
    int choice = 0;
    while (choice != 5) {
            cout << "\nМОЯ ЖИЗНЬ В УНИВЕРСИТЕТЕ\n";
            cout << "1. Начать игру\n";
            cout << "2. Загрузить игру\n";
            cout << "3. Настройки\n";
            cout << "4. О программе\n";
            cout << "5. Выход\n";
            cin >> choice;
            switch (choice) {
            case 1:
                startGame(settings);
                break;
            case 2:
                loadGame(settings);
                break;
            case 3:
                settingsMenu(settings, specialties, studentNames);
                break;
            case 4:
                about();
                break;
            }
    }
    return 0;
}

