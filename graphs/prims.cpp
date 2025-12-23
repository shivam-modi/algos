#include <priority_queue>
#include <vector>

using namespace std;

/** 
  Prim's Algorithm (MST) - Greedy
  Intuition:
// - Grow a tree one vertex at a time.
// - Maintain "best known edge" to connect each outside vertex to the tree.
// - Repeatedly pick the vertex with the minimum connection cost.
// - This works because of the cut property: the cheapest edge crossing the cut is always safe.
//
// Complexity:
// - Using adjacency list + min-heap: O(E log V)
// - Space: O(V + E)
//
// When to use:
// - Need MST in a weighted, undirected graph (connected or you'll get MST forest).
// - Great for dense graphs too (heap version is standard).
*/

//Function to find the sum of weights of edges of the Minimum Spanning Tree.
int spanningTree(int V, vector<vector<int>> adj[]) {
    priority_queue<P, vector<P>, greater<P>> pq;
    pq.push({0, 0});
    vector<bool> inMST(V, false);
    int sum = 0;
          
    while(!pq.empty()) {
              
      auto p = pq.top();
      pq.pop();
              
      int wt     = p.first;
      int node   = p.second;
              
      if(inMST[node] == true)
         continue;
              
      inMST[node] = true; //added to mst
         sum += wt;
              
      for(auto &tmp : adj[node]) {
                  
         int neighbor      = tmp[0];
         int neighbor_wt   = tmp[1];
                  
         if(inMST[neighbor] == false) {
             pq.push({neighbor_wt, neighbor});
         }
      }
    }
          
  return sum;
}
