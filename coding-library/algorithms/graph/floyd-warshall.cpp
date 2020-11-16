#include <iostream>
#include <vector>
#include <set>
#include <utility>

#define MAX(type) numeric_limits<type>::max()
#define MIN(type) numeric_limits<type>::min()

using namespace std;

#define vectypes(T) typedef vector<T> V##T; typedef vector<V##T> VV##T

typedef int I; vectypes(I);
typedef double D; vectypes(D);
typedef pair<int, int> II; vectypes(II);

struct WeightedEdge {
    int to, w;
};

struct FloydWarshall {
    vector<vector<WeightedEdge>> G;        //!< Weighted graph as adjacency list (used in Shortest Path Finding)
   
    FloydWarshall(int n) {
        G.resize(n, vector<WeightedEdge>());
    }

    void addEdge(int x, int y, int w);
    void addDirEdge(int x, int y, int w);

    // 6. Shortest Path Finding Algorithms
    void floyd_warshall(VVI &dists);
};

/**
 * @brief Floyd-Warshall algorithm
 * @details Implementation of Floyd-Warshall algorithm for all-pairs 
 * shortest paths.
 * -    Can handle negative edge weights too.
 * -    Can detect negative cycles.
 * -    Time Complexity: O(|V|^3)
 * 
 * @param dist  dist[i][j] = distance of node i from node j
 */
void FloydWarshall::floyd_warshall(VVI &dist) {
    int n = G.size();
    dist = VVI(n, VI(n, MAX(int)));
    for(int v1 = 0; v1 < n; v1++) {
        dist[v1][v1] = 0;
        for(WeightedEdge e : G[v1])
            dist[v1][e.to] = e.w;
    }
    for(int k = 0; k < n; k++){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(dist[i][k] == MAX(int) || dist[k][j] == MAX(int)) continue;
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}

void floydWarshallTest() {
    ios::sync_with_stdio(false);
    int n, m;
    // TODO: add test code
}