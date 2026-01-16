#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Patient {
public:
    int patientId;
    string name;
    int age;
    string disease;
    string doctor;
    double bill;

    void display() const {
        cout << "\nPatient ID: " << patientId
             << "\nName: " << name
             << "\nAge: " << age
             << "\nDisease: " << disease
             << "\nDoctor: " << doctor
             << "\nBill Amount: ₹" << bill << endl;
    }
};

class Hospital {
private:
    vector<Patient> patients;
    const string fileName = "patients.txt";

public:
    Hospital() {
        loadFromFile();
    }

    ~Hospital() {
        saveToFile();
    }

    void addPatient() {
        Patient p;
        cout << "Enter Patient ID: ";
        cin >> p.patientId;
        cout << "Enter Name: ";
        cin >> p.name;
        cout << "Enter Age: ";
        cin >> p.age;
        cout << "Enter Disease: ";
        cin >> p.disease;
        cout << "Assigned Doctor: ";
        cin >> p.doctor;
        cout << "Initial Bill Amount: ";
        cin >> p.bill;

        patients.push_back(p);
        cout << "Patient record added successfully.\n";
    }

    void displayAllPatients() const {
        if (patients.empty()) {
            cout << "No patient records found.\n";
            return;
        }

        for (const auto &p : patients)
            p.display();
    }

    void searchPatient() const {
        int id;
        cout << "Enter Patient ID to search: ";
        cin >> id;

        for (const auto &p : patients) {
            if (p.patientId == id) {
                p.display();
                return;
            }
        }
        cout << "Patient not found.\n";
    }

    void updateBill() {
        int id;
        double amount;

        cout << "Enter Patient ID: ";
        cin >> id;
        cout << "Enter Additional Charges: ";
        cin >> amount;

        for (auto &p : patients) {
            if (p.patientId == id) {
                p.bill += amount;
                cout << "Bill updated successfully.\n";
                return;
            }
        }
        cout << "Patient not found.\n";
    }

    void saveToFile() {
        ofstream out(fileName);
        for (const auto &p : patients) {
            out << p.patientId << " "
                << p.name << " "
                << p.age << " "
                << p.disease << " "
                << p.doctor << " "
                << p.bill << endl;
        }
        out.close();
    }

    void loadFromFile() {
        ifstream in(fileName);
        if (!in) return;

        Patient p;
        while (in >> p.patientId >> p.name >> p.age >> p.disease >> p.doctor >> p.bill) {
            patients.push_back(p);
        }
        in.close();
    }
};

int main() {
    Hospital hospital;
    int choice;

    do {
        cout << "\n===== HOSPITAL MANAGEMENT SYSTEM =====\n";
        cout << "1. Add Patient\n";
        cout << "2. View All Patients\n";
        cout << "3. Search Patient\n";
        cout << "4. Update Bill\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            hospital.addPatient();
            break;
        case 2:
            hospital.displayAllPatients();
            break;
        case 3:
            hospital.searchPatient();
            break;
        case 4:
            hospital.updateBill();
            break;
        case 5:
            cout << "Exiting system...\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 5);

    return 0;
}
