#include "FenwickTree.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <string>

// Constructor implementation
template <typename T>
FenwickTree<T>::FenwickTree(int size) {
    n = size;
    bit.resize(n + 1, 0); // Using resize for better memory management
}

// Update the value at index
template <typename T>
void FenwickTree<T>::update(int index, T value) {
    while (index <= n) {
        bit[index] += value;
        index += index & -index; // Move to the next responsible node
    }
}

// Get the sum from 1 to index
template <typename T>
T FenwickTree<T>::get(int index) {
    T sum = 0;
    while (index > 0) {
        sum += bit[index];
        index -= index & -index; // Move to the parent node
    }
    return sum;
}

// Get the sum in the range [l, r]
template <typename T>
T FenwickTree<T>::range_query(int l, int r) {
    return get(r) - get(l - 1);
}

// Get the k-th smallest element
template <typename T>
T FenwickTree<T>::kth_query(int k) {
	int index = 0;
    int LOG = 0; 
	while ((1 << LOG) <= n) LOG++;


	for (int i = LOG; i >= 0; i--) {
		int nextIndex = index + (1 << i);
		if (nextIndex <= n && bit[nextIndex] < k) {
			k -= bit[nextIndex];
			index = nextIndex;
		}
	}

	return index + 1; // Return the 1-based index
}









///////////////////////////////////////////////////////////////////////////

// Explicit template instantiation for common types
template class FenwickTree<int>;
template class FenwickTree<long long>;
template class FenwickTree<double>;
template class FenwickTree<float>;

// Run a test case from a specified file
void runTestCase(const string filename, bool verify) {
    ifstream fin(filename);

    if (!fin) {
        cerr << "Error: Could not open file: " << filename << endl;
        return;
    }

    int n, m; // n: number of elements, m: number of queries
    fin >> n >> m;

    FenwickTree<int> fenwick(n);
    vector<int> originalArray(n + 1, 0);

    // Start measuring execution time
    auto start = std::chrono::steady_clock::now();

    // Initialize Fenwick tree with array values
    for (int i = 1; i <= n; i++) {
        int x;
        fin >> x;
        originalArray[i] = x;
        fenwick.update(i, x);
    }

    cout << "Processing " << m << " queries from " << filename << "...\n";

    int updateCount = 0, queryCount = 0;
    vector<pair<int, int>> queryResults; // Store query results for verification

    // Process queries
    for (int i = 0; i < m; i++) {
        int type, l, r;
        fin >> type >> l >> r;

        if (type == 1) {
            // Update query
            fenwick.update(l, r);
            originalArray[l] += r; // Update the original array for verification
            updateCount++;
        }
        else {
            // Range query
            int result = fenwick.range_query(l, r);
            cout << "Query " << i + 1 << " (range " << l << "-" << r << "): " << result << endl;
            queryResults.push_back({ i + 1, result });
            queryCount++;
        }
    }

    // Stop measuring execution time
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> duration = end - start;
    double timeElapsed = duration.count();

    cout << "\nExecution Summary:\n";
    cout << "- Total queries processed: " << m << " (" << updateCount << " updates, "
        << queryCount << " range queries)\n";
    cout << "- Execution time: " << fixed << setprecision(6) << timeElapsed << " seconds\n";

    // Calculate and display performance metrics
    double queriesPerSecond = m / timeElapsed;
    cout << "- Performance: " << fixed << setprecision(2) << queriesPerSecond << " queries/second\n";

    // If verification is requested, verify the results
    if (verify) {
        cout << "\nVerifying results against naive implementation..." << endl;
        bool verified = verifyTestCase(filename);
        if (verified) {
            cout << "✓ Verification PASSED: All results match the naive implementation." << endl;
        }
        else {
            cout << "✗ Verification FAILED: Results do not match the naive implementation." << endl;
        }
    }

    cout << endl;
    fin.close();
}

// Run a test case with a predefined naming convention
void runTestCase(int I, bool verify) {
    string filename = "Testcases/Testcase_" + to_string(I) + ".txt";
    runTestCase(filename, verify);
}

// Verify that a test case produces correct results
bool verifyTestCase(const string filename) {
    ifstream fin(filename);

    if (!fin) {
        cerr << "Error: Could not open file: " << filename << endl;
        return false;
    }

    int n, m;
    fin >> n >> m;

    // Initialize Fenwick tree
    FenwickTree<int> fenwick(n);

    // Initialize naive array implementation
    vector<int> naiveArray(n + 1, 0);

    // Read initial array values
    for (int i = 1; i <= n; i++) {
        int x;
        fin >> x;
        naiveArray[i] = x;
        fenwick.update(i, x);
    }

    bool allCorrect = true;
    int mismatchCount = 0;

    // Process queries
    for (int i = 0; i < m; i++) {
        int type, l, r;
        fin >> type >> l >> r;

		if (type < 1 || type > 2) {
			cerr << "Error: Invalid query type " << type << " in file: " << filename << endl;
		    
			return false;
		}


        if (type == 1) {
			if (l < 1 || l > n) {
				cerr << "Error: Invalid update query [" << l << ", " << r << "] in file: " << filename << endl;
				return false;
			}
            // Update query
            fenwick.update(l, r);
            naiveArray[l] += r;
        }
        else {
            if (l < 1 || l > min(r, n) || r < max(l, 1) || r > n) {
                cerr << "Error: Invalid query range [" << l << ", " << r << "] in file: " << filename << endl;
                return false;
            }
            // Range query
            int fenwickResult = fenwick.range_query(l, r);

            // Calculate naive result
            int naiveResult = 0;
            for (int j = l; j <= r; j++) {
                naiveResult += naiveArray[j];
            }

            // Compare results
            if (fenwickResult != naiveResult) {
                std::cout << "  Mismatch at query " << i + 1 << ": Fenwick = " << fenwickResult
                    << ", Naive = " << naiveResult << endl;
                allCorrect = false;
                mismatchCount++;

                // Limit the number of mismatches displayed
                if (mismatchCount >= 5) {
                    std::cout << "  Too many mismatches, stopping verification..." << endl;
                    break;
                }
            }
        }
    }

    fin.close();
    return allCorrect;
}

// Run a comprehensive benchmark analysis on a test case
void benchmarkTestCase(const string filename) {
    ifstream fin(filename);

    if (!fin) {
        cerr << "Error: Could not open file: " << filename << endl;
        return;
    }

    int n, m;
    fin >> n >> m;

    cout << "Running benchmark on " << filename << "..." << endl;
    cout << "Test case size: " << n << " elements, " << m << " queries" << endl;

    // Read array elements
    vector<int> elements(n + 1);
    for (int i = 1; i <= n; i++) {
        fin >> elements[i];
    }

    // Read queries
    vector<tuple<int, int, int>> queries;
    for (int i = 0; i < m; i++) {
        int type, l, r;
        fin >> type >> l >> r;
        queries.push_back({ type, l, r });
    }

    fin.close();

    // Benchmark Fenwick Tree
    auto fenwickStart = std::chrono::high_resolution_clock::now();

    FenwickTree<int> fenwick(n);
    for (int i = 1; i <= n; i++) {
        fenwick.update(i, elements[i]);
    }

    for (const auto& [type, l, r] : queries) {
        if (type == 1) {
            fenwick.update(l, r);
        }
        else {
            int result = fenwick.range_query(l, r);
        }
    }

    auto fenwickEnd = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> fenwickDuration = fenwickEnd - fenwickStart;

    // Benchmark naive array
    auto naiveStart = std::chrono::high_resolution_clock::now();

    vector<int> naiveArray = elements;

    for (const auto& [type, l, r] : queries) {
        if (type == 1) {
            naiveArray[l] += r;
        }
        else {
            int result = 0;
            for (int j = l; j <= r; j++) {
                result += naiveArray[j];
            }
        }
    }

    auto naiveEnd = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> naiveDuration = naiveEnd - naiveStart;

    // Report benchmark results
    cout << "\nBenchmark Results:\n";
    cout << "-------------------------------\n";
    cout << "Fenwick Tree: " << fixed << setprecision(3) << fenwickDuration.count() << " ms\n";
    cout << "Naive Array:  " << fixed << setprecision(3) << naiveDuration.count() << " ms\n";
    cout << "Speedup:      " << fixed << setprecision(2) << naiveDuration.count() / fenwickDuration.count() << "x\n";

    // Calculate and display performance metrics
    double queriesPerSecond = m / (fenwickDuration.count() / 1000.0);
    cout << "Performance:  " << fixed << setprecision(2) << queriesPerSecond << " queries/second\n";
    cout << "-------------------------------\n\n";
}
