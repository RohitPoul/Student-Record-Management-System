#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <conio.h>
#include <windows.h>
#include <direct.h>

using namespace std;

class Student {
private:
    string studentId;
    string name;
    int age;
    string course;
    float gpa;

public:
    Student(string id = "", string n = "", int a = 0, string c = "", float g = 0.0) 
        : studentId(id), name(n), age(a), course(c), gpa(g) {}

    string getStudentId() const { return studentId; }
    string getName() const { return name; }
    int getAge() const { return age; }
    string getCourse() const { return course; }
    float getGPA() const { return gpa; }

    void setStudentId(string id) { studentId = id; }
    void setName(string n) { name = n; }
    void setAge(int a) { age = a; }
    void setCourse(string c) { course = c; }
    void setGPA(float g) { gpa = g; }
};

class StudentManager {
private:
    vector<Student> students;
    const string filename = "students.txt";

    void clearScreen() {
        system("cls");
    }

    void displayHeader(string title) {
        clearScreen();
        cout << "\n\t\t" << string(50, '=');
        cout << "\n\t\t\t" << title;
        cout << "\n\t\t" << string(50, '=') << "\n";
    }

    bool isValidStudentId(const string& id) {
        if (id.length() != 10) return false;
        for (char c : id) {
            if (!isalnum(c)) return false;
        }
        return true;
    }

    bool isValidGPA(float gpa) {
        return gpa >= 0.0 && gpa <= 10.0;
    }

    string getCurrentDirectory() {
        char buffer[FILENAME_MAX];
        _getcwd(buffer, FILENAME_MAX);
        return string(buffer);
    }

public:
    StudentManager() {
        loadFromFile();
        cout << "\n\tFile location: " << getCurrentDirectory() << "\\" << filename << "\n";
        cout << "\tPress any key to continue...";
        _getch();
    }

    void addStudent() {
        displayHeader("Add New Student");
        
        Student student;
        string id, name, course;
        int age;
        float gpa;

        cout << "\n\tEnter Student ID (10 characters): ";
        cin >> id;
        
        if (!isValidStudentId(id)) {
            cout << "\n\tInvalid Student ID format! Press any key to continue...";
            _getch();
            return;
        }

        for (const Student& s : students) {
            if (s.getStudentId() == id) {
                cout << "\n\tStudent ID already exists! Press any key to continue...";
                _getch();
                return;
            }
        }

        cin.ignore();
        cout << "\tEnter Name: ";
        getline(cin, name);
        
        cout << "\tEnter Age: ";
        cin >> age;
        
        cin.ignore();
        cout << "\tEnter Course: ";
        getline(cin, course);
        
        cout << "\tEnter GPA (0.0-10.0): ";
        cin >> gpa;

        if (!isValidGPA(gpa)) {
            cout << "\n\tInvalid GPA! Press any key to continue...";
            _getch();
            return;
        }

        student.setStudentId(id);
        student.setName(name);
        student.setAge(age);
        student.setCourse(course);
        student.setGPA(gpa);

        students.push_back(student);
        saveToFile();

        cout << "\n\tStudent added successfully!";
        cout << "\n\tData saved to: " << getCurrentDirectory() << "\\" << filename;
        cout << "\n\tPress any key to continue...";
        _getch();
    }

    void displayStudents() {
        displayHeader("Student Records");

        if (students.empty()) {
            cout << "\n\tNo students found!";
            cout << "\n\tFile location: " << getCurrentDirectory() << "\\" << filename;
            cout << "\n\tPress any key to continue...";
            _getch();
            return;
        }

        cout << "\n\t" << left << setw(10) << "ID" 
             << setw(20) << "Name" 
             << setw(8) << "Age" 
             << setw(15) << "Course" 
             << "GPA\n";
        cout << "\t" << string(60, '-') << "\n";

        for (const Student& student : students) {
            cout << "\t" << left << setw(10) << student.getStudentId()
                 << setw(20) << student.getName()
                 << setw(8) << student.getAge()
                 << setw(15) << student.getCourse()
                 << fixed << setprecision(2) << student.getGPA() << "\n";
        }

        cout << "\n\tData loaded from: " << getCurrentDirectory() << "\\" << filename;
        cout << "\n\tPress any key to continue...";
        _getch();
    }

    void searchStudent() {
        displayHeader("Search Student");

        string searchId;
        cout << "\n\tEnter Student ID to search: ";
        cin >> searchId;

        for (const Student& student : students) {
            if (student.getStudentId() == searchId) {
                cout << "\n\tStudent Found!\n";
                cout << "\n\tID: " << student.getStudentId();
                cout << "\n\tName: " << student.getName();
                cout << "\n\tAge: " << student.getAge();
                cout << "\n\tCourse: " << student.getCourse();
                cout << "\n\tGPA: " << fixed << setprecision(2) << student.getGPA();
                cout << "\n\tData source: " << getCurrentDirectory() << "\\" << filename;
                cout << "\n\n\tPress any key to continue...";
                _getch();
                return;
            }
        }

        cout << "\n\tStudent not found! Press any key to continue...";
        _getch();
    }

    void deleteStudent() {
        displayHeader("Delete Student");

        string deleteId;
        cout << "\n\tEnter Student ID to delete: ";
        cin >> deleteId;

        for (auto it = students.begin(); it != students.end(); ++it) {
            if (it->getStudentId() == deleteId) {
                students.erase(it);
                saveToFile();
                cout << "\n\tStudent deleted successfully!";
                cout << "\n\tFile updated at: " << getCurrentDirectory() << "\\" << filename;
                cout << "\n\tPress any key to continue...";
                _getch();
                return;
            }
        }

        cout << "\n\tStudent not found! Press any key to continue...";
        _getch();
    }

    void viewFile() {
        displayHeader("View Data File");
        
        ifstream file(filename);
        if (!file) {
            cout << "\n\tFile not found at: " << getCurrentDirectory() << "\\" << filename;
            cout << "\n\tPress any key to continue...";
            _getch();
            return;
        }

        cout << "\n\tContent of " << filename << ":\n\n";
        string line;
        while (getline(file, line)) {
            cout << "\t" << line << "\n";
        }
        file.close();

        cout << "\n\tFile location: " << getCurrentDirectory() << "\\" << filename;
        cout << "\n\tPress any key to continue...";
        _getch();
    }

private:
    void saveToFile() {
        ofstream file(filename);
        for (const Student& student : students) {
            file << student.getStudentId() << ","
                 << student.getName() << ","
                 << student.getAge() << ","
                 << student.getCourse() << ","
                 << student.getGPA() << "\n";
        }
        file.close();
    }

    void loadFromFile() {
        ifstream file(filename);
        if (!file) return;

        students.clear();
        string line;
        while (getline(file, line)) {
            size_t pos = 0;
            vector<string> tokens;
            string delimiter = ",";

            while ((pos = line.find(delimiter)) != string::npos) {
                tokens.push_back(line.substr(0, pos));
                line.erase(0, pos + delimiter.length());
            }
            tokens.push_back(line);

            if (tokens.size() == 5) {
                Student student(
                    tokens[0],
                    tokens[1],
                    stoi(tokens[2]),
                    tokens[3],
                    stof(tokens[4])
                );
                students.push_back(student);
            }
        }
        file.close();
    }
};

int main() {
    StudentManager manager;
    char choice;

    while (true) {
        system("cls");
        cout << "\n\t\tSTUDENT RECORD MANAGEMENT SYSTEM\n";
        cout << "\t\t==============================\n\n";
        cout << "\t1. Add Student\n";
        cout << "\t2. Display All Students\n";
        cout << "\t3. Search Student\n";
        cout << "\t4. Delete Student\n";
        cout << "\t5. View Data File\n";
        cout << "\t6. Exit\n\n";
        cout << "\tEnter your choice (1-6): ";
        
        choice = _getch();

        switch (choice) {
            case '1':
                manager.addStudent();
                break;
            case '2':
                manager.displayStudents();
                break;
            case '3':
                manager.searchStudent();
                break;
            case '4':
                manager.deleteStudent();
                break;
            case '5':
                manager.viewFile();
                break;
            case '6':
                cout << "\n\n\tThank you for using the system!\n";
                return 0;
            default:
                cout << "\n\tInvalid choice! Press any key to continue...";
                _getch();
        }
    }

    return 0;
}