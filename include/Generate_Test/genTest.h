#pragma once
#include <iostream>
#include <random>
#include <chrono>
#include <fstream>
#include <vector>
#include <string>
using namespace std; 

#define ll long long

void genSpecialTest(int n = 0, int m = 0); // generate test case with n elements and m queries
void genTest(int I = 0); // generate test case I
void genTest(int l, int r); // generate test case I with range [l, r]

