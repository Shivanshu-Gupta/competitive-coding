#include <bits/stdc++.h>

using namespace std;

struct myTuple {  
    int origIdx;   // stores original index of suffix  
    int firstHalf;       // store rank for first half of suffix  
    int secondHalf;      // store rank for second half of suffix  
};

int cmp(myTuple a, myTuple b) {  
    if(a.firstHalf == b.firstHalf) return a.secondHalf < b.secondHalf;  
    else return a.firstHalf < b.firstHalf;  
}

struct SuffixArray {
    const int L;
    string s;
    vector<vector<int> > P;
    vector<myTuple> M;

    SuffixArray(const string &s) : L(s.length()), s(s), M(L) {
        P.resize(ceil(log2(L)) + 1, vector<int>(L, 0));
        
        for (int i = 0; i < L; i++) P[0][i] = int(s[i]);
        
        for (int cnt = 1, stp = 1; cnt < L; cnt *= 2, stp++) {
            for (int i = 0; i < L; i++) {
                M[i].firstHalf = P[stp - 1][i];
                M[i].secondHalf = i + cnt < L ? P[stp - 1][i + cnt] : -1;
                M[i].origIdx = i;
            }
            
            sort(M.begin(), M.end(), cmp);
            
            for (int i = 0; i < L; i++) 
                P[stp][M[i].origIdx] = (i > 0 && M[i].firstHalf == M[i-1].firstHalf && M[i].secondHalf == M[i-1].secondHalf) ? P[stp][M[i-1].origIdx] : i;
        }   
    }

    vector<int> GetRankArray() { return P.back(); }
    
    vector<int> GetSuffixArray() { 
        vector<int> v;
        for(int i = 0; i < L; ++i) v.push_back(M[i].origIdx);
        return v;
    }

    // returns the length of the longest common prefix of s[i...L-1] and s[j...L-1]
    int LongestCommonPrefix(int i, int j) {
        int len = 0;
        if (i == j) return L - i;
        for (int k = P.size() - 1; k >= 0 && i < L && j < L; k--) {
            if (P[k][i] == P[k][j]) {
                i += 1 << k;
                j += 1 << k;
                len += 1 << k;
            }
        }
        return len;
    }

    vector<int> GetLCPArray() {
        vector<int> lcp(L, 0);
        for(int i = 1; i < L; i++) {
            lcp[i] = LongestCommonPrefix(M[i].origIdx, M[i - 1].origIdx);
        }
        return lcp;
    }
};

int main() {
    string str;
    cin>>str;
    str += str;
    cout<<str;
    SuffixArray suffix(str);
    vector<int> sa = suffix.GetSuffixArray();
    for(auto s : sa) {
        cout<<s<<'\t'<<str.substr(s)<<endl;
    }
    cout<<str.substr(sa[0])<<endl;
}




