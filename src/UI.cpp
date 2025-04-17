#include "UI.h"
#include "../include/FenwickTree/Fenwicktree.h"
#include "../include/Generate_Test/genTest.h"


void printHelp() {
    cout << "\nFenwick Tree\n";
    cout << "A Fenwick Tree implementation in C++\n";

    cout << "1: update, 2: query\n";
    cout << "Testcases are generated in the Testcases folder\n\n";

    cout << "Usage: [options]\n";
    cout << "Options:\n";
    
    cout << "  -g, --generate    Generate random test cases\n";
    cout << "  -s, --small       Generate small test cases\n";
    cout << "  -r, --run         Run test cases\n";
    cout << "  -p, --print       Print test cases\n";
    cout << "  -i, --input       Input your own testcase\n";
    cout << "  -e, --exit        Exit the program\n";
    cout << "  -c, --clear       Clear the screen\n";
    cout << "  -h, --help        Show this help message\n\n";
}

void process(){
    int choice = 0; 

    printHelp(); 

    while(true){
        char input; 
        cout << "Enter your choice: ";

        cin >> input;

        if(input != '-'){
            cout << "Invalid choice. Please try again.\n\n"; 
            continue; 
        }

        cin >> input; 
        
        if(input != 'g' && input != 'r' && input != 'i' && input != 's'  && input != 'e' && input != 'h' && input != 'p' && input != 'c') {
            cout << "Invalid choice. Please try again.\n\n"; 
            continue;
        }

        if(input == 'g'){
            cout << "Enter the test case number: ";
            int number; cin >> number; 
            genTest(number); 
            cout << "We have generated " << number << " test cases.\n\n";
        }

        if(input == 'r'){
            cout << "Enter the filename: ";
            string filename; cin >> filename;
            runTestCase("../Testcases/" + filename + ".txt"); 
        }

        if(input == 'i'){
            cout << "Enter the input file name: ";
            string filename; cin >> filename;
			string path = "../Testcases/" + filename + ".txt";
            ofstream fout(path);
            
            int n, m;
            cout << "Enter the number of elements and queries (n, m): ";
            cin >> n >> m;

            fout << n << ' ' << m << '\n'; 

            cout << "Enter the elements: ";
            for (int i = 0; i < n; i++){
                int x; cin >> x; 
                fout << x << ' '; 
            }

            fout << '\n';

            cout << "Enter the queries (type, l, r):\n";
			cout << "Format (1 2 3): update a[2] += 3\n";
			cout << "Format (2 2 3): get sum: 2 -> 3\n\n";

            
            for (int i = 0; i < m; i++){
                int type, l, r; 
                cin >> type; 

				if (type != 1 && type != 2) {
					cout << "Invalid query type. Please enter 1 or 2.\n";
					i--; // Decrement i to repeat this iteration
					continue;
				}

				if (type == 1){
                    cout << "Enter the index to update: "; cin >> l; 
					if (l < 1 || l > n) {
						cout << "Invalid index. Please enter a valid index between 1 and " << n << ".\n";
						i--; // Decrement i to repeat this iteration
						continue;
					}

                    cout << "Enter the value to add: ";
					int value; cin >> value;
					fout << type << ' ' << l << ' ' << value << '\n';
				}
				else {
                    cout << "Enter the range (l, r): "; cin >> l >> r; 

					if (l < 1 || l > n || r < 1 || r > n || l > r) {
						cout << "Invalid range. Please enter valid indices between 1 and " << n << ", with l <= r.\n";
						i--; // Decrement i to repeat this iteration
						continue;
					}

					fout << type << ' ' << l << ' ' << r << '\n';
				}

                fout << type << ' ' << l << ' ' << r << '\n'; 
            }
            
            cout << "Test case saved to " << filename << "\n\n";
        }

        if(input == 's'){
            cout << "Enter the number of elements and queries (n, m): ";
            int n, m; cin >> n >> m;
            genSpecialTest(n, m);
            cout << "Small test case generated with " << n << " elements and " << m << " queries.\n\n";
        }
        
        if(input == 'e'){
            cout << "Exiting the program...\n"; 
            break; 
        }

        if (input == 'c') {
            system("cls"); // Clear the console screen
			cout << "Screen cleared.\n\n";
        }

		if (input == 'p') {
			cout << "Enter the filename: ";
			string filename; cin >> filename;
			ifstream fin("../Testcases/" + filename + ".txt");
			
            if (!fin) {
				cout << "Error opening file: " + filename + "\n\n";
				continue;
			}

			string line;
			while (getline(fin, line)) {
				cout << line << '\n';
			}
			cout << "\n";
		}
        
        if(input == 'h'){
            printHelp(); 
        }
    }
}


