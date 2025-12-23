````md
# Graph Algorithms — Intuition + Crisp Pseudocode (README)

A compact “revise-before-interview” sheet for the most-used graph algorithms.

---

## 0) Graph Basics

### Representations
- **Adjacency List** (preferred): `adj[u] = [(v, w), ...]`
- **Adjacency Matrix**: `O(V^2)` memory; useful for dense/small graphs.

### Common patterns
- **Visited / Color arrays** for traversals & cycle checks
- **Parent array** for path reconstruction / trees
- **In-degree array** for topological sort

---

## 1) BFS — Breadth First Search
**Intuition:** Explore level-by-level. Gives shortest path in **unweighted** graphs.

**Use:** shortest path (unweighted), connectivity, bipartite.

```pseudo
BFS(src):
  queue q
  visited[src] = true
  dist[src] = 0
  q.push(src)

  while q not empty:
    u = q.pop()
    for v in adj[u]:
      if not visited[v]:
        visited[v] = true
        dist[v] = dist[u] + 1
        parent[v] = u
        q.push(v)
````

**Complexity:** `O(V+E)`

---

## 2) DFS — Depth First Search

**Intuition:** Go deep, then backtrack. Great for components, cycle detection, ordering.

```pseudo
DFS(u):
  visited[u] = true
  for v in adj[u]:
    if not visited[v]:
      parent[v] = u
      DFS(v)
```

**Complexity:** `O(V+E)`

---

## 3) Connected Components (Undirected)

**Intuition:** Each BFS/DFS from an unvisited node gives one component.

```pseudo
count = 0
for each node u:
  if not visited[u]:
    BFS(u) or DFS(u)
    count++
```

---

## 4) Topological Sort (DAG)

### 4.1 Kahn’s Algorithm (BFS on indegree)

**Intuition:** Nodes with indegree 0 can be placed first.

```pseudo
TopoSort_Kahn():
  indeg[] from edges
  queue q with all nodes indeg=0
  order = []

  while q not empty:
    u = q.pop()
    order.append(u)
    for v in adj[u]:
      indeg[v]--
      if indeg[v]==0: q.push(v)

  if order.size != V: cycle exists
  return order
```

**Complexity:** `O(V+E)`

### 4.2 DFS Topo

**Intuition:** Finish-time reverse order.

```pseudo
DFS_Topo(u):
  visited[u]=true
  for v in adj[u]:
    if not visited[v]: DFS_Topo(v)
  stack.push(u)

TopoSort_DFS():
  for u in 0..V-1:
    if not visited[u]: DFS_Topo(u)
  return reverse(stack)
```

---

## 5) Cycle Detection

### 5.1 Undirected Graph (DFS parent)

**Intuition:** Visiting an already-visited neighbor that isn’t your parent => cycle.

```pseudo
hasCycleUndirected(u, p):
  visited[u]=true
  for v in adj[u]:
    if not visited[v]:
      if hasCycleUndirected(v, u): return true
    else if v != p:
      return true
  return false
```

### 5.2 Directed Graph (DFS colors)

**Intuition:** Back-edge to a node in current recursion stack => cycle.

Colors: `0=unvisited, 1=visiting, 2=done`

```pseudo
hasCycleDirected(u):
  color[u]=1
  for v in adj[u]:
    if color[v]==0 and hasCycleDirected(v): return true
    if color[v]==1: return true
  color[u]=2
  return false
```

---

## 6) Bipartite Check (BFS/DFS coloring)

**Intuition:** 2-coloring. If an edge connects same color => not bipartite.

```pseudo
isBipartite():
  color[] = -1
  for each node s:
    if color[s]==-1:
      color[s]=0
      queue q; q.push(s)
      while q not empty:
        u=q.pop()
        for v in adj[u]:
          if color[v]==-1:
            color[v]=color[u]^1
            q.push(v)
          else if color[v]==color[u]:
            return false
  return true
```

---

## 7) Disjoint Set Union (Union-Find)

**Intuition:** Maintain components dynamically with near O(1) merges.

```pseudo
makeSet(n):
  parent[i]=i
  rank[i]=0

find(x):
  if parent[x]==x: return x
  parent[x] = find(parent[x])   // path compression
  return parent[x]

union(a,b):
  ra=find(a), rb=find(b)
  if ra==rb: return
  if rank[ra]<rank[rb]: swap
  parent[rb]=ra
  if rank[ra]==rank[rb]: rank[ra]++
```

---

## 8) Minimum Spanning Tree (MST)

### 8.1 Kruskal (Sort edges + DSU)

**Intuition:** Always take the cheapest edge that doesn’t create a cycle.

```pseudo
Kruskal(edges):
  sort edges by weight
  DSU init
  mstWeight=0
  for (u,v,w) in edges:
    if find(u)!=find(v):
      union(u,v)
      mstWeight += w
  return mstWeight
```

**Complexity:** `O(E log E)`

### 8.2 Prim (Min-heap)

**Intuition:** Grow MST like “Dijkstra but cost is edge weight into tree”.

```pseudo
Prim(start):
  key[] = INF
  inMST[] = false
  key[start]=0
  pq.push( (0,start) )
  total=0

  while pq not empty:
    (w,u)=pq.popMin()
    if inMST[u]: continue
    inMST[u]=true
    total += w
    for (v,wt) in adj[u]:
      if not inMST[v] and wt < key[v]:
        key[v]=wt
        pq.push((key[v], v))
  return total
```

**Complexity:** `O(E log V)`

---

## 9) Shortest Paths

### 9.1 BFS Shortest Path (Unweighted)

**Use:** shortest steps in unweighted graph
**Time:** `O(V+E)` (see BFS)

### 9.2 0–1 BFS (Edge weights only 0 or 1)

**Intuition:** Use deque: weight 0 edges go front, weight 1 edges go back.

```pseudo
ZeroOneBFS(src):
  dist[]=INF; dist[src]=0
  deque dq; dq.pushFront(src)

  while dq not empty:
    u = dq.popFront()
    for (v,w) in adj[u]:   // w in {0,1}
      if dist[u] + w < dist[v]:
        dist[v] = dist[u] + w
        if w==0: dq.pushFront(v)
        else:    dq.pushBack(v)
```

**Time:** `O(V+E)`

### 9.3 Dijkstra (Non-negative weights)

**Intuition:** Always finalize the node with smallest known distance (non-neg edges guarantee correctness).

```pseudo
Dijkstra(src):
  dist[]=INF; dist[src]=0
  pq.push((0,src))  // (dist,node)

  while pq not empty:
    (d,u)=pq.popMin()
    if d != dist[u]: continue   // stale entry
    for (v,w) in adj[u]:
      if dist[u] + w < dist[v]:
        dist[v] = dist[u] + w
        parent[v] = u
        pq.push((dist[v], v))
```

**Time:** `O(E log V)`

### 9.4 Bellman-Ford (Negative weights allowed)

**Intuition:** Relax all edges V-1 times. Can detect negative cycles.

```pseudo
BellmanFord(src):
  dist[]=INF; dist[src]=0
  repeat V-1 times:
    updated=false
    for each edge (u,v,w):
      if dist[u]!=INF and dist[u]+w < dist[v]:
        dist[v]=dist[u]+w
        updated=true
    if not updated: break

  // Detect negative cycle
  for each edge (u,v,w):
    if dist[u]!=INF and dist[u]+w < dist[v]:
      negativeCycleExists = true
```

**Time:** `O(VE)`

### 9.5 Floyd–Warshall (All pairs, small graphs)

**Intuition:** DP over intermediate nodes.

```pseudo
FloydWarshall():
  dist[][] initialized (INF), dist[i][i]=0
  for each edge (u,v,w): dist[u][v]=min(dist[u][v], w)

  for k in 0..V-1:
    for i in 0..V-1:
      for j in 0..V-1:
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])
```

**Time:** `O(V^3)`

---

## 10) Strongly Connected Components (Directed)

### 10.1 Kosaraju (2-pass DFS)

**Intuition:** Order by finish time, then DFS on reversed graph.

```pseudo
Kosaraju():
  visited=false
  stack = []
  for u:
    if not visited[u]: dfs1(u)   // push u on stack at finish

  build reverse graph radj
  visited=false
  sccCount=0
  while stack not empty:
    u = stack.pop()
    if not visited[u]:
      dfs2(u) on radj
      sccCount++
```

**Time:** `O(V+E)`

### 10.2 Tarjan (1-pass, lowlink)

**Intuition:** DFS + stack; lowlink tells SCC roots.
**Time:** `O(V+E)` (more code-heavy)

---

## 11) Bridges & Articulation Points (Undirected)

**Intuition:** DFS discovery time + low-link.

* **Bridge**: removing edge disconnects graph.
* **Articulation point**: removing vertex disconnects graph.

(Usually asked in advanced rounds.)

---

## 12) Maximum Flow (Dinic)

**Intuition:** Level graph (BFS) + blocking flow (DFS).
**Use:** max flow, bipartite matching, min cut.

**Time:** ~`O(E * sqrt(V))` for bipartite; general `O(E V^2)` worst-case but fast in practice.

---

## 13) Euler Path/Circuit

**Intuition:** Use degree conditions + Hierholzer’s algorithm.

* Undirected Euler circuit: all degrees even
* Undirected Euler path: exactly 0 or 2 odd degrees
* Directed versions use in/out-degree.

---

# Quick “Which algorithm?” Map

* **Unweighted shortest path:** BFS
* **Weights 0/1:** 0–1 BFS
* **Non-negative weights:** Dijkstra
* **Negative weights:** Bellman-Ford
* **Need MST:** Kruskal / Prim
* **DAG order:** Toposort
* **Directed SCC:** Kosaraju / Tarjan
* **Cycle check:** DFS (parent / colors)
* **Connectivity / components:** DFS/BFS
* **Bipartite:** BFS/DFS coloring
* **Max flow / matching:** Dinic

---

# Templates reminder

* Always confirm: **directed vs undirected**, **weighted vs unweighted**, **negative edges?**, **connected?**
* Always track: **visited**, **parent**, **dist**, **indegree**, **low/tin** when needed.
