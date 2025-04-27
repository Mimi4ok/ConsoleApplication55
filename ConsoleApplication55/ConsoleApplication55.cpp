// ConsoleApplication55.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAX_CONTACTS = 100;

struct Contact {
    char name[100];
    char homePhone[20];
    char workPhone[20];
    char mobilePhone[20];
    char extraInfo[100];
};

Contact contacts[MAX_CONTACTS];
int contactCount = 0;

void addContact() {
    if (contactCount >= MAX_CONTACTS) {
        cout << "Phonebook is full.\n";
        return;
    }
    cin.ignore();
    cout << "Enter name: "; cin.getline(contacts[contactCount].name, 100);
    cout << "Home phone: "; cin.getline(contacts[contactCount].homePhone, 20);
    cout << "Work phone: "; cin.getline(contacts[contactCount].workPhone, 20);
    cout << "Mobile phone: "; cin.getline(contacts[contactCount].mobilePhone, 20);
    cout << "Extra info: "; cin.getline(contacts[contactCount].extraInfo, 100);
    contactCount++;
}

void showAll() {
    if (contactCount == 0) {
        cout << "Phonebook is empty.\n";
        return;
    }
    for (int i = 0; i < contactCount; ++i) {
        cout << "Name: " << contacts[i].name << endl;
        cout << "Home Phone: " << contacts[i].homePhone << endl;
        cout << "Work Phone: " << contacts[i].workPhone << endl;
        cout << "Mobile Phone: " << contacts[i].mobilePhone << endl;
        cout << "Extra Info: " << contacts[i].extraInfo << endl;
        cout << "--------------------------\n";
    }
}

void searchByName() {
    char query[100];
    cin.ignore();
    cout << "Enter name to search: "; cin.getline(query, 100);
    bool found = false;
    for (int i = 0; i < contactCount; ++i) {
        if (strcmp(contacts[i].name, query) == 0) {
            cout << "Name: " << contacts[i].name << endl;
            cout << "Home Phone: " << contacts[i].homePhone << endl;
            cout << "Work Phone: " << contacts[i].workPhone << endl;
            cout << "Mobile Phone: " << contacts[i].mobilePhone << endl;
            cout << "Extra Info: " << contacts[i].extraInfo << endl;
            cout << "--------------------------\n";
            found = true;
        }
    }
    if (!found)
        cout << "Contact not found.\n";
}

void deleteByName() {
    char query[100];
    cin.ignore();
    cout << "Enter name to delete: "; cin.getline(query, 100);
    for (int i = 0; i < contactCount; ++i) {
        if (strcmp(contacts[i].name, query) == 0) {
            for (int j = i; j < contactCount - 1; ++j)
                contacts[j] = contacts[j + 1];
            contactCount--;
            cout << "Contact deleted.\n";
            return;
        }
    }
    cout << "Contact not found.\n";
}

void saveToFile(const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        cout << "Cannot open file.\n";
        return;
    }
    fwrite(&contactCount, sizeof(contactCount), 1, file);
    fwrite(contacts, sizeof(Contact), contactCount, file);
    fclose(file);
    cout << "Contacts saved.\n";
}

void loadFromFile(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        cout << "Cannot open file.\n";
        return;
    }
    fread(&contactCount, sizeof(contactCount), 1, file);
    fread(contacts, sizeof(Contact), contactCount, file);
    fclose(file);
    cout << "Contacts loaded.\n";
}

int main() {
    int choice;
    const char* filename = "fle.txt";

    do {
        cout << "\n--- Phonebook Menu ---\n";
        cout << "1. Add contact\n";
        cout << "2. Show all contacts\n";
        cout << "3. Search by name\n";
        cout << "4. Delete contact\n";
        cout << "5. Save to file\n";
        cout << "6. Load from file\n";
        cout << "0. Exit\n";
        cout << "Your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: addContact(); break;
        case 2: showAll(); break;
        case 3: searchByName(); break;
        case 4: deleteByName(); break;
        case 5: saveToFile(filename); break;
        case 6: loadFromFile(filename); break;
        }
    } while (choice != 0);

    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
