#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Base class representing a general library item
class LibraryItem {
protected:
    string title;
    int itemId;
    bool isAvailable;

public:
    LibraryItem(string t, int id) : title(t), itemId(id), isAvailable(true) {}
    
    // Virtual function to display item details
    virtual void displayInfo() const {
        cout << "Title: " << title << ", Item ID: " << itemId;
        cout << ", Available: " << (isAvailable ? "Yes" : "No") << endl;
    }

    // Virtual function to check out the item
    virtual void checkOut() {
        if (isAvailable) {
            isAvailable = false;
            cout << "Item checked out successfully.\n";
        } else {
            cout << "Item is already checked out.\n";
        }
    }

    // Virtual function to return the item
    virtual void returnItem() {
        if (!isAvailable) {
            isAvailable = true;
            cout << "Item returned successfully.\n";
        } else {
            cout << "Item was not checked out.\n";
        }
    }

    virtual ~LibraryItem() {}
};

// Derived class representing a book in the library
class Book : public LibraryItem {
    string author;

public:
    Book(string t, int id, string a) : LibraryItem(t, id), author(a) {}

    // Override displayInfo to include author details
    void displayInfo() const override {
        cout << "Book: " << title << " by " << author << ", ID: " << itemId;
        cout << ", Available: " << (isAvailable ? "Yes" : "No") << endl;
    }
};

// Base class representing a general user in the library
class User {
protected:
    string name;
    int userId;

public:
    User(string n, int id) : name(n), userId(id) {}

    // Virtual function for borrowing an item
    virtual void borrowItem(LibraryItem &item) {
        cout << name << " is borrowing an item.\n";
        item.checkOut();
    }

    // Virtual function for returning an item
    virtual void returnItem(LibraryItem &item) {
        cout << name << " is returning an item.\n";
        item.returnItem();
    }

    virtual void displayUserInfo() const {
        cout << "User: " << name << ", ID: " << userId << endl;
    }

    virtual ~User() {}
};

// Derived class representing a member of the library
class Member : public User {
    int maxBorrowLimit;

public:
    Member(string n, int id, int limit = 5) : User(n, id), maxBorrowLimit(limit) {}

    // Override borrowItem for Members
    void borrowItem(LibraryItem &item) override {
        cout << "Member " << name << " is borrowing an item.\n";
        item.checkOut();
    }

    void displayUserInfo() const override {
        cout << "Member: " << name << ", ID: " << userId << ", Max Borrow Limit: " << maxBorrowLimit << endl;
    }
};

// Derived class representing a librarian
class Librarian : public User {
public:
    Librarian(string n, int id) : User(n, id) {}

    // Override borrowItem for Librarians (different privileges)
    void borrowItem(LibraryItem &item) override {
        cout << "Librarian " << name << " is borrowing an item.\n";
        item.checkOut();
    }

    // Librarian can return items
    void returnItem(LibraryItem &item) override {
        cout << "Librarian " << name << " is returning an item.\n";
        item.returnItem();
    }

    void displayUserInfo() const override {
        cout << "Librarian: " << name << ", ID: " << userId << endl;
    }
};

// Main function to demonstrate the system
int main() {
    // Create some library items
    Book book1("C++ Programming", 101, "Bjarne Stroustrup");
    Book book2("Introduction to Algorithms", 102, "Thomas H. Cormen");

    // Create users
    Member member1("Alice", 201);
    Librarian librarian1("Mr. Smith", 301);

    // Demonstrate borrowing items
    cout << "Before borrowing:\n";
    book1.displayInfo();
    member1.displayUserInfo();
    
    // Member borrows book
    member1.borrowItem(book1);
    
    cout << "\nAfter borrowing:\n";
    book1.displayInfo();

    // Librarian tries to borrow the same book
    librarian1.borrowItem(book1);  // Should show that the book is already borrowed

    // Return the book
    member1.returnItem(book1);
    
    cout << "\nAfter returning:\n";
    book1.displayInfo();

    // Librarian borrows the book now
    librarian1.borrowItem(book1);
    cout << "\nAfter librarian borrows:\n";
    book1.displayInfo();

    return 0;
}
