#include <iostream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;

struct Record {
    int    roll;
    char   name[30];
    char    div;
    char   addr[50];
};

const char* DB_FILE = "StudentDB.dat";

// 1) Truncate file (build fresh database)
void buildMaster() {
    ofstream f(DB_FILE, ios::binary | ios::trunc);
    if (f)
        cout << "Database has been initialized (cleared).\n";
    else
        cout << "Error: Could not initialize the database.\n";
}

// 2) Append a new record
void insertRecord() {
    Record r = {};
    cout << "Roll: ";    cin >> r.roll;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Name: ";    cin.getline(r.name, 30);
    cout << "Div: ";     cin >> r.div;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Addr: ";    cin.getline(r.addr, 50);

    ofstream f(DB_FILE, ios::binary | ios::app);
    if (f) {
        f.write((char*)&r, sizeof(r));
        cout << "Record inserted successfully.\n";
    } else {
        cout << "Error: Could not write to database.\n";
    }
}

// 3) List all records
void listRecords() {
    Record r;
    ifstream f(DB_FILE, ios::binary);
    if (!f) {
        cout << "Error: Could not open database.\n";
        return;
    }

    cout << "\n--- All Records ---\n";
    bool found = false;
    while (f.read((char*)&r, sizeof(r))) {
        cout << r.roll << "\t" << r.name
             << "\t" << r.div << "\t" << r.addr << "\n";
        found = true;
    }
    if (!found)
        cout << "No records found.\n";
}

// 4) Search by roll no.
void searchRecord() {
    int key;
    cout << "Roll to search: ";
    cin >> key;

    Record r;
    ifstream f(DB_FILE, ios::binary);
    if (!f) {
        cout << "Error: Could not open database.\n";
        return;
    }

    while (f.read((char*)&r, sizeof(r))) {
        if (r.roll == key) {
            cout << "Found: " << r.roll << "\t" << r.name
                 << "\t" << r.div << "\t" << r.addr << "\n";
            return;
        }
    }
    cout << "Record not found.\n";
}

// 5) Delete by roll no.
void deleteRecord() {
    int key;
    cout << "Roll to delete: ";
    cin >> key;

    Record r;
    ifstream fin(DB_FILE, ios::binary);
    ofstream fout("Temp.dat", ios::binary);
    bool deleted = false;

    if (!fin || !fout) {
        cout << "Error opening files.\n";
        return;
    }

    while (fin.read((char*)&r, sizeof(r))) {
        if (r.roll == key) {
            deleted = true;
            continue; // skip writing the matching record
        }
        fout.write((char*)&r, sizeof(r));
    }

    fin.close(); fout.close();
    remove(DB_FILE);
    rename("Temp.dat", DB_FILE);

    if (deleted)
        cout << "Record deleted.\n";
    else
        cout << "Record not found.\n";
}

// 6) Edit by roll no.
void editRecord() {
    int key;
    cout << "Roll to edit: ";
    cin >> key;

    fstream f(DB_FILE, ios::binary | ios::in | ios::out);
    if (!f) {
        cout << "Error: Could not open database.\n";
        return;
    }

    Record r;
    while (f.read((char*)&r, sizeof(r))) {
        if (r.roll == key) {
            cout << "New Name: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.getline(r.name, 30);
            cout << "New Div: ";
            cin >> r.div;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "New Addr: ";
            cin.getline(r.addr, 50);

            f.seekp(-static_cast<int>(sizeof(r)), ios::cur);
            f.write((char*)&r, sizeof(r));
            cout << "Record updated.\n";
            return;
        }
    }
    cout << "Record not found.\n";
}

// --- Main Program ---
int main() {
    int choice;
    do {
        cout << "\n1=Build  2=Insert  3=List  4=Search  5=Delete  6=Edit  7=Quit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: buildMaster();   break;
            case 2: insertRecord();  break;
            case 3: listRecords();   break;
            case 4: searchRecord();  break;
            case 5: deleteRecord();  break;
            case 6: editRecord();    break;
            case 7: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 7);

    return 0;
}
