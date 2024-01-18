#include<iostream>
#include<vector>
#include<algorithm>
#include<ctime>

using namespace std;

class Book {
public:
    string title;
    string author;
    string genre;

    Book(string t, string a, string g) : title(t), author(a), genre(g) {}
};

class User {
public:
    string name;

    User(string n) : name(n) {}
};

class Library {
private:
    vector<Book> books;
    vector<User> users;

public:
    void addBook(const Book& book) {
        books.push_back(book);
        cout << "Book added successfully.\n";
    }

    void displayBooks() {
        if (books.empty()) {
            cout << "No books in the library.\n";
        } else {
            cout << "Library Books:\n";
            for (const Book& book : books) {
                cout << "Title: " << book.title << "\tAuthor: " << book.author << "\tGenre: " << book.genre << endl;
            }
        }
    }

    void addUser(const User& user) {
        users.push_back(user);
        cout << "User added successfully.\n";
    }

    void displayUsers() {
        if (users.empty()) {
            cout << "No users in the library.\n";
        } else {
            cout << "Library Users:\n";
            for (const User& user : users) {
                cout << "User: " << user.name << endl;
            }
        }
    }

    void borrowBook(const string& title, const string& userName) {
        auto userIt = find_if(users.begin(), users.end(), [&userName](const User& user) {
            return user.name == userName;
        });

        auto bookIt = find_if(books.begin(), books.end(), [&title](const Book& book) {
            return book.title == title;
        });

        if (userIt != users.end() && bookIt != books.end()) {
            cout << "Book '" << title << "' borrowed by user '" << userName << "' successfully.\n";

            // Set a due date for the borrowed book (e.g., 7 days from now)
            time_t now = time(0);
            tm* dueDate = localtime(&now);
            dueDate->tm_mday += 7; // 7 days due date
            cout << "Due Date: " << asctime(dueDate);

            // Remove the borrowed book from the library
            books.erase(bookIt);
        } else {
            cout << "Book or user not found in the library.\n";
        }
    }
};

int main() {
    Library library;

    User user1("John Doe");
    User user2("Alice Smith");

    library.addUser(user1);
    library.addUser(user2);

    Book book1("The Catcher in the Rye", "J.D. Salinger", "Fiction");
    Book book2("To Kill a Mockingbird", "Harper Lee", "Drama");
    Book book3("1984", "George Orwell", "Science Fiction");

    library.addBook(book1);
    library.addBook(book2);
    library.addBook(book3);

    library.displayBooks();
    library.displayUsers();

    library.borrowBook("To Kill a Mockingbird", "John Doe");

    library.displayBooks();

    return 0;
}
