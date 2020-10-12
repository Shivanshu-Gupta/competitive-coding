// DINIC ALGORITHM for MAX FLOW
// Source:
// -    http://code-library.herokuapp.com/dinic-flow/c++
// -    max-flow.pdf
// Status: Tested

/**
 * Flow Update Options:
 * At any time, res[u][v] + flow[u][v] == cap[u][v] and res[u][v] >= 0
 * which also means that flow[u][v] <= cap[u][v]
 *
 * flow f:u->v update:
 * -   In terms of Residual Capacity:
 *     -   only if: res[u][v] >= f
 *     -   update: res[u][v] -= f, res[v][u] += f
 * -   In terms of Edge Flow:
 *     -   only if: flow[u][v] + f <= cap[u][v]
 *     -   update: flow[u][v] += f, flow[v][u] -= f
 *
 * final u->v flow = max(0, cap[u][v] - res[u][v]) = max(0, flow[u][v])
 *
 * Some Theorems:
 * Let Z = {v \in V s.t. v is reachable from saturated residual graph}
 * 1. Max-flow Min-cut Theorem: The maximum amount of flow passing from
 * the source to the sink is equal to the total weight of the edges in
 * the minimum cut, i.e. the smallest total weight of the edges which
 * if removed would disconnect the source from the sink.
 * Proof: Easy to show that every flow is smaller than every cut.
 *      To show that maximum flow is equal to the minimum cut, consider the
 *      cut (Z, V-Z). Every edge from Z to V-Z will have been saturated.
 *
 * 2. Menger's Theorem: The max number of edge-disjoint s-t paths is
 * equal to the min number of arcs whose removal disconnects t from s.
 * Proof: Special case of Max-Flow Min-Cut theorem.
 *
 * 3. Hall’s Theorem. Let G = (L ∪ R, E) be a bipartite graph with |L| = |R|.
 * Then, either
 * ■ 	(i) G either has a perfect matching, or
 * ■ 	(ii) There exists a subset X ⊆ L such that |N(X)| < |X|
 * where N(X) = set of nodes adjacent to nodes in X.
 * Proof: Construct the maximal matching M. Let U be the unmatched subset of L.
 *      Then A = Z-U is the set of matched vertices in L reachable from s.
 *      Claim 0: U ⊆ Z
 *      Claim 1: Any matched vertex of L will be in Z iff it's partner was in Z.
 *      Claim 2: No unmatched vertex of R will be in Z.
 *      Thus, Z = U ∪ A ∪ M(A), where M(A) is the set of partners of A.
 *      Let X = L ∩ Z = U ∪ A. Then N(X) = M(A).
 *      => |N(X)| = |M(A)| = |A| <= |U ∪ A| = |X|.
 *      Equality holds iff U is empty or M is a perfect match.
 *
 * 4. König-Egerváry Theorem:  In a bipartite, undirected graph, the sizes of
 * max matching and min vertex cover are equal.
 * Proof: Easy to show that every M is smaller than every VC.
 *      To show equality of max M and min VC, use the proof of Hall's theorem.
 *      and show that the set of vertices: K = M(A) ∪ (L-Z) is a vertex cover
 *      s.t. |K| = |M|.
 *      - K = {all the reachable vertices in R} ∪ {all unreachable vertices in L}
*/

#include "bits/stdc++.h"

#define fillv(v, x) fill((v).begin(), (v).end(), (x))

using namespace std;

#define vectypes(T) typedef vector<T> V##T; typedef vector<V##T> VV##T

typedef int I; vectypes(I);
typedef double D; vectypes(D);
typedef pair<int, int> II; vectypes(II);

struct MaxFlow {
    struct Edge {
        int to, rev;
        int cap, flow;
    };

	vector<vector<Edge>> res;
	VI level;       //!< Depth of a node in DFS/BFS tree (level[root] = 0)
	VI work;        //!< used in dinic_dfs() to keep track of next nbr to try from each node.
	VI Q;
	MaxFlow(int n) {
		res.resize(n);
		level.resize(n, -1);
		work.resize(n);
		Q.resize(n);
	}

	void addDirEdge(int x, int y, int c);
	void addEdge(int x, int y, int c);
	bool bfs(int src, int sink); 
	int dinic_dfs(int v1, int sink, int f);
	uint64_t dinic(int src, int sink);
};

/**
 * @brief Add directed edge and it's back edge to residual graph
 * 
 * @param x from
 * @param y to
 * @param c weight for weighted graph, forward capacity for residual graph.
 */
void MaxFlow::addDirEdge(int x, int y, int c) {
	Edge e1 = {y, (int)res[y].size(), c, 0};
	Edge e2 = {x, (int)res[x].size(), 0, 0};
	res[x].push_back(e1);
	res[y].push_back(e2);
}

/**
 * @brief Add bidirectional edge to residual graph
 * 
 * @param x from
 * @param y to
 * @param c weight for weighted graph, forward capacity for residual graph.
 */
void MaxFlow::addEdge(int x, int y, int c) {
	Edge e1 = {y, (int)res[y].size(), c, 0};
	Edge e2 = {x, (int)res[x].size(), c, 0};
	res[x].push_back(e1);
	res[y].push_back(e2);
}

/**
 * @brief BFS on residual graph.
 * @details BFS on residual graph for use in Dinic algorithm to generate 
 * the level graph.
 * Requires the residual graph to be represented as an adjacency list 
 * with pointers to reverse edge.
 * 
 * @param src 	Source Vertex
 * @param sink 	Destination Vertex
 *
 * @return 	reachability of sink from src.
 */

bool MaxFlow::bfs(int src, int sink) {
	level[src] = 0;
	if(src == sink) return true;
	int qt = 0, qh = 0;
	Q[qt++] = src;
	while(qh < qt) {
		int v1 = Q[qh++];
		for(Edge e : res[v1]) {
			int v2 = e.to;
			if(level[e.to] >= 0 || e.flow >= e.cap) continue;
			level[v2] = level[v1] + 1;
			if(v2 == sink) return true;
			else Q[qt++] = v2;
		}
	}
	return false;   
}

/**
 * @brief DFS on level graph.
 * @details Recursive DFS on level graphs for use in Dinic algorithm,
 * to repeatedly find src-sink paths following the generation of the 
 * level graph using BFS.
 * Requires the residual graph to be represented as an adjacency list 
 * with pointers to reverse edge.
 * 
 * @param src 	Source Vertex
 * @param sink 	Destination Vertex
 * @param f		Capacity of the currently explored path.
 * 
 * @return 	Capacity of the newly discovered src-sink path.
 */
int MaxFlow::dinic_dfs(int v1, int sink, int f) {
	if(v1 == sink) return f;
	else if(level[v1] >= level[sink]) return 0;
	for(int &i = work[v1]; i < res[v1].size(); i++) {
		Edge &e = res[v1][i];
		int v2 = e.to;
		if(e.flow >= e.cap || level[v2] != level[v1] + 1)
			continue;
		if(int df = dinic_dfs(v2, sink, min(f, e.cap - e.flow))) {
			e.flow += df;
			res[v2][e.rev].flow -= df;
			return df;
		}
	}
	return 0;
}

/**
 * @brief Dinic Algorithm
 * @details An implementation of the Dinic algorithm to find the Maximum Flow
 * from src to sink in a directed graph. Uses BFS to get the level graph and 
 * then uses DFS to find multiple augmenting paths.
 * 
 * @param src 	Source Vertex
 * @param sink 	Sink Vertex
 * 
 * @return 	Maximum src-sink flow.
 */
uint64_t MaxFlow::dinic(int src, int sink) {
    uint64_t maxFlow = 0;
    while(bfs(src, sink)) {
    	fillv(work, 0);
        while(int df = dinic_dfs(src, sink, INT_MAX))
        	maxFlow += df;
        fillv(level, -1);
    }
    return maxFlow;
}

void dinicTest() {
    ios::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    MaxFlow g(n);
    for(int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        if(a != b) {
            g.addEdge(a-1, b-1, c);
        } 
    }
    uint64_t maxFlow = g.dinic(0, n-1);
    cout << maxFlow << endl;
}