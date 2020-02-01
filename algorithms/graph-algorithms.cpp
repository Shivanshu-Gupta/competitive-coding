#include "bits/stdc++.h"
#include "../util/util.h"
#include "../data-structures/DisjointSet.cpp"

using namespace std;

struct Edge {
    int a, b, w;
};

bool compEdge(const Edge &lhs, const Edge &rhs) {
    return lhs.w < rhs.w;
}

struct Graph {
    VVI adj;                //!< adjacency list
    VVI revAdj;            //!< Reverse adjacency list for directed graphs (used in SCC Finding)
    VVII w;                //!< Weighted graph as adjacency list (used in Shortest Path Finding)

    vector<Edge> edges;    //!< list of edges (used in Kruskal)

    vector<unordered_map<int, int>> cap;    //!< Original graph capacities (used in Max-Flow).
    vector<unordered_map<int, int>> res;    //!< Residual graph capacities (used in Max-Flow).
    vector<unordered_map<int, int>> flow;   //!< Edge Flow (used in Max-Flow).

    // some data structures for storing information
    VI parent;              //!< Parent in DFS/BFS tree
    VI level;                //!< Depth of a node in DFS/BFS tree (level[root] = 0)
    VVI ancestor;            //!< Jump pointers to ancestors of node in DFS/BFS tree.
    //!<ancestor[i][j] = 2^jth ancestor of node i.
    vector<uint32_t> in;    //!< in[i] = time at which node i was visited in DFS/BFS (init:inf)
    vector<uint32_t> out;   //!< out[i] = time at which node i was exited in DFS/BFS (init:inf)
    vector<uint32_t> low;   //!< low[i] = lowest in-time among all nodes to which there's a
    //!< back-edges from subtree at node i. (init:inf) (used in Tarjan).

    // Variables for DFS/BFS
    VI v;        //!< Visited flag array
    VI s;        //!< Stack for DFS
    VI Q;        //!< Queue for BFS

    // Variables for Tarjan.
    unsigned int t = 0;                  //!< Time
    stack<II> tarjanStack;      //!< Stack of edges used in tarjan to find biconnected components.

    // Variables for Iterative DFS
    VI path;                    //!< used in DFS to keep track of path from root to current node.

    Graph(int n) {
        auto m = cap[0];
        auto x = max_element(m.begin(), m.end());

        adj.resize(n, VI());
        revAdj.resize(n, VI());
        w.resize(n, VII());
        cap.resize(n, unordered_map<int, int>());
        res.resize(n, unordered_map<int, int>());
        flow.resize(n, unordered_map<int, int>());

        v.resize(n);
        s.resize(n);
        Q.resize(n);
        parent.resize(n, -1);
        level.resize(n);
        ancestor.resize(n, VI());
        in.resize(n, UINT32_MAX);
        out.resize(n, UINT32_MAX);
        low.resize(n, UINT32_MAX);

        /*
            To reset these, as vectors for PDOs use contiguous mem, use the following:
                memset(&v[0], 0, sizeof(v[0]) * v.size());  // init:false
                memset(&in[0], 0xff, sizeof(in[0]) * in.size());    // init:inf
                memset(&parent[0], 0xff, sizeof(parent[0]) * parent.size());    // init:-1
            May also use fill(), which with -O3 is will be equivalent to above.
        */
    }

    void addEdge(int x, int y, int w);

    // 1. DFS, BFS Algorithms
    void dfs_iter(int src);
    void dfs_recur(int src, VI &exitOrder);
    void bfs(int src);

    // 8. Tree Algorithms
    int kA(int u, int k);
    int LCA(int u, int v);

    // 2. Topological Sort Finding Algorithms
    VI topSortDFS();
    VI topSort();

    // 3. Cut Vertex and Bridge Finding Algorithms
    void tarjan(int src, unordered_set<int> &aps, VII &bridges, VVII &BCCs);

    // 4. Biconnected and Strongly Connected components finding Algorithms.
    void BCC(VVII &BCCs);
    void kosaraju(VVI &SCCs);

    // 5. Minimum Spanning Tree Algorithms
    void kruskal(const int &n, vector<Edge> &mst);


    // 7. Max Flow
    bool flowBfs(int src, int sink);
    int edmonds_karp(int src, int sink);
};

/**
 * @brief Add edge to graph
 * 
 * @param x from
 * @param y to
 * @param c weight for weighted graph, forward capacity for residual graph.
 */
void Graph::addEdge(int u, int v, int c) {
    adj[u].push_back(v);
    revAdj[v].push_back(u);
    w[u].push_back({v, c});

    // For max-flow problems, add directed edge and it's back-edge.
    if (cap[u].find(v) == cap[u].end()) cap[u][v] = c;
    else cap[u][v] += c;
    // If doing in terms of residual capacity.
    if (res[u].find(v) == res[u].end()) res[u][v] = c;
    else res[u][v] += c;
    if (res[v].find(u) == res[u].end()) res[v][u] = 0;
    // If doing in terms of edge flow.
    if (flow[u].find(v) == flow[u].end()) flow[u][v] = 0;
    if (flow[v].find(u) == flow[v].end()) flow[v][u] = 0;
}

///////////////////////////////////////////////////////////////////////////////////
////////////////////////// DFS, BFS Algorithms  ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Depth First Search
 * @details Non-recursive implementation using stack
 * -    faster than recursive implementation.
 * -    can be used to get level, parent, and ancestor jump-pointers in DFS tree.
 * -    Time Complexity: O(|V|+|E|)
 * -    variables to reset: v, level, parent, ancestor, path
 * 
 * @param src   Source node
 */
void Graph::dfs_iter(int src) {
    int st = 0;
    s[st++] = src;
    while (st) {
        int curr = s[--st];
        v[curr] = true;

        // Backtrack to the parent.
        while (!path.empty() && path.back() != parent[curr]) path.pop_back();
        // Setup jump pointers to ancestors
        for(int i = 1; i <= path.size(); i<<=1)
            ancestor[curr].push_back(path[path.size() - i]);
        path.push_back(curr);

        for (int nbr : adj[curr]) {
            if (!v[nbr]) {
                parent[nbr] = curr;
                level[nbr] = level[curr] + 1;
                s[st++] = nbr;
            }
        }
    }
}

/**
 * @brief Depth First Search
 * @details Recursive implementation (using call stack)
 * -    can be used to get in-time, out-time, level, parent
 * 		and ancestor jump-pointers in DFS tree.
 * -    can be used to implement the Tarjan's algorithm.
 * -	can lead to Stack Overflow if height of the recursion 
 * 		tree gets too high.
 * -	Time Complexity: O(|V|+|E|)
 * -    variables to reset: v, in, out, level, parent, ancestor, path
 * 
 * @param src       Source node
 * @param exitOrder list of vertices in the order they were exited
 */
void Graph::dfs_recur(int src, VI &exitOrder) {
    if (v[src]) return;
    v[src] = true;
    in[src] = t++;

    // Setup jump pointers to ancestors
    for(int i = 1; i <= path.size(); i<<=1)
        ancestor[src].push_back(path[path.size() - i]);
    path.push_back(src);

    for (int nbr : adj[src]) {
        if (!v[nbr]) {
            parent[nbr] = src;
            level[nbr] = level[src] + 1;
            dfs_recur(nbr, exitOrder);
        }
    }
    out[src] = t++;
    path.pop_back();
    exitOrder.push_back(src);
}

/**
 * @brief Breadth First Search
 * @details
 * -    can be used to get level and parent in BFS tree.
 * Time Complexity: O(|V|+|E|)
 * -    variables to reset: level, parent
 * @param src   Source node
 */
void Graph::bfs(int src) {
    int qt = 0, qh = 0;
    v[src] = true;
    Q[qt++] = src;
    while (qh < qt) {
        int node = Q[qh++];
        for (int nbr : adj[node]) {
            if (v[src]) continue;
            v[src] = true;
            parent[nbr] = src;
            level[nbr] = level[src] + 1;
            Q[qt++] = nbr;
        }
    }
}

/**
 * @brief kth Ancestor
 * @details Finds kth ancestor of a node in a tree using jump pointers
 * to ancestors.
 * -	Time Complexity: <O(nlogn) preprocessing, O(logn) query>
 * 
 * @param u node whose ancestor is found.
 * @param k the distance of the ancestor form the node.
 * 
 * @return the kth ancestor
 */
int Graph::kA(int u, int k) {
    while (k) {
        int x = 31 - __builtin_clz(k);
        u = ancestor[u][x];
        k &= (~(1 << x));
    }
    return u;
}

/**
 * @brief Lowest Common Ancestor
 * @details Jump pointers/DP-based soltion for LCA.
 * -	first uses LA() to bring the nodes to same level.
 * -	Time Complexity: <O(nlogn) preprocessing, O(logn) query>
 * 
 * @param u first node 
 * @param v second node
 * 
 * @return Lowest common ancestor of u and v.
 */
int Graph::LCA(int u, int v) {
    // bring the nodes to same level.
    if (level[u] > level[v]) u = kA(u, level[u] - level[v]);
    else if (level[u] < level[v]) v = kA(v, level[v] - level[u]);;

    // find LCA
    int x = 0;
    while(u != v) {
        if((1 << (x+1)) > level[u] || ancestor[u][x+1] == ancestor[v][x+1]) {
            // if the (1 << (x+1))th ancestor doesn't exist or it's same then move to the (1 << x)th ancestor.
            u = ancestor[u][x];
            v = ancestor[v][x];
            x = 0;
        } else {
            // o.w. continue to the next ancestor in the jump pointers.
            x++;
        }
    }
    return u;

//    if (u == v) return u;
//    int x = 31 - __builtin_clz(level[u]);       // level[u] > 0 as o/w u = v = root
//    while (x >= 0) {
//        if (ancestor[u][x] != ancestor[v][x]) {
//            u = ancestor[u][x];
//            v = ancestor[v][x];
//            x = 31 - __builtin_clz(level[u]);
//        } else {
//            x--;
//        }
//    }
//    return parent[u];
}


/**
 * @brief Reverse Topological Sort
 * @details Uses recursive DFS to get reverse topological ordering 
 * of the vertices of a DAG.
 * -	Time Complexity: O(|V|+|E|)
 * 
 * @return topOrder   Topological order
 */
VI Graph::topSortDFS() {
    int n = adj.size();
    VI exitOrder;
    fill(v.begin(), v.end(), 0);
    for (int i = 0; i < n; i++) {
        if (!v[i]) dfs_recur(i, exitOrder);
    }
    VI topOrder(exitOrder.rbegin(), exitOrder.rend());  // top order is reverse of exit order
    return topOrder;
}

/**
 * @brief Topological Sort
 * @details Finds a topological ordering of vertices of a DAG using
 * BFS with queue holding vertices with 0 in-degree.
 * -    Time Complexity: O(|V|+|E|)
 * -    Can also be used to check if a directed graph is a DAG.
 *      Not DAG <=> queue empty before all vertices have been visited.
 * -    Lexicographically smallest/largest top. ordering may be
 *      obtained using a priority queue instead of a queue. 
 *      -   Time Complexity: O((|V|+|E|)log|V|)
 * 
 * @return topOrder   Topological order
 */
VI Graph::topSort() {
    int n = adj.size();
    VI topOrder;
    VI indeg(n, 0);
    for (int i = 0; i < n; i++) {
        for (int j : adj[i]) {
            indeg[j]++;
        }
        v[i] = false;
    }
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (indeg[i] == 0) {
            q.push(i);
            v[i] = true;
        }
    }
    while (!q.empty()) {
        int node = q.front(); q.pop();
        topOrder.push_back(node);
        for (int nbr : adj[node]) {
            if (!v[nbr]) {
                if (--indeg[nbr] == 0) {
                    q.push(nbr);
                    v[nbr] = true;
                }
            }
        }
    }
    return topOrder;
}


/**
 * @brief Tarjan's Algorithm
 * @details An implementation of the Tarjan's algorithm using recursive DFS.
 * -    applicable to undirected graphs.
 * -    can be used to find cut vertices (articulation points) and bridges
 * -    if no cut vertices are found => the graph is biconnected.
 * -    can be used to find biconnected components (subgraphs with no cut vertices)
 * -    https://www.hackerearth.com/practice/algorithms/graphs/biconnected-components/tutorial/
 * -    Time Complexity: O(|V|+|E|)
 * 
 * @param src       Source node
 * @param aps       set of articulation points / cut vertices
 * @param bridges   list of bridge edges
 * @param BCCs   list of biconnected components where each is a list of edges in that component.
 */
void Graph::tarjan(int src, unordered_set<int> &aps, VII &bridges, VVII &BCCs) {
    if (v[src]) return;
    v[src] = true;
    low[src] = in[src] = ++t;
    int nChild = 0;
    for (int nbr : adj[src]) {
        if (!v[nbr]) {
            // nbr is a child of src
            parent[nbr] = src;
            nChild++;
            tarjanStack.push({src, nbr});
            tarjan(nbr, aps, bridges, BCCs);
            if (low[nbr] < low[src]) low[src] = low[nbr];

            // Cut Vertex: iff src is root with more than 1 child
            // or it has a child s.t. low[child] >= in[src]
            if ((parent[src] == -1 && nChild > 1)
                || (parent[src] != -1 && low[nbr] >= in[src])) {
                aps.insert(src);

                // Cut vertices divide the graph into biconnected components.
                // Cut vertex found => new biconnected component
                vector<pair<int, int>> bcc;
                while (tarjanStack.top() != make_pair(src, nbr)) {
                    bcc.push_back(tarjanStack.top()); tarjanStack.pop();
                }
                bcc.push_back(tarjanStack.top()); tarjanStack.pop();
                BCCs.push_back(bcc);
            }

            // Bridge: iff low[nbr] > in[src]
            if (low[nbr] > in[src]) {
                bridges.push_back({src, nbr});
            }
        } else if (nbr != parent[src] && in[nbr] < low[src]) {
            // nbr is an ancestor of src, src has back-edge to nbr
            low[src] = in[nbr];
            tarjanStack.push({src, nbr});
        }
    }
}


/**
 * @brief Use Tarjan's algorithm to get Biconnected components in
 * the graph.
 * @details 
 * -    https://www.hackerearth.com/practice/algorithms/graphs/biconnected-components/tutorial/
 * -    Time Complexity: O(|V|+|E|)
 * 
 * @param BCCs   list of biconnected components where each is a list of edges in that component.
 */
void Graph::BCC(VVII &BCCs) {
    auto n = adj.size();
    unordered_set<int> aps;
    VII bridges;

    // reset variables for use in tarjan()
    fillv(in, UINT32_MAX);
    fillv(out, UINT32_MAX);
    fillv(parent, -1);

    t = 0;
    for (int i = 0; i < n; i++) {
        if (!v[i]) {
            tarjan(i, aps, bridges, BCCs);
            // Add any remaining biconnnected component.
            if (!tarjanStack.empty()) {
                VII bcc;
                while (!tarjanStack.empty()) {
                    bcc.push_back(tarjanStack.top()); tarjanStack.pop();
                }
                BCCs.push_back(bcc);
            }
        }
    }
}

/**
 * @brief Kosaraju's Algorithm 
 * @details Implementation of Kosaraju's Algo for SCCs of a directed graph.
 * SCCs form a DAG => DFS exits SCCs in reverse topological order.
 * 1.   Do DFS on the graph to get vertices in topological ordering.
 * 2.   Do DFS on the reverse graph (source <-> sink) in the topological
 * 		order. 
 * -    Each DFS will give a sink SCC in the reverse graph or a source SCC in the graph.
 * -    SCCs will be obtained in the topological order.
 * -    Time Complexity: O(|V|+|E|)
 * 
 * @param SCCs List of list of vertices in SCCs.
 */
void Graph::kosaraju(VVI &SCCs) {
    VI revTopOrder;
    topSortDFS(revTopOrder);
    memset(&v[0], 0, sizeof(v[0]) * v.size());

    // DFS on reverse graph in the reverse order of exit i.e. the topological order.
    stack<int> s;
    while (!revTopOrder.empty()) {
        int node = revTopOrder.back();
        revTopOrder.pop_back();
        if (v[node]) continue;

        // new strongly connected component.
        VI scc;
        s.push(node);
        while (!s.empty()) {
            node = s.top(); s.pop();
            v[node] = true;
            scc.push_back(node);
            for (int nbr : revAdj[node]) {
                if (!v[nbr]) {
                    s.push(nbr);
                }
            }
        }
        SCCs.push_back(scc);
    }
}


/**
 * @brief Kruskal's Algorithm
 * @details Implementation of the Kruskal's algorithms for finding 
 * the Minimum Spanning tree of the graph.
 * -    Time Complexity: O(|V|log|V| + |E|log|E|)
 * @param n     Number of vertices in the graph.
 * @param mst   List of edges forming the MST.
 */

void Graph::kruskal(const int &n, vector<Edge> &mst) {
    DisjointSet ds(n);
    sort(edges.begin(), edges.end(), compEdge);
    for (Edge e : edges) {
        if (ds.find(e.a) != ds.find(e.b)) {
            ds.merge(e.a, e.b);
            mst.push_back(e);
        }
    }
}

bool Graph::flowBfs(int src, int sink) {
    v[src] = true;
    if (src == sink) return true;
    int qt = 0, qh = 0;
    Q[qt++] = src;
    while (qh < qt) {
        int v1 = Q[qh++];
        for (II p : res[v1]) {
            int v2 = p.first;
            if (v[v2] || p.second <= 0) continue;
            v[v2] = true;
            parent[v2] = v1;
            level[v2] = level[v1] + 1;
            if (v2 == sink) return true;
            else Q[qt++] = v2;
        }
    }
    return false;
}

/**
 * @brief Edmonds Karp Algorithm
 * @details Ford Fulkerson Algorithm doesn't specify how to find the
 * augmenting path. The clever choices for augmenting path include:
 * 1. Sufficiently large capacity (capacity scaling) - O(E^2log(U))
 * 2. Fewest edges (shortest path) - Edmonds Karp
 * Edmonds Karp Algorithms is an implementation of the Ford 
 * Fulkerson Algo for finding the maximum flow in a graph using BFS
 * to find shortest unsaturated path.
 * -    https://www.topcoder.com/community/data-science/data-science-tutorials/maximum-flow-section-1/
 * -	Time Complexity - O(VE^2) 
 * 		- proof: http://www.cs.princeton.edu/~wayne/cs423/lectures/max-flow-4up.pdf
 * 		- O(mn) augmentations are necessary for some networks 
 * 		=> need faster augmentations
 * 			- Dinic Algorithm (O(EV^2))
 * 	Use either Dinic or Capcity Scaling.
 * @param src 	Source Vertex
 * @param sink 	Sink Vertex
 * 
 * @return the maximum flow possible.
 */
int Graph::edmonds_karp(int src, int sink) {
    int maxFlow = 0;
    while (flowBfs(src, sink)) {
        int df = INT_MAX;
        for (int curr = sink; parent[curr] != -1; curr = parent[curr]) {
            int resf = cap[parent[curr]][curr] - flow[parent[curr]][curr];
            df = min(df, resf);
        }
        for (int curr = sink; parent[curr] != -1; curr = parent[curr]) {
            // flow f:u->v => res[u][v] >= f and res[u][v] -= f, res[v][u] += f
            flow[parent[curr]][curr] += df;
            flow[curr][parent[curr]] -= df;
        }
        maxFlow += df;
        fillv(v, 0);
        fillv(level, 0);
    }
    return maxFlow;
}


int biCompsTest() {
    ios::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    Graph g(n);
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        g.adj[a].push_back(b);
        g.adj[b].push_back(a);
    }
    VVII biComps;
    g.BCC(biComps);
    unordered_set<int> nodes;
    int nEven = 0, nOdd = 0;
    for (VII edges : biComps) {
        nodes.clear();
        for (II e : edges) {
            nodes.insert(e.first);
            nodes.insert(e.second);
        }
        if (nodes.size() % 2)
            nOdd++;
        else
            nEven++;
    }
    cout << nOdd << ' ' << nEven << endl;
    return 0;
}