//
// Created by Shivanshu Gupta on 12/02/20.
//
#include "bits/stdc++.h"

using namespace std;

/*
	BINARY SEARCH
	-	search for the first/last occurence of something.

	x is in the range [lo, hi] i.e. for N elements, [0, N-1]
	p - the predicate over which to search
	p(x) : int -> bool : F F F F....F F T T....T T T T

	Checking correctness:
	- 	check on both ranges [k, k] and [k, k+1]
	- 	if it works on these two ranges, it will work on every other range.

	Invariant if an ans exists: lo <= ans <= hi
*/
int last0(int l, int r, function<int(const int&)> p) {
    assert(l <= r);
    int lo = l, hi = r;
    while(l < r) {
        int m = l + ((r - l + 1) >> 1); // if you add 1 here
        if(!p(m)) l = m;
        else r = m - 1;                 // you subtract 1 here
    }
    if(p(r)) return lo - 1;     // p true for all i
    else return r;
}

int first1(int l, int r, function<bool(const int&)> p) {
    assert(l <= r);
    int lo = l, hi = r;
    while(l < r) {
        int m = l + ((r - l) >> 1); // if you don't add 1 here
        if(!p(m)) l = m + 1;        // you add 1 here
        else r = m;
    }
    if(!p(r)) return hi + 1;    // p false for all i
    else return r;
}

int main() {
    int t = 100;
    while(t--) {
        int n = rand() % 10 + 1;
        int c0 = rand() % (n + 1);
        vector<int> a(n);
        for(int i = 0; i < n; i++) {
            if(i >= c0) a[i] = 1;
            cout << a[i] << ' ';
        }
        cout << endl;
        int last = last0(0, n - 1, [a](const int &i){return a[i];});
        int first = first1(0, n - 1, [a](const int &i){return a[i];});
        cout << last << ' ' << first << endl;
        assert(c0 - 1 == last);
        assert(c0 == first);
    }
}