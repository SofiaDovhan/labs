#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// Інтерфейс
class Printable {
public:
    virtual void print() const = 0;
};

// Базовий клас
class LibraryItem : public Printable {
protected:
    string title;

public:
    LibraryItem(string t = "Невідомо") : title(t) {}

    virtual void print() const = 0;
    virtual void info() const {
        cout << "Базова інформація\n";
    }

    virtual ~LibraryItem() {}
};

class Book : public LibraryItem {
protected:
    string author;
    int year;

public:
    Book() : Book("Невідома", "Невідомий", 0) {}

    Book(string t, string a, int y)
        : LibraryItem(t), author(a), year(y) {}

    // гетери
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getYear() const { return year; }

    void print() const override {
        cout << "Книга: " << title
             << ", Автор: " << author
             << ", Рік: " << year << endl;
    }
};

class EBook final : public Book {
private:
    double fileSize;

public:
    EBook(string t, string a, int y, double size)
        : Book(t, a, y), fileSize(size) {}

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

    void print() const override {
        cout << "Ім’я: " << name << endl;
    }
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

// КОМПОЗИЦІЯ + ФАЙЛИ
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

    // збереження
    void saveToFile() {
        ofstream file("books.txt");
        for (const auto& b : books) {
            file << b.getTitle() << " "
                 << b.getAuthor() << " "
                 << b.getYear() << endl;
        }
    }

    // завантаження
    void loadFromFile() {
        ifstream file("books.txt");
        string t, a;
        int y;

        while (file >> t >> a >> y) {
            books.push_back(Book(t, a, y));
        }
    }
};
// КОНСОЛЬНЕ МЕНЮ
// Меню адміністратора
void adminMenu(Library& lib) {
    string password;
    cout << "Пароль: ";
    cin >> password;
   //  Аутентифікація —перевірка користувача.
    if (password != "1234") {
        cout << "Невірний пароль!\n";
        return;
    }

    string t, a;
    int y;

    cout << "Назва: ";
    cin >> t;
    cout << "Автор: ";
    cin >> a;
    cout << "Рік: ";
    cin >> y;

    lib.addBook(Book(t, a, y));
    lib.saveToFile();

    cout << "Книгу додано!\n";
}

// Меню користувача
void userMenu(Library& lib) {
    lib.showBooks();

    ofstream history("history.txt", ios::app);
    history << "Перегляд книг\n";
}

// reference
void show(const LibraryItem& item) {
    item.print();
}

int main() {

    Library lib;
    lib.loadFromFile();

    int choice;

    cout << "1. Адміністратор\n";
    cout << "2. Користувач\n";
    cin >> choice;

    if (choice == 1) {
        adminMenu(lib);
    }
    else if (choice == 2) {
        userMenu(lib);
    }

    cout << "\nПоліморфізм\n";
    Book b1("1984", "Орвелл", 1949);
    EBook eb("Guide", "Author", 2020, 5.5);

    show(b1);
    show(eb);

    return 0;
}