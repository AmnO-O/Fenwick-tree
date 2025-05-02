#ifndef UI_H
#define UI_H

#include <iostream>
#include <fstream>
#include <string>
#include <limits>

void printHelp();
void clearScreen();

int getIntInput(const std::string& prompt, int minValue = std::numeric_limits<int>::min(),
    int maxValue = std::numeric_limits<int>::max());

std::string getStringInput(const std::string& prompt);

bool getYesNoInput(const std::string& prompt);

void handleGenerateTestCase();
void handleGenerateSmallTest();
void handleRunTestCase();
void handleVerifyTestCase();
void handleBenchmarkTestCase();
void handlePrintTestCase();
void handleInputTestCase();
void process();

#endif // UI_H
