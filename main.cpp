#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <limits>
#include <algorithm>
#include <sstream>

using namespace std;

class PatientRecordManager {

public:
    struct PatientRecord {
        string name;
        string address;
        int age;
        char gender;
        string diseaseDescription;
        int specialistRoomNumber;
        string service;
    };

private:
    vector<PatientRecord> records;

public:
    void addNewPatient(string name, string address, int age, char gender, string diseaseDescription, int specialistRoomNumber, string service) {
        PatientRecord record = { name, address, age, gender, diseaseDescription, specialistRoomNumber, service };
        records.push_back(record);
    }

    const vector<PatientRecord>& getRecords() const {
        return records;
    }

    void searchOrEditPatientRecord(int recordNumber) {
        if (recordNumber >= 1 && recordNumber <= records.size()) {
            PatientRecord& record = records[recordNumber - 1];
            cout << "Record found." << endl << "Enter new name: ";
            string newName;
            cin.ignore();
            getline(cin, newName);
            record.name = newName;
        }
        else {
            cout << "Record not found." << endl;
        }
    }

    void searchOrEditPatientRecord(string fullName) {
        for (auto& record : records) {
            if (record.name == fullName) {
                cout << "Record found." << endl;
                cout << "Enter new name: ";
                string newName;
                cin.ignore();
                getline(cin, newName);
                record.name = newName;
                return;
            }
        }
        cout << "Record not found." << endl;
    }

    void listPatientRecords(string choice) {
        for (const auto& record : records) {
            cout << "Name: " << record.name << ", Address: " << record.address
                << ", Age: " << record.age << ", Gender: " << record.gender
                << ", Disease: " << record.diseaseDescription
                << ", Room: " << record.specialistRoomNumber
                << ", Service: " << record.service << endl;
        }
    }

    void deletePatientRecord(int recordNumber) {
        if (recordNumber >= 1 && recordNumber <= records.size()) {
            records.erase(records.begin() + (recordNumber - 1));
            cout << "Record deleted." << endl;
        }
        else {
            cout << "Record not found." << endl;
        }
    }
};

class FinancialRecordManager {
private:
    struct FinancialRecord {
        double totalCharge;
        double totalDeposited;
        double totalMoneyToReturn; // Remove initialization here
    };

    unordered_map<int, FinancialRecord> records;

public:
    void addFinancialRecord(int recordNumber, double totalCharge, double totalDeposited) {
        // Calculate totalMoneyToReturn
        double totalMoneyToReturn = totalCharge - totalDeposited;

        // Add the record to the map
        records[recordNumber] = { totalCharge, totalDeposited, totalMoneyToReturn };
    }

    void editFinancialRecord(int recordNumber, double totalCharge, double totalDeposited) {
        if (records.find(recordNumber) != records.end()) {
            // Calculate totalMoneyToReturn
            double totalMoneyToReturn = totalCharge - totalDeposited;

            // Update the record in the map
            records[recordNumber] = { totalCharge, totalDeposited, totalMoneyToReturn };
        }
        else {
            cout << "Financial Record not found for Record Number: " << recordNumber << endl;
        }
    }

    void displayFinancialRecords(int recordNumber) {
        auto it = records.find(recordNumber);
        if (it != records.end()) {
            cout << "Financial Records for Record Number: " << recordNumber << endl;
            cout << "Total Charge: " << it->second.totalCharge << endl;
            cout << "Total Deposited: " << it->second.totalDeposited << endl;
            cout << "Total Money to Return: " << it->second.totalMoneyToReturn << endl;
        }
        else {
            cout << "Financial Records not found for Record Number: " << recordNumber << endl;
        }
    }
};
class TreatmentManager {
private:
    unordered_map<int, string> treatments;

public:
    void addTreatment(int recordNumber, string treatmentDescription) {
        treatments[recordNumber] = treatmentDescription;
    }

    void displayTreatment(int recordNumber) {
        auto it = treatments.find(recordNumber);
        if (it != treatments.end()) {
            cout << "Treatment for Record Number: " << recordNumber << ": " << it->second << endl;
        }
        else {
            cout << "Treatment not found for Record Number: " << recordNumber << endl;
        }
    }

    void editTreatment(int recordNumber, string newTreatmentDescription) {
        if (treatments.find(recordNumber) != treatments.end()) {
            treatments[recordNumber] = newTreatmentDescription;
            cout << "Treatment updated." << endl;
        }
        else {
            cout << "Treatment not found for Record Number: " << recordNumber << endl;
        }
    }

    void deleteTreatment(int recordNumber) {
        if (treatments.erase(recordNumber)) {
            cout << "Treatment deleted." << endl;
        }
        else {
            cout << "Treatment not found for Record Number: " << recordNumber << endl;
        }
    }
};

class MedicineManager {
private:
    unordered_map<int, vector<string>> medicineLists;

public:
    void addMedicine(int recordNumber, string medicine) {
        medicineLists[recordNumber].push_back(medicine);
    }

    void displayMedicine(int recordNumber) {
        auto it = medicineLists.find(recordNumber);
        if (it != medicineLists.end()) {
            cout << "Medicines for Record Number: " << recordNumber << ": ";
            for (const auto& medicine : it->second) {
                cout << medicine << ", ";
            }
            cout << endl;
        }
        else {
            cout << "Medicines not found for Record Number: " << recordNumber << endl;
        }
    }

    void deleteMedicine(int recordNumber, string medicine) {
        auto it = medicineLists.find(recordNumber);
        if (it != medicineLists.end()) {
            auto& medicines = it->second;
            auto pos = find(medicines.begin(), medicines.end(), medicine);
            if (pos != medicines.end()) {
                medicines.erase(pos);
                cout << "Medicine deleted." << endl;
            }
            else {
                cout << "Medicine not found." << endl;
            }
        }
        else {
            cout << "Medicines not found for Record Number: " << recordNumber << endl;
        }
    }
};

class FileHandler {
public:
    struct PatientRecord {
        string name;
        string address;
        int age;
        char gender;
        string diseaseDescription;
        int specialistRoomNumber;
        string service;
    };

    void saveToFile(const vector<PatientRecordManager::PatientRecord>& patientRecords) {
        ofstream outFile("HospitalData.txt");
        if (outFile.is_open()) {
            for (const auto& record : patientRecords) {
                outFile << record.name << '\t'
                    << record.address << '\t'
                    << record.age << '\t'
                    << record.gender << '\t'
                    << record.diseaseDescription << '\t'
                    << record.specialistRoomNumber << '\t'
                    << record.service << endl;
            }
            outFile.close();
            cout << "Patient records saved to file." << endl;
        }
        else {
            cout << "Unable to open file for saving patient records." << endl;
        }
    }

    vector<PatientRecord> readFromFile() {
        vector<PatientRecord> patientRecords;
        ifstream inFile("HospitalData.txt");
        if (inFile.is_open()) {
            cout << "File opened successfully." << endl;
            string line;
            while (getline(inFile, line)) {
                cout << "Reading line: " << line << endl;
                istringstream iss(line);
                PatientRecord record;
                if (iss >> record.name >> record.address >> record.age >> record.gender
                    >> record.diseaseDescription >> record.specialistRoomNumber >> record.service) {
                    patientRecords.push_back(record);
                }

            }
            inFile.close();
            cout << "Finished reading file." << endl;
        }
        else {
            cout << "Unable to open file for reading patient records." << endl;
        }
        return patientRecords;
    }
};
class Menu {
public:
    void displayMainMenu() {
        cout << "\t\t\t\t*************Hospital Management System************" << endl << endl;
        cout << "1.  Add New Patient Record" << endl;
        cout << "2.  Search/Edit Patient Record" << endl;
        cout << "3.  Display the List Patient Records" << endl;
        cout << "4.  Delete a Patient Record" << endl;
        cout << "5.  Add/Edit Financial Records of patients" << endl;
        cout << "6.  Display Financial Records of patients" << endl;
        cout << "7.  Add Treatment details for patient" << endl;
        cout << "8.  Display Treatment details of a patient" << endl;
        cout << "9.  Edit Treatment details of a patient" << endl;
        cout << "10. Delete Treatment details of a patient" << endl;
        cout << "11. Add Medicines prescribed to patient" << endl;
        cout << "12. Display the list of medicines prescribed to a patient" << endl;
        cout << "13. Delete a particular medicine for a patient" << endl;
        cout << "14. Save Patient Records to file" << endl;
        cout << "15. Read Patient Records from file" << endl;
        cout << "0.  Exit" << endl;
    }

    int getChoice() {
        int choice;
        cout << endl << "Enter your choice: ";
        cin >> choice;
        while (cin.fail() || choice < 0 || choice > 15) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice, please try again: ";
            cin >> choice;
        }
        return choice;
    }
};

int main() {
    PatientRecordManager prm;
    FinancialRecordManager frm;
    TreatmentManager tm;
    MedicineManager mm;
    FileHandler fileHandler;
    Menu menu;

    while (true) {
        menu.displayMainMenu();
        int choice = menu.getChoice();

        switch (choice) {
        case 1: {
            string name, address, diseaseDescription, service;
            int age, specialistRoomNumber;
            char gender;

            cout << "Enter name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter address: ";
            getline(cin, address);
            cout << "Enter age: ";
            cin >> age;
            cout << "Enter gender (M/F): ";
            cin >> gender;
            cout << "Enter disease description: ";
            cin.ignore();
            getline(cin, diseaseDescription);
            cout << "Enter specialist room number: ";
            cin >> specialistRoomNumber;
            cout << "Enter service: ";
            cin.ignore();
            getline(cin, service);

            prm.addNewPatient(name, address, age, gender, diseaseDescription, specialistRoomNumber, service);
            cout << endl;
            break;
        }
        case 2: {
            int searchChoice;
            cout << "Search/Edit by 1. Record Number or 2. Full Name: ";
            cin >> searchChoice;

            if (searchChoice == 1) {
                int recordNumber;
                cout << "Enter record number: ";
                cin >> recordNumber;
                prm.searchOrEditPatientRecord(recordNumber);
            }
            else if (searchChoice == 2) {
                string fullName;
                cout << "Enter full name: ";
                cin.ignore();
                getline(cin, fullName);
                prm.searchOrEditPatientRecord(fullName);
            }
            cout << endl;
            break;
        }
        case 3: {
            string choice;
            cout << "Display 1. All records or 2. Specific records: ";
            cin >> choice;
            prm.listPatientRecords(choice);
            cout << endl;
            break;
        }
        case 4: {
            int recordNumber;
            cout << "Enter record number to delete: ";
            cin >> recordNumber;
            prm.deletePatientRecord(recordNumber);
            cout << endl;
            break;
        }
        case 5: {
            int recordNumber;
            double totalCharge, totalDeposited, totalMoneyToReturn;

            cout << "Enter record number: ";
            cin >> recordNumber;
            cout << "Enter total charge: ";
            cin >> totalCharge;
            cout << "Enter total deposited: ";
            cin >> totalDeposited;
            cout << "Enter total money to return: " << (totalDeposited - totalCharge) << "$" << endl;

            frm.addFinancialRecord(recordNumber, totalCharge, totalDeposited);
            cout << endl;
            break;
        }
        case 6: {
            int recordNumber;
            cout << "Enter record number to display financial records: ";
            cin >> recordNumber;
            frm.displayFinancialRecords(recordNumber);
            cout << endl;
            break;
        }
        case 7: {
            int recordNumber;
            string treatmentDescription;
            cout << "Enter record number: ";
            cin >> recordNumber;
            cout << "Enter treatment description: ";
            cin.ignore();
            getline(cin, treatmentDescription);
            tm.addTreatment(recordNumber, treatmentDescription);
            cout << endl;
            break;
        }
        case 8: {
            int recordNumber;
            cout << "Enter record number to display treatment: ";
            cin >> recordNumber;
            tm.displayTreatment(recordNumber);
            cout << endl;
            break;
        }
        case 9: {
            int recordNumber;
            string newTreatmentDescription;
            cout << "Enter record number to edit treatment: ";
            cin >> recordNumber;
            cout << "Enter new treatment description: ";
            cin.ignore();
            getline(cin, newTreatmentDescription);
            tm.editTreatment(recordNumber, newTreatmentDescription);
            cout << endl;
            break;
        }
        case 10: {
            int recordNumber;
            cout << "Enter record number to delete treatment: ";
            cin >> recordNumber;
            tm.deleteTreatment(recordNumber);
            cout << endl;
            break;
        }
        case 11: {
            int recordNumber;
            string medicine;
            cout << "Enter record number: ";
            cin >> recordNumber;
            cout << "Enter medicine: ";
            cin.ignore();
            getline(cin, medicine);
            mm.addMedicine(recordNumber, medicine);
            cout << endl;
            break;
        }
        case 12: {
            int recordNumber;
            cout << "Enter record number to display medicines: ";
            cin >> recordNumber;
            mm.displayMedicine(recordNumber);
            cout << endl;
            break;
        }
        case 13: {
            int recordNumber;
            string medicine;
            cout << "Enter record number: ";
            cin >> recordNumber;
            cout << "Enter medicine to delete: ";
            cin.ignore();
            getline(cin, medicine);
            mm.deleteMedicine(recordNumber, medicine);
            cout << endl;
            break;
        }
        case 14: {
            fileHandler.saveToFile(prm.getRecords());
            cout << endl;
            break;
        }
        case 15: {
            vector<FileHandler::PatientRecord> patientRecords = fileHandler.readFromFile();
            for (const auto& record : patientRecords) {
                prm.addNewPatient(record.name, record.address, record.age, record.gender, record.diseaseDescription, record.specialistRoomNumber, record.service);
            }
            cout << endl;
            break;
        }
        case 0:
            cout << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }
    return 0;
}