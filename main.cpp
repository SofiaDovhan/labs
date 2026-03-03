#include <iostream>
#include <string>

using namespace std;

class Book {
private:
    string title;
    string author;
    int year;

public:
    Book() : Book("Невідома книга", "Невідомий автор", 0) {}

    Book(string t, string a, int y = 0)
        : title(t), author(a), year(y) {}

    ~Book() {
        cout << "Книга \"" << title << "\" знищена\n";
    }

    void printInfo() const {
        cout << "Книга: " << title
             << ", Автор: " << author
             << ", Рік: " << year << endl;
    }
};

class Reader {
private:
    string name;
    int ticketNumber;

public:
    Reader() : Reader("Без імені", 0) {}

    Reader(string n, int t)
        : name(n), ticketNumber(t) {} // Перевантажений конструктор

    ~Reader() {
        cout << "Читач " << name << " видалений\n";   // Деструктор
    }

    void showReader() const {
        cout << "Читач: " << name
             << ", Квиток №" << ticketNumber << endl;
    }
};

class Librarian {
private:
    string name;
    int experience;

public:
    Librarian() : name("Невідомий"), experience(0) {} // Конструктор за замовчуванням

    Librarian(string n, int exp)
        : name(n), experience(exp) {} // Конструктор з параметрами

    ~Librarian() {
        cout << "Бібліотекар " << name << " звільнений\n"; // Деструктор
    }

    void info() const {
        cout << "Бібліотекар: " << name
             << ", стаж: " << experience << " років\n";
    }
};

int main() {
    Book b1;
    Book b2("1984", "Джордж Орвелл", 1949);

    Reader r1("Софія", 1234);
    Librarian l1("Олена", 10);

    b1.printInfo();
    b2.printInfo();
    r1.showReader();
    l1.info();

    return 0;
}