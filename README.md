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
Clone the Repository: If the code is in a repository, clone it to your local machine.
Open a Terminal: Navigate to the directory where the code is located.
Compile the Code: Use a C++ compiler to compile the code.
Run the Application: Execute the compiled program

# Code Structure
  # Classes:
      contactNode: Represents a single contact with attributes like ID, phone number, name, email, gender, and relation.
      tree: Manages the binary search tree operations, including insertion, deletion, searching, and file operations.
  # Functions:

      insert_contact(): Prompts the user to enter contact details and inserts a new contact into the tree.
      delete_contact(): Deletes a contact based on user input.
      update_contact(): Updates the details of an existing contact.
      search_contacts_by_fname(): Searches for contacts by first name.
      search_contacts_by_phone(): Searches for contacts by phone number.
      display_all_contacts(): Displays all contacts in the phonebook.
      saveToFile(): Saves contacts to a file.
      loadData(): Loads contacts from a file when the application starts.

# Error Handling
The application includes basic error handling for invalid inputs, such as invalid phone numbers, email formats, and gender entries.
If a contact is not found during a search or delete operation, the user is informed accordingly.
