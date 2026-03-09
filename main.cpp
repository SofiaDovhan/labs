#include <iostream>
#include <string>

using namespace std;

class Book {
private:
    string title;
    string author;
    int year;

    static int bookCount;

public:
    Book() : Book("Невідома книга", "Невідомий автор", 0) {}

    Book(string t, string a, int y = 0)
        : title(t), author(a), year(y)
    {
        bookCount++;
    }
    // Конструктор копіювання
    Book(const Book& other)
      : title(other.title), author(other.author), year(other.year)
    {
        cout << "Copy constructor\n";
        bookCount++;
    }
    // Конструктор переміщення
    Book(Book&& other)
       : title(move(other.title)), author(move(other.author)), year(other.year)
    {
        cout << "Move constructor\n";
        bookCount++;
    }

    ~Book() {
        cout << "Книга \"" << title << "\" знищена\n";
    }
    // Використання this
    void setTitle(string title) {
        this->title = title;
    }
    // const метод
    void printInfo() const {
        cout << "Книга: " << title
             << ", Автор: " << author
             << ", Рік: " << year << endl;
    }
// static метод
static int getBookCount() {
    return bookCount;
}
    // Унарний оператор
    Book operator!() {
        Book temp = *this;
        temp.year = -temp.year;
        return temp;
    }

    //Бінарний оператор
    Book operator+(const Book& other) {
        Book temp;
        temp.title = this->title + " & " + other.title;
        temp.author = this->author;
        temp.year = this->year;
        return temp;
    }

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