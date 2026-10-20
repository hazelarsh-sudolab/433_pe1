// Snippet standard crucial preprocessor directive; "#include and #define"
#include <iostream> // << STD input/output stream
#include <fstream> // << read/write data to/from file
#include <string> // << specialized container optimized for human-readable text
#include <vector> // << generic data storage
#include <cctype> // << for std::isdigit

#ifndef File_Ext
#define File_Ext ".txt"
#endif

struct Student {
    std::string StudentName;
    std::string MatricNumber;
};

// Checks if a string is exactly 8 characters and all digits.
bool Valid_MN(const std::string& s) {
    if (s.size() != 8) return false;
    for (char c : s) {
        if (!std::isdigit(static_cast<unsigned char>(c))) return false;
    }
    return true;
}

// "mn" remarks the matric number to check, and "existing" is a vector of already used matric numbers.
bool ExistValue(const std::string& mn, const std::vector<std::string>& existing) {
    for (const auto& e : existing) {
        if (e == mn) return true;
    }
    return false;
}

// Asks the user for their full name and returns it.
std::string AskName() {
    std::string name;
    while (true) {
        std::cout << "Enter your full name: ";
        std::getline(std::cin, name);

        if (!name.empty()) {
            break;
        }
        std::cout << "Name cannot be empty. Please enter your full name.\n";
    }
    return name;
}

int main() {

    std::string USER_MatricNumber;
    std::string USER_Name;

    // Ask matric number first (used as the filename).
    // Must be exactly 8 digits.
    while (true) {
        std::cout << "Enter the users matric number (8 digits, e.g. 22303498): ";
        std::getline(std::cin, USER_MatricNumber);

        if (Valid_MN(USER_MatricNumber)) {
            break;
        }
        std::cout << "Invalid matric number. Please enter exactly 8 digits.\n";
    }

    // Then ask for the user's full name.
    USER_Name = AskName();

    // Banner shown after both identity inputs are collected.
    std::cout << "==================================================\n";
    std::cout << "            Students Record Data Entry            \n";
    std::cout << "==================================================\n";
    std::cout << "--------------------------------------------------\n";

    // Prevent multiple entries with the same matric number.
    std::vector<std::string> UsedMatricNumbers;
    UsedMatricNumbers.push_back(USER_MatricNumber);

    // Remark: The number of students to be recorded is set to 5, as per the project requirements.
    const int NOStudent = 5; // << Number of students to be recorded
    std::vector<Student> Students(NOStudent); // << Vector to store student details

    // Inquire user course of study to be used as the users program name.
    // User must choose between "Mechatronic Engineering" or "Electronic Engineering"
    std::string UserCourse;
    while (true) {
        std::cout << "Enter user course of study:\n";
        std::cout << "1. Mechatronic Engineering\n";
        std::cout << "2. Electronic Engineering\n" << std::endl;
        std::cout << "Enter 1 or 2: ";

        std::getline(std::cin, UserCourse);

        if (UserCourse == "1" ||
            UserCourse == "Mechatronic" ||
            UserCourse == "Mechatronic Engineering")
        {
            UserCourse = "Mechatronic Engineering";
            break;
        }

        else if (UserCourse == "2" ||
                 UserCourse == "Electronic" ||
                 UserCourse == "Electronic Engineering")
        {
            UserCourse = "Electronic Engineering";
            break;
        }

        // Invalid input will prompt the user to re-enter their course of study until a valid input is provided.

        else {
            std::cout << "Invalid input. Please enter 1 or 2." << std::endl;
        }
    }

    std::cout << "--------------------------------------------------\n\n";

 // Say; If user chooses "Mechatronic Engineering", the program will proceed to inquire 5 students details of the opposite program, and vice versa.
std::cout << "You have selected: " << UserCourse << std::endl;
std::cout << "--------------------------------------------------\n\n";

std::string OppositeCourse = (UserCourse == "Mechatronic Engineering") ? "Electronic Engineering" : "Mechatronic Engineering";

// Print the header only ONCE, before the loop.
std::cout << "Submit students details for " << OppositeCourse << ":\n\n";

// Prompt user input for 5 respective engineering students.
// Inquire each of students name and their matric number respectively.
for (int i = 0; i < NOStudent; ++i) {
    std::cout << "Student " << (i + 1) << ":\n";

    std::cout << "Enter student name: ";
    std::getline(std::cin, Students[i].StudentName);

    // Matric number must be exactly 8 digits and not already used.
    while (true) {
        std::cout << "Enter student matric number (8 digits): ";
        std::getline(std::cin, Students[i].MatricNumber);

        if (!Valid_MN(Students[i].MatricNumber)) {
            std::cout << "Invalid matric number. Please enter exactly 8 digits.\n";
        }
        else if (ExistValue(Students[i].MatricNumber, UsedMatricNumbers)) {
            std::cout << "Duplicate matric number. That number is already in use.\n";
        }
        else {
            UsedMatricNumbers.push_back(Students[i].MatricNumber);
            break;
        }
    }

    std::cout << "--------------------------------------------------\n";
}

// Set filename using the entered "matric number" + ".txt" file type. >> "e.g.: 22303498.txt"
std::string filename = USER_MatricNumber + File_Ext;
std::ofstream outputFile(filename); // << Create and open the file for writing

if (!outputFile) {
    std::cerr << "Error: Could not create file " << filename << std::endl;
    return 1; // << Exit with error code
}

// Write the data into the plain text (ASCII / .txt) file.
outputFile << "==================================================\n";
outputFile << "            Students Record Data Entry            \n";
outputFile << "==================================================\n\n";
outputFile << "Name: " << USER_Name << " | Matric No: " << USER_MatricNumber << "\n";
outputFile << "User Course of Study: " << UserCourse << "\n";
outputFile << "Targeted Course of Study: " << OppositeCourse << "\n";
outputFile << "==================================================\n\n";
for (const auto& student : Students) {
    outputFile << "Student Name: " << student.StudentName << "\n";
    outputFile << "Matric Number: " << student.MatricNumber << "\n";
    outputFile << "--------------------------------------------------\n";
}
outputFile << "==================================================\n";

outputFile.close(); // << Close the file after writing

// Console confirmation.
std::cout << "==================================================\n";
std::cout << "Data successfully written to " << filename << "\n";
std::cout << "==================================================\n";
return 0; // << Exit the program successfully
}