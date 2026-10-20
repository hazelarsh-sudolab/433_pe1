// Snippet standard crucial preprocessor directive; "#include and #define"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <cctype>

#ifndef Dat_Ext
#define Dat_Ext ".dat"
#endif

// Checks if a string is exactly 8 characters and all digits.
bool Valid_MN(const std::string& s) {
    if (s.size() != 8) return false;
    for (char c : s) {
        if (!std::isdigit(static_cast<unsigned char>(c))) return false;
    }
    return true;
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

    // 1. Ask user identity
    while (true) {
        std::cout << "Enter the users matric number (8 digits, e.g. 22303498): ";
        std::getline(std::cin, USER_MatricNumber);
        if (Valid_MN(USER_MatricNumber)) break;
        std::cout << "Invalid matric number. Please enter exactly 8 digits.\n";
    }

    USER_Name = AskName();

    // 2. Print Identity Line
    std::cout << "Name: " << USER_Name << " | Matric No: " << USER_MatricNumber << "\n";
    std::cout << "==================================================\n";
    std::cout << "            Binary Record Data Viewer             \n";
    std::cout << "==================================================\n";

    // 3. Main loop to read files
    while (true) {

        std::string TargetMatricNumber;
        while (true) {
            std::cout << "Enter the recorded matric number to read: ";
            std::getline(std::cin, TargetMatricNumber);
            if (Valid_MN(TargetMatricNumber)) break;
            std::cout << "Invalid matric number. Please enter exactly 8 digits.\n";
        }

        std::cout << "--------------------------------------------------\n";

        std::string filename = TargetMatricNumber + Dat_Ext;

        // OPEN AS BINARY. NO TEXT MODE.
        std::ifstream inputFile(filename, std::ios::binary);

        if (!inputFile) {
            std::cerr << "Error: Could not open binary file " << filename << std::endl;
            std::cerr << "No such record exists.\n\n";
            continue; 
        }

        std::cout << "Extracted Data from " << filename << ":\n\n";

        // READ RAW BINARY BYTES DIRECTLY
        while (true) {
            std::uint32_t len = 0;
            
            // Read 4 bytes of raw binary data for the length
            inputFile.read(reinterpret_cast<char*>(&len), sizeof(len));
            
            // End of file reached
            if (!inputFile) break;

            // Read the exact number of characters specified by len
            std::string line(len, '\0');
            inputFile.read(&line[0], len);

            // Since it's binary, we only print the specific records requested
            if (line.rfind("Student Name: ", 0) == 0) {
                std::cout << line << "\n";
            }
            else if (line.rfind("Matric Number: ", 0) == 0) {
                std::cout << line << "\n";
                std::cout << "--------------------------------------------------\n";
            }
        }

        inputFile.close();

        std::cout << "\nEnd of binary record for " << filename << "\n\n";
    }

    return 0; 
}