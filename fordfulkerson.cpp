#include <iostream>
#include <queue>
#include <vector>
using namespace std;
bool bfs(vector<vector<int>> &graph, int &n, int s, int t,
         vector<int> &parent){
    queue<int> q;
    q.push(s);
    vector<int> visited(n, 0);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        visited[u] = 1;
        if (u == t){
            return true;
        }
        for (int v = 0; v < n; v++){
            if (graph[u][v] > 0 && !visited[v]){
                // there is residual capacity
                // to go from u to v
                parent[v] = u;
                q.push(v);
            }
        }
    }
    return false;
}
int fordFulkersonMaxFlow(vector<vector<int>> &graph, int &n, int s,
                         int t) {
    vector<int> parent(n, -1);
    int max_flow = 0;
    vector<vector<int>> resGraph(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            resGraph[i][j] = graph[i][j]; // initial condition
        }
    }
    while (bfs(resGraph, n, s, t, parent)) { // while there is an augmenting path
        int next = t;
        int curr_flow = INT8_MAX;
        for (int i = parent[t]; i != s; i = parent[i]) {
            curr_flow = min(curr_flow, resGraph[i][next]);
            next = i;
        }
        curr_flow = min(curr_flow, resGraph[s][next]);
        next = t;
        for (int i = parent[t]; i != s; i = parent[i]) {
            resGraph[i][next] -= curr_flow;
            resGraph[next][i] += curr_flow;
            next = i;
        }
        max_flow += curr_flow;
    }

    return max_flow;
}
int main() {
 vector<vector<int>> graph = {
            {0, 8, 0, 15, 10, 0},
            {0, 0, 9, 0, 8, 0},
            {0, 0, 0, 7, 0, 6},
            {0, 0, 0, 0, 0, 5},
            {0, 0, 0, 0, 0, 9},
            {0, 0, 0, 0, 0, 0}
        };

    int n = graph.size();
    cout << "The maximum possible flow is "
         << fordFulkersonMaxFlow(graph, n, 0, 5);
    return 0;
}