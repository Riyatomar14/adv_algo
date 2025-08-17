# Bellman-Ford Algorithm

## 📌 Introduction
The **Bellman–Ford algorithm** is a single-source shortest path algorithm.  
It works on **graphs with positive and negative edge weights** (unlike Dijkstra’s algorithm, which fails on negative weights).  

- Input: A weighted graph (V vertices, E edges) and a source vertex.  
- Output: Shortest path from source to every other vertex (or detect negative cycle).  

---

## ⚡ Why Relax `V-1` Times?
- The **shortest path** between two vertices can have at most **V-1 edges** (where V = number of vertices).  
- If we relax all edges **V-1 times**, all shortest paths will be correctly computed.  

Example:  
- With 5 vertices, the longest simple path (no cycles) has **4 edges** → relax **V-1 = 4** times.

---

## ⚠️ Detecting Negative Cycles
- After `V-1` iterations, all shortest paths should be finalized.  
- If we can still relax an edge in the **V-th iteration**, it means there’s a **negative weight cycle** (a cycle whose total weight < 0).  
- Such a cycle allows reducing distance infinitely, so shortest paths do not exist.

---

## ⏱️ Time Complexity
- **Relaxing edges:** `O(V-1) * O(E)` → `O(VE)`  
- **Checking negative cycle:** `O(E)`  
- **Total:** `O(VE)`  

### Space Complexity
- Distance array: `O(V)`  
- Edge list: `O(E)`  

---

## 📝 Pseudocode

```text
BellmanFord(Graph, V, E, src):
    dist[0..V-1] = ∞
    dist[src] = 0

    # Step 1: Relax all edges V-1 times
    for i = 1 to V-1:
        for each edge (u, v, w) in E:
            if dist[u] + w < dist[v]:
                dist[v] = dist[u] + w

    # Step 2: Check for negative weight cycle
    for each edge (u, v, w) in E:
        if dist[u] + w < dist[v]:
            print("Graph contains negative cycle")
            return

    return dist
