/*
Implementation of Union Find / Disjoint Set data structure as described in [1].
- Tree based implementation
- Employs heuristics for speed up:
	- Union by Rank - where rank approximates the logarithm of the sub-tree size 
	and is also an upper bound on the height of the node
	- Path Compression

Sample Problems:
-	Hackerrank	-	maximum-cost-queries

[1] https://www.topcoder.com/community/data-science/data-science-tutorials/disjoint-set-data-structures/
*/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <utility>
#include <algorithm>

using namespace std;

/*

parent[x] = the parent of node x.
rank[x] = the rank of node x.
size[x] = the size of set with x.

CREATE-SET(x) 
	parent[x] = x
	rank[x] = 0
	size[x] = 1

MERGE-SETS(x, y) : merges trees containing x and y.
	PX = FIND-SET(X)
	PY = FIND-SET(Y)

	If (rank[PX] < rank[PY]): swap(PX, PY)
	parent[PY] = PX

	If (rank[PX] == rank[PY]) rank[PY] = rank[PY] + 1

FIND-SET(x) : returns the root of tree with x.
	If (x != parent[x]) parent[x] = FIND-SET(parent[X])
	Return parent[X]

 */

struct DisjointSet {
	vector<int> P, R, S;

	DisjointSet(int n) {
		P.resize(n);
		R.resize(n, 0);
		S.resize(n, 1);
		for(int i = 0; i < n; i++) {
			P[i] = i;
		}
	}

	int find(int x) {
		return (x == P[x]) ? x : P[x] = find(P[x]);
	}

	void merge(int x, int y) {
		int rootx = find(x), rooty = find(y);
		if(rootx == rooty) return;

		// make rootx the root with greater rank.
		if(R[rootx] < R[rooty]) swap(rootx, rooty);

		// make rootx the parent of rooty.
		P[rooty] = rootx;

		if(R[rootx] == R[rooty]) R[rootx]++; 

		S[rootx] += S[rooty];
	}
};




