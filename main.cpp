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

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getYear() const { return year; }

    void print() const override {
        cout << "Книга: " << title
             << ", Автор: " << author
             << ", Рік: " << year << endl;
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

    // Збереження з обробкою помилки
    void saveToFile() {
        try {
            ofstream file("books.txt");

            if (!file) {
                throw "Помилка запису у файл!";
            }

            for (const auto& b : books) {
                file << b.getTitle() << " "
                     << b.getAuthor() << " "
                     << b.getYear() << endl;
            }

        } catch (const char* msg) {
            cout << msg << endl;
        }
    }

    // Завантаження з обробкою помилки
    void loadFromFile() {
        try {
            ifstream file("books.txt");

            if (!file) {
                throw "Файл не знайдено!";
            }

            string t, a;
            int y;

            while (file >> t >> a >> y) {
                books.push_back(Book(t, a, y));
            }

        } catch (const char* msg) {
            cout << msg << endl;
        }
    }
};

// АДМІН МЕНЮ
void adminMenu(Library& lib) {
    string password;
    cout << "Пароль: ";
    cin >> password;

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

    // перевірка вводу
    if (cin.fail()) {
        cout << "Помилка вводу року!\n";
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }

    lib.addBook(Book(t, a, y));
    lib.saveToFile();

    // ІСТОРІЯ
    ofstream history("history.txt", ios::app);
    history << "Адміністратор додав книгу: " << t << endl;

    cout << "Книгу додано!\n";
}

// КОРИСТУВАЧ
void userMenu(Library& lib) {
    lib.showBooks();

    // ІСТОРІЯ
    ofstream history("history.txt", ios::app);
    history << "Користувач переглянув книги\n";
}
int main() {

    Library lib;
    lib.loadFromFile();

    int choice;

    while (true) {
        cout << "\nМЕНЮ\n";
        cout << "1. Адміністратор\n";
        cout << "2. Користувач\n";
        cout << "3. Вихід\n";
        cout << "Ваш вибір: ";

        cin >> choice;

        // перевірка вводу
        if (cin.fail()) {
            cout << "Помилка вводу!\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        if (choice == 1) {
            adminMenu(lib);
        }
        else if (choice == 2) {
            userMenu(lib);
        }
        else if (choice == 3) {
            cout << "Вихід з програми\n";
            break; // вихід
        }
        else {
            cout << "Невірний вибір!\n";
        }
    }

    return 0;
}