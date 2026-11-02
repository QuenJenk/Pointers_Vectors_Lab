#include <iostream>
#include <vector>
#include <string>

// Book Class Definition
class Book {
private:
    std::string title;
    std::string author;
    double price;

public:
    // Constructor to initialize all members
    Book(const std::string& t, const std::string& a, double p)
        : title(t), author(a), price(p) {}

    // Method to print out book details
    void displayInfo() const {
        std::cout << "Title: " << title
                  << " | Author: " << author
                  << " | Price: $" << price << "\n";
    }
};

// Inventory Class Definition
class Inventory {
private:
    std::vector<Book*> books;

public:
    // Destructor
    ~Inventory() {
        for (Book* bookPtr : books) {
            delete bookPtr;
        }
        books.clear();
    }

    // Adds a dynamically allocated book pointer to the vector
    void addBook(Book* bookPtr) {
        if (bookPtr != nullptr) {
            books.push_back(bookPtr);
        }
    }

    // Iterates and displays all books in the inventory
    void displayAll() const {
        if (books.empty()) {
            std::cout << "The inventory is currently empty.\n";
            return;
        }

        std::cout << "\n--- Current Inventory ---\n";
        for (size_t i = 0; i < books.size(); ++i) {
            std::cout << "[" << i << "] ";
            books[i]->displayInfo();
        }
        std::cout << "-------------------------\n";
    }

    // Removes and deallocates a book at a specific index
    void removeBook(int index) {
        if (index < 0 || static_cast<size_t>(index) >= books.size()) {
            std::cout << "Invalid index! Operation failed.\n";
            return;
        }

        // Deallocate the memory for the object first
        delete books[index];

        // Remove the pointer from the vector list
        books.erase(books.begin() + index);
        std::cout << "Book successfully removed and deallocated.\n";
    }
};

// Main Program
int main() {
    Inventory store; // Instantiated on the stack. Destructor handles clean up at exit.
    int choice = 0;

    while (choice != 4) {
        std::cout << "\n===== Book Inventory Menu =====\n"
                  << "1. Add New Book\n"
                  << "2. Display All Books\n"
                  << "3. Remove Book\n"
                  << "4. Quit\n"
                  << "Enter your choice: ";

        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Exiting program safely.\n";
            break;
        }

        std::cin.ignore(); // Clear newline from input buffer

        if (choice == 1) {
            std::string title, author;
            double price;

            std::cout << "Enter title: ";
            std::getline(std::cin, title);
            std::cout << "Enter author: ";
            std::getline(std::cin, author);
            std::cout << "Enter price: ";
            std::cin >> price;

            // Dynamically allocate memory for a new Book
            Book* newBook = new Book(title, author, price);
            store.addBook(newBook);
            std::cout << "Book added successfully!\n";

        } else if (choice == 2) {
            store.displayAll();

        } else if (choice == 3) {
            int index;
            store.displayAll();
            std::cout << "Enter the index of the book to remove: ";
            std::cin >> index;
            store.removeBook(index);

        } else if (choice == 4) {
            std::cout << "Exiting system. Cleaning up allocated resources...\n";
        } else {
            std::cout << "Invalid choice! Please select 1-4.\n";
        }
    }

    return 0;
}
