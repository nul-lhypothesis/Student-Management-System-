/*
 * ============================================================
 *   STUDENT MANAGEMENT SYSTEM
 *   Console-based | File Handling | Menu-Driven | C++
 * ============================================================
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>
#include <algorithm>

using namespace std;

// ─────────────────────────────────────────
//  Constants
// ─────────────────────────────────────────
const string DATA_FILE = "students.dat";
const string SEPARATOR = "------------------------------------------------------------";
const string THICK_SEP = "============================================================";

// ─────────────────────────────────────────
//  Student Structure
// ─────────────────────────────────────────
struct Student {
    int    id;
    string name;
    int    age;
    string course;
    float  gpa;
};

// ─────────────────────────────────────────
//  Utility Helpers
// ─────────────────────────────────────────

// Clear input buffer
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Pause until user presses Enter
void pause() {
    cout << "\n  Press Enter to continue...";
    clearInput();
}

// Convert Student to a CSV line
string serialize(const Student& s) {
    ostringstream oss;
    oss << s.id << "," << s.name << "," << s.age << ","
        << s.course << "," << fixed << setprecision(2) << s.gpa;
    return oss.str();
}

// Parse a CSV line back into a Student
bool deserialize(const string& line, Student& s) {
    istringstream iss(line);
    string token;

    try {
        if (!getline(iss, token, ',')) return false;
        s.id = stoi(token);

        if (!getline(iss, s.name, ',')) return false;

        if (!getline(iss, token, ',')) return false;
        s.age = stoi(token);

        if (!getline(iss, s.course, ',')) return false;

        if (!getline(iss, token, ',')) return false;
        s.gpa = stof(token);
    } catch (...) {
        return false;
    }
    return true;
}

// ─────────────────────────────────────────
//  File I/O
// ─────────────────────────────────────────

// Load all students from file into a vector
vector<Student> loadAll() {
    vector<Student> list;
    ifstream fin(DATA_FILE);
    if (!fin.is_open()) return list;   // file may not exist yet

    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        Student s;
        if (deserialize(line, s))
            list.push_back(s);
    }
    fin.close();
    return list;
}

// Save the entire vector back to file (overwrite)
bool saveAll(const vector<Student>& list) {
    ofstream fout(DATA_FILE, ios::trunc);
    if (!fout.is_open()) return false;

    for (const auto& s : list)
        fout << serialize(s) << "\n";

    fout.close();
    return true;
}

// Check if a student ID already exists
bool idExists(const vector<Student>& list, int id) {
    return any_of(list.begin(), list.end(),
                  [id](const Student& s){ return s.id == id; });
}

// ─────────────────────────────────────────
//  Display Helpers
// ─────────────────────────────────────────

void printHeader() {
    cout << "\n" << THICK_SEP << "\n";
    cout << "  " << left
         << setw(6)  << "ID"
         << setw(22) << "Name"
         << setw(6)  << "Age"
         << setw(20) << "Course"
         << setw(6)  << "GPA"
         << "\n";
    cout << SEPARATOR << "\n";
}

void printStudent(const Student& s) {
    cout << "  " << left
         << setw(6)  << s.id
         << setw(22) << s.name
         << setw(6)  << s.age
         << setw(20) << s.course
         << fixed << setprecision(2) << s.gpa
         << "\n";
}

void printFooter() {
    cout << THICK_SEP << "\n";
}

// ─────────────────────────────────────────
//  Core Operations
// ─────────────────────────────────────────

// 1. Add a new student
void addStudent() {
    cout << "\n" << THICK_SEP;
    cout << "\n  ADD NEW STUDENT\n";
    cout << THICK_SEP << "\n";

    vector<Student> list = loadAll();
    Student s;

    // ID
    while (true) {
        cout << "  Enter Student ID   : ";
        if (cin >> s.id) {
            if (s.id <= 0) {
                cout << "  [!] ID must be a positive integer.\n";
            } else if (idExists(list, s.id)) {
                cout << "  [!] ID " << s.id << " already exists. Choose another.\n";
            } else {
                break;
            }
        } else {
            cout << "  [!] Invalid input. Enter a number.\n";
            clearInput();
        }
    }
    clearInput();

    // Name
    cout << "  Enter Name          : ";
    getline(cin, s.name);
    if (s.name.empty()) s.name = "Unknown";

    // Age
    while (true) {
        cout << "  Enter Age           : ";
        if (cin >> s.age && s.age > 0 && s.age < 150) break;
        cout << "  [!] Invalid age. Enter a value between 1 and 149.\n";
        clearInput();
    }
    clearInput();

    // Course
    cout << "  Enter Course        : ";
    getline(cin, s.course);
    if (s.course.empty()) s.course = "N/A";

    // GPA
    while (true) {
        cout << "  Enter GPA (0.0-4.0) : ";
        if (cin >> s.gpa && s.gpa >= 0.0f && s.gpa <= 4.0f) break;
        cout << "  [!] GPA must be between 0.0 and 4.0.\n";
        clearInput();
    }
    clearInput();

    list.push_back(s);
    if (saveAll(list))
        cout << "\n  [✓] Student added successfully (ID: " << s.id << ").\n";
    else
        cout << "\n  [✗] Error: Could not write to file.\n";

    pause();
}

// 2. Display all students
void displayAll() {
    cout << "\n" << THICK_SEP;
    cout << "\n  ALL STUDENT RECORDS\n";

    vector<Student> list = loadAll();

    if (list.empty()) {
        cout << THICK_SEP << "\n";
        cout << "  No records found. Add students first.\n";
        cout << THICK_SEP << "\n";
        pause();
        return;
    }

    printHeader();
    for (const auto& s : list)
        printStudent(s);
    printFooter();

    cout << "  Total records: " << list.size() << "\n";
    pause();
}

// 3. Search / Display a student by ID
void searchStudent() {
    cout << "\n" << THICK_SEP;
    cout << "\n  SEARCH STUDENT BY ID\n";
    cout << THICK_SEP << "\n";

    int id;
    cout << "  Enter Student ID to search: ";
    if (!(cin >> id)) {
        cout << "  [!] Invalid input.\n";
        clearInput();
        pause();
        return;
    }
    clearInput();

    vector<Student> list = loadAll();
    for (const auto& s : list) {
        if (s.id == id) {
            printHeader();
            printStudent(s);
            printFooter();
            pause();
            return;
        }
    }

    cout << "  [!] No student found with ID " << id << ".\n";
    pause();
}

// 4. Update a student record
void updateStudent() {
    cout << "\n" << THICK_SEP;
    cout << "\n  UPDATE STUDENT RECORD\n";
    cout << THICK_SEP << "\n";

    int id;
    cout << "  Enter Student ID to update: ";
    if (!(cin >> id)) {
        cout << "  [!] Invalid input.\n";
        clearInput();
        pause();
        return;
    }
    clearInput();

    vector<Student> list = loadAll();
    bool found = false;

    for (auto& s : list) {
        if (s.id == id) {
            found = true;
            cout << "\n  Current record:\n";
            printHeader();
            printStudent(s);
            printFooter();

            cout << "\n  Enter new details (press Enter to keep current value):\n\n";

            // Name
            cout << "  Name [" << s.name << "]: ";
            string input;
            getline(cin, input);
            if (!input.empty()) s.name = input;

            // Age
            cout << "  Age  [" << s.age << "]: ";
            getline(cin, input);
            if (!input.empty()) {
                try {
                    int newAge = stoi(input);
                    if (newAge > 0 && newAge < 150)
                        s.age = newAge;
                    else
                        cout << "  [!] Invalid age — kept original.\n";
                } catch (...) {
                    cout << "  [!] Invalid input — kept original.\n";
                }
            }

            // Course
            cout << "  Course [" << s.course << "]: ";
            getline(cin, input);
            if (!input.empty()) s.course = input;

            // GPA
            cout << "  GPA  [" << fixed << setprecision(2) << s.gpa << "]: ";
            getline(cin, input);
            if (!input.empty()) {
                try {
                    float newGpa = stof(input);
                    if (newGpa >= 0.0f && newGpa <= 4.0f)
                        s.gpa = newGpa;
                    else
                        cout << "  [!] GPA out of range — kept original.\n";
                } catch (...) {
                    cout << "  [!] Invalid input — kept original.\n";
                }
            }

            break;
        }
    }

    if (!found) {
        cout << "  [!] No student found with ID " << id << ".\n";
        pause();
        return;
    }

    if (saveAll(list))
        cout << "\n  [✓] Record updated successfully.\n";
    else
        cout << "\n  [✗] Error: Could not write to file.\n";

    pause();
}

// 5. Delete a student record
void deleteStudent() {
    cout << "\n" << THICK_SEP;
    cout << "\n  DELETE STUDENT RECORD\n";
    cout << THICK_SEP << "\n";

    int id;
    cout << "  Enter Student ID to delete: ";
    if (!(cin >> id)) {
        cout << "  [!] Invalid input.\n";
        clearInput();
        pause();
        return;
    }
    clearInput();

    vector<Student> list = loadAll();
    auto it = find_if(list.begin(), list.end(),
                      [id](const Student& s){ return s.id == id; });

    if (it == list.end()) {
        cout << "  [!] No student found with ID " << id << ".\n";
        pause();
        return;
    }

    cout << "\n  Record to delete:\n";
    printHeader();
    printStudent(*it);
    printFooter();

    cout << "  Are you sure you want to delete this record? (y/n): ";
    char confirm;
    cin >> confirm;
    clearInput();

    if (tolower(confirm) != 'y') {
        cout << "  [!] Deletion cancelled.\n";
        pause();
        return;
    }

    list.erase(it);
    if (saveAll(list))
        cout << "  [✓] Student with ID " << id << " deleted successfully.\n";
    else
        cout << "  [✗] Error: Could not write to file.\n";

    pause();
}

// 6. Display students sorted by GPA (descending)
void displayByGPA() {
    cout << "\n" << THICK_SEP;
    cout << "\n  STUDENTS RANKED BY GPA (Highest First)\n";

    vector<Student> list = loadAll();

    if (list.empty()) {
        cout << THICK_SEP << "\n";
        cout << "  No records found.\n";
        cout << THICK_SEP << "\n";
        pause();
        return;
    }

    sort(list.begin(), list.end(),
         [](const Student& a, const Student& b){ return a.gpa > b.gpa; });

    printHeader();
    for (size_t i = 0; i < list.size(); i++) {
        cout << "  #" << (i + 1) << " ";
        printStudent(list[i]);
    }
    printFooter();
    pause();
}

// 7. Count total students
void countStudents() {
    vector<Student> list = loadAll();
    cout << "\n" << THICK_SEP << "\n";
    cout << "  Total students in record: " << list.size() << "\n";
    cout << THICK_SEP << "\n";
    pause();
}

// ─────────────────────────────────────────
//  Main Menu
// ─────────────────────────────────────────
void showMenu() {
    cout << "\n" << THICK_SEP << "\n";
    cout << "       STUDENT MANAGEMENT SYSTEM\n";
    cout << THICK_SEP << "\n";
    cout << "  1. Add Student\n";
    cout << "  2. Display All Students\n";
    cout << "  3. Search Student by ID\n";
    cout << "  4. Update Student Record\n";
    cout << "  5. Delete Student Record\n";
    cout << "  6. View Students Ranked by GPA\n";
    cout << "  7. Total Student Count\n";
    cout << "  0. Exit\n";
    cout << THICK_SEP << "\n";
    cout << "  Enter your choice: ";
}

// ─────────────────────────────────────────
//  Entry Point
// ─────────────────────────────────────────
int main() {
    int choice;

    while (true) {
        showMenu();

        if (!(cin >> choice)) {
            clearInput();
            cout << "  [!] Invalid choice. Please enter a number.\n";
            continue;
        }
        clearInput();

        switch (choice) {
            case 1: addStudent();     break;
            case 2: displayAll();     break;
            case 3: searchStudent();  break;
            case 4: updateStudent();  break;
            case 5: deleteStudent();  break;
            case 6: displayByGPA();   break;
            case 7: countStudents();  break;
            case 0:
                cout << "\n  Goodbye! All data saved to '" << DATA_FILE << "'.\n\n";
                return 0;
            default:
                cout << "  [!] Invalid choice. Select 0-7.\n";
        }
    }
}