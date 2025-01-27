#include "editor.h"
#include "io_window.h"
#include <iostream>
#include <fstream>
#include <string>

void displayMenu() {
    std::cout << "========================\n";
    std::cout << " Multi-Pass Compiler\n";
    std::cout << "========================\n";
    std::cout << "1. Enter code manually\n";
    std::cout << "2. Load code from file\n";
    std::cout << "3. Exit\n";
    std::cout << "Choose an option: ";
}

std::string getSourceCodeFromUser() {
    std::cout << "Enter your code (type 'END' on a new line to finish):\n";
    std::string line, source_code;
    while (std::getline(std::cin, line)) {
        if (line == "END") break; // Stop when user types "END"
        source_code += line + "\n";
    }
    return source_code;
}

std::string getSourceCodeFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file: " << filename << std::endl;
        return "";
    }

    std::string line, source_code;
    while (std::getline(file, line)) {
        source_code += line + "\n";
    }
    file.close();
    return source_code;
}

int main() {
    Editor editor;

    while (true) {
        displayMenu();

        int choice;
        std::cin >> choice;
        std::cin.ignore(); // Ignore trailing newline from std::cin

        std::string source_code;

        if (choice == 1) {
            // Input source code manually
            source_code = getSourceCodeFromUser();
        } else if (choice == 2) {
            // Load source code from a file
            std::cout << "Enter file name: ";
            std::string filename;
            std::cin >> filename;
            std::cin.ignore(); // Ignore trailing newline
            source_code = getSourceCodeFromFile(filename);
        } else if (choice == 3) {
            std::cout << "Exiting compiler. Goodbye!" << std::endl;
            break;
        } else {
            std::cerr << "Invalid choice. Please try again.\n";
            continue;
        }

        if (source_code.empty()) {
            std::cerr << "No source code provided. Returning to menu.\n";
            continue;
        }

        // Compile the provided source code and display all steps
        if (!editor.compileSource(source_code)) {
            std::cerr << "Compilation failed. Returning to menu.\n";
        }
    }

    return 0;
}
