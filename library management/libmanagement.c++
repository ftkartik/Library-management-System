#include <iostream>
#include <string>

using namespace std;

const int MAX_BOOKS = 100;
const int MAX_MEMBERS = 100;

class Book {
    private:
        string title;
        string author;
        int book_id;
        bool checked_out;
    public:
        Book() {
            title = "";
            author = "";
            book_id = -1;
            checked_out = false;
        }
        void set_book(string t, string a, int id) {
            title = t;
            author = a;
            book_id = id;
            checked_out = false;
        }
        void display_book() {
            cout << "Title: " << title << endl;
            cout << "Author: " << author << endl;
            cout << "Book ID: " << book_id << endl;
            if (checked_out) {
                cout << "Status: Checked Out" << endl;
            } else {
                cout << "Status: Available" << endl;
            }
        }
        int get_id() {
            return book_id;
        }
        bool is_checked_out() {
            return checked_out;
        }
        void check_out() {
            checked_out = true;
        }
        void return_book() {
            checked_out = false;
        }
};

class Member {
    private:
        string name;
        int member_id;
        int books_checked_out;
        Member* next;
    public:
        Member() {
            name = "";
            member_id = -1;
            books_checked_out = 0;
            next = nullptr;
        }
        void set_member(string n, int id) {
            name = n;
            member_id = id;
        }
        void display_member() {
            cout << "Name: " << name << endl;
            cout << "Member ID: " << member_id << endl;
            cout << "Books Checked Out: " << books_checked_out << endl;
        }
        int get_id() {
            return member_id;
        }
        void increment_books_checked_out() {
            books_checked_out++;
        }
        void decrement_books_checked_out() {
            books_checked_out--;
        }
        Member* get_next() {
            return next;
        }
        void set_next(Member* ptr) {
            next = ptr;
        }
};

class Library {
    private:
        Book books[MAX_BOOKS];
        Member* members[MAX_MEMBERS];
        int num_books;
        int num_members;
    public:
        Library() {
            num_books = 0;
            num_members = 0;
            for (int i = 0; i < MAX_MEMBERS; i++) {
                members[i] = nullptr;
            }
        }
        void add_book(string title, string author, int book_id) {
            if (num_books < MAX_BOOKS) {
                books[num_books].set_book(title, author, book_id);
                num_books++;
            } else {
                cout << "The library has reached its maximum capacity." << endl;
            }
        }
        void add_member(string name, int member_id) {
            if (num_members < MAX_MEMBERS) {
                members[num_members] = new Member();
                members[num_members]->set_member(name, member_id);
                num_members++;
            } else {
                cout << "The library has reached its maximum capacity." << endl;
            }
        }
        Book* find_book(int book_id) {
    for (int i = 0; i < num_books; i++) {
        if (books[i].get_id() == book_id) {
            return &books[i];
        }
    }
    return nullptr;
}
Member* find_member(int member_id) {
    for (int i = 0; i < num_members; i++) {
        if (members[i]->get_id() == member_id) {
            return members[i];
        }
    }
    return nullptr;
}
void check_out_book(int book_id, int member_id) {
    Book* book_ptr = find_book(book_id);
    Member* member_ptr = find_member(member_id);
    if (book_ptr == nullptr || member_ptr == nullptr) {
        cout << "Invalid book or member ID." << endl;
    } else if (book_ptr->is_checked_out()) {
        cout << "The book is already checked out." << endl;
    } else {
        book_ptr->check_out();
        member_ptr->increment_books_checked_out();
        cout << "Book checked out successfully." << endl;
    }
}
void return_book(int book_id, int member_id) {
    Book* book_ptr = find_book(book_id);
    Member* member_ptr = find_member(member_id);
    if (book_ptr == nullptr || member_ptr == nullptr) {
        cout << "Invalid book or member ID." << endl;
    } else if (!book_ptr->is_checked_out()) {
        cout << "The book is already available." << endl;
    } else {
        book_ptr->return_book();
        member_ptr->decrement_books_checked_out();
        cout << "Book returned successfully." << endl;
    }
}
void display_books() {
    if (num_books == 0) {
        cout << "There are no books in the library." << endl;
    } else {
        for (int i = 0; i < num_books; i++) {
            books[i].display_book();
            cout << endl;
        }
    }
}
void display_members() {
    if (num_members == 0) {
        cout << "There are no members in the library." << endl;
    } else {
        for (int i = 0; i < num_members; i++) {
            members[i]->display_member();
            cout << endl;
        }
    }
}

};

int main() {
    Library library;
    int choice = 0;
    while (choice != 6) {
        cout << "1. Add book\n";
        cout << "2. Add member\n";
        cout << "3. Check out book\n";
        cout << "4. Return book\n";
        cout << "5. Display books and members\n";
        cout << "6. Quit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: {
                string title, author;
                int id;
                cout << "Enter the title of the book: ";
                cin >> title;
                cout << "Enter the author of the book: ";
                cin >> author;
                cout << "Enter the ID of the book: ";
                cin >> id;
                library.add_book(title, author, id);
                break;
            }
            case 2: {
                string name;
                int id;
                cout << "Enter the name of the member: ";
                cin >> name;
                cout << "Enter the ID of the member: ";
                cin >> id;
                library.add_member(name, id);
                break;
            }
            case 3: {
                int book_id, member_id;
                cout << "Enter the ID of the book to be checked out: ";
                cin >> book_id;
                cout << "Enter the ID of the member who is checking out the book: ";
                cin >> member_id;
                library.check_out_book(book_id, member_id);
                break;
            }
            case 4: {
                int book_id, member_id;
                cout << "Enter the ID of the book to be returned: ";
                cin >> book_id;
                cout << "Enter the ID of the member who is returning the book: ";
                cin >> member_id;
                library.return_book(book_id, member_id);
                break;
            }
            case 5: {
                library.display_books();
                library.display_members();
                break;
            }
            case 6: {
                break;
            }
            default: {
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
        }
    }
    return 0;
}
