#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Graph {
public:
    Graph(vector<vector<int>>& edges, int m, int n)
        // : m_(m), n_(n), graph_(m + n + 2, vector<int>(m + n + 2, 0)) 
        {
               m_ = m;
    n_ = n;
    graph_ = vector<vector<int>>(m + n + 2, vector<int>(m + n + 2, 0));
        int s = 0, t = 1;
        for (int i = 0; i < m_; i++) {
            graph_[s][i + 2] = 1;
            for (int j : edges[i]) {
                graph_[i + 2][j + m_ + 2] = 1;
            }
        }
        for (int i = 0; i < n_; i++) {
            graph_[i + m_ + 2][t] = 1;
        }
    }

    int maximumBipartiteMatching() {
        vector<int> parent(m_ + n_ + 2, -1);
        int max_flow = 0;
        while (bfs(parent)) {
            int next = 1;
            int curr_flow = INT8_MAX;
            for (int i = parent[next]; i != -1; i = parent[i]) {
                curr_flow = min(curr_flow, graph_[i][next]);
                next = i;
            }
            next = 1;
            for (int i = parent[next]; i != -1; i = parent[i]) {
                graph_[i][next] -= curr_flow;
                graph_[next][i] += curr_flow;
            }
            max_flow += curr_flow;
        }
        return max_flow;
    }

private:
    bool bfs(vector<int>& parent) {
        int V = graph_.size();
        vector<int> visited(V, 0);
        queue<int> q;
        q.push(0);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            visited[u] = 1;
            if (u == 1) {
                return true;
            }
            for (int v = 0; v < V; v++) {
                if (!visited[v] && graph_[u][v] > 0) {
                    parent[v] = u;
                    q.push(v);
                }
            }
        }
        return false;
    }

    int m_;
    int n_;
    vector<vector<int>> graph_;
};

int main() {
    int m = 4, n = 3;
    vector<vector<int>> edges = {{0, 1}, {0, 2}, {1}, {1, 2}};

    Graph graph(edges, m, n);
    int max_flow = graph.maximumBipartiteMatching();

    cout << "The maximum bipartite matching in the given graph is " << max_flow << endl;

    return 0;
}