// ConsoleApplication55.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAX_CONTACTS = 100;

class Contact {
private:
    char* name;
    char homePhone[20];
    char workPhone[20];
    char mobilePhone[20];
    char extraInfo[100];

public:
    Contact() {
        name = nullptr;
        homePhone[0] = workPhone[0] = mobilePhone[0] = extraInfo[0] = '\0';
    }

    Contact(const char* n, const char* home, const char* work, const char* mobile, const char* extra) {
        name = new char[strlen(n) + 1];
        strcpy(name, n);
        strcpy(homePhone, home);
        strcpy(workPhone, work);
        strcpy(mobilePhone, mobile);
        strcpy(extraInfo, extra);
    }

    Contact(const Contact& c) {
        name = new char[strlen(c.name) + 1];
        strcpy(name, c.name);
        strcpy(homePhone, c.homePhone);
        strcpy(workPhone, c.workPhone);
        strcpy(mobilePhone, c.mobilePhone);
        strcpy(extraInfo, c.extraInfo);
    }

    Contact& operator=(const Contact& c) {
        if (this != &c) {
            delete[] name;
            name = new char[strlen(c.name) + 1];
            strcpy(name, c.name);
            strcpy(homePhone, c.homePhone);
            strcpy(workPhone, c.workPhone);
            strcpy(mobilePhone, c.mobilePhone);
            strcpy(extraInfo, c.extraInfo);
        }
        return *this;
    }

    ~Contact() {
        delete[] name;
    }

    const char* getName() const {
        return name;
    }

    void display() const {
        cout << "Name: " << name << endl;
        cout << "Home Phone: " << homePhone << endl;
        cout << "Work Phone: " << workPhone << endl;
        cout << "Mobile Phone: " << mobilePhone << endl;
        cout << "Extra Info: " << extraInfo << endl;
        cout << "--------------------------\n";
    }

    void saveToFile(FILE* file) const {
        int len = strlen(name);
        fwrite(&len, sizeof(len), 1, file);
        fwrite(name, sizeof(char), len, file);
        fwrite(homePhone, sizeof(homePhone), 1, file);
        fwrite(workPhone, sizeof(workPhone), 1, file);
        fwrite(mobilePhone, sizeof(mobilePhone), 1, file);
        fwrite(extraInfo, sizeof(extraInfo), 1, file);
    }

    void loadFromFile(FILE* file) {
        int len;
        fread(&len, sizeof(len), 1, file);
        name = new char[len + 1];
        fread(name, sizeof(char), len, file);
        name[len] = '\0';
        fread(homePhone, sizeof(homePhone), 1, file);
        fread(workPhone, sizeof(workPhone), 1, file);
        fread(mobilePhone, sizeof(mobilePhone), 1, file);
        fread(extraInfo, sizeof(extraInfo), 1, file);
    }
};

Contact contacts[MAX_CONTACTS];
int contactCount = 0;

void addContact() {
    if (contactCount >= MAX_CONTACTS) {
        cout << "Phonebook is full.\n";
        return;
    }

    char name[100], home[20], work[20], mobile[20], extra[100];
    cin.ignore();
    cout << "Enter name: "; cin.getline(name, 100);
    cout << "Home phone: "; cin.getline(home, 20);
    cout << "Work phone: "; cin.getline(work, 20);
    cout << "Mobile phone: "; cin.getline(mobile, 20);
    cout << "Extra info: "; cin.getline(extra, 100);

    contacts[contactCount++] = Contact(name, home, work, mobile, extra);
}

void showAll() {
    if (contactCount == 0) {
        cout << "Phonebook is empty.\n";
        return;
    }
    for (int i = 0; i < contactCount; ++i) {
        contacts[i].display();
    }
}

void searchByName() {
    char query[100];
    cin.ignore();
    cout << "Enter name to search: "; cin.getline(query, 100);
    bool found = false;
    for (int i = 0; i < contactCount; ++i) {
        if (strcmp(contacts[i].getName(), query) == 0) {
            contacts[i].display();
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
        if (strcmp(contacts[i].getName(), query) == 0) {
            for (int j = i; j < contactCount - 1; ++j)
                contacts[j] = contacts[j + 1];
            --contactCount;
            cout << "Contact deleted.\n";
            return;
        }
    }
    cout << "Contact not found.\n";
}

void saveToFile(const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        cout << "Cannot open file for writing.\n";
        return;
    }
    fwrite(&contactCount, sizeof(contactCount), 1, file);
    for (int i = 0; i < contactCount; ++i) {
        contacts[i].saveToFile(file);
    }
    fclose(file);
    cout << "Contacts saved to file.\n";
}

void loadFromFile(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        cout << "Cannot open file for reading.\n";
        return;
    }
    fread(&contactCount, sizeof(contactCount), 1, file);
    for (int i = 0; i < contactCount; ++i) {
        contacts[i].loadFromFile(file);
    }
    fclose(file);
    cout << "Contacts loaded from file.\n";
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
