// Directed graph only, we have to make undirected graph as bidirected graph to run this algo (having no negative edge)
// helps to detect negative edge cycle
// helps when there is negative edge

// single source shortest path to every node

// have to run the relxtaion to v-1 times because atmost v-1 nodes have no definate shortest path 

// if relax one more times and we found some value is updated there is negative cycle

vector<int> bellmonFord(int v, int e, int src, vector<vector<int>> &edges) {
    vector<int> dis(v+1, 1e8);
    dis[src] = 0;

    for(int i = 0; i<v-1; i++) {
       for(auto edge: edges) {
           int u = edge[0];
           int v = edge[1];
           int d = edge[2];

           if(dis[u] != INT_MAX && dis[u] + d < dis[v]) {
               dis[v] = dis[u]+d; 
           } 
       }
    }

    return dis;
}