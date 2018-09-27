#include "bits/stdc++.h"
using namespace std;

string manacher(string s) {
    int n = (s.length()<<1)|1;
    
    // add delimiters: bab -> $b$a$b$
    string y(n, '$');   
    for(int i = 0; i < s.length(); i++) {
        y[(i<<1)|1] = s[i];
    }
    
    // Algorithm similar to z-algorithm.
    vector<int> dp(n);  // dp[i] = k => y[i-k:i+k] is a palindrome
    int l = 0, r = 0;   // r = max(i+dp[i]) of all i seen till now.
    int maxlen = 0, maxidx;
    for(int i = 1; i < n; i++) {
        if(i < r) dp[i] = min(r-i, dp[l-(i-l)]);
        while(i-dp[i] > 0 && i+dp[i] < n-1 && y[i-dp[i]-1] == y[i+dp[i]+1]) {
            dp[i]++;
        }
        if(i+dp[i] > r) {
            l = i;
            r = i + dp[i];
        }
        if(dp[i] > maxlen) {
            maxlen = dp[i];
            maxidx = i;
        }
    }
    return s.substr(maxidx/2 - maxlen/2, maxlen);
}