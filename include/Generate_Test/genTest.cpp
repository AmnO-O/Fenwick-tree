#include "GenTest.h"

extern mt19937_64 rd(chrono::steady_clock::now().time_since_epoch().count());

ll random(ll l, ll r) {
	return l + rd() % (r - l + 1);
}

void genTest(int I) {
	ofstream fout("Testcases/Testcase_" + to_string(I) + ".txt");
	
	int n = random(100, 5e5); // length of the array
	int m = random(100, 6e5); // number of queries
	
	fout << n << ' ' << m << '\n';
	
	for (int i = 0; i < n; i++) {
		fout << random(0, 1e5) << ' ';
	}
	
	fout << '\n';
	// type 1: update, type 2: query
	for (int i = 0; i < m; i++) {
		int type = random(1, 2);
		if (type == 1) {
			int l = random(1, n);
			int r = random(l, n);
			fout << 2 << ' ' << l << ' ' << r << '\n';
		}
		else fout << 1 << ' ' << random(1, n) << ' ' << random(1, 1e5) << '\n';
	}

	fout.close(); 
}

void genTest(int l, int r) {
	for (int i = l; i <= r; i++) genTest(i);
}

void genSpecialTest(int n, int m ){
	ofstream fout("Testcases/smallTest.txt");
	
	fout << n << ' ' << m << '\n';
	
	for (int i = 0; i < n; i++) 
		fout << random(0, 50) << ' ';
	
	fout << '\n';
	// type 1: update, type 2: query

	for (int i = 0; i < m; i++) {
		int type = random(1, 2);
		if (type == 1) {
			int l = random(1, n);
			int r = random(l, n);
			fout << 2 << ' ' << l << ' ' << r << '\n';
		}
		else fout << 1 << ' ' << random(1, n) << ' ' << random(1, 1e5) << '\n';
	}

	cout << "Named the test case: smallTest\n";

	fout.close(); 
}