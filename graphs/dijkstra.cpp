// algo to return the shortest path from source to every node
// single source shortest path to every node

// don't work in negative cycle and negative edge weights

// we can use set also to optimize further

// Dijkstra's Algorithm
// Goal:
// - Find shortest distance from a source node to all other nodes
// - Works only when ALL edge weights are NON-NEGATIVE
//
// Core Idea (Greedy):
// - Always expand the node with the smallest known distance so far
// - Once a node is "finalized", its shortest distance is guaranteed
//
// Why this works:
// - Because with non-negative edges, taking a longer path later
//   can never beat the shortest path found first (greedy correctness)
//
// Data Structures:
// - dist[v]: best known distance from source to v
// - Min-heap (priority_queue) to always pick node with smallest dist
// - Adjacency list for graph representation
//
// Time Complexity:
// - O(E log V) using adjacency list + min-heap
// - O(V^2) with array (dense graph, no heap)
//
// Space:
// - O(V + E)

#include <priority_queue>
#include <unordered_map>
#include <vector>

vector<int> dijkstra(vector<vector<int>> &edge, int vertices, int edges, int source){
    unordered_map<int, vector<pair<int,int>>> graph;

    for(int i = 0; i<edges; i++) {
        graph[edge[i][0]].push_back({edge[i][1], edge[i][2]});
        graph[edge[i][1]].push_back({edge[i][0], edge[i][2]});
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // set can be used to instead to remove the unnessary iteration

    vector<int> res(vertices, INT_MAX);

    res[source] = 0;

    pq.push({0, source});

    while(!pq.empty()) {
        pair<int, int> nodeWDis = pq.top();
        pq.pop();

        for(auto &e: graph[nodeWDis.second]) {
            int dis = e.second;
            int next = e.first;

            if(dis+nodeWDis.first < res[next]) {
              /*
                if(res[next] != INT_MAX) {
                    st.erase({res[next], next});
                }
              */
              res[next] = dis + nodeWDis.first;
              pq.push({dis + nodeWDis.first, next});
            }
        }
    }

    return res;
}
