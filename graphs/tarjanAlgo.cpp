/**
 * Tarjan's Algorithm is used to find all bridges in a graph.
 * Bridges are the edges in a graph whose removal increases the number of connected components.
 * This algorithm uses DFS to find bridges efficiently in O(V + E) time complexity.
 */

/**
 * A function that implements Tarjan's Algorithm to find bridges in a graph efficiently.
 *
 * @param node the current node being processed
 * @param parent the parent node of the current node
 * @param vis a vector to keep track of visited nodes
 * @param adj an array of vectors representing the adjacency list of the graph
 * @param tin an array to store the time of entry for each node
 * @param low an array to store the lowest time reachable from a node in a subtree
 * @param bridges a vector of vectors to store the bridges found in the graph
 * @param timer a reference to keep track of time during the algorithm
 *
 * @throws None
 */
```  
void tarjanAlgo(int node, int parent, vector<int>& vis, vector<int> adj[], int tin[], int low[], vector<vector<int>>& bridges, int& timer) {
        vis[node] = 1;
        tin[node] = low[node] = timer;
        timer++;
        
        for(auto it: adj[node]) {
            if(it == parent) continue;
            if(vis[it] == 0) {
                tarjanAlgo(it, node, vis, adj, tin, low, bridges, timer);
                
                low[node] = min(low[node], low[it]);
                
                if(low[it] > tin[node]) {
                    bridges.push_back({node, it});
                }
            } else {
                low[node] = min(low[node], low[it]);
            }
        }
    }


vector<vector<int>> findBridges(vector<vector<int>> &edges, int v, int e) {
        vector<int> adj[v];
        
        for(auto &connection: edges) {
            adj[connection[0]].push_back(connection[1]);
            adj[connection[1]].push_back(connection[0]);          
        }
        
        vector<int> vis(v, 0);
        int tin[v];
        int low[v];
        
        vector<vector<int>> bridges;
        int timer = 0;
        tarjanAlgo(0, -1, vis, adj, tin, low, bridges, timer);
        
        return bridges;

}