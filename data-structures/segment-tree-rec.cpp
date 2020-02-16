/*
    Recursive implementation of sum based Segment Tree
    https://cp-algorithms.com/data_structures/segment_tree.html
    build - O(n)
    point modify - O(logn)
    interval modify - O(logn)
    sum - O(logn)
 */

#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

#define gc getchar_unlocked
#define DEBUG(x) cout << #x << " >> " << x << endl

using namespace std;
namespace segtreerec {
    const int N = 1000000;

// fast integer read
    void read_int(int &ret) {
        ret = 0;
        int sign = 1;
        char c = gc();
        while (c != '-' && (c < '0' || c > '9')) c = gc();
        if (c == '-') {
            sign = -1;
            c = gc();
        }
        while (c >= '0' && c <= '9') {
            ret = (ret << 3) + (ret << 1) + c - '0';
            c = gc();
        }
        ret *= sign;
    }

    int n;
    int a[N], s[4 * N] = {}, lazy[4 * N] = {};

    void build(int id = 1, int l = 0, int r = n) {
        if (r - l < 2) {           // l + 1 == r
            s[id] = a[l];
            return;
        }

        int mid = ((l + r) >> 1);
        build(id << 1, l, mid);
        build(id << 1 | 1, mid, r);

        s[id] = s[id << 1] + s[id << 1 | 1];
    }

// point modification
    void modify(int p, int x, int id = 1, int l = 0, int r = n) {
        s[id] += x - a[p];
        if (r - l < 2) {             // l == r - 1 = p
            a[p] = x;
            return;
        }

        int mid = ((l + r) >> 1);
        if (p < mid)
            modify(p, x, id << 1, l, mid);
        else
            modify(p, x, id << 1 | 1, mid, r);
    }

// int sum(int x, int y, int id=1, int l=0, int r=n) {
//     if(r<=x || y<=l) return 0;
//     if(x<=l && r<=y) return s[id];

//     int mid = ((l+r)>>1);
//     return sum(x,y,id<<1,l,mid) + sum(x,y,id<<1|1,mid,r);
// }

/*******************************lazy propagation methods*****************************/
    void shift(int id, int l, int r) {
        int mid = ((l + r) >> 1);

        //update left child
        lazy[id << 1] += lazy[id];
        s[id << 1] += (mid - l) * lazy[id];

        //update right child
        lazy[id << 1 | 1] += lazy[id];
        s[id << 1 | 1] += (r - mid) * lazy[id];

        lazy[id] = 0;
    }

// interval modification (increase in case of sum)
    void modify(int x, int y, int v, int id = 1, int l = 0, int r = n) {
        if (r <= x || y <= l) return;
        if (x <= l && r <= y) {
            lazy[id] += v;
            s[id] += (r - l) * v;
            return;
        }

        if (lazy[id]) shift(id, l, r);

        int mid = ((l + r) >> 1);
        modify(x, y, v, id << 1, l, mid);
        modify(x, y, v, id << 1 | 1, mid, r);
        s[id] = s[id << 1] + s[id << 1 | 1];
    }

// sum function with lazy propagation
    int sum(int x, int y, int id = 1, int l = 0, int r = n) {
        if (r <= x || y <= l) return 0;
        if (x <= l && r <= y) return s[id];

        if (lazy[id]) shift(id, l, r);

        int mid = ((l + r) >> 1);
        return sum(x, y, id << 1, l, mid) + sum(x, y, id << 1 | 1, mid, r);
    }
/************************************************************************************/

};

