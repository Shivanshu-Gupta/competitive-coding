#include <iostream>
#include <string>
#include <vector>
using namespace std;

/**********************************************************************************************
Z Algorithm
- Fundamental preprocessing based string matching algorithm.
- If m = pattern length, n = text length, k = |Σ|
    - Time complexity:
        - Preprcessing time: O(m+n)
        - Searching time: O(n).
    - Space complexity: O(m+n).
- alphabet-independent - need not be finite.
- Useful for a single (pattern, text) pair as preprocessing time depends on n (unlike KMP).
- http://code-library.herokuapp.com/z-function/java
************************************************************************************************/

// z[i] = lcp(s[0:], s[i:])
vector<int> zFunction(string &s) {
    int n = s.length();
    vector<int> z(n);
//    z[0] = n;
    int l = 0, r = 0;   // r = max(i + z[i]) for all i seen till now.
    for(int i = 1; i < n; i++) {
        if(i < r) z[i] = min(r-i, z[i-l]);
        while(i+z[i] < n && s[z[i]] == s[i+z[i]]) z[i]++;
        if(i+z[i] > r) {
            l = i;
            r = i+z[i];
        }
    }
    return z;
}

int findZ(string &s, string &pattern) {
    string str = pattern + "$" + s;
    vector<int> z = zFunction(str);
    for (int i = pattern.length() + 1; i < z.size(); i++)
        if (z[i] == pattern.length())
            return i - pattern.length() - 1;
    return -1;
}

/**********************************************************************************************
KMP
- Searches for the string w in the string s (of length k). Returns the
 0-based index of the first match (k if no match is found).
- If m = pattern length, n = text length, k = |Σ|
    - Time complexity:
        - Preprcessing time: O(m)
        - Searching time: O(n).
    - Space complexity: O(m).
- Useful to search single pattern against multiple texts.
************************************************************************************************/

/*
A suffix of w[:i-1] that is also prefix of w will be called a suffix/prefix
of w[:i-1].

f[i] = length of largest suffix/prefix of w[:i-1] (OTHER than w[:i-1] itself).
By above defn, f[f[i]] = length of 2nd largest proper suffix/prefixx of w[:i-1].

If there exists a suffix/prefix of w[:i-2] that when extended by w[i-1] forms a suffix/prefix of w[:i-1],
        f[i] = 1 + (length of LARGEST such suffix/prefix of w[:i-2])
Else,
        f[i] = 0
*/
void FailureFunction(string &w, vector<int> &f) {
    f.resize(w.length() + 1);
    f[0] = -1;
    f[1] = 0;

    int i = 2, j = f[i - 1];

    while(i <= w.length()) {
        if(w[i-1] == w[j]) {
            f[i] = j+1; i++; j++;
        } else if(j > 0) {
            // try the next largest suffix/prefix of w[:i-2].
            j = f[j];
        } else {
            // w[:i-1] has no suffix/prefix.
            f[i] = 0; i++;
        }
    }
    for(int i = 0; i < w.length(); i++) {
        cout<<w[i]<<'\t'<<f[i]<<endl;
    }
}

int findKMP(string &s, string &w) {
    // m: pos of current partial match.
    // i: length of current partial match.
    int m = 0, i = 0;
    vector<int> f;
    FailureFunction(w, f);
    while(m + i < s.length()) {
        if(s[m+i] == w[i]) {
            i++;
            if(i == w.length()) {
                // match found.
                return m;

                // to continue looking:
                m += i - f[i];
                i = f[i];
            }
        } else {
            // as f[0] = -1, if i = 0, we'll just advance m.
            m += i - f[i];
            if(i > 0) i = f[i];
        }
    }
    return -1;
}

/**********************************************************************************************
Tests
**********************************************************************************************/
void getRandomstring(string &s) {
    for (int i = 0; i < s.length(); i++)
        s[i] = 'a' + rand() % 3;
}

// random tests
void test() {
    srand(121321);
    for (int step = 0; step < 1000000; step++) {
        string s(100, '\0'); getRandomstring(s);
        string pattern(5, '\0'); getRandomstring(pattern);
        // cout << s << ' ' << pattern << endl;
        int pos1 = s.find(pattern);
        int pos2 = findZ(s, pattern);
        int pos3 = findKMP(s, pattern);
        // cout << pos1 << ' ' << pos2 << endl;
        assert(pos1 == pos2);
    }
}