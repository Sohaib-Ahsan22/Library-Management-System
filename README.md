📚 Library Management System
A console-based Library Management System written in C++, using Linked Lists and Queues to manage books, borrowers, and waiting queues efficiently.
This project demonstrates practical implementation of core data structures in a real system.

🚀 Features
📘 Book Management

Add new books

Remove existing books

View all books

Search by Title

Search by Author

View total books available

👤 Borrowing System

Borrow books by ID

Return books

Track who borrowed which book

View all borrowed books

🕒 Waiting Queue

If a book is already borrowed, additional users are added to a FIFO queue

As soon as a book is returned → next person automatically gets the book

🧠 Data Structures Used
Purpose	Data Structure	Role
Store books	Singly Linked List (Node)	Each node contains a Book record
Track borrowers	Singly Linked List (BorrowedBy)	Stores borrower name, date & book ID
Handle waitlist	Queue (QNode)	Implements FIFO for multiple users requesting same book
📂 Program Menu (User Interface)
1. Add Book
2. Borrow Book
3. Return Book
4. Search Book by Title
5. Search Book by Author
6. Display All Books
7. Remove a Book
8. View Borrowed Books
9. View Total Number of Books
10. Check Borrower Details
11. Exit

🛠️ How Each Operation Works
➕ Add Book

Auto-generates a unique book ID

Appends to the linked list of books

📥 Borrow Book

If book is free → borrow instantly

If already borrowed → user added to queue

📤 Return Book

Marks book as returned

Removes borrower record

Checks queue → assigns to next waiting user automatically

🛠️ Technologies Used

C++

Linked Lists

Queue Implementation

Console Input/Output

📸 Demo Output (Console)
**** Welcome To Library Management System ****

Enter book ID to borrow:
Book borrowed successfully.

📌 Future Enhancements

File handling (save/load records)

Admin/User roles

Due date & fine system

Category-based search

GUI-based version

👨‍💻 Author

Sohaib
BS Software Engineering
UBIT – University of Karachi

⭐ Show Support

If you like this project, consider giving it a star ⭐ on GitHub!
