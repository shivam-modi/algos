class DisjointSetUnion {
private:
  vector<int> parent;
  vector<int> rank;

public:
  DisjointSetUnion(int size) {
      parent.resize(size);  
      rank.resize(size, 0);
        for (int i = 0; i < size; i++) {
          parent[i] = i;
        }
  }

  int find(int node) {
    if (node != parent[node]) {
      parent[node] = find(parent[node]); 
    }
    return parent[node];
  }

  void Union(int u, int v) {
    int uParent = find(u);
    int vParent = find(v);

    if (uParent == vParent) {
      return;
    }

    if (rank[uParent] > rank[vParent]) {
      parent[vParent] = uParent;
    } else if (rank[uParent] < rank[vParent]) {
      parent[uParent] = vParent;
    } else {
      parent[vParent] = uParent;
      rank[uParent]++;
    }
  }
};


/**
 * A function to find the minimum spanning tree using Kruskal's algorithm.
 *
 * @param n the number of vertices in the graph
 * @param edges a vector of vectors representing the edges of the graph with weights
 *
 * @return the total weight of the minimum spanning tree
 *
 * @throws None
 */
int kruskalMST(int n, vector<vector<int>> &edges){
   auto comparator = [&](vector<int>& vec1, vector<int>& vec2){
        return vec1[2] < vec2[2];
   };

 	sort(edges.begin(), edges.end(), comparator);
   
   DisjointSetUnion ds(n);
   int sum = 0;

   for(auto& edge: edges) {
       int u = edge[0];
	   int v = edge[1];
	   int wt = edge[2];

	   int uParent = ds.find(u);
	   int vParent = ds.find(v);

	   if(uParent != vParent) {
		   ds.Union(u, v);
		   sum += wt;
	   }
   }

   return sum;
}
