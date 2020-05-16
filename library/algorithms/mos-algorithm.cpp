/**
 * Implementation of Mo's Algorithm
 *  - sqrt-decomposition based algorithm for range queries
 *  - basically answer the queries **offline** in a special order.
 *  - Restrictions
 *      - cannot use online where the queries need to be answered in fixed order.
 *      - cannot use this when there are update operations.
 *      - need to be able to write the functions add() and remove()
 *  - https://blog.anudeep2011.com/mos-algorithm/ - good explanation of  algorithm
 *  - https://www.hackerrank.com/topics/mos-algorithm - Different applications of sqrt decompositions
 *  - Time Complexity: O((N+M)√N) where M = #queries.
 */

#include "bits/stdc++.h"
// #define DEBUG
#define gc() getchar_unlocked()
using namespace std;

class MosAlgorithm {
    struct Query {
        int idx;
        int l, r;
        int block;
    };

    static bool comp(const Query &lhs, const Query &rhs) {
        if(lhs.block != rhs.block) return lhs.block < rhs.block;
        else return lhs.r < rhs.r;
    }

    static const int N = 3 * 1E5;
    static const int M = 2 * 1E5;
    int freq[int(1E6 + 1)];
    int a[N], ans[M];
    Query queries[M];

    void add(int pos, int &currAns) {
        if(!freq[a[pos]]) currAns++;
        freq[a[pos]]++;
    }

    void remove(int pos, int &currAns) {
        freq[a[pos]]--;
        if(!freq[a[pos]]) currAns--;
    }

    /**
     * Mo's Algorithm
     * - Assumes that query range is [l, r)
     * - Trivial to modify for [l, r]
     * @param m     number of queries
     */
    void processQueries(int m) {
        sort(queries, queries + m, comp);
        int currL = 0, currR = 0, currAns = 0;
        for(int i = 0; i < m; i++) {
            Query &q = queries[i];
            // always do the adds before removes (http://codeforces.com/blog/entry/46399?#comment-308528)
            while(currL > q.l) add(--currL, currAns);
            while(currR < q.r) add(currR++, currAns);
            while(currL < q.l) remove(currL++, currAns);
            while(currR > q.r) remove(--currR, currAns);
            ans[q.idx] = currAns;
        }
    }

    void read_int(int &ret) {
        ret = 0;
        char ch = gc();
        while(ch >= '0' && ch <= '9') {
            ret = (ret << 3) + (ret << 1) + ch - '0';
            ch = gc();
        }
    }

    int test() {
        int n; read_int(n);
        for(int i = 0; i < n; i++)
            read_int(a[i]);
        int m; read_int(m);

        int B = ceil(sqrt(n));
        for(int i = 0; i < m; i++) {
            Query &q = queries[i];
            q.idx = i;
            read_int(q.l); read_int(q.r);
            q.l--; q.r--;
            q.block = q.l / B;
        }
        processQueries(m);
        for(int i = 0; i < m; i++) {
            printf("%d\n", ans[i]);
        }
        return 0;
    }
};
