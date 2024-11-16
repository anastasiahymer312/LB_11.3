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
    cout << "������ ��'� ����� ��� ������: ";
    cin >> filename;

    int menuItem;

    while (true) {
        cout << "\n����:\n";
        cout << "1 - �������� ����\n";
        cout << "2 - ������ ���������� �� �����\n";
        cout << "3 - ������� ���� �����\n";
        cout << "4 - ������ ����������\n";
        cout << "5 - ���������� ��� ����������\n";
        cout << "6 - �������� ����������\n";
        cout << "0 - �����\n";
        cout << "������ ��: ";
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
            cout << "������� ����! ��������� �� ���.\n";
        }
    }
}

void CreateFile(const string& filename) {
    ofstream file(filename, ios::out);
    if (!file) {
        cout << "�� ������� �������� ����!\n";
        return;
    }
    cout << "���� �������� ������.\n";
    file.close();
}

void AddToFile(const string& filename) {
    ofstream file(filename, ios::app);
    if (!file) {
        cout << "�� ������� ������� ���� ��� ������!\n";
        return;
    }

    Employee emp;
    cin.ignore(); 
    cout << "������ �������: ";
    getline(cin, emp.last_name);
    cout << "������ �������: ";
    getline(cin, emp.initials);
    cout << "������ ������: ";
    getline(cin, emp.position);
    cout << "������ �� ��������� �� ������: ";
    cin >> emp.hire_year;
    cout << "������ �����: ";
    cin >> emp.salary;

    file << emp.last_name << "\n"
        << emp.initials << "\n"
        << emp.position << "\n"
        << emp.hire_year << "\n"
        << emp.salary << "\n";
    file.close();
    cout << "��� ������ ����� �� �����.\n";
}

void PrintFile(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "�� ������� ������� ���� ��� �������!\n";
        return;
    }

    Employee emp;
    int number = 1;

    cout << "===============================================================================\n";
    cout << "| � | �������       | ������� | ������          | г� ��������� | �����     |\n";
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
        cout << "�� ������� ������� ���� ��� �������!\n";
        return;
    }

    string search_last_name;
    cout << "������ ������� ��� ������: ";
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
            cout << "�������� ����������:\n";
            cout << "�������: " << emp.last_name << "\n"
                << "�������: " << emp.initials << "\n"
                << "������: " << emp.position << "\n"
                << "г� ���������: " << emp.hire_year << "\n"
                << "�����: " << emp.salary << "\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "���������� � ����� �������� �� ��������.\n";
    }

    file.close();
}

void EditFile(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "�� ������� ������� ���� ��� �������!\n";
        return;
    }

    ofstream temp("temp.txt", ios::out);
    if (!temp) {
        cout << "�� ������� �������� ���������� ����!\n";
        return;
    }

    string search_last_name;
    cout << "������ ������� ���������� ��� �����������: ";
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
            cout << "������ ��� ��� ��� ����������:\n";
            cin.ignore();
            cout << "�������: ";
            getline(cin, emp.last_name);
            cout << "�������: ";
            getline(cin, emp.initials);
            cout << "������: ";
            getline(cin, emp.position);
            cout << "г� ���������: ";
            cin >> emp.hire_year;
            cout << "�����: ";
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
        cout << "��� ������ ������.\n";
    }
    else {
        cout << "���������� � ����� �������� �� ��������.\n";
    }
}

void DeleteFromFile(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "�� ������� ������� ���� ��� �������!\n";
        return;
    }

    ofstream temp("temp.txt", ios::out);
    if (!temp) {
        cout << "�� ������� �������� ���������� ����!\n";
        return;
    }

    string search_last_name;
    cout << "������ ������� ���������� ��� ���������: ";
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
        cout << "���������� ������ ��������.\n";
    }
    else {
        cout << "���������� � ����� �������� �� ��������.\n";
    }
}
