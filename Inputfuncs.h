//
// Created by Арсений Волынец on 27.10.2020.
//

#ifndef DM_LAB1_INPUTFUNCS_H
#define DM_LAB1_INPUTFUNCS_H
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cctype>
#include <cmath>
#include "funcs.h"

using namespace std;
const int BAD_INPUT = -1;

void printMenu();
long long takeNum(u_int min, u_int max, string& ss, int start = 0, u_int* stop = 0);
void takeInput(string& buf);
long long takeNum(u_int min, u_int max, string& buf, const char* message);
vector<u_int> takeNums(u_int min, const vector<u_int>& max, size_t sz, const char* message, bool checkDoubles = false);
void calc_print(const char* message, set (*pf)(set&), set&);
void calc_print(const char* message, set (*pf)(set&, set&), set&, set&);

#endif //DM_LAB1_INPUTFUNCS_H
