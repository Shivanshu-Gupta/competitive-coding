// Bellman Ford Algorithm
// Status: Tested

#include "../../util/util.h"

using namespace std;

#define vectypes(T) typedef vector<T> V##T; typedef vector<V##T> VV##T

typedef int I; vectypes(I);
typedef double D; vectypes(D);
typedef pair<int, int> II; vectypes(II);

const auto INF = INT64_MAX;

struct BellmanFord {

    struct Edge {
        int to, w;
    };

    vector<vector<Edge>> G;        //!< Weighted graph as adjacency list (used in Shortest Path Finding)
   
    // some data structures for storing information
    vector<int64_t> dist;   //!< dist[i] = shortest path from src to i.    (init: inf)
    VI prev;                //!< prev[i] = previous node on the shortest path from src.    (init: -1)
    VI Q;                   //!< Circular Queue for use in FIFO based Bellman Ford.

    BellmanFord(int n) {
        G.resize(n, vector<Edge>());
        dist.resize(n, INF);
        prev.resize(n, -1);
        Q.resize(n);
    }

    void addEdge(int x, int y, int w);
    void addDirEdge(int x, int y, int w);

    // 6. Shortest Path Finding Algorithms
    bool bellman_ford_dp(int src, vector<int64_t> &dist);
    bool bellman_ford_fifo(int src, vector<int64_t> &dist);
    VI findNegativeCycle();
};

/**
 * @brief Add undirected edge to graph
 * 
 * @param x from
 * @param y to
 * @param w weight for weighted graph
 */
void BellmanFord::addEdge(int u, int v, int w) {
    G[u].push_back({v, w});
    G[v].push_back({u, w});
}

/**
 * @brief Add directed edge to graph
 * 
 * @param x from
 * @param y to
 * @param w weight for weighted graph
 */
void BellmanFord::addDirEdge(int u, int v, int w) {
    G[u].push_back({v, w});
}

/**
 * @brief Bellman-Ford algorithm
 * @details DP-based Implementation of Bellman-Ford algorithm for single source 
 * shortest paths.
 * -    Can handle negative edge weights too.
 * -    Can detect and find negative cycle.
 * -    Time Complexity: O(|V||E|)
 * 
 * @param src   Source node
 * 
 * @return true if no negative cycle, false o.w.
 */
bool BellmanFord::bellman_ford_dp(int src, vector<int64_t> &dist) {
    auto n = G.size();
    fillv(dist, INF);
    dist[src] = 0;
    bool updated = false;
    for(int i = 0; i < n; i++) {
        updated = false;
        for(int v1 = 0; v1 < n; v1++) {
            if(dist[v1] == INF) continue;
            for(Edge e : G[v1]) {
                int v2 = e.to;
                if(dist[v2] > dist[v1] + e.w) {
                    dist[v2] = dist[v1] + e.w;
                    prev[v2] = v1;
                    updated = true;
                }
            }
        }
        if(!updated) 
            return true;
    }
    // if updated is true then a negative cycle exists
    return !updated;
}

/**
 * @brief Bellman-Ford algorithm
 * @details FIFO implementation of Bellman-Ford algorithm for single source 
 * shortest paths. 
 * -    https://cs.stackexchange.com/questions/2039/bellman-ford-variation
 * -    Can handle negative edge weights.
 * -    Doesn't work if negative cycles are present.
 *      -   Hack: There's a negative cycle if any vertex gets enqueued n times.
 *      -   Stops the moment a negative cycle is detected. 
 * -    Better than dp-based approach when there are no negative cycles as
 *      it checks edges from only those nodes whose dist has updated.
 * -    Time Complexity: O(|V||E|)
 * 
 * @param src   Source node
 */
bool BellmanFord::bellman_ford_fifo(int src, vector<int64_t> &dist) {
    int n = G.size();
    fill(dist.begin(), dist.end(), INF); // shortest distance
    VI inQueue(n, false);   // to ensure that any vertex gets enqued only once
    VI updateCount(n);      // for negative cycle detection hack
    int qt = 0, qh = 0;
    dist[src] = 0;
    Q[qt++] = src;
    updateCount[src]++;
    inQueue[src] = true;
    while((qh - qt) % n != 0) {
        int v1 = Q[qh++ % n];
        inQueue[v1] = false;
        for(Edge e : G[v1]) {
            int v2 = e.to;
            if(dist[v2] > dist[v1] + e.w) {
                dist[v2] = dist[v1] + e.w;
                prev[v2] = v1;
                if(!inQueue[v2]) {
                    Q[qt++ % n] = v2;
                    inQueue[v2] = true;
                }
                updateCount[v2]++;
                if(updateCount[v2] == n) return false;  // negative cycle
            }
        }
    }
    return true;
}

VI BellmanFord::findNegativeCycle() {
    int n = G.size();
    fill(dist.begin(), dist.end(), 0);      // initialize with 0's as we are interested only in negative length paths.
    int last;
    for(int i = 0; i < n; i++) {
        last = -1;
        for(int v1 = 0; v1 < n; v1++) {
            for(Edge e : G[v1]) {
                int v2 = e.to;
                if(dist[v2] > dist[v1] + e.w) {
                    dist[v2] = dist[v1] + e.w;
                    prev[v2] = v1;
                    last = v2;
                }
            }
        }
        if(last == -1) 
            return VI();
    }
    // if even on the nth iteration the distances change, then there's a negative cycle.
    // We can find it by going up the shortest path to the last updated vertex.
    VI cycle;
    // go up n times to ensure that last is a vertex on a cycle.
    for(int i = 0; i < n; i++) last = prev[last];
    // follow predecessors to get the cycle in reverse.
    int u = last;
    do {
        cycle.push_back(u);
        u = prev[u];
    } while(u != last);
    
    return cycle;
}


// TEST CODE
// Problem: http://www.spoj.com/problems/UCV2013B/
const int N = 100;
vector<string> monuments(N);
vector<vector<int64_t>> dists(N, vector<int64_t>());
vector<int> negCycle(N);

void bellmanFordTest() {
    ios::sync_with_stdio(false);
    int k = 1, n;
    while(1) {
        cin >> n;
        if(!n) break;
        fill(dists.begin(), dists.begin() + n, vector<int64_t>());
        fill(negCycle.begin(), negCycle.begin() + n, false);
        BellmanFord g(n);
        for(int i = 0; i < n ; i++) {
            string s; cin >> s;
            monuments[i] = s;
            for(int j = 0 ; j < n; j++) {
                int w; cin >> w;
                if(w) {
                    if(i != j || w < 0) g.addDirEdge(i, j, w);
                }
            }
        }
        cout << "Case #" << k << ':' << endl; k++;
        int q; cin >> q;
        while(q--) {
            int u, v;
            cin >> u >> v;
            if(dists[u].empty()) {
                dists[u].resize(n, INF);
                negCycle[u] = !g.bellman_ford_dp(u, dists[u]);
            }
            if(dists[u][v] == INF)
                    cout << monuments[u] << '-' << monuments[v] << " NOT REACHABLE" << endl;
            else if(negCycle[u])
                cout << "NEGATIVE CYCLE" << endl;
            else
                cout << monuments[u] << '-' << monuments[v] << " " << dists[u][v] << endl;
        }
    }
}