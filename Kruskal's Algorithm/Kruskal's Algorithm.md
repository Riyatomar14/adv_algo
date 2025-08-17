# Spanning Tree and Minimum Spanning Tree

## Spanning Tree

A **spanning tree** of a graph is a subset of edges that connects all
the vertices together without forming any cycle.\
If a graph has **V vertices**, then every spanning tree will have
exactly **V - 1 edges**.

------------------------------------------------------------------------

## Minimum Spanning Tree (MST)

A **Minimum Spanning Tree (MST)** is a spanning tree with the minimum
possible total edge weight.\
It is widely used in network design, clustering, and approximation
algorithms.

### Popular Algorithms to find MST:

1.  **Kruskal's Algorithm**
2.  **Prim's Algorithm**

------------------------------------------------------------------------

## Kruskal's Algorithm -- Pseudocode

1.  Sort the edges in increasing order of their weights.
2.  Iterate through the sorted edges:
    -   If inclusion of the current edge creates a cycle, skip it.
    -   Otherwise, include the edge in the MST.

------------------------------------------------------------------------

## Complexity Analysis

-   **Time Complexity**: O(E log V)
-   **Space Complexity**: O(E + V)

------------------------------------------------------------------------

### Example Applications

-   Network design (telephone, electrical, water supply)
-   Approximation algorithms for NP-hard problems
-   Clustering in Machine Learning
------------------------------------------------------------------------

# Disjoint Set (Union-Find) Explanation

Disjoint Set (also called Union-Find) is a data structure that keeps track of elements partitioned into **disjoint (non-overlapping)** sets. It supports two main operations efficiently:

1. **Find** → Determines which set an element belongs to.
2. **Union** → Merges two sets into one.

This is very useful in problems like **Kruskal’s Minimum Spanning Tree (MST)**, connectivity problems in graphs, etc.

---

## Step 1: Naïve Implementation

### Functions:
- **make(v):** Initializes a set for element `v`.
- **find_set(v):** Finds the representative (parent) of `v`.
- **union_sets(a, b):** Joins the sets of `a` and `b`.

```cpp
void make(int v) {
    parent[v] = v;
}

int find_set(int v) {
    if (v == parent[v])
        return v;
    return find_set(parent[v]);
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b)
        parent[b] = a;
}
```

### Complexity:
- Worst case `find_set` may travel **O(N)** (long chains).
- Union is also **O(N)** in worst case.

---

## Step 2: Path Compression Optimization

Instead of following long chains, we make nodes directly point to the representative.

```cpp
int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}
```

### Effect:
- Reduces time complexity from **O(N)** → **O(log N)** (almost flat trees).

---

## Step 3: Union by Size/Rank

We always attach the **smaller tree under the larger tree** (by size or rank).

```cpp
void make(int v) {
    parent[v] = v;
    size[v] = 1;
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (size[a] < size[b])
            swap(a, b);
        parent[b] = a;
        size[a] += size[b];
    }
}
```

### Effect:
- Prevents long chains.
- Together with **path compression**, gives near-constant time.

---

## Final Time & Space Complexity

- **Time Complexity:** `O(α(N))` per operation  
  (where `α(N)` = Inverse Ackermann Function, which grows so slowly that for all practical inputs it is almost constant → often treated as `O(1)`).

- **Space Complexity:** `O(N)` (to store parent[] and size[] arrays).

---

## Summary

| Step                        | Method Used               | Complexity |
|-----------------------------|---------------------------|-------------|
| Naïve                       | Simple parent assignment  | O(N)        |
| Path Compression            | Flatten tree              | O(log N)    |
| Union by Size/Rank + Path Compression | Balanced + flat trees | O(α(N)) ≈ O(1) |

✅ Final optimized Disjoint Set supports almost constant-time operations with `O(N)` extra space.

---
