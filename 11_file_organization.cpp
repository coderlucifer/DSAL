#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Record {
    int    roll;
    char   name[30];
    int    div;
    char   addr[50];
};

// 1) Truncate file (build fresh database)
void buildMaster() {
    ofstream f("StudentDB.dat", ios::binary | ios::trunc);
}

// 2) Append a new record
void insertRecord() {
    Record r = {};               // zero‐init everything
    cout << "Roll: ";    cin  >> r.roll;
    cout << "Name: ";    cin.ignore();  cin.getline(r.name,30);
    cout << "Div: ";     cin  >> r.div;
    cout << "Addr: ";    cin.ignore();  cin.getline(r.addr,50);

    ofstream f("StudentDB.dat", ios::binary | ios::app);
    f.write((char*)&r, sizeof(r));
}

// 3) List all records
void listRecords() {
    Record r;
    ifstream f("StudentDB.dat", ios::binary);
    while (f.read((char*)&r, sizeof(r))) {
        cout << r.roll << "\t" << r.name
             << "\t" << r.div << "\t" << r.addr << "\n";
    }
}

// 4) Search by roll no.
void searchRecord() {
    int key;  cout << "Roll to search: ";  cin >> key;
    Record r;
    ifstream f("StudentDB.dat", ios::binary);
    while (f.read((char*)&r, sizeof(r))) {
        if (r.roll == key) {
            cout << "Found: " << r.roll << "\t" << r.name
                 << "\t" << r.div << "\t" << r.addr << "\n";
            return;
        }
    }
    cout << "Not found\n";
}

// 5) Delete by roll no.
void deleteRecord() {
    int key;  cout << "Roll to delete: ";  cin >> key;
    Record r;
    ifstream fin("StudentDB.dat", ios::binary);
    ofstream fout("Temp.dat", ios::binary);
    while (fin.read((char*)&r, sizeof(r))) {
        if (r.roll != key) fout.write((char*)&r, sizeof(r));
    }
    fin.close(); fout.close();
    remove("StudentDB.dat");
    rename("Temp.dat", "StudentDB.dat");
}

// 6) Edit by roll no.
void editRecord() {
    int key;  cout << "Roll to edit: ";  cin >> key;
    fstream f("StudentDB.dat", ios::binary|ios::in|ios::out);
    Record r;
    while (f.read((char*)&r, sizeof(r))) {
        if (r.roll == key) {
            cout << "New Name: ";    cin.ignore();  cin.getline(r.name,30);
            cout << "New Div: ";     cin  >> r.div;
            cout << "New Addr: ";    cin.ignore();  cin.getline(r.addr,50);
            f.seekp(-static_cast<int>(sizeof(r)), ios::cur);
            f.write((char*)&r, sizeof(r));
            break;
        }
    }
}

int main() {
    int choice;
    do {
        cout << "\n1=Build 2=Insert 3=List 4=Search 5=Delete 6=Edit 7=Quit\n";
        cout << "Choice: ";  cin >> choice;

        switch (choice) {
            case 1: buildMaster();    break;  // clear the file
            case 2: insertRecord();   break;
            case 3: listRecords();    break;
            case 4: searchRecord();   break;
            case 5: deleteRecord();   break;
            case 6: editRecord();     break;
        }
    } while (choice != 7);
    return 0;
}
