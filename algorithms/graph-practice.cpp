#include "bits/stdc++.h"
#include "../util/util.h"
#include "../data-structures/disjoin-set.cpp"

using namespace std;

#define vectypes(T) typedef vector<T> V##T; typedef vector<V##T> VV##T;
typedef int I; vectypes(I);
typedef double D; vectypes(D);
typedef pair<int, int> II; vectypes(II);

struct Edge {
    int a, b, w;
};

bool compEdge(const Edge &lhs, const Edge &rhs) {
    return lhs.w < rhs.w;
}

class Graph {
    vector<vector<int>> adj;
    vector<vector<pair<int, int>>> w;
    vector<int> parent, level;
    vector<vector<int>> ancestors;
    vector<int>
    int t;
    vector<int> in, out;
    vector<int> v;

    graph(int n){
        adj.resize(n);
        w.resize(n);
        parent.resize(n, -1);
        level.resize(n, 0);
        ancestors.resize(n);
        t = 0;
        in.resize(n, numeric_limits<uint32_t>::max());
        out.resize(n, numeric_limits<uint32_t>::max());
        v.resize(n);
    }

    void dfs(int u);
}

void Graph::dfs(int src) {
    v[src] = true;
    in[src] = t++;
    for(int nbr: adj[src]) {
        if(!v[nbr]) {
            parent[nbr] = src;
            level[nbr] = level[src] + 1;
            dfs(nbr);
        }
    }
    out[src] = t++;
}