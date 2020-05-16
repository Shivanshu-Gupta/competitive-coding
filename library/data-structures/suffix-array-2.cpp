/*
Ref: https://github.com/jaehyunp/stanfordacm/blob/master/code/SuffixArray.cc
Explanation: http://web.stanford.edu/class/cs97si/suffix-array.pdf
Complexity: O(nlog^2n)
Sample Problems:
-	Spoj			-	BEADS (minimum lexicographic rotation)
					-	MINMOVE (same as BEADS but req O(n))

- 	Hackerrank		-	how-many-substrings (# of unique substrings)
*/

// Suffix array construction in O(L log^2 L) time.  Routine for
// computing the length of the longest common prefix of any two
// suffixes in O(log L) time.
//
// INPUT:   string s
//
// OUTPUT:  array suffix[] such that suffix[i] = index (from 0 to L-1)
//          of substring s[i...L-1] in the list of sorted suffixes.
//          That is, if we take the inverse of the permutation suffix[],
//          we get the actual suffix array.

#include <cmath>
#include <vector>
#include <iostream>
#include <string>

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

void suffixArray2Test() {

	// bobocel is the 0'th suffix
	//  obocel is the 5'th suffix
	//   bocel is the 1'st suffix
	//    ocel is the 6'th suffix
	//     cel is the 2'nd suffix
	//      el is the 3'rd suffix
	//       l is the 4'th suffix
	SuffixArray suffix("bobocel");
	vector<int> v = suffix.GetRankArray();
	
	// Expected output: 0 5 1 6 2 3 4
	//                  2
	for (int i = 0; i < v.size(); i++) cout << v[i] << " ";
	cout << endl;
	cout << suffix.LongestCommonPrefix(0, 2) << endl;
}
