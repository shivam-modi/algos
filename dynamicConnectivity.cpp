#include <iostream>
#include <vector>
using namespace std;
class DSU {
    vector<int> parent, rank;
    int n;
public:
    int sets = 0;
    DSU(int _n){
        n = _n;
        parent.assign(n, -1);
        rank.assign(n, 1);
        sets = n;
    }
    int find(int x) {
        if (parent[x] == -1) {
            return x;
        } else
            return parent[x] = find(parent[x]);
    }
    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) {
            // already same set, no need
            return;
        }
        if (rank[x] >= rank[y]){
            parent[y] = x;
            rank[x] += rank[y];
        } else {
            parent[x] = y;
            rank[y] += rank[x];
        }
        sets--;
    }
};

int main() {
    int n, q;
    cout<< "Enter number of nodes and number of addition queries: ";
    cin >> n >> q;

    DSU dsu(n);
    cout<<"Number of connected components: "<< dsu.sets << endl;

    for (int i = 0; i < q; i++) {
        int u, v;
        cout << "Enter the start and end index of edge:(0-indexed) ";
        cin >> u >> v;
        dsu.unite(u, v);
        cout<<"Number of connected components after query "<< i+1 << ": "<<dsu.sets << endl;
    }

    return 0;
}