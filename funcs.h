#pragma once
#ifndef DM_LAB1_FUNCS_H
#define DM_LAB1_FUNCS_H

#include <iostream>
#include <cctype>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

vector<u_int> generateVector(u_int min, u_int max, u_int len, bool IsDistinctNums = true);

struct Pair{
    typedef u_int value_type;
    value_type elem;
    value_type mult;
    Pair(value_type a, value_type b): elem(a), mult(b){}
    Pair(const Pair&) = default;
    Pair(Pair&&) = default;
    Pair& operator=(const Pair&) = default;
    Pair& operator=(Pair&&) = default;
    Pair(): elem(0), mult(0){}
    bool operator!=(const Pair& pair) const {return !((elem == pair.elem) && (mult == pair.mult));}
};

const Pair inf{std::numeric_limits<Pair::value_type>::max(), 0};

typedef vector<Pair> set;
extern set unvr;
//кратности элементов мультимножества не превосходят кратностей соответствующих элементов в универсуме
//пустое множество - у всех элементов кратность равна нулю, а элементы такие же как и в универсуме
set empty_set(); //возвращает пустое множество
set create_set(size_t sz, vector<Pair::value_type>&& elems, vector<Pair::value_type>&& mults);
set calc_union(set&, set&);
set calc_intersect(set&, set&) ;
set calc_complement(set& s);
set calc_symdif(set& s1, set& s2);
set calc_dif(set& s1, set& s2);
set multiply(set&, set&);
set pow_set(u_int p, set& s);
set multiply(set& s, u_int n);
set calc_sum(set& s1, set& s2);
void clean(set& s);
ostream& operator<<(ostream& os, const set& s);

vector<u_int> generateMults(const vector<u_int>& maxs, const vector<u_int>& elems);

#endif //DM_LAB1_FUNCS_H
