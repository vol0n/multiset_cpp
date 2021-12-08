//
// Created by Арсений Волынец on 27.10.2020.
//

#include "Inputfuncs.h"

using namespace std;

unsigned long long ipow(int base, int exp)
{
    unsigned long long result = 1;
    for (int i = 0; i < exp; i++)
        result *= base;
    return result;
}

long long takeNum(u_int min, u_int max, string& ss, int start, u_int* stop){
    //return a min <= number <= max, from ss, that is between ss[start] and ss.size(), update stop
    int i = start;
    for (; i < ss.size(); i++){
        if (!isdigit(ss[i])) {
            if (ss[i] != ' ') {
                cout << ss[i] << " is not a digit!" << endl;
                return BAD_INPUT;
            }
            break;
        }
    }

    if (stop) *stop = i+1;
    i--;
    u_int res = 0;
    for (int j = 0, x = i-start; j <= x; j++, i--)
        res += (ss[i]-'0')*ipow(10, j);

    if (res > max) {
        cout << "Incorrect number: " << res << ". The number must be not greater than " << max << endl;
        return BAD_INPUT;
    }
    if (res < min) {
        cout << "Incorrect number: " << res << ". The number must be at least " << min << endl;
        return BAD_INPUT;
    }

    return res;
}


void takeInput(string& buf){
    buf.clear();
    while (buf.empty()) {
        cin >> ws;
        getline(cin, buf);
    }
}

vector<u_int> takeNums(u_int min, const vector<u_int>& max, size_t sz, const char* message, bool checkDoubles){
    string buf;
    vector<u_int> v;
    u_int stop = 0;
    u_int res = 0;
    bool toBreak = false;
    while (!toBreak){
        v.clear();
        cout << message;
        takeInput(buf);
        stop = 0; res = 0;
        while (buf[stop] == ' ') stop++;
        while(stop != buf.size()+1 and v.size() < sz)
        {
            if (max.size() == 1) {
                res = takeNum(min, max[0], buf, stop, &stop);
            }
            else res = takeNum(min, max[v.size()], buf, stop, &stop);
            if (res == -1) break;
            v.push_back(res);
        }
        if (res == -1) continue;
        if (v.size() < sz) {
            cout << "Too few elements, please try again.\n";
            continue;
        }
        toBreak = true;
        if (checkDoubles){
            for (u_int i = 0; i < v.size()-1; i++){
                for (u_int j = i+1; j < v.size(); j++){
                    if (v[i] == v[j]){
                        cout << "Repeating numbers are not allowed, please try again.\n";
                        toBreak = false;
                        break;
                    }
                }
                if (!toBreak) break;
            }
        }
    }
    return v;
}

long long takeNum(u_int min, u_int max, string& buf, const char* message){
    long long num = BAD_INPUT;
    do {
        cout << message;
        takeInput(buf);
        num = takeNum(min, max, buf);
    } while (num == BAD_INPUT);

    return num;
}

void calc_print(const char* message, set (*pf)(set&), set& s){
    cout << message << pf(s);
}

void calc_print(const char* message, set (*pf)(set&, set&), set& s1, set& s2){
    cout << message << pf(s1, s2);
}

void printMenu(){
    cout << "\tMENU";
    cout << "\n(1) Union";
    cout << "\n(2) Intersection";
    cout << "\n(3) Symmetric difference";
    cout << "\n(4) Complement";
    cout << "\n(5) Difference S1 \\ S2";
    cout << "\n(6) Difference S2 \\ S1";
    cout << "\n(7) Arithmetic sum";
    cout << "\n(8) Multiplication on number";
    cout << "\n(9) Multiplication of sets";
    cout << "\n(p) Raise to the power";
    cout << "\n(m) Print menu of operations";
    cout << "\n(u) Print universum";
    cout << "\n(s) Print current sets";
    cout << "\n(n) Choose new sets";
    cout << "\n(q) Quit program";
    cout << endl;
}
