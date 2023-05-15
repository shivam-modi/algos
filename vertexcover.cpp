#include <iostream>
#include <vector>
using namespace std;

void findVertexCovers(vector<pair<int, int>> &edges, vector<int> &visited_edge, int edgesLeft, int i, int V, vector<int> &curr_set) {
    if (i == V && edgesLeft == 0) {
        // or i == V, but that will
        // always lead to edgesLeft = 0
        cout << "{ ";
        for (auto j : curr_set) {
            cout << j << " ";
        }
        cout << "}, ";
        return;
    } else if (i == V)
        return;

    vector<int> removed;
    int _e = edges.size();
    for (int j = 0; j < _e; j++) {
        if (visited_edge[j])
            continue;
        if (edges[j].first == i || edges[j].second == i) {
            visited_edge[j] = 1;
            edgesLeft--;
            removed.push_back(j);
        }
    }
    curr_set.push_back(i);
    findVertexCovers(edges, visited_edge, edgesLeft, i + 1, V,
                     curr_set);
    curr_set.pop_back();
    for (auto idx : removed) {
        visited_edge[idx] = 0;
        edgesLeft++;
    }
    findVertexCovers(edges, visited_edge, edgesLeft, i + 1, V,
                     curr_set);
}

int main() {
    int V;
    cout << "Enter the number of vertices in the graph: ";
    cin >> V;
    vector<pair<int, int>> edges;
    int E;
    cout << "Enter the number of edges: ";
    cin >> E;
    cout << "Enter the edges as two space separated integers per line:" << endl;
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        edges.push_back({u, v});
        edges.push_back({v, u});
    }
    vector<int> curr_set;
    vector<int> visited_edge(2 * E, 0);
    int edgesLeft = 2 * E;
    cout << "The Vertex Covers are: " << endl;
    findVertexCovers(edges, visited_edge, edgesLeft, 0, V,
                     curr_set);

    return 0;
}