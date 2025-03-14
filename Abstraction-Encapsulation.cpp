#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Employee {
private:
    int ID;
    string name;

public:

    Employee(int id, string empName) : ID(id), name(empName) {}

    virtual double salary() = 0;
    virtual void displayInfo() = 0;

    int getID() { return ID; }
    string getName() { return name; }
    
    virtual ~Employee() {}
};

class FullTimeEmployee : public Employee {
private:
    double fixedSalary;
public:
    FullTimeEmployee(int id, string name, double salary) 
        : Employee(id, name), fixedSalary(salary) {}

    double salary() override {
        return fixedSalary;
    }

    void displayInfo() override {
        cout << "Employee: " << getName() << " (ID: " << getID() << ")\n";
        cout << "Fixed Monthly Salary: $" << fixedSalary << "\n\n";
    }
};

class PartTimeEmployee : public Employee {
private:
    double hourlyWage;
    int hoursWorked;
public:
    PartTimeEmployee(int id, string name, double wage, int hours) 
        : Employee(id, name), hourlyWage(wage), hoursWorked(hours) {}

    double salary() override {
        return hourlyWage * hoursWorked;
    }

    void displayInfo() override {
        cout << "Employee: " << getName() << " (ID: " << getID() << ")\n";
        cout << "Hourly Wage: $" << hourlyWage << "\n";
        cout << "Hours Worked: " << hoursWorked << "\n";
        cout << "Total Salary: $" << salary() << "\n\n";
    }
};

class ContractualEmployee : public Employee {
private:
    double paymentPerProject;
    int projectsCompleted;
public:
    ContractualEmployee(int id, string name, double payment, int projects) 
        : Employee(id, name), paymentPerProject(payment), projectsCompleted(projects) {}

    double salary() override {
        return paymentPerProject * projectsCompleted;
    }

    void displayInfo() override {
        cout << "Employee: " << getName() << " (ID: " << getID() << ")\n";
        cout << "Contract Payment Per Project: $" << paymentPerProject << "\n";
        cout << "Projects Completed: " << projectsCompleted << "\n";
        cout << "Total Salary: $" << salary() << "\n\n";
    }
};

vector<Employee*> employees;

bool isDuplicateID(int id) {
    for (const auto& emp : employees) {
        if (emp->getID() == id) return true;
    }
    return false;
}

bool isValidInteger(const string& input) {
    if (input.empty()) return false;
    for (char c : input) {
        if (!isdigit(c)) return false;
    }
    return true;
}

bool isValidDouble(const string& input) {
    if (input.empty()) return false;
    bool decimalPoint = false;
    for (char c : input) {
        if (!isdigit(c)) {
            if (c == '.' && !decimalPoint) {
                decimalPoint = true;
            } else {
                return false;
            }
        }
    }
    return true;
}

bool isValidName(const string& input) {
    if (input.empty()) return false;
    for (char c : input) {
        if (isdigit(c)) return false;
    }
    return true;
}

int getValidInt(string prompt, int minValue, int maxValue) {
    string input;
    int number;

    cout << prompt;
    getline(cin, input);
    while (!isValidInteger(input) || (number = stoi(input), number < minValue || number > maxValue)) {
        cout << "Invalid input! Enter a number between " << minValue << " and " << maxValue << ".\n";
        cout << prompt;
        getline(cin, input);
    }
    return number;
}

double getValidDouble(string prompt, double minValue) {
    string input;
    double number;

    cout << prompt;
    getline(cin, input);
    while (!isValidDouble(input) || (number = stod(input), number < minValue)) {
        cout << "Invalid input! Enter a number greater than " << minValue << ".\n";
        cout << prompt;
        getline(cin, input);
    }
    return number;
}

string getValidName(string prompt) {
    string name;
    cout << prompt;
    getline(cin, name);
    while (!isValidName(name)) {
        cout << "Invalid input! Name should not contain numbers.\n";
        cout << prompt;
        getline(cin, name);
    }
    return name;
}

void addEmployee(int type) {
    int id;
    do {
        id = getValidInt("Enter Employee ID: ", 1, 99999);
        if (isDuplicateID(id)) {
            cout << "Error: Employee ID already exists! Please enter a unique ID.\n";
        }
    } while (isDuplicateID(id));

    string name = getValidName("Enter Employee Name: ");

    if (type == 1) {
        double salary = getValidDouble("Enter Fixed Salary: $", 0);
        employees.push_back(new FullTimeEmployee(id, name, salary));
    } 
    else if (type == 2) {
        double wage = getValidDouble("Enter Hourly Wage: $", 0);
        int hours = getValidInt("Enter Hours Worked: ", 0, 1000);
        employees.push_back(new PartTimeEmployee(id, name, wage, hours));
    } 
    else if (type == 3) {
        double payment = getValidDouble("Enter Payment Per Project: $", 0);
        int projects = getValidInt("Enter Projects Completed: ", 0, 1000);
        employees.push_back(new ContractualEmployee(id, name, payment, projects));
    }
}

void displayPayrollReport() {
    if (employees.empty()) {
        cout << "No employees in the payroll system.\n";
        return;
    }
    
    cout << "\nPayroll Report:\n";
    for (const auto& emp : employees) {
        emp->displayInfo();
    }
}

int main() {
    int choice;

    do {
        cout << "\nMenu:\n";
        cout << "1 - Full-time Employee\n";
        cout << "2 - Part-time Employee\n";
        cout << "3 - Contractual Employee\n";
        cout << "4 - Display Payroll Report\n";
        cout << "5 - Exit\n";
        
        choice = getValidInt("Enter choice: ", 1, 5);

        switch (choice) {
            case 1: case 2: case 3: addEmployee(choice); break;
            case 4: displayPayrollReport(); break;
            case 5: cout << "Exiting...\n"; break;
        }
    } while (choice != 5);

    for (auto emp : employees) delete emp;

    return 0;
} 


