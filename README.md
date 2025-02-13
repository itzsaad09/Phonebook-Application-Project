# Phonebook Application

# Overview
This Phonebook Application is a console-based program written in C++ that allows users to manage their contacts. Users can add, delete, update, search, and display contacts. The application uses a binary search tree (BST) to store contacts, ensuring efficient searching and sorting.

# Features
Add Contact: Users can add a new contact with details such as first name, last name, phone number, email, gender, and relation.
Delete Contact: Users can delete a contact by searching for it using either the first name or phone number.
Update Contact: Users can update the details of an existing contact.
Search Contacts: Users can search for contacts by first name or phone number.
Display All Contacts: Users can view all contacts stored in the phonebook.
Persistent Storage: Contacts are saved to a file (Contacts.txt) and loaded when the application starts, allowing data persistence between sessions.

# Requirements
C++ compiler (e.g., g++, MSVC)
Windows operating system (due to the use of Windows-specific headers like <windows.h> and <conio.h>)

# How to Compile and Run
1. Clone the Repository: If the code is in a repository, clone it to your local machine.
2. Open a Terminal: Navigate to the directory where the code is located.
3. Compile the Code: Use a C++ compiler to compile the code.

        g++ -o phonebook phonebook.cpp
4. Run the Application: Execute the compiled program:

       ./phonebook

# Code Structure
  # Classes:
  1. contactNode: Represents a single contact with attributes like ID, phone number, name, email, gender, and relation.
  2. tree: Manages the binary search tree operations, including insertion, deletion, searching, and file operations.
  # Functions:
  1. insert_contact(): Prompts the user to enter contact details and inserts a new contact into the tree.
  2. delete_contact(): Deletes a contact based on user input.
  3. update_contact(): Updates the details of an existing contact.
  4. search_contacts_by_fname(): Searches for contacts by first name.
  5. search_contacts_by_phone(): Searches for contacts by phone number.
  6. display_all_contacts(): Displays all contacts in the phonebook.
  7. saveToFile(): Saves contacts to a file.
  8. loadData(): Loads contacts from a file when the application starts.

# Error Handling
The application includes basic error handling for invalid inputs, such as invalid phone numbers, email formats, and gender entries.
If a contact is not found during a search or delete operation, the user is informed accordingly.
