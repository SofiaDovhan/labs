#include <iostream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

// Інтерфейс (8) - він тільки з virtual function
class Printable {
public:
    virtual void print() const = 0;
};

//БАЗОВИЙ КЛАС (абстрактний)
class LibraryItem : public Printable {
protected:
    string title;

public:
    LibraryItem(string t = "Невідомо") : title(t) {
        cout << "LibraryItem створено\n";
    }

    //Віртуальні функції - викликає правильний метод під час виконання
    virtual void print() const = 0; // pure virtual function - змушує  дочірні класи реалізувати
    virtual void info() const {
        cout << "Базова інформація\n";
    }

    //Віртуальний деструктор - треба щоб правильно звільнялася пам'ять
    virtual ~LibraryItem() {
        cout << "LibraryItem знищено\n";
    }
};
class Book : public LibraryItem {
protected:
    string author;
    int year;

public:
    Book() : Book("Невідома", "Невідомий", 0) {}

    Book(string t, string a, int y)
        : LibraryItem(t), author(a), year(y) {}

    // Copy
    Book(const Book& other)
        : LibraryItem(other.title),
          author(other.author),
          year(other.year)
    {
        cout << "Book Copy\n";
    }

    // Move
    Book(Book&& other)
        : LibraryItem(move(other.title)),
          author(move(other.author)),
          year(other.year)
    {
        cout << "Book Move\n";
    }

    // operator=
    Book& operator=(const Book& other) {
        if (this != &other) {
            title = other.title;
            author = other.author;
            year = other.year;
        }
        return *this;
    }

    ~Book() {
        cout << "Book знищено\n";
    }

    //Override - використовується в дочірньому класі, а virtual - для базового
    void print() const override {
        cout << "Книга: " << title
             << ", Автор: " << author
             << ", Рік: " << year << endl;
    }

    void info() const override {
        cout << "Інформація про книгу\n";
    }
};

// FINAL КЛАС (5) - після цього класу не можна наслідувати або його не можна визначити

class EBook final : public Book {
private:
    double fileSize;

public:
    EBook(string t, string a, int y, double size)
        : Book(t, a, y), fileSize(size) {}

    ~EBook() {
        cout << "EBook знищено\n";
    }

    void print() const override {
        cout << "EBook: " << title
             << ", розмір: " << fileSize << "MB\n";
    }
};

class Person : public Printable {
protected:
    string name;

public:
    Person(string n = "Невідомий") : name(n) {}

    virtual void print() const override {
        cout << "Ім’я: " << name << endl;
    }

    virtual ~Person() {}
};

class Reader : public Person {
private:
    int ticket;

public:
    Reader(string n, int t) : Person(n), ticket(t) {}

    void print() const override {
        cout << "Читач: " << name
             << ", квиток: " << ticket << endl;
    }
};

class Librarian : public Person {
private:
    int exp;

public:
    Librarian(string n, int e) : Person(n), exp(e) {}

    void print() const override {
        cout << "Бібліотекар: " << name
             << ", стаж: " << exp << endl;
    }
};

// КОМПОЗИЦІЯ
class Library {
private:
    vector<Book> books;

public:
    void addBook(const Book& b) {
        books.push_back(b);
    }

    void showBooks() const {
        for (const auto& b : books) {
            b.print();
        }
    }
};

// ФУНКЦІЯ (reference) (6) -передаємо будь який об'єкт-нащадок
void show(const LibraryItem& item) {
    item.print();
}

int main() {

    cout << "=== Static binding ===\n";
    Book b1("1984", "Орвелл", 1949);
    b1.print(); // статична прив’язка - Метод визначається на етапі компіляції

    cout << "\n=== Dynamic polymorphism (pointer) ===\n";
    LibraryItem* ptr = new Book("C++", "Bjarne", 2000);
    ptr->print();

    cout << "\n=== Dynamic polymorphism (reference) ===\n";
    EBook eb("Guide", "Author", 2020, 5.5);
    show(b1);
    show(eb);

    cout << "\n=== Інтерфейс (Printable) ===\n";
    Printable* p = new Reader("Софія", 123);
    p->print();

    cout << "\n=== Композиція ===\n";
    Library lib;
    lib.addBook(b1);
    lib.showBooks();

    delete ptr;
    delete p;

    return 0;
}