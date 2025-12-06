#include <iostream>
#include <string>
using namespace std;

struct Book 
{
    int id;
    string title;
    string author;
    bool isBorrowed;
};

struct BorrowedBy 
{
    int bookId;
    string Name;
    string date;
    BorrowedBy* next;
};

struct Node 
{
    Book* book;
    Node* next;
};

struct QNode 
{
    int value;
    QNode* next;
};

QNode* front = NULL;
QNode* rear = NULL;

void EnQueue(int store) 
{
    QNode* temp = new QNode();
    temp->value = store;
    temp->next = NULL;

    if (front == NULL) 
    {
        front = temp;
        rear = temp;
    } 
    else 
    {
        rear->next = temp;
        rear = temp;
    }
}

int DeQueue() {
    if (front == NULL) 
    {
        return 0;
    } 
    else 
    {
        QNode* curr = front;
        int val = front->value;
        front = front->next;
        delete curr;
        if (front == NULL) 
        {
            rear = NULL;
        }
        return val;
    }
}

Node* head = NULL;
int nextId = 1;
BorrowedBy* start = NULL;

void addBook(string title, string author) 
{
    Book* newbook = new Book();
    newbook->id = nextId++;
    newbook->title = title;
    newbook->author = author;
    newbook->isBorrowed = false;

    Node* newNode = new Node();
    newNode->book = newbook;
    newNode->next = NULL;

    if (head == NULL) 
    {
        head = newNode;
    } 
    else 
    {
        Node* curr = head;
        while (curr->next != NULL) 
        {
            curr = curr->next;
        }
        curr->next = newNode;
    }
    cout << "Book added successfully.\n";
}

void Borrow(int ID) 
{
    BorrowedBy* ptr = new BorrowedBy();
    ptr->bookId = ID;
    cout << "Enter Name Of The Person Who Wants To Borrow: ";
    cin.ignore();
    getline(cin, ptr->Name);
    cout << "Enter Date: ";
    getline(cin, ptr->date);
    ptr->next = NULL;
    if (start == NULL) 
    {
        start = ptr;
    } else 
    {
        BorrowedBy* curr = start;
        while (curr->next != NULL) 
        {
            curr = curr->next;
        }
        curr->next = ptr;
    }
}

int counter = 0;

void borrowBook(int id) 
{
    Node* curr = head;
    while (curr != NULL) 
    {
        if (curr->book->id == id) {
            if (!curr->book->isBorrowed) 
            {
                curr->book->isBorrowed = true;
                Borrow(id);
                cout << "Book borrowed successfully." << endl;
                return;
            } 
            else 
            {
                cout << "Book is currently borrowed." << endl;  // adding to the waitlist.
                counter++;
                EnQueue(id);
                return;
            }
        }
        curr = curr->next;
    }
    cout << "Book not found.\n";
}

void removeBorrow(int ID) 
{
    BorrowedBy* curr = start;
    BorrowedBy* prev = NULL;
    while (curr != NULL) 
    {
        if (curr->bookId == ID) 
        {
            if (prev == NULL) 
            {
                start = curr->next;
            } 
            else 
            {
                prev->next = curr->next;
            }
            delete curr;
            cout << "Book Returned By The Borrower.\n";
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

void returnBook(int id) 
{
    Node* curr = head;
    while (curr != NULL) 
    {
        if (curr->book->id == id && curr->book->isBorrowed) 
        {
            curr->book->isBorrowed = false;
            removeBorrow(id);
            cout << "Book returned successfully.\n";
            if (front != NULL) 
            {
                for (int i = 0; i < counter; i++) 
                {
                    int ID = DeQueue();
                    if (ID == id) 
                    {
                        borrowBook(ID);
                    } 
                    else 
                    {
                        EnQueue(ID);
                    }
                }
            }
            return;
        }
        curr = curr->next;
    }
    cout << "Book not found.\n";
}

Book* searchBookByTitle(string title) 
{
    Node* curr = head;
    while (curr != NULL) 
    {
        if (curr->book->title == title) 
        {
            return curr->book;
        }
        curr = curr->next;
    }
    return NULL;
}

void searchBookByAuthor(string author) 
{
    Node* curr = head;
    bool found = false;
    while (curr != NULL) 
    {
        if (curr->book->author == author) 
        {
            Book* book = curr->book;
            cout << "Book found: ID: " << book->id << ", Title: " << book->title
                 << ", Borrowed: " << (book->isBorrowed ? "Yes" : "No") << endl;
            found = true;
        }
        curr = curr->next;
    }
    if (!found) 
    {
        cout << "Books by this author not found.\n";
    }
}

void displayBooks() 
{
    Node* curr = head;
    if (head == NULL) 
    {
        cout << "Library has no books" << endl;
    }
    while (curr != NULL) 
    {
        cout << "Book Details:\n"
             << "ID: " << curr->book->id << "\n"
             << "Title: " << curr->book->title << "\n"
             << "Author: " << curr->book->author << "\n"
             << "Is it borrowed?: " << (curr->book->isBorrowed ? "Yes" : "No") << "\n"
             << endl;
        curr = curr->next;
    }
}

int count = 0;

void removeBook(int id) 
{
    Node* curr = head;
    Node* prev = NULL;

    while (curr != NULL) 
    {
        if (curr->book->id == id) 
        {
            if (prev == NULL) 
            {
                head = curr->next;
            } 
            else 
            {
                prev->next = curr->next;
            }
            delete curr->book;
            delete curr;
            removeBorrow(id);
            cout << "Book removed successfully.\n";
            count++;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    cout << "Book not found.\n";
}

void viewBorrowedBooks() 
{
    Node* curr = head;
    bool found = false;

    while (curr != NULL) 
    {
        if (curr->book->isBorrowed) 
        {
            cout << "Borrowed Book Details:\n"
                 << "ID: " << curr->book->id << "\n"
                 << "Title: " << curr->book->title << "\n"
                 << "Author: " << curr->book->author << "\n"
                 << endl;
            found = true;
        }
        curr = curr->next;
    }

    if (!found) 
    {
        cout << "No borrowed books found.\n";
    }
}

void totalbooks() 
{
    if (nextId == 1) 
    {
        cout << "Library has no books." << endl;
    } 
    else 
    {
        cout << "Total number of books: " << (nextId - count - 1) << endl;
    }
}

void BorrowerDetails(int ID) 
{
    BorrowedBy* curr = start;
    while (curr != NULL) 
    {
        if (curr->bookId == ID) 
        {
            cout << "Book ID: " << curr->bookId << "\n"
                 << "Borrowed By: " << curr->Name << "\n"
                 << "Date Of Issue: " << curr->date << endl;
            return;
        }
        curr = curr->next;
    }
    cout << "No book issued of this ID." << endl;
}

int main() 
{
    int option;
    cout << "\n\n**** Welcome To Library Management System ****\n\n" << endl;
    do {
        cout << "**** Library Management System ****\n"
             << "Press 1 to Add Book\n"
             << "Press 2 to Borrow Book\n"
             << "Press 3 to Return Book\n"
             << "Press 4 to Search Book by Title\n"
             << "Press 5 to Search Book by Author\n"
             << "Press 6 to Display All Books\n"
             << "Press 7 to Remove a Book\n"
             << "Press 8 to View Borrowed Books\n"
             << "Press 9 to View Total Number of Books\n"
             << "Press 10 to Check Who Has Borrowed the Book\n"
             << "Press 11 to Exit\n"
             << "Select any option: " << endl;
        cin >> option;

        switch (option) 
        {
            case 1: 
            {
                string title, author;
                cout << "Enter book title: ";
                cin.ignore();
                getline(cin, title);
                cout << "Enter book author: ";
                getline(cin, author);
                addBook(title, author);
                break;
            }
            case 2: 
            {
                int ID;
                cout << "Enter book ID to borrow: ";
                cin >> ID;
                borrowBook(ID);
                break;
            }
            case 3: 
            {
                int id;
                cout << "Enter book ID to return: ";
                cin >> id;
                returnBook(id);
                break;
            }
            case 4: 
            {
                string title;
                cout << "Enter book title to search: ";
                cin.ignore();
                getline(cin, title);
                Book* book = searchBookByTitle(title);
                if (book) 
                {
                    cout << "Book found: ID: " << book->id << ", Author: " << book->author
                         << ", Borrowed: " << (book->isBorrowed ? "Yes" : "No") << endl;
                } 
                else 
                {
                    cout << "Book not found.\n";
                }
                break;
            }
            case 5: 
            {
                string author;
                cout << "Enter book author to search: ";
                cin.ignore();
                getline(cin, author);
                if (head == NULL) 
                {
                    cout << "No record.\n";
                } 
                else 
                {
                    searchBookByAuthor(author);
                }
                break;
            }
            case 6: 
            {
                displayBooks();
                break;
            }
            case 7: 
            {
                int id;
                cout << "Enter book ID to remove: ";
                cin >> id;
                if (head == NULL) 
                {
                    cout << "Library has no books." << endl;
                } 
                else 
                {
                    removeBook(id);
                }
                break;
            }
            case 8: 
            {
                viewBorrowedBooks();
                break;
            }
            case 9: 
            {
                totalbooks();
                break;
            }
            case 10: 
            {
                int ID = 0;
                cout << "Enter book ID: ";
                cin >> ID;
                BorrowerDetails(ID);
                break;
            }
            case 11: 
            {
                cout << "Thanks for working\n" << "RATE MY WORK OUT OF 5:\n";
                int rating;
                cin >> rating;
                cout << "Ratings: " << rating;
                break;
            }
            default:
                cout << "Invalid entry, try again.\n";
                break;
        }
    } while (option != 11);

    return 0;
}
