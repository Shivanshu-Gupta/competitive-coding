/*
    Fundamental preprocessing based string matching algorithm.
    -   O(n) time, O(n) space.
    -   alphabet-independent - need not be finite.
    -   Ref. http://code-library.herokuapp.com/z-function/java
*/

#include "bits/stdc++.h"
using namespace std;

// z[i] = lcp(s[0:], s[i:])
vector<int> zFunction(string &s) {
    int n = s.length();
    vector<int> z(n);
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

int find(string &s, string &pattern) {
    string str = pattern + "$" + s;
    vector<int> z = zFunction(str);
    for (int i = pattern.length() + 1; i < z.size(); i++)
        if (z[i] == pattern.length())
            return i - pattern.length() - 1;
    return -1;
}

void getRandomstring(string &s) {
    for (int i = 0; i < s.length(); i++)
        s[i] = 'a' + rand() % 3;
}

// random tests
void testZAlgorithm() {
    srand(121321);
    for (int step = 0; step < 1000000; step++) {
        string s(100, '\0'); getRandomstring(s);
        string pattern(5, '\0'); getRandomstring(pattern);
        // cout << s << ' ' << pattern << endl;
        int pos1 = find(s, pattern);
        int pos2 = s.find(pattern);
        // cout << pos1 << ' ' << pos2 << endl;
        assert(pos1 == pos2);
    }
}