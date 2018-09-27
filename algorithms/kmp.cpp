/*
Searches for the string w in the string s (of length k). Returns the
0-based index of the first match (k if no match is found). Algorithm
runs in O(k) time.
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

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

int KMP(string &s, string &w) {
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
    return s.length();
}

void KMPTest()
{
    string s, w;
    cin>>s>>w;
    int pos = KMP(s, w);
    cout<<pos<<' '<<s.substr(pos, w.length())<<'='<<w<<endl;
}
