#include <iostream>
#include <vector>

using namespace std;

template <typename T>
// Fenwick Tree (Binary Indexed Tree) for range sum queries
class FenwickTree {
private:
    int n;
public:
    vector<T> bit; // binary indexed tree array
    
    FenwickTree(int _ = 0); // Constructor with size parameter
    void update(int index, T value); // Update the value at index
	T get(int index); // Get the sum in the range [1, index]
	T range_query(int l, int r); // Get the sum in the range [l, r]
}; 

void runTestCase(int I); // Run test case I
void runTestCase(const string filename = ""); // Run test case I