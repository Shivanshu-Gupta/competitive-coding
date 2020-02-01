/*
    Fast and efficient, non-recursive implementation
    ref: http://codeforces.com/blog/entry/18051
    build - O(n)
    point modification - O(logn)
    sum - O(logn)
*/

#include <iostream>
#include <cstdio>
#include <limits.h>


#define gc getchar_unlocked;

using namespace std;

namespace segtreeiter{
    long N = 1<<9;
    int n;
    int *T;

    int max (int x, int y) {
        return x > y ? x : y;
    }

    int sum(int x, int y) {
        return x+y;
    }

    int combine(const int& x, const int& y) {
        return sum(x, y);
    }

// build the tree
    void build() {
        for(int i = n-1; i>0; i--) {
            // V[i] = V[i<<1] + V[i<<1|1];
            T[i] = combine(T[i<<1], T[i<<1|1]);
        }
    }

// modify single element at position p
    void modify(int p, int val) {
        for(T[p += n] = val; p>1; p>>=1) {
            T[p>>1] = combine(T[p], T[p^1]);
        }
    }

// query on interval [l, r)]
    int query(int l, int r) {  // max on interval [l, r)
        // works only with commutative functions. eg: sum, max, min
        /*int res = 0;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l&1) res += V[l++];
            if (r&1) res += V[--r];
            // if (l&1) res = max(res, V[l++]);
            // if (r&1) res = max(res, V[--r]);
        }
        return res;*/

        int resl = 0, resr = 0;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l&1) resl = combine(resl, T[l++]);
            if (r&1) resr = combine(T[--r], resr);
        }
        return combine(resl, resr);
    }

/********************************************************************************************/
// REVERSED OPERATIONS

/*
    modify the interval [l, r) of elements
    eg: increment each by val for a sum based tree
*/
    void modify(int l, int r, int val) {
        for(l+=n, r+=n; l<r; l >>= 1, r >>= 1) {
            if(l&1) T[l++] += val;
            if(r&1) T[--r] += val;
        }
    }

// query for single element at position p
    int query(int p) {
        int res = 0;

        // need to get value all the way from the root
        // as there might have been modifications.
        for (p += n; p > 0; p >>= 1) {
            res += T[p];
        }

        return res;
    }

// push : used to update the array elements, before reading the array.
    void push() {
        for (int i = 1; i < n; ++i) {
            T[i<<1] += T[i];
            T[i<<1|1] += T[i];
            T[i] = 0;
        }
    }
/* NOTE: Above code above works only in case the order of modifications on a single element
doesn't affect the result.
Assignment, for example, doesn't satisfy this condition. Lazy Propagation is required for it.*/
/********************************************************************************************/

    void print() {
        if(!(n & (n-1))) {                      // check if n is power of 2
            //printing as tree is useful only if n is a power of 2.
            for(int i=0; i<2*n; i++) {
                cout<<T[i]<<' ';
                if ( !(i+1 & (i)) ) {           // check if i+1 is power of 2
                    cout<<endl;
                }
            }
        } else {
            for(int i=0; i<2*n; i++) {
                cout<<T[i]<<' ';
            }
            cout<<endl;
        }
    }

    void segmentTreeIterTest() {
        cin >> n;
        T = new int[2*n];
        for(int i=0; i<n ; i++) {
            cin >> T[n+i];
        }

        //build
        build();
        print();

        // int pos, val;
        // cin>>pos>>val;
        // modify(pos, val);
        // print();

        int l, r;
        cin>>l>>r;
        cout<<query(l,r)<<'\n';
    }
};

