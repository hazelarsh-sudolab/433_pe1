// Snippet standard crucial preprocessor directive; "#include and #define"
#include <iostream> // << STD input/output stream
#include <fstream> // << read/write data to/from file
#include <string> // << specialized container optimized for human-readable text
#include <vector> // << generic data storage
#include <cstdint> // << for std::uint32_t (fixed-width integer for binary layout)
#include <cctype>

#ifndef File_Ext
#define File_Ext ".txt"
#endif

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

// Writes lines into a binary file, each line prefixed with its length.
bool WriteBinary(const std::string& filename, const std::vector<std::string>& lines) {
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile) return false;

    for (const auto& line : lines) {
        std::uint32_t len = static_cast<std::uint32_t>(line.size());
        outFile.write(reinterpret_cast<const char*>(&len), sizeof(len));
        outFile.write(line.data(), len);
    }

    outFile.close();
    return true;
}

// Asks the user Y/N; returns true only if they confirm.
bool AskCreateDat() {
    std::string choice;
    while (true) {
        std::cout << "Create a .dat binary copy of this record? (Y/N): ";
        std::getline(std::cin, choice);

        if (choice == "Y" || choice == "y") return true;
        if (choice == "N" || choice == "n") return false;

        std::cout << "Invalid input. Please enter Y or N.\n";
    }
}

int main() {

    std::cout << "==================================================\n";
    std::cout << "            Students Record Data Viewer           \n";
    std::cout << "==================================================\n";

    // Loop to allow multiple attempts to read different student records.
    while (true) {

        // Request user matric number to read any recorded data. >> "e.g.: 22303498"
        // Must be exactly 8 digits.
        std::string USER_MatricNumber;
        while (true) {
            std::cout << "Enter the requested recorded matric number to be read: ";
            std::getline(std::cin, USER_MatricNumber);

            if (Valid_MN(USER_MatricNumber)) {
                break;
            }

            std::cout << "Invalid matric number. Please enter exactly 8 digits.\n";
        }

        std::cout << "--------------------------------------------------\n";

        // Reconstruct the filename using the entered "matric number" + ".txt" file type.
        std::string filename = USER_MatricNumber + File_Ext;

        // Read-only mode to preview the recorded data.
        std::ifstream inputFile(filename);

        if (!inputFile) {
            std::cerr << "Error: Could not open file " << filename << std::endl;
            std::cerr << "No such record exists, or it cannot be accessed/read.\n\n";
            continue; // << back to the top to ask again
        }

        // Read and display the contents of the file.
        std::cout << "Contents of " << filename << ":\n\n";

        std::vector<std::string> lines;
        std::string line;
        while (std::getline(inputFile, line)) {
            std::cout << line << "\n";
            lines.push_back(line);
        }

        inputFile.close(); // << Close the file after reading

        std::cout << "\n";
        std::cout << "End of record for " << filename << "\n\n";

        // Ask before writing the binary copy.
        if (AskCreateDat()) {
            std::string datFilename = USER_MatricNumber + Dat_Ext;
            if (WriteBinary(datFilename, lines)) {
                std::cout << "Binary copy written to " << datFilename << "\n";
            } else {
                std::cerr << "Error: Could not create binary file " << datFilename << "\n";
            }
        } else {
            std::cout << "Binary copy skipped.\n";
        }

        std::cout << "--------------------------------------------------\n\n";
    }

    return 0; // << Exit the program successfully
}