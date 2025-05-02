#include "genTest.h"
#include <filesystem>

// Initialize random number generator
mt19937_64 rd(chrono::steady_clock::now().time_since_epoch().count());

// Generate a random number within a specified range
ll random(ll l, ll r) {
    return l + rd() % (r - l + 1);
}

// Ensure the Testcases directory exists
void ensureTestcasesDirectory() {
    const std::string dir = "Testcases";
    if (!std::filesystem::exists(dir)) {
        std::filesystem::create_directory(dir);
        cout << "Created directory: " << dir << endl;
    }
}

// Generate a test case with a specified number
void genTest(int I) {
    ensureTestcasesDirectory();

    string filename = "Testcases/Testcase_" + to_string(I) + ".txt";
    ofstream fout(filename);

    if (!fout) {
        cerr << "Error: Could not create file: " << filename << endl;
        return;
    }

    // Generate test case parameters
    int n = random(100, 5e5);  // Length of the array
    int m = random(100, 6e5);  // Number of queries

    cout << "Generating test case " << I << " with " << n << " elements and "
        << m << " queries..." << endl;

    // Write test case parameters
    fout << n << ' ' << m << '\n';

    // Generate array elements
    for (int i = 0; i < n; i++) {
        fout << random(0, 1e5) << ' ';
    }
    fout << '\n';

    // Generate queries
    int updateQueries = 0, rangeQueries = 0;

    for (int i = 0; i < m; i++) {
        int type = random(1, 2);

        if (type == 2) {
            // Range query (type 2)
            int l = random(1, n);
            int r = random(l, n);  // Ensure r >= l
            fout << 2 << ' ' << l << ' ' << r << '\n';
            rangeQueries++;
        }
        else {
            // Update query (type 1)
            int index = random(1, n);
            int value = random(1, 1e5);
            fout << 1 << ' ' << index << ' ' << value << '\n';
            updateQueries++;
        }
    }

    fout.close();

    cout << "Test case " << I << " generated successfully:" << endl;
    cout << "- File: " << filename << endl;
    cout << "- Elements: " << n << endl;
    cout << "- Queries: " << m << " (" << updateQueries << " updates, "
        << rangeQueries << " range queries)" << endl;
}

// Generate multiple test cases with numbers in the range [l, r]
void genTest(int l, int r) {
    cout << "Generating " << (r - l + 1) << " test cases..." << endl;

    for (int i = l; i <= r; i++) {
        genTest(i);
    }

    cout << "All test cases generated successfully!" << endl;
}

// Generate a small test case with specified parameters
void genSpecialTest(int n, int m) {
    ensureTestcasesDirectory();

    string filename = "Testcases/smallTest.txt";
    ofstream fout(filename);

    if (!fout) {
        cerr << "Error: Could not create file: " << filename << endl;
        return;
    }

    cout << "Generating small test case with " << n << " elements and "
        << m << " queries..." << endl;

    // Write test case parameters
    fout << n << ' ' << m << '\n';

    // Generate array elements with smaller values for easier verification
    for (int i = 0; i < n; i++) {
        fout << random(0, 50) << ' ';
    }
    fout << '\n';

    // Generate queries
    int updateQueries = 0, rangeQueries = 0;

    for (int i = 0; i < m; i++) {
        int type = random(1, 2);

        if (type == 2) {
            // Range query (type 2)
            int l = random(1, n);
            int r = random(l, n);  // Ensure r >= l
            fout << 2 << ' ' << l << ' ' << r << '\n';
            rangeQueries++;
        }
        else {
            // Update query (type 1)
            int index = random(1, n);
            int value = random(1, 20);  // Smaller values for easier verification
            fout << 1 << ' ' << index << ' ' << value << '\n';
            updateQueries++;
        }
    }

    fout.close();

    cout << "Small test case generated successfully:" << endl;
    cout << "- File: " << filename << endl;
    cout << "- Elements: " << n << endl;
    cout << "- Queries: " << m << " (" << updateQueries << " updates, "
        << rangeQueries << " range queries)" << endl;
}
