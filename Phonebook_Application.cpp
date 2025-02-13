#include <iostream>
#include <sstream> 
#include <windows.h>   
#include <conio.h>   
#include <thread> 
#include <fstream> 

using namespace std;
ofstream outf; 
ifstream myFileStream; 

int nextID = 1;  
bool found = false; 

class contactNode {  
public:
    int id;
    long long int phone_number;
    char fname[20], lname[20], email[50], gender[20], relation[20];
    contactNode *left, *right;  
};

class tree {
public:
    contactNode *root;
    tree() {  
        root = NULL;
    }

    void insert_newNode(contactNode *newNode) { 
        contactNode *parent;
        contactNode *temp = root;
        newNode->left = NULL;  
        newNode->right = NULL;
        if (root == NULL) {
            root = newNode;
        } else {
            while (temp != NULL) {
                parent = temp;
                if (strcmp(newNode->fname, temp->fname) < 0) {  
                    temp = temp->left;
                } else {
                    temp = temp->right;
                }
            }
            if (strcmp(newNode->fname, parent->fname) < 0) {  
                parent->left = newNode;
            } else {
                parent->right = newNode;
            }
        }
    }

    void insert_contact() {
        bool check = 0;
        contactNode *temp, *newNode, *parent = NULL;
        temp = root;
        newNode = new contactNode(); 
        newNode->id = nextID++; 
        
        cout << "\n\t\t\t\t\t\t\t\t\tEnter First Name: ";
        cin.ignore();  
        cin.getline(newNode->fname, 20);
        capitalizeFName(newNode->fname);   
        cout << "\t\t\t\t\t\t\t\t\tEnter Last Name (Press Enter to Skip): ";
        cin.getline(newNode->lname, 20);
        capitalizeLName(newNode->lname);    
        do {
            cout << "\t\t\t\t\t\t\t\t\tEnter Phone Number: ";
            cin >> newNode->phone_number;
            check = numb_valid(newNode->phone_number);  
        } while (check != 1);
        do {
            cout << "\t\t\t\t\t\t\t\t\tEnter email address (Type # to Skip): ";
            cin >> newNode->email;
            check = mail_valid(newNode->email);
        } while (check != 1);
        do {
            cout << "\t\t\t\t\t\t\t\t\tEnter Gender (M/F) (Type # to Skip): ";
            cin >> newNode->gender;
            check = gender_valid(newNode->gender);
        } while (check != 1);
        cout << "\t\t\t\t\t\t\t\t\tEnter Relation (Type # to Skip): ";
        cin.ignore();
        cin.getline(newNode->relation, 20);
        check = relation_valid(newNode->relation);

        newNode->left = NULL;
        newNode->right = NULL;
        if (root == NULL) {
            root = newNode;
        } else {
            while (temp != NULL) {
                parent = temp;
                if (strcmp(newNode->fname, temp->fname) < 0) {
                    temp = temp->left;
                } else {
                    temp = temp->right;
                }
            }
            if (strcmp(newNode->fname, parent->fname) < 0) {
                parent->left = newNode;
            } else {
                parent->right = newNode;
            }
        }
    }

    void capitalizeFName(char fname[]) {  
        if (fname[0] != '\0') {
            fname[0] = toupper(fname[0]);  
            for (int i = 1; fname[i] != '\0'; i++) {
                fname[i] = tolower(fname[i]); 
            } 
        }
    }

    void capitalizeLName(char lname[]) {
        if (lname[0] != '\0') {
            lname[0] = toupper(lname[0]);
            for (int i = 1; lname[i] != '\0'; i++) {
                lname[i] = tolower(lname[i]);
            }
        }
    }

    int numb_valid(long long int phone_number) {  
        int count = 0; 
        while (phone_number > 0) {
            count++; 
            phone_number /= 10;
        }
        if (count == 10) {
            return 1;
        } else {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 4);
            cout << "\t\t\t\t\t\t\t\t\t\tPhone Number Invalid\n"; 
            SetConsoleTextAttribute(hConsole, 7);
            return 0;
        }
    }

    int mail_valid(char email[]) { 
        int j = 0, i = 0;
        if (email[0] == '#') {
            return 1;
        } else {
            while (email[i] != '\0') { 
                if (email[i] == '@') j++;
                i++;
            }
            if (j == 1) {
                return 1;
            } else {
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 4);
                cout << "\t\t\t\t\t\t\t\t\t\tEmail ID Invalid\n";
                SetConsoleTextAttribute(hConsole, 7);
                return 0;
            }
        }
    }

    int gender_valid(char gender[]) {  
        if (gender[0] == '#') {
            return 1;
        } else if (gender[0] == 'M' || gender[0] == 'F' || gender[0] == 'm' || gender[0] == 'f') {
            return 1;
        } else {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 4);
            cout << "\t\t\t\t\t\t\t\t\t\tEnter Valid Character For Gender\n";
            SetConsoleTextAttribute(hConsole, 7);
            return 0;
        }
    }

    int relation_valid(char relation[]) { 
        if (relation[0] == '#') {
            return 1;
        }
        return 0;
    }

    contactNode* contact_by_id(contactNode* root, int id) { 
        if (root == NULL) {
            return NULL;
        }
        contact_by_id(root->left, id);
        if (root->id == id) {
            return root;    
        }
        return contact_by_id(root->right, id);
    }
    contactNode* delete_node(contactNode* root, int id, string fname) {
        if (root == NULL) {
            return NULL;
        }
        delete_node(root->left, id, fname);
        if (fname < root->fname) {
            root->left = delete_node(root->left, id, fname);
        } else if (fname > root->fname) {
            root->right = delete_node(root->right, id, fname);
        } else { 
            if (root->left == NULL) {
                contactNode* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == NULL) {
                contactNode* temp = root->left;
                delete root;
                return temp;
            }
            contactNode* temp = minValueNode(root->right); 
            root->id = temp->id;
            strcpy(root->fname, temp->fname);  
            strcpy(root->lname, temp->lname);
            root->phone_number = temp->phone_number;
            strcpy(root->email, temp->email);
            strcpy(root->gender, temp->gender);
            strcpy(root->relation, temp->relation);

            root->right = delete_node(root->right, temp->id, temp->fname);
        }
        delete_node(root->right, id, fname);
        return root;
    }

    contactNode* minValueNode(contactNode* node) { 
        contactNode* current = node; 
        while (current && current->left != NULL) {
            current = current->left;
        }
        return current;
    }

    void delete_contact() {
        int id;
        cout << "\n\t\t\t\t\t\t\t\t\tEnter ID of the contact to delete: ";
        cin >> id;
        string fname;
        contactNode* contact = contact_by_id(root, id);
        cout << "\t\t\t\t\t\t\t\t\tFirst Name: " << contact->fname << "\n";
        fname = contact->fname;
        if (contact == NULL) {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
            SetConsoleTextAttribute(hConsole, 4);
            cout << "\n\t\t\t\t\t\t\t\t\tContact not found.\n";
            SetConsoleTextAttribute(hConsole, 7);
            return;
        }
        root = delete_node(root, id, fname);
        cout << "\n\t\t\t\t\t\t\t\t\tContact deleted successfully.";
    }

    void update_contact() {
        int id;
        cout << "\n\t\t\t\t\t\t\t\t\tEnter ID of the contact to update: ";
        cin >> id;

        contactNode* contact = contact_by_id(root, id);
        if (contact == NULL) {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
            SetConsoleTextAttribute(hConsole, 4);
            cout << "\n\t\t\t\t\t\t\t\t\tContact not found.\n";
            SetConsoleTextAttribute(hConsole, 7);
            return;
        }

        system("cls"); 
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
        SetConsoleTextAttribute(hConsole, 1);
        cout << "\n\t\t\t\t\t\t\t\t\t--------------------------";
        cout << "\n\t\t\t\t\t\t\t\t\t|Updating Contact Details|";
        cout << "\n\t\t\t\t\t\t\t\t\t--------------------------\n";
        SetConsoleTextAttribute(hConsole, 7);
        cout << "\t\t\t\t\t\t\t\t\tCurrent First Name: " << contact->fname << "\n";
        cout << "\t\t\t\t\t\t\t\t\tCurrent Last Name: " << contact->lname << "\n";
        cout << "\t\t\t\t\t\t\t\t\tCurrent Phone Number:  " << contact->phone_number << "\n";
        cout << "\t\t\t\t\t\t\t\t\tCurrent Email: " << contact->email << "\n";
        cout << "\t\t\t\t\t\t\t\t\tCurrent Gender: " << contact->gender << "\n";
        cout << "\t\t\t\t\t\t\t\t\tCurrent Relation: " << contact->relation << "\n";

        cout << "\n\t\t\t\t\t\t\t\t\tEnter New First Name (Press Enter to keep current): ";
        cin.ignore();
        char new_fname[20];
        cin.getline(new_fname, 20);
        if (strlen(new_fname) > 0) { 
            strcpy(contact->fname, new_fname);
            capitalizeFName(contact->fname);
        }

        cout << "\t\t\t\t\t\t\t\t\tEnter New Last Name (Press Enter to keep current): ";
        char new_lname[20];
        cin.getline(new_lname, 20);
        if (strlen(new_lname) > 0) {
            strcpy(contact->lname, new_lname);
            capitalizeLName(contact->lname);
        }

        long long int new_phone_number;
        cout << "\t\t\t\t\t\t\t\t\tEnter New Phone Number (Press Enter to keep current): ";
        string phone_input;
        cin.ignore();  
        getline(cin, phone_input); 
        if (!phone_input.empty()) { 
            new_phone_number = stoll(phone_input); 
            if (numb_valid(new_phone_number)) { 
                contact->phone_number = new_phone_number;
            } else { 
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
                SetConsoleTextAttribute(hConsole, 4); 
                cout << "\t\t\t\t\t\t\t\t\tInvalid phone number. Keeping current value.\n"; 
                SetConsoleTextAttribute(hConsole, 7); 
            } 
        }

        cout << "\t\t\t\t\t\t\t\t\tEnter New Email (Press Enter to keep current): ";
        char new_email[50];
        cin.getline(new_email, 50);
        if (strlen(new_email) > 0) {
            if (mail_valid(new_email)) {
                strcpy(contact->email, new_email);
            } else {
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 4);
                cout << "\t\t\t\t\t\t\t\t\tInvalid email. Keeping current value.\n";
                SetConsoleTextAttribute(hConsole, 7);
            }
        }

        cout << "\t\t\t\t\t\t\t\t\tEnter New Gender (M/F) (Press Enter to keep current): ";
        char new_gender[20];
        cin.getline(new_gender, 20);
        if (strlen(new_gender) > 0) {
            if (gender_valid(new_gender)) {
                strcpy(contact->gender, new_gender);
            } else {
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 4);
                cout << "\t\t\t\t\t\t\t\t\tInvalid gender. Keeping current value.\n";
                SetConsoleTextAttribute(hConsole, 7);
            }
        }

        cout << "\t\t\t\t\t\t\t\t\tEnter New Relation (Press Enter to keep current): ";
        char new_relation[20];
        cin.getline(new_relation, 20);
        if (strlen(new_relation) > 0) {
            strcpy(contact->relation, new_relation);
        }

        cout << "\n\t\t\t\t\t\t\t\t\tContact updated successfully.\n";
    }

    void search_contacts_by_fname() {
        string name;
        cout << "\n\t\t\t\t\t\t\t\t\tEnter First Name: ";
        cin >> name;

        found = false;
        searchbyfname(root, name, found);

        if (!found) {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 4);
            cout << "\n\t\t\t\t\t\t\t\t\tNo Match Found.\n";
            SetConsoleTextAttribute(hConsole, 7);
        }
    }

    void searchbyfname(contactNode* root, const string& name, bool& found) { 
        if (root == NULL) return;

        string fname = root->fname;
        for (int i = 0; i < fname.length(); ++i) { 
            fname[i] = toupper(fname[i]);
        }

        string searchFname = name;
        for (int i = 0; i < searchFname.length(); ++i) {
            searchFname[i] = toupper(searchFname[i]);
        }

        if (fname.length() >= searchFname.length() && 
            fname.substr(0, searchFname.length()) == searchFname) {

            //cout << "\n\t\t\t\t\t\t\t\t\tContact Details:\n";
            cout << "\n\t\t\t\t\t\t\t\t\tID: " << root->id
                << "\n\t\t\t\t\t\t\t\t\tFirst Name: " << root->fname
                << "\n\t\t\t\t\t\t\t\t\tLast Name: " << root->lname
                << "\n\t\t\t\t\t\t\t\t\tPhone Number:  " << root->phone_number
                << "\n\t\t\t\t\t\t\t\t\tEmail: " << root->email
                << "\n\t\t\t\t\t\t\t\t\tGender: " << root->gender 
                << "\n\t\t\t\t\t\t\t\t\tRelation: " << root->relation << endl;
            found = true;
        }
        searchbyfname(root->left, name, found);
        searchbyfname(root->right, name, found);
    }

    void search_contacts_by_phone() {
        string phone;
        cout << "\n\t\t\t\t\t\t\t\t\tEnter Phone Number to search:  ";
        cin >> phone;

        found = false;
        searchbynumber(root, phone, found);

        if (!found) {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 4);
            cout << "\n\t\t\t\t\t\t\t\t\tNo Match Found.\n";
            SetConsoleTextAttribute(hConsole, 7);
        }
    }

    void searchbynumber(contactNode* root, const string& phone, bool& found) {
        if (root == NULL) {
            return;
        }

        string phone_number_str = to_string(root->phone_number);

        if (phone_number_str.rfind(phone,0) == 0) {
            cout << "\n\t\t\t\t\t\t\t\t\tID: " << root->id
                 << "\n\t\t\t\t\t\t\t\t\tFirst Name: " << root->fname
                 << "\n\t\t\t\t\t\t\t\t\tLast Name: " << root->lname
                 << "\n\t\t\t\t\t\t\t\t\tPhone Number:  " << phone_number_str
                 << "\n\t\t\t\t\t\t\t\t\tEmail: " << root->email
                 << "\n\t\t\t\t\t\t\t\t\tGender: " << root->gender
                 << "\n\t\t\t\t\t\t\t\t\tRelation: " << root->relation << endl;
            found = true;
        }

        searchbynumber(root->left, phone, found);
        searchbynumber(root->right, phone, found);
    }

    void display_all_contacts(contactNode* root) {
        if (root != NULL) {
            display_all_contacts(root->left);
            cout << "\n\t\t\t\t\t\t\t\t\tID: " << root->id
                << "\n\t\t\t\t\t\t\t\t\tFirst Name: " << root->fname
                << "\n\t\t\t\t\t\t\t\t\tLast Name: " << root->lname
                << "\n\t\t\t\t\t\t\t\t\tPhone Number:  " << root->phone_number
                << "\n\t\t\t\t\t\t\t\t\tEmail: " << root->email
                << "\n\t\t\t\t\t\t\t\t\tGender: " << root->gender
                << "\n\t\t\t\t\t\t\t\t\tRelation: " << root->relation << endl;
            display_all_contacts(root->right);
        }
    }

    void file(contactNode* root) { // Save in File
        if (root != NULL) {
            file(root->left);
            outf << root->id << "," << root->fname << "," << root->lname << ","
                 << root->phone_number << "," << root->email << ","
                 << root->gender << "," << root->relation << "\n";
            file(root->right);
        }
    }

    void saveToFile() {
        outf.open("Contacts.txt", ios::trunc); 
        if (!outf.is_open()) {
            cout << "\n\t\t\t\t\t\t\t\t\tError: Could not open file for writing.\n";
            return;
        }
        file(root);
        outf.close();
    }

    void loadData() {
        string line, id, fname, lname, phone_number, email, gender, relation;
        myFileStream.open("Contacts.txt");
        if (!myFileStream.is_open()) {
            cout << "\n\t\t\t\t\t\t\t\t\tFile failed to open" << endl;
        }

        contactNode *temp, *newNode, *parent = NULL;
        temp = root;

        int maxID = 0;

        while (getline(myFileStream, line)) {
            newNode = new contactNode();
            stringstream ss(line); 
            getline(ss, id, ',');
            getline(ss, fname, ','); 
            getline(ss, lname, ',');
            getline(ss, phone_number, ',');
            getline(ss, email, ',');
            getline(ss, gender, ',');
            getline(ss, relation, ',');

            newNode->id = stoi(id); 
            maxID = max(maxID, newNode->id);

            strcpy(newNode->fname, fname.c_str()); 
            strcpy(newNode->lname, lname.c_str());
            newNode->phone_number = atoll(phone_number.c_str());
            strcpy(newNode->email, email.c_str());
            strcpy(newNode->gender, gender.c_str());
            strcpy(newNode->relation, relation.c_str());

            insert_newNode(newNode);
        }
        myFileStream.close();

        nextID = maxID + 1;
    }
};

int main() {
    tree t;
    int choice;
    char response;
    char fname[20];
    t.loadData();

    do {
        cout << "\n\n\n";
        system("cls");
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 1);
        cout << "\n\t\t\t\t\t\t\t\t\t----------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\t|Welcome to Phonebook Application|";
        cout << "\n\t\t\t\t\t\t\t\t\t----------------------------------\n";
        cout << "\n\t\t\t\t\t\t\t\t\t1. Add Contact\n";
        cout << "\t\t\t\t\t\t\t\t\t2. Delete Contact\n";
        cout << "\t\t\t\t\t\t\t\t\t3. Update Contact\n";
        cout << "\t\t\t\t\t\t\t\t\t4. Search Contact\n";
        cout << "\t\t\t\t\t\t\t\t\t5. Display All\n";
        cout << "\t\t\t\t\t\t\t\t\t6. Exit\n";
        SetConsoleTextAttribute(hConsole, 7);
        cout << "\n\t\t\t\t\t\t\t\t\tChoose an option: ";

        while (!(cin >> choice) || choice < 1 || choice > 6) { 
            if (cin.fail()) { 
                cin.clear();
                cin.ignore(1000, '\n');
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 4);
                cout << "\t\t\t\t\t\t\t\t\tInvalid input! Please enter a number between 1 and 6.\n";
                SetConsoleTextAttribute(hConsole, 7);
            } else if (choice < 1 || choice > 6) {
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 4);
                cout << "\t\t\t\t\t\t\t\t\tPlease choose a valid option (1, 2, 3, 4, 5, 6).\n";
                SetConsoleTextAttribute(hConsole, 7);
            }
            cout << "\t\t\t\t\t\t\t\t\tChoose an option: ";
        }

        switch (choice) {
            case 1:
                t.insert_contact();
                cout << "\n\t\t\t\t\t\t\t\t\tContact Saved";
                break;
            case 2:
                cout << "\n\t\t\t\t\t\t\t\t\t1. Search by First Name\n";
                cout << "\t\t\t\t\t\t\t\t\t2. Search by Phone Number\n";
                cout << "\n\t\t\t\t\t\t\t\t\tChoose an option: ";
                while (true) {
                    cin >> choice;
                    if (cin.fail()) {
                        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                        SetConsoleTextAttribute(hConsole, 4);
                        cout << "\t\t\t\t\t\t\t\t\tInvalid input. Please enter a numeric option (1 or 2).\n";
                        SetConsoleTextAttribute(hConsole, 7);
                        cin.clear();
                        cin.ignore(1000, '\n');
                    } else if (choice == 1) {
                        t.search_contacts_by_fname();
                        break;
                    } else if (choice == 2) {
                        t.search_contacts_by_phone();
                        break;
                    } else {
                        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                        SetConsoleTextAttribute(hConsole, 4);
                        cout << "\t\t\t\t\t\t\t\t\tPlease choose a valid option (1 or 2).\n";
                        SetConsoleTextAttribute(hConsole, 7);
                    }
                    cout << "\t\t\t\t\t\t\t\t\tChoose an option: ";
                }
                if (found) {
                    t.delete_contact();
                }
                break;
            case 3:
                cout << "\n\t\t\t\t\t\t\t\t\t1. Search by First Name\n";
                cout << "\t\t\t\t\t\t\t\t\t2. Search by Phone Number\n";
                cout << "\n\t\t\t\t\t\t\t\t\tChoose an option: ";
                while (true) {
                    cin >> choice;
                    if (cin.fail()) {
                        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                        SetConsoleTextAttribute(hConsole, 4);
                        cout << "\t\t\t\t\t\t\t\t\tInvalid input. Please enter a numeric option (1 or 2).\n";
                        SetConsoleTextAttribute(hConsole, 7);
                        cin.clear();
                        cin.ignore(1000, '\n'); 
                    } else if (choice == 1) {
                        t.search_contacts_by_fname();
                        break;
                    } else if (choice == 2) {
                        t.search_contacts_by_phone();
                        break;
                    } else {
                        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                        SetConsoleTextAttribute(hConsole, 4);
                        cout << "\t\t\t\t\t\t\t\t\tPlease choose a valid option (1 or 2).\n";
                        SetConsoleTextAttribute(hConsole, 7);
                    }
                    cout << "\t\t\t\t\t\t\t\t\tChoose an option: ";
                }
                if (found) {
                    t.update_contact();
                }
                break;
            case 4:
                cout << "\n\t\t\t\t\t\t\t\t\t1. Search by First Name\n";
                cout << "\t\t\t\t\t\t\t\t\t2. Search by Phone Number\n";
                cout << "\n\t\t\t\t\t\t\t\t\tChoose an option: ";
                while (true) {
                    cin >> choice;
                    if (cin.fail()) {
                        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                        SetConsoleTextAttribute(hConsole, 4);
                        cout << "\t\t\t\t\t\t\t\t\tInvalid input. Please enter a numeric option (1 or 2).\n";
                        SetConsoleTextAttribute(hConsole, 7);
                        cin.clear();
                        cin.ignore(1000, '\n'); 
                    } else if (choice == 1) {
                        t.search_contacts_by_fname();
                        break;
                    } else if (choice == 2) {
                        t.search_contacts_by_phone();
                        break;
                    } else {
                        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                        SetConsoleTextAttribute(hConsole, 4);
                        cout << "\t\t\t\t\t\t\t\t\tPlease choose a valid option (1 or 2).\n";
                        SetConsoleTextAttribute(hConsole, 7);
                    }
                    cout << "\t\t\t\t\t\t\t\t\tChoose an option: ";
                }
                break;
            case 5:
                t.display_all_contacts(t.root);
                break;
            case 6:
                response = 'N';
                break;
        }

        t.saveToFile();

        do {  //validation
            if (response == 'N' || response == 'n') {
                break;
            } else {
                cout << "\n\t\t\t\t\t\t\t\t\tDo You Want To Continue (Y/N): ";
                response = getch();
            }
            if (response == 'Y' || response == 'y') {
                break;
            } else if (response == 'N' || response == 'n') {
                break;
            } else {
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 4);
                cout << "\n\t\t\t\t\t\t\t\t\tPlease choose a valid option.\n";
                SetConsoleTextAttribute(hConsole, 7);
            }
        } while (response != 'Y' || response != 'y' || response != 'N' || response != 'n');

    } while (response == 'Y' || response == 'y');

    cout << "\n\t\t\t\t\t\t\t\t\tExiting........";
    this_thread::sleep_for(2s);                           
}