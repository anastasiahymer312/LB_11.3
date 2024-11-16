#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <windows.h>

using namespace std;

struct Employee {
    string last_name;
    string initials;
    string position;
    int hire_year = 0;
    double salary = 0;
};

void CreateFile(const string& filename);
void AddToFile(const string& filename);
void PrintFile(const string& filename);
void SearchInFile(const string& filename);
void EditFile(const string& filename);
void DeleteFromFile(const string& filename);

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string filename;
    cout << "Введіть ім'я файлу для роботи: ";
    cin >> filename;

    int menuItem;

    while (true) {
        cout << "\nМеню:\n";
        cout << "1 - Створити файл\n";
        cout << "2 - Додати працівника до файлу\n";
        cout << "3 - Вивести вміст файлу\n";
        cout << "4 - Знайти працівника\n";
        cout << "5 - Редагувати дані працівника\n";
        cout << "6 - Видалити працівника\n";
        cout << "0 - Вийти\n";
        cout << "Оберіть дію: ";
        cin >> menuItem;

        switch (menuItem) {
        case 1:
            CreateFile(filename);
            break;
        case 2:
            AddToFile(filename);
            break;
        case 3:
            PrintFile(filename);
            break;
        case 4:
            SearchInFile(filename);
            break;
        case 5:
            EditFile(filename);
            break;
        case 6:
            DeleteFromFile(filename);
            break;
        case 0:
            return 0;
        default:
            cout << "Невірний вибір! Спробуйте ще раз.\n";
        }
    }
}

void CreateFile(const string& filename) {
    ofstream file(filename, ios::out);
    if (!file) {
        cout << "Не вдалося створити файл!\n";
        return;
    }
    cout << "Файл створено успішно.\n";
    file.close();
}

void AddToFile(const string& filename) {
    ofstream file(filename, ios::app);
    if (!file) {
        cout << "Не вдалося відкрити файл для запису!\n";
        return;
    }

    Employee emp;
    cin.ignore(); 
    cout << "Введіть прізвище: ";
    getline(cin, emp.last_name);
    cout << "Введіть ініціали: ";
    getline(cin, emp.initials);
    cout << "Введіть посаду: ";
    getline(cin, emp.position);
    cout << "Введіть рік прийняття на роботу: ";
    cin >> emp.hire_year;
    cout << "Введіть оклад: ";
    cin >> emp.salary;

    file << emp.last_name << "\n"
        << emp.initials << "\n"
        << emp.position << "\n"
        << emp.hire_year << "\n"
        << emp.salary << "\n";
    file.close();
    cout << "Дані успішно додані до файлу.\n";
}

void PrintFile(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Не вдалося відкрити файл для читання!\n";
        return;
    }

    Employee emp;
    int number = 1;

    cout << "===============================================================================\n";
    cout << "| № | Прізвище       | Ініціали | Посада          | Рік прийняття | Оклад     |\n";
    cout << "-------------------------------------------------------------------------------\n";

    while (getline(file, emp.last_name) &&
        getline(file, emp.initials) &&
        getline(file, emp.position) &&
        file >> emp.hire_year &&
        file >> emp.salary) {
        file.ignore(); 
        cout << "| " << setw(2) << number++ << " | "
            << setw(13) << left << emp.last_name << " | "
            << setw(8) << emp.initials << " | "
            << setw(14) << emp.position << " | "
            << setw(13) << emp.hire_year << " | "
            << setw(9) << fixed << setprecision(2) << emp.salary << " |\n";
    }
    cout << "===============================================================================\n";
    file.close();
}

void SearchInFile(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Не вдалося відкрити файл для читання!\n";
        return;
    }

    string search_last_name;
    cout << "Введіть прізвище для пошуку: ";
    cin >> search_last_name;

    Employee emp;
    bool found = false;

    while (getline(file, emp.last_name) &&
        getline(file, emp.initials) &&
        getline(file, emp.position) &&
        file >> emp.hire_year &&
        file >> emp.salary) {
        file.ignore(); 
        if (emp.last_name == search_last_name) {
            cout << "Знайдено працівника:\n";
            cout << "Прізвище: " << emp.last_name << "\n"
                << "Ініціали: " << emp.initials << "\n"
                << "Посада: " << emp.position << "\n"
                << "Рік прийняття: " << emp.hire_year << "\n"
                << "Оклад: " << emp.salary << "\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Працівника з таким прізвищем не знайдено.\n";
    }

    file.close();
}

void EditFile(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Не вдалося відкрити файл для читання!\n";
        return;
    }

    ofstream temp("temp.txt", ios::out);
    if (!temp) {
        cout << "Не вдалося створити тимчасовий файл!\n";
        return;
    }

    string search_last_name;
    cout << "Введіть прізвище працівника для редагування: ";
    cin >> search_last_name;

    Employee emp;
    bool found = false;

    while (getline(file, emp.last_name) &&
        getline(file, emp.initials) &&
        getline(file, emp.position) &&
        file >> emp.hire_year &&
        file >> emp.salary) {
        file.ignore(); 
        if (emp.last_name == search_last_name) {
            cout << "Введіть нові дані для працівника:\n";
            cin.ignore();
            cout << "Прізвище: ";
            getline(cin, emp.last_name);
            cout << "Ініціали: ";
            getline(cin, emp.initials);
            cout << "Посада: ";
            getline(cin, emp.position);
            cout << "Рік прийняття: ";
            cin >> emp.hire_year;
            cout << "Оклад: ";
            cin >> emp.salary;
            found = true;
        }
        temp << emp.last_name << "\n"
            << emp.initials << "\n"
            << emp.position << "\n"
            << emp.hire_year << "\n"
            << emp.salary << "\n";
    }

    file.close();
    temp.close();

    remove(filename.c_str());
    rename("temp.txt", filename.c_str());

    if (found) {
        cout << "Дані успішно змінено.\n";
    }
    else {
        cout << "Працівника з таким прізвищем не знайдено.\n";
    }
}

void DeleteFromFile(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Не вдалося відкрити файл для читання!\n";
        return;
    }

    ofstream temp("temp.txt", ios::out);
    if (!temp) {
        cout << "Не вдалося створити тимчасовий файл!\n";
        return;
    }

    string search_last_name;
    cout << "Введіть прізвище працівника для видалення: ";
    cin >> search_last_name;

    Employee emp;
    bool found = false;

    while (getline(file, emp.last_name) &&
        getline(file, emp.initials) &&
        getline(file, emp.position) &&
        file >> emp.hire_year &&
        file >> emp.salary) {
        file.ignore();
        if (emp.last_name == search_last_name) {
            found = true;
            continue; 
        }
        temp << emp.last_name << "\n"
            << emp.initials << "\n"
            << emp.position << "\n"
            << emp.hire_year << "\n"
            << emp.salary << "\n";
    }

    file.close();
    temp.close();

    remove(filename.c_str());
    rename("temp.txt", filename.c_str());

    if (found) {
        cout << "Працівника успішно видалено.\n";
    }
    else {
        cout << "Працівника з таким прізвищем не знайдено.\n";
    }
}
