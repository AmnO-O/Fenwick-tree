#include "UI.h"
#include "../include/FenwickTree/Fenwicktree.h"
#include "../include/Generate_Test/genTest.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <functional>
#include <limits>
#include <algorithm>
#include <cctype>

// Clear screen function that works across platforms
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear"); // For Unix/Linux/MacOS
#endif
    std::cout << "Screen cleared.\n\n";
}

// Print help menu with available commands
void printHelp() {
    std::cout << "\n====== Fenwick Tree ======\n";
    std::cout << "A Fenwick Tree implementation in C++\n\n";

    std::cout << "Available Commands:\n";
    std::cout << "  g, generate    - Generate random test cases\n";
    std::cout << "  s, small       - Generate small test cases\n";
    std::cout << "  r, run         - Run test cases\n";
    std::cout << "  v, verify      - Verify test case correctness\n";
    std::cout << "  b, benchmark   - Benchmark test case performance\n";
    std::cout << "  p, print       - Print test cases\n";
    std::cout << "  i, input       - Input your own testcase\n";
    std::cout << "  c, clear       - Clear the screen\n";
    std::cout << "  h, help        - Show this help message\n";
    std::cout << "  e, exit        - Exit the program\n\n";

    std::cout << "For queries:\n";
    std::cout << "  1: update [index] [value] - Update value at index\n";
    std::cout << "  2: query [left] [right]   - Get sum from left to right\n\n";
}

// Safely get integer input with validation
int getIntInput(const std::string& prompt, int minValue, int maxValue) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            if (value >= minValue && value <= maxValue) {
                break;
            }
            std::cout << "Value must be between " << minValue << " and " << maxValue << ".\n";
        }
        else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
        }
    }
    return value;
}

// Get string input with validation
std::string getStringInput(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    std::cin >> input;
    return input;
}

// Get yes/no input from user
bool getYesNoInput(const std::string& prompt) {
    std::string input;
    while (true) {
        std::cout << prompt << " (y/n): ";
        std::cin >> input;

        // Convert to lowercase for case-insensitive comparison
        std::transform(input.begin(), input.end(), input.begin(),
            [](unsigned char c) { return std::tolower(c); });

        if (input == "y" || input == "yes") {
            return true;
        }
        else if (input == "n" || input == "no") {
            return false;
        }
        else {
            std::cout << "Please enter 'y' or 'n'.\n";
        }
    }
}

// Generate random test cases
void handleGenerateTestCase() {
    int number = getIntInput("Enter the number of test cases to generate: ", 1, 100);
    genTest(number);
    std::cout << "Successfully generated " << number << " test cases.\n\n";

    bool runAfterGenerate = getYesNoInput("Would you like to run one of the generated test cases?");
    if (runAfterGenerate) {
        int testNum = getIntInput("Enter the test case number to run (1-" + std::to_string(number) + "): ", 1, number);
        bool verifyResults = getYesNoInput("Would you like to verify the results?");
        runTestCase(testNum, verifyResults);
    }
}

// Generate small test case
void handleGenerateSmallTest() {
    int n = getIntInput("Enter the number of elements: ", 1, 1000);
    int m = getIntInput("Enter the number of queries: ", 1, 1000);
    genSpecialTest(n, m);
    std::cout << "Small test case generated with " << n << " elements and " << m << " queries.\n\n";

    bool runAfterGenerate = getYesNoInput("Would you like to run this test case?");
    if (runAfterGenerate) {
        bool verifyResults = getYesNoInput("Would you like to verify the results?");
        runTestCase("Testcases/smallTest.txt", verifyResults);
    }
}

// Run a test case
void handleRunTestCase() {
    std::string filename = getStringInput("Enter the filename (without .txt extension): ");
    std::string fullPath = "Testcases/" + filename + ".txt";

    // Check if file exists before attempting to run
    std::ifstream testFile(fullPath);
    if (!testFile) {
        std::cout << "Error: File '" << fullPath << "' not found.\n\n";
        return;
    }
    testFile.close();

    bool verifyResults = getYesNoInput("Would you like to verify the results?");
    runTestCase(fullPath, verifyResults);

    bool benchmarkAfterRun = getYesNoInput("Would you like to run a benchmark on this test case?");
    if (benchmarkAfterRun) {
        benchmarkTestCase(fullPath);
    }
}

// Verify a test case for correctness
void handleVerifyTestCase() {
    std::string filename = getStringInput("Enter the filename (without .txt extension): ");
    std::string fullPath = "Testcases/" + filename + ".txt";

    // Check if file exists before attempting to verify
    std::ifstream testFile(fullPath);
    if (!testFile) {
        std::cout << "Error: File '" << fullPath << "' not found.\n\n";
        return;
    }
    testFile.close();

    std::cout << "Verifying test case: " << filename << "...\n";
    bool result = verifyTestCase(fullPath);

    if (result) {
        std::cout << "✓ Verification PASSED: All results match the naive implementation.\n\n";
    }
    else {
        std::cout << "✗ Verification FAILED: Results do not match the naive implementation.\n\n";
    }
}

void handleBenchmarkTestCase() {
    std::string filename = getStringInput("Enter the filename (without .txt extension): ");
    std::string fullPath = "Testcases/" + filename + ".txt";

    // Check if file exists before attempting to benchmark
    std::ifstream testFile(fullPath);
    if (!testFile) {
        std::cout << "Error: File '" << fullPath << "' not found.\n\n";
        return;
    }
    testFile.close();

    benchmarkTestCase(fullPath);
}

void handlePrintTestCase() {
    std::string filename = getStringInput("Enter the filename (without .txt extension): ");
    std::string fullPath = "Testcases/" + filename + ".txt";
    std::ifstream fin(fullPath);

    if (!fin) {
        std::cout << "Error: File '" << fullPath << "' not found.\n\n";
        return;
    }

    std::cout << "\n===== Contents of " << filename << ".txt =====\n";
    std::string line;
    while (getline(fin, line)) {
        std::cout << line << '\n';
    }
    std::cout << "\n";
    fin.close();
}

void handleInputTestCase() {
    std::string filename = getStringInput("Enter the filename (without .txt extension): ");
    std::string path = "Testcases/" + filename + ".txt";
    std::ofstream fout(path);

    if (!fout) {
        std::cout << "Error: Could not create file '" << path << "'\n\n";
        return;
    }

    int n = getIntInput("Enter the number of elements: ", 1, 1000000);
    int m = getIntInput("Enter the number of queries: ", 1, 1000000);

    fout << n << ' ' << m << '\n';

    std::cout << "Enter " << n << " elements (space-separated): ";
    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        fout << x << ' ';
    }
    fout << '\n';

    std::cout << "\nEnter " << m << " queries:\n";
    std::cout << "Format: 1 [index] [value] - Update array[index] += value\n";
    std::cout << "Format: 2 [left] [right]  - Query sum from left to right\n\n";

    for (int i = 0; i < m; i++) {
        std::cout << "Query " << (i + 1) << "/" << m << ": ";
        int type = getIntInput("Type (1 for update, 2 for query): ", 1, 2);

        if (type == 1) {
            int index = getIntInput("Index to update (1 to " + std::to_string(n) + "): ", 1, n);
            int value = getIntInput("Value to add: ");
            fout << type << ' ' << index << ' ' << value << '\n';
        }
        else {
            int left = getIntInput("Left bound (1 to " + std::to_string(n) + "): ", 1, n);
            int right = getIntInput("Right bound (" + std::to_string(left) + " to " + std::to_string(n) + "): ", left, n);
            fout << type << ' ' << left << ' ' << right << '\n';
        }
    }

    fout.close();
    std::cout << "Test case saved to file: " << path << "\n\n";

    bool runAfterCreate = getYesNoInput("Would you like to run this test case?");
    if (runAfterCreate) {
        bool verifyResults = getYesNoInput("Would you like to verify the results?");
        runTestCase(path, verifyResults);
    }
}

void process() {
    // Map commands to handler functions for cleaner dispatch
    std::map<std::string, std::function<void()>> commandHandlers = {
        {"g", handleGenerateTestCase}, {"generate", handleGenerateTestCase},
        {"s", handleGenerateSmallTest}, {"small", handleGenerateSmallTest},
        {"r", handleRunTestCase}, {"run", handleRunTestCase},
        {"v", handleVerifyTestCase}, {"verify", handleVerifyTestCase},
        {"b", handleBenchmarkTestCase}, {"benchmark", handleBenchmarkTestCase},
        {"p", handlePrintTestCase}, {"print", handlePrintTestCase},
        {"i", handleInputTestCase}, {"input", handleInputTestCase},
        {"c", clearScreen}, {"clear", clearScreen},
        {"h", printHelp}, {"help", printHelp}
    };

    printHelp();

    while (true) {
        std::string command;
        std::cout << "Enter command (or 'h' for help): ";
        std::cin >> command;

        // Remove leading dash if present for flexibility
        if (!command.empty() && command[0] == '-') {
            command = command.substr(1);
        }

        if (command == "e" || command == "exit") {
            std::cout << "Exiting the program. Goodbye!\n";
            break;
        }

        auto it = commandHandlers.find(command);
        if (it != commandHandlers.end()) {
            // Call the appropriate handler function
            it->second();
        }
        else {
            std::cout << "Unknown command: '" << command << "'. Type 'h' for help.\n\n";
        }

        // Clear input buffer to prevent issues with subsequent input
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}
