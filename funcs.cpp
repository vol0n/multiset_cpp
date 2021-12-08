//
// Created by Арсений Волынец on 21.09.2020.
//

#include "funcs.h"
#include <algorithm>
#include <cstdlib>

using namespace std;
extern u_int len_of_code;


inline u_int graencode(u_int g){
    return g ^ (g >> 1);
}


string tobin(u_int num){
    string s(len_of_code, '0');
    for (int i= len_of_code-1; i>=0; --i)
    {
        s[len_of_code-1-i] = '0' + ((num>>i)&1);
    }
    return s;
}


bool binarySearch(vector<u_int>& v, long long l, long long r, u_int x)
{
    if (r >= l) {
        int mid = l + (r - l) / 2;

        if (v[mid] == x)
            return true;

        if (v[mid] > x)
            return binarySearch(v, l, mid - 1, x);

        return binarySearch(v, mid + 1, r, x);
    }

    return false;
}


vector<u_int> generateVector(u_int min, u_int max, u_int len, bool IsDistinctNums)
{
    if (min >= max) return vector<u_int>(len, max);
    vector<u_int> v;
    assert(max != numeric_limits<Pair::value_type>::max());
    v.assign(len, numeric_limits<Pair::value_type>::max());
    for (long long i = 0; i < len; ){
        u_int elem = min + rand() % (max+1);
        //Если хотим чтобы не было повторяющихся чисел
        if (IsDistinctNums) {
            do {
                elem = min + rand() % (max+1);
            } while (binarySearch(v, 0, i, elem));
        }
        long long j = i-1;
        while (j > -1 and elem < v[j]){
            v[j+1] = v[j];
            j--;
        }
        v[j+1] = elem;
        i++;
    }
    return v;
}


vector<u_int> generateMults(const vector<u_int>& maxs, const vector<u_int>& elems){
    vector<u_int> res;
    for (size_t i = 0; i < elems.size(); i++){
        res.push_back(1 + rand() % maxs[elems[i]]);
    }
    return res;
}


set empty_set(){
    set res;
    u_int i = 0;
    for (; i < unvr.size(); i++)
        res.emplace_back(i, 0);
    return res;
}

set create_set(size_t sz, vector<Pair::value_type>&& elems, vector<Pair::value_type>&& mults){
    set res;
    if (sz)
        transform(elems.begin(), elems.begin()+sz, mults.begin(), back_inserter(res),
                [](u_int el, u_int mul){return Pair(el, mul);});
    else res = empty_set();
    return res;
}

template<class Fun>
set calc_max(set& lhs, set& rhs, Fun f){
    set res;
    lhs.push_back(inf); rhs.push_back(inf);
    Pair::value_type i = 0, j = 0;
    do{
        if (lhs[i].elem == rhs[j].elem){
            f(lhs, i, rhs, j, res);
            ++i;
            ++j;
        }
        else if (lhs[i].elem > rhs[j].elem) {
            res.emplace_back(rhs[j].elem, rhs[j].mult);
            ++j;
        }
        else {
            res.emplace_back(lhs[i].elem, lhs[i].mult);
            ++i;
        }
    }while (i < lhs.size()-1 || j < rhs.size()-1);
    lhs.pop_back(); rhs.pop_back();

    return res;
}

set calc_union(set& lhs, set& rhs){
    set res = calc_max(lhs, rhs, [](set& l, u_int i, set& r, u_int j, set& re){
        re.emplace_back(l[i].elem, max(l[i].mult, r[j].mult));
    });
    return res;
}

template<class Fun>
set calc_min(set& lhs, set& rhs, Fun fun){
    Pair::value_type i = 0, j = 0;
    set res;
    do{
        if (lhs[i].elem == rhs[j].elem){
            fun(lhs, i, rhs, j, res);
            ++i;
            ++j;
        }
        else if (lhs[i].elem > rhs[j].elem)
            ++j;
        else
            ++i;
    }while((i != lhs.size()) && (j != rhs.size()));
    if (res.empty()) res = empty_set();
    return res;
}


set calc_intersect(set& lhs, set& rhs){
    return calc_min(lhs, rhs, [](set& l, u_int i, set& r, u_int j, set& re){
        re.emplace_back(l[i].elem, min(l[i].mult, r[j].mult));
    });
}


set calc_complement(set& s){
    set res;
    size_t sz = unvr.size(), i = 0, j = 0;
    res.reserve(sz);
    for (; i < unvr.size(); i++){
        if (unvr[i].elem != s[j].elem){
            res.emplace_back(i, unvr[i].mult);
        }
        else {
            if (unvr[i].mult != s[j].mult)
                res.emplace_back(i, unvr[i].mult - s[j].mult);
            ++j;
        }
    }
    res.shrink_to_fit();

    return res;
}


set calc_symdif(set& lhs, set& rhs){
    auto f = [](set& l, u_int i, set& r, u_int j, set& result){
         if (l[i].mult != r[j].mult) {
             result.emplace_back(l[i].elem, max(l[i].mult, r[j].mult) - min(l[i].mult, r[j].mult));
         }
    };
    set res = calc_max(lhs, rhs, f);
    return res;
}


set calc_dif(set& lhs, set& rhs){
    Pair::value_type i = 0, j = 0;
    set res;
    lhs.push_back(inf); rhs.push_back(inf);
    do{
        if (lhs[i].elem == rhs[j].elem){
            if (lhs[i].mult > rhs[j].mult) {
                res.emplace_back(lhs[i].elem, lhs[i].mult - rhs[j].mult);
            }
            ++i;
            ++j;
        }
        else if (lhs[i].elem > rhs[j].elem)
            ++j;
        else {
            res.push_back(lhs[i]);
            ++i;
        }
    }while(i != lhs.size());
    lhs.pop_back(); rhs.pop_back();
    if (res.empty()) res = empty_set();
    return res;
}


set pow_set(u_int p, set& s) {
    set res;
    for (auto&& i: s)
        res.emplace_back(i.elem, min(unvr[i.elem].mult, (u_int)pow(i.mult, p)));
    return res;
}


set multiply(set& lhs, set& rhs){
    auto f =[](set& l, u_int i, set& r, u_int j, set& re){
        re.emplace_back(l[i].elem, min(l[i].mult*r[j].mult, unvr[l[i].elem].mult));
    };
    return calc_min(lhs, rhs, f);
}


set multiply(set& s, u_int p){
    set res;
    for (auto&& i : s)
        res.emplace_back(i.elem, min(unvr[i.elem].mult, i.mult*p));
    return res;
}


set calc_sum(set& lhs, set& rhs){
    set res =  calc_max(lhs, rhs,
        [](set& l, u_int i, set& r, u_int j, set& re)
        {re.emplace_back(l[i].elem, min(l[i].mult+r[j].mult, unvr[l[i].elem].mult));});
    return res;
}


ostream& operator<<(ostream& os, const set& s){
    set tmp;
    if (!s.empty()) tmp = s;
    clean(tmp);
    os << "\n";
    if (tmp.empty()){
        os << "\t\tEmpty set" << endl;
        return os;
    }
    for (auto&& i : tmp)
        os << "\t\tNo. " << i.elem << " " << tobin(graencode(i.elem)) << " mult: " << i.mult << endl;
    return os;
}


void clean(set& s){
    s.erase(remove_if(s.begin(), s.end(), [](Pair& p){return (p.mult == 0);}), s.end());
}
