// SUCCESSIVE SHORTEST PATH ALGORITHM for MAX FLOW MIN CUT
// Source: https://www.topcoder.com/community/data-science/data-science-tutorials/minimum-cost-flow-part-two-algorithms/
// Status: Tested

#include "bits/stdc++.h"
#define fillv(v, x) fill((v).begin(), (v).end(), (x))

using namespace std;

#define vectypes(T) typedef vector<T> V##T; typedef vector<V##T> VV##T

typedef int I;
vectypes(I);
typedef double D;
vectypes(D);
typedef pair<int, int> II;
vectypes(II);

const auto INF = INT64_MAX;

struct MinCostMaxFlow {
    struct Edge {
        int to, rev;
        int64_t cap, flow;
        int64_t cost;
    };

    vector<vector<Edge>> res;
    vector<int64_t> dist, pot;
    VI prevnode, prevedge;
    vector<int64_t> currFlow;

    MinCostMaxFlow(int n) {
        res.resize(n);
        dist.resize(n, INF);
        prevnode.resize(n, -1);
        prevedge.resize(n);
        currFlow.resize(n);
        pot.resize(n);
    }

    void addDirEdge(int x, int y, int cap, int cost);
    void addEdge(int x, int y, int cap, int cost);

    bool bellmanFord(int src);
    void dijkstra(int src);

    // Successive Shortest Path Algorithm
    pair<int64_t, int64_t> SSP(int src, int sink);
    pair<int64_t, int64_t> SSPReducedCosts(int src, int sink);
};

/**
 * @brief Add directed edge and it's back edge to residual graph
 * 
 * @param x from
 * @param y to
 * @param c weight for weighted graph, forward capacity for residual graph.
 */
void MinCostMaxFlow::addDirEdge(int x, int y, int cap, int cost) {
    if(0) cout << x << ' ' << y << ' ' << cap << ' ' << cost << endl;
    Edge e1 = {y, (int) res[y].size(), cap, 0, cost};
    Edge e2 = {x, (int) res[x].size(), 0, 0, -cost};
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
void MinCostMaxFlow::addEdge(int x, int y, int cap, int cost) {
    addDirEdge(x, y, cap, cost);
    addDirEdge(y, x, cap, cost);
}

bool MinCostMaxFlow::bellmanFord(int src) {
    fillv(dist, INF);
    auto n = res.size();
    dist[src] = 0;
    prevnode[src] = -1;
    currFlow[src] = INF;
    bool updated = false;
    for (int i = 0; i < n; i++) {
        updated = false;
        for (int v1 = 0; v1 < n; v1++) {
            if (dist[v1] == INF) continue;
            for (int j = 0; j < res[v1].size(); j++) {
                Edge &e = res[v1][j];
                if (e.flow >= e.cap) continue;
                int v2 = e.to;
                if (dist[v2] > dist[v1] + e.cost) {
                    dist[v2] = dist[v1] + e.cost;
                    prevnode[v2] = v1;
                    prevedge[v2] = j;
                    currFlow[v2] = min(currFlow[v1], e.cap - e.flow);
                    updated = true;
                }
            }
        }
        if (!updated)
            return true;
    }
    return !updated;
}

void MinCostMaxFlow::dijkstra(int src) {
    fillv(dist, INF);
    priority_queue<II, VII, greater<II>> pq;
    dist[src] = 0;
    prevnode[src] = -1;
    currFlow[src] = INF;
    pq.push({dist[src], src});
    while(!pq.empty()) {
        II top = pq.top(); pq.pop();
        int v1 = top.second;
        if(dist[v1] < top.first) continue;
        for(int j = 0; j < res[v1].size(); j++) {
            Edge &e = res[v1][j];
            if (e.flow >= e.cap) continue;
            int v2 = e.to;
            int64_t ndist = dist[v1] + e.cost + pot[v1] - pot[e.to];
            if(dist[v2] > ndist) {
                dist[v2] = ndist;
                prevnode[v2] = v1;
                prevedge[v2] = j;
                currFlow[v2] = min(currFlow[v1], e.cap - e.flow);
                pq.push({dist[v2], v2});
            }
        }
    }
}

/**
 * SUCCESSIVE SHORTEST PATH (without cost reduction)
 * Idea: Starting with 0-flow, achieve feasible flow via a series of optimal flows.
 * -    In each iteration, flow is augmented along the shortest s-t path.
 * -    Doesn't work in the presence of negative cycles even if 'capacited'.
 * -    If a residual graph doesn't contain any negative cycle, then augmenting it
 *      with the shortest s-t flow will also not reduce a negative cycle.
 * Time Complexity:
 * -    #iterations <= MAX FLOW <= O(nB), B = largest supply from any node.
 * -    Without cost-reduction, negative edges possible
 *      => Need Bellman Ford for finding shortest paths.
 *      => Time complexity per Iteration: O(nm)
 * -    Total Time Complexity: O(n * m * FLOW)
 *
 * @param src
 * @param sink
 * @return {maximum flow, minimum cost for the maximum flow}
 */
pair<int64_t, int64_t> MinCostMaxFlow::SSP(int src, int sink) {
    int64_t maxFlow = 0;
    int64_t maxFlowCost = 0;
    while (1) {
        bellmanFord(src);
        if (dist[sink] == INF) break;

        int64_t df = currFlow[sink];
        for (int curr = sink; prevnode[curr] != -1; curr = prevnode[curr]) {
            Edge &e = res[prevnode[curr]][prevedge[curr]];
            e.flow += df;
            res[e.to][e.rev].flow -= df;
        }

        maxFlow += df;
        maxFlowCost += df * dist[sink];
    }
    return {maxFlow, maxFlowCost};
}

/**
 * SUCCESSIVE SHORTEST PATH (with cost reduction)
 * Idea: Starting with 0-flow, achieve feasible flow via a series of optimal flows.
 * -    In each iteration, flow is augmented along the shortest s-t path.
 * -    Doesn't work in the presence of negative cycles even if 'capacited'.
 * -    If a residual graph doesn't contain any negative cycle, then augmenting it
 *      with the shortest s-t flow will also not reduce a negative cycle.
 *
 * Cost Reduction: c(p)[i,j] = c(0)[i,j] + p[i] - p[j]
 * -    Doesn't change the shortest paths.
 *
 * If flow x satisfies the reduced cost optimality conditions with respect to
 * some node potentials p and if the vector d represent the shortest distances
 * from some node s in residual network G(x) with cij(p) as edge costs, then the
 * following are valid:
 * (a) x also satisfies the reduced cost optimality with respect to node
 * potentials p' = p + d. (Reason why djikstra is followed by recudeCosts)
 * (b) The reduced costs cij(p') are zero for all arcs (i, j) that are on some
 * shortest path.
 *
 * c(0) -> d(1) -> p(1) -> c(2) -> d(2) -> p(2) -> ...
 * kth iteration:
 * 2. c(k-1) are used to compute shortest distances d(k).
 * 3. d(k) which give us next potentials as: p[k] = p[k-1] + d[k] - d[t].
 * 1. p(k) are used as potentials to give reduced costs: c(k)[i,j] = c(0) + p(k)[i] - p(k)[j].
 *
 * Suppose P is the shortest s-t path found, then,
 * reduced path cost = length(P(c(k))) = d(k)[s].
 * Also, length(P(c(k))) = length(P(c(0))) + p(k-1)[s] - p(k-1)[t]
 * => length(P(c(0))) = d(k)[t] - p(k-1)[s] + p(k-1)[t]
 *  Now, p(k)[s] = p(k-1)[s] - d(k)[t] and p(k)[t] = p(k-1)[t] = p(0)[t] = 0
 *
 * Thus, path cost = length(P(c(0))) = -p(k)[s]
 *
 * Time Complexity:
 * -    #iterations <= MAX FLOW <= O(nB), B = largest supply from any node.
 * -    Cost-reduction => negative edges not possible
 *      => Can use Dijkstra for finding shortest paths.
 *      => Time complexity per Iteration: O(mlogn)
 * -    Total Time Complexity: O(m * logn * FLOW)
 *
 * @param src
 * @param sink
 * @return {maximum flow, minimum cost for the maximum flow}
 */
pair<int64_t, int64_t> MinCostMaxFlow::SSPReducedCosts(int src, int sink) {
    int64_t maxFlow = 0;
    int64_t maxFlowCost = 0;

    bool reduced = false;
    while (1) {
        if(!reduced) {
            bellmanFord(src);
            reduced = true;
        } else dijkstra(src);
        if (dist[sink] == INF) break;

        // compute next potentials p(k) from d(k)
        for(int v1 = 0; v1 < res.size(); v1++) {
            pot[v1] += dist[v1] - dist[sink];
        }

        int64_t df = currFlow[sink];
        for (int curr = sink; prevnode[curr] != -1; curr = prevnode[curr]) {
            Edge &e = res[prevnode[curr]][prevedge[curr]];
            e.flow += df;
            res[e.to][e.rev].flow -= df;
        }
        maxFlow += df;
        maxFlowCost += df * (-pot[src]);    // sum of all the e.cost on the augmenting path
    }
    return {maxFlow, maxFlowCost};
}

// TEST CODE
// problem: https://www.hackerearth.com/practice/algorithms/graphs/minimum-cost-maximum-flow/practice-problems/algorithm/bruce-and-the-chocolates-9/
int gcd(int x, int y) {
    if (y > x) return gcd(y, x);
    else if (y == 0) return x;
    else return gcd(y, x % y);
}

vector<int> chocs(200);
vector<unordered_set<int>> nbrs(200);

int testMinCostMaxFlow() {
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        MinCostMaxFlow g(n + 1);
        fillv(nbrs, unordered_set<int>());
        for (int i = 1; i < n; i++) {
            cin >> chocs[i-1];
            if(i&1) g.addDirEdge(0, i, 1, 0);
            else g.addDirEdge(i, n, 1, 0);
        }
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            if(v & 1) swap(u, v);
            int gcdChocs = gcd(chocs[u - 1], chocs[v - 1]);
            g.addDirEdge(u, v, 1, -gcdChocs);
            nbrs[u].insert(v);
        }
        for(int i = 1; i < n; i+=2) {
            for(int j = 2; j < n; j+=2) {
                if(nbrs[i].find(j) == nbrs[i].end()) {
                    g.addDirEdge(i, j, 1, 0);
                    nbrs[i].insert(j);
                }
            }
        }
        auto maxChocs = g.SSPReducedCosts(0, n);
        cout << -maxChocs.second << endl;
    }
    return 0;
}
