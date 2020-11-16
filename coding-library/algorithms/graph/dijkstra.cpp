// DIJKSTRA ALGORITHM
// Status: Tested

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <unordered_map>
#include <utility>

#define MAX(type) numeric_limits<type>::max()
#define MIN(type) numeric_limits<type>::min()

using namespace std;

#define vectypes(T) typedef vector<T> V##T; typedef vector<V##T> VV##T

typedef int I; vectypes(I);
typedef double D; vectypes(D);
typedef pair<int, int> II; vectypes(II);


struct Dijkstra {
    struct Edge {
        int to, w;
    };

    vector<vector<Edge>> G;        //!< Weighted graph as adjacency list (used in Shortest Path Finding)
   
    // some data structures for storing information
    VI dist;        //!< dist[i] = shortest path from src to i.    (init: inf)
    VI prev;        //!< prev[i] = previous node on the shortest path from src.    (init: -1)
    Dijkstra(int n) {
        G.resize(n, vector<Edge>());
        dist.resize(n, INT_MIN);
        prev.resize(n, -1);
    }

    void addEdge(int x, int y, int w);
    void addDirEdge(int x, int y, int w);

    void djikstra_priority_queue(int src, int dest);
    void djikstra_set(int src, int dest);
    VI shortestPath(int src, int dest);
};

/**
 * @brief Add undirected edge to graph
 * 
 * @param x from
 * @param y to
 * @param w weight for weighted graph
 */
void Dijkstra::addEdge(int u, int v, int w) {
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
void Dijkstra::addDirEdge(int u, int v, int w) {
    G[u].push_back({v, w});
}


/**
 * @brief Dijkstra's algorithm
 * @details Implementation of Dijkstra's algorithm for single source 
 * shortest paths using priority queue.
 * -    Cannot handle negative edge weights.
 * -    Seems to be faster than set implementation -> prefer this.
 * -    Time Complexity: O(|V| + |E| log |V|)
 * 
 * @param src   Source Vertex
 */
void Dijkstra::djikstra_priority_queue(int src, int dest = -1) {
    fill(prev.begin(), prev.end(), -1);
    fill(dist.begin(), dist.end(), INT_MAX);
    
    dist[src] = 0;
    // use priority queue in which top element has the "smallest" 
    // priority i.e. distance in this case.
    priority_queue<II, VII, greater<II>> pq;
    pq.push({0, src});
    while(!pq.empty()) {
        II top = pq.top(); pq.pop();
        int v1 = top.second;
        // if v1's distance has been updated this entry can be ignored.
        if(top.first > dist[v1]) continue;
        if(v1 == dest) return;
        for(Edge e : G[v1]) {
            int v2 = e.to;
            if(dist[v2] > dist[v1] + e.w) {
                dist[v2] = dist[v1] + e.w;
                prev[v2] = v1;
                pq.push({dist[v2], v2});
            }
        }
    }
}

/**
 * @brief Dijkstra's algorithm
 * @details Implementation of Dijkstra's algorithm for single source 
 * shortest paths using set.
 * -    Cannot handle negative edge weights.
 * -    Unlike priority queue implementation it removes
 *      obsolete {node, dist} pairs, it seems to be slower.
 * -    Relies on the fact that set stores elements in sorted order
 * -    Time Complexity: O(|V| + |E| log |V|)
 * 
 * @param src   Source vertex
 */
void Dijkstra::djikstra_set(int src, int dest = -1) {
    fill(prev.begin(), prev.end(), -1);
    fill(dist.begin(), dist.end(), INT_MAX);
    dist[src] = 0;
    set<II> s;
    s.insert({0, src});
    while(!s.empty()) {
        II top = *(s.begin()); s.erase(s.begin());
        int v1 = top.second;
        // cout << v1 << dist[v1] << endl;
        if(v1 == dest) return;
        for(Edge e : G[v1]) {
            int v2 = e.to;
            if(dist[v2] > dist[v1] + e.w) {
                s.erase({dist[v2], v2});
                dist[v2] = dist[v1] + e.w;
                prev[v2] = v1;
                s.insert({dist[v2], v2});
            }
        }
    }
}

VI Dijkstra::shortestPath(int src, int dest) {
    djikstra_priority_queue(src, dest);
    VI path;
    int u = dest;
    while(prev[u] != -1) {
        path.push_back(u);
        u = prev[u];
    }
    path.push_back(u);
    reverse(path.begin(), path.end());
    return path;
}


// TEST CODE
// Test Problem: http://www.spoj.com/problems/SHPATH/
int djikstraTest()
{
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--) {
        unordered_map<string, int> cityid;
        int n; cin >> n;
        Dijkstra g(n);
        for(int i = 0; i < n ; i++) {
            string c; cin >> c;
            cityid[c] = i;
            int deg; cin >> deg;
            for(int j = 0 ; j < deg; j++) {
                int nbr, w;
                cin >> nbr >> w;
                g.addDirEdge(i, nbr-1, w);
            }
        }
        int r; cin >> r;
        while(r--) {
            string c1, c2;
            cin >> c1 >> c2;
            g.djikstra_priority_queue(cityid[c1], cityid[c2]);
            cout << g.dist[cityid[c2]] << endl;
        }
    }
    return 0;
}