//
// Created by Shivanshu Gupta on 09/07/17.
//

#include "bits/stdc++.h"
#include "util.h"

void read_int(int &ret) {
    ret = 0;
    char c = gc();
    while(c != '-' && (c<'0' || c>'9')) c = gc();
    while(c>='0' && c<='9') {
        ret = (ret<<3) + (ret<<1) + c - '0';
        c = gc();
    }
}

void printVI(const VI &a) {
    for(int x : a) cout << x << '\t';
    cout << endl;
}
