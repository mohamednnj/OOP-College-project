#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Lesson {
private:
    string lessonTitle;
    string content;

public:
    Lesson(string title = "", string cont = "") : lessonTitle(title), content(cont) {}

    void displayLesson() {
        cout << "Lesson: " << lessonTitle << "\nContent: " << content << endl;
    }
};

class Course {
private:
    string courseID, title;
    vector<Lesson> lessons;

public:
    Course(string id = "", string t = "") : courseID(id), title(t) {}

    void addLesson(string title, string content) {
        lessons.push_back(Lesson(title, content));
    }

    void displayCourse() {
        cout << "Course ID: " << courseID << ", Title: " << title << endl;
        for (auto& lesson : lessons) {
            lesson.displayLesson();
        }
    }

    string getCourseID() { return courseID; }

    friend class Student;
};

class User {
protected:
    string username, password, name;

public:
    User(string u = "", string p = "", string n = "") : username(u), password(p), name(n) {}

    virtual void displayProfile() {
        cout << "Name: " << name << ", Username: " << username << endl;
    }

    bool login(string u, string p) {
        return username == u && password == p;
    }

    void setPassword(string newPass) {
        password = newPass;
    }

    string getUsername() const {
        return username;
    }

    virtual string getRole() const = 0;
};

class Student : virtual public User {
private:
    vector<Course*> enrolledCourses;

public:
    Student(string u, string p, string n) : User(u, p, n) {}

    void enroll(Course* course) {
        enrolledCourses.push_back(course);
    }

    void viewEnrolledCourses() {
        cout << "--- Enrolled Courses for " << name << " ---\n";
        for (auto c : enrolledCourses)
            c->displayCourse();
    }

    void displayProfile() override {
        cout << "[Student] ";
        User::displayProfile();
    }

    string getRole() const override {
        return "Student";
    }
};

class Instructor : virtual public User {
public:
    Instructor(string u, string p, string n) : User(u, p, n) {}

    void displayProfile() override {
        cout << "[Instructor] ";
        User::displayProfile();
    }

    string getRole() const override {
        return "Instructor";
    }

    void addCourse(vector<Course>& courses) {
        string id, title;
        cout << "Enter Course ID: ";
        cin >> id;
        cout << "Enter Course Title: ";
        cin.ignore();
        getline(cin, title);
        Course newCourse(id, title);

        int lessonCount;
        cout << "How many lessons? ";
        cin >> lessonCount;
        cin.ignore();
        for (int i = 0; i < lessonCount; i++) {
            string lt, lc;
            cout << "Enter Lesson Title: ";
            getline(cin, lt);
            cout << "Enter Lesson Content: ";
            getline(cin, lc);
            newCourse.addLesson(lt, lc);
        }

        courses.push_back(newCourse);
        cout << "Course added successfully.\n";
    }
};

class TeachingAssistant : public Student, public Instructor {
public:
    TeachingAssistant(string u, string p, string n)
        : User(u, p, n), Student(u, p, n), Instructor(u, p, n) {}

    void displayProfile() override {
        cout << "[Teaching Assistant] ";
        User::displayProfile();
    }

    string getRole() const override {
        return "TA";
    }
};

class Admin : public User {
public:
    Admin(string u, string p, string n) : User(u, p, n) {}

    void displayProfile() override {
        cout << "[Admin] ";
        User::displayProfile();
    }

    string getRole() const override {
        return "Admin";
    }

    void resetPassword(User& u, string newPass) {
        u.setPassword(newPass);
        cout << "Password changed for " << u.getUsername() << endl;
    }

    void addUser(vector<User*>& users) {
        int type;
        string u, p, n;
        cout << "Enter username: "; cin >> u;
        cout << "Enter password: "; cin >> p;
        cout << "Enter name: "; cin.ignore(); getline(cin, n);
        cout << "User type (1-Student, 2-Instructor, 3-TA, 4-Admin): "; cin >> type;

        switch (type) {
        case 1:
            users.push_back(new Student(u, p, n));
            break;
        case 2:
            users.push_back(new Instructor(u, p, n));
            break;
        case 3:
            users.push_back(new TeachingAssistant(u, p, n));
            break;
        case 4:
            users.push_back(new Admin(u, p, n));
            break;
        default:
            cout << "Invalid type.\n";
        }

        cout << "User added.\n";
    }
};

bool loginSystem(vector<User*>& users, User*& loggedInUser) {
    string u, p;
    cout << "\n--- Login Page ---\n";
    cout << "1. Login\n0. Exit\nChoice: ";
    int option;
    cin >> option;
    if (option == 0) return false;

    cout << "Username: "; cin >> u;
    cout << "Password: "; cin >> p;

    for (auto user : users) {
        if (user->login(u, p)) {
            loggedInUser = user;
            return true;
        }
    }
    cout << "Invalid credentials.\n";
    return true;
}

int main() {
    vector<User*> users;
    vector<Course> courses;

    Student* s1 = new Student("std1", "123", "Ali");
    Instructor* ins1 = new Instructor("ins1", "123", "Dr. Ahmed");
    TeachingAssistant* ta1 = new TeachingAssistant("ta1", "123", "Mona");
    Admin* admin1 = new Admin("admin", "admin", "Admin");

    users.push_back(s1);
    users.push_back(ins1);
    users.push_back(ta1);
    users.push_back(admin1);

    Course c1("C101", "OOP");
    c1.addLesson("Intro", "OOP Basics");
    c1.addLesson("Inheritance", "How inheritance works");

    Course c2("C102", "Data Structures");
    c2.addLesson("Arrays", "Introduction to arrays");
    c2.addLesson("Linked Lists", "How linked lists work");

    courses.push_back(c1);
    courses.push_back(c2);

    cout << "Welcome to the Course Management System\n";

    while (true) {
        User* loggedIn = nullptr;
        bool continueLogin = loginSystem(users, loggedIn);
        if (!continueLogin) break;

        if (loggedIn == nullptr) continue;

        cout << "Login successful as " << loggedIn->getRole() << "\n";

        if (loggedIn->getRole() == "Student") {
            Student* s = dynamic_cast<Student*>(loggedIn);
            int choice;
            do {
                cout << "\n1. View Courses\n2. Enroll in Course\n3. View Enrolled Courses\n0. Logout\nChoice: ";
                cin >> choice;
                if (choice == 1) {
                    for (auto& c : courses) c.displayCourse();
                } else if (choice == 2) {
                    string id;
                    cout << "Enter Course ID: ";
                    cin >> id;
                    for (auto& c : courses) {
                        if (c.getCourseID() == id) {
                            s->enroll(&c);
                            cout << "Enrolled successfully.\n";
                        }
                    }
                } else if (choice == 3) {
                    s->viewEnrolledCourses();
                }
            } while (choice != 0);
        } else if (loggedIn->getRole() == "Instructor") {
            Instructor* ins = dynamic_cast<Instructor*>(loggedIn);
            int choice;
            do {
                cout << "\n1. Add Course\n0. Logout\nChoice: ";
                cin >> choice;
                if (choice == 1) {
                    ins->addCourse(courses);
                }
            } while (choice != 0);
        } else if (loggedIn->getRole() == "Admin") {
            Admin* a = dynamic_cast<Admin*>(loggedIn);
            int choice;
            do {
                cout << "\n1. Add User\n2. Reset Password\n0. Logout\nChoice: ";
                cin >> choice;
                if (choice == 1) {
                    a->addUser(users);
                } else if (choice == 2) {
                    string uname;
                    cout << "Enter username to reset password: ";
                    cin >> uname;
                    for (auto u : users) {
                        if (u->getUsername() == uname) {
                            a->resetPassword(*u, "newpass123");
                        }
                    }
                }
            } while (choice != 0);
        } else {
            loggedIn->displayProfile();
        }
    }

    cout << "Exiting system.\n";

    for (auto u : users) delete u;

    return 0;
}
