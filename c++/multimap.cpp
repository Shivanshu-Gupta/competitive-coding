//
// Created by Shivanshu Gupta on 21/03/20.
//


#include <bits/stdc++.h>
#include <functional>

using namespace std;

void key_order() {
    multimap<int, int, less<int>> m0;           // keeps equivalent keys in insertion order
    multimap<int, int, less_equal<int>> m1;     // keeps equivalent keys in reverse insertion order
    multimap<int, int, greater<int>> m2;        // keeps equivalent keys in insertion order
    multimap<int, int, greater_equal<int>> m3;  // keeps equivalent keys in reverse insertion order
    for(int i = 0; i < 9; i++) {
        m0.insert({i/3, i});
        m1.insert({i/3, i});
        m2.insert({i/3, i});
        m3.insert({i/3, i});
    }
    for(auto p: m0) cout << p.first << ':' << p.second << ' ';      // 0:0 0:1 0:2 1:3 1:4 1:5 2:6 2:7 2:8
    cout << endl;
    for(auto p: m1) cout << p.first << ':' << p.second << ' ';      // 0:2 0:1 0:0 1:5 1:4 1:3 2:8 2:7 2:6
    cout << endl;
    for(auto p: m2) cout << p.first << ':' << p.second << ' ';      // 2:6 2:7 2:8 1:3 1:4 1:5 0:0 0:1 0:2
    cout << endl;
    for(auto p: m3) cout << p.first << ':' << p.second << ' ';      // 2:8 2:7 2:6 1:5 1:4 1:3 0:2 0:1 0:0
    cout << endl;
}



void bounds() {
    multimap<int, int, less<int>> m0;
    for(int i = 0; i < 9; i++) {
        m0.insert({i/3, i});
    }
    auto beg = m0.lower_bound(1);
    auto end = m0.upper_bound(1);
    for(auto it = beg; it != end; it++)
        cout << it->first << ':' << it->second << ' ';      // 1:3 1:4 1:5
    cout << endl;
}

int main() {

    return 0;
}
