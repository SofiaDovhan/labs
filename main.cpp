#include <iostream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

   // БАЗОВИЙ КЛАС (IS-A) - наслідування (успадковує властивості іншого)
class LibraryItem {
protected:
    string title;

public:
    LibraryItem(string t = "Невідомо") : title(t) {
        cout << "LibraryItem створено\n";
    }

    virtual ~LibraryItem() {
        cout << "LibraryItem знищено\n";
    }

    virtual void print() const {
        cout << "Назва: " << title << endl;
    }
};

   // КЛАС Book (наслідує) - з базового класу доступне в дочірньому
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
    Book& operator=(const Book& other){
        if (this != &other) {
            LibraryItem::operator=(other);
            title = other.title;
            author = other.author;
            year = other.year;
        }
        return *this;
    }

    ~Book() {
        cout << "Book знищено\n";
    }

    void print() const override {
        cout << "Книга: " << title
             << ", Автор: " << author
             << ", Рік: " << year << endl;
    }
};
   // ДОЧІРНІЙ КЛАС (IS-A)
class EBook : public Book {
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


   // БАЗОВИЙ КЛАС Person
class Person {
protected:
    string name;

public:
    Person(string n = "Невідомий") : name(n) {}

    virtual void info() const {
        cout << "Ім’я: " << name << endl;
    }

    virtual ~Person() {}
};

   //Reader (IS-A Person)
class Reader : public Person {
private:
    int ticket;

public:
    Reader(string n, int t) : Person(n), ticket(t) {}

    void info() const override {
        cout << "Читач: " << name
             << ", квиток: " << ticket << endl;
    }
};

// Librarian (IS-A Person)
class Librarian : public Person {
private:
    int exp;

public:
    Librarian(string n, int e) : Person(n), exp(e) {}

    void info() const override {
        cout << "Бібліотекар: " << name
             << ", стаж: " << exp << endl;
    }
};

//КОМПОЗИЦІЯ (HAS-A)
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

int main() {

    Book b1("1984", "Орвелл", 1949);
    EBook eb("C++ Guide", "Bjarne", 2020, 5.5);

    Reader r("Софія", 123);
    Librarian l("Олена", 10);

    Library lib;
    lib.addBook(b1);

    cout << "\n--- Вивід ---\n";
    b1.print();
    eb.print();

    r.info();
    l.info();

    cout << "\n--- Бібліотека ---\n";
    lib.showBooks();

    return 0;
}