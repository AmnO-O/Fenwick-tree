#include "FenwickTree.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <time.h>
#include <algorithm>
#include <random>
#include<string>
#include <cstring>


template <typename T>
FenwickTree<T>::FenwickTree(int _) { // Corrected constructor definition
	n = _;
	bit = vector<T>(n + 2, 0); // Corrected size to n + 1 for 1-based indexing
}

template <typename T>
void FenwickTree<T>::update(int index, T value) { // Update the value at index
	while (index <= n) {
		bit[index] += value;
		index += index & -index;
	}
}

template <typename T>
T FenwickTree<T>::get(int index){ // get the sum in the range [1, index]
	T sum = 0;
	while (index > 0) { 
		sum += bit[index];
		index -= index & -index; // Corrected index update
	}
	return sum;
}


template <typename T>
T FenwickTree<T>::range_query(int l, int r) { // get the sum in the range [l, r]
	return get(r) - get(l - 1);
}

void runTestCase(const string filename){
	ifstream fin(filename); // Open the file with the given filename
	
	if(!fin){
		cerr << "Error opening file: " + filename + " \n"; // Error handling for file opening
		return;
	}

	int n, m; // n: number of elements, m: number of queries
	fin >> n >> m; 

	FenwickTree<int> fenwick(n); 
	vector<int> arr(n + 1);

	auto start = std::chrono::steady_clock::now();

	for (int i = 1; i <= n; i++) {
		int x; fin >> x; 
		
		fenwick.bit[i] += x; 
		
		int par = i + (i & -i); // find the parent index
		
		if (par <= n) 
			fenwick.bit[par] += fenwick.bit[i]; 
	}

	for (int i = 0; i < m; i++) {
		int type, l, r;
		fin >> type >> l >> r; // read the query type and range

		if (type == 1) { // update query
			fenwick.update(l, r); // update the Fenwick Tree at index l with value r
		} else { // range query
			cout << "Query " << i + 1 << ": " << fenwick.range_query(l, r) << '\n'; // print the result of the range query
		}
	}

	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> duration = end - start;
	double timeElapsed = duration.count();

    std::cout << "Execution time using Fenwicktree on " + filename + ": " << timeElapsed << " s\n"; 
        
	
}

void runTestCase(int I){
	string filename = "../Testcases/Testcase_" + to_string(I) + ".txt"; // Construct the filename
	runTestCase(filename); // Call the function with the constructed filename
}